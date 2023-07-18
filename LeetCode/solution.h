#pragma once

class ISolutionTest
{
public:
    virtual bool test() = 0;
};

class SolutionMgr {
public:
    enum Rule { exclude,  include };

    SolutionMgr() {}
    SolutionMgr(Rule def) :m_defaultRule(def) {}

    void RunTest()
    {
        for (auto& i : SolutionMap) {
            if (m_excludeRule.find(i.first) != m_excludeRule.end())
                continue;
            if (m_defaultRule == exclude && m_includeRule.find(i.first) == m_includeRule.end())
                continue;

            i.second->test();
        }
    }

    void setDefaultRule(Rule def) { m_defaultRule = def; };

    template<typename... Args>
    void setIncludeRule(Args&&... args) { (m_includeRule.insert(args), ...); }

    template<typename... Args>
    void setExcludeRule(Args&&... args) { (m_excludeRule.insert(args), ...); }

    static inline std::map<std::string, std::unique_ptr<ISolutionTest>> SolutionMap;

private:

    class serialStr : public std::string
    {
    public:
        serialStr() :std::string() {}
        serialStr(size_t n) :std::string(std::to_string(n)),m_isPureNum(true), m_serial(n) {}
        serialStr(const char* s) :std::string(s), m_isPureNum(getNumCharSize(s) == strlen(s)), m_serial(atoi(s)) {}
        serialStr(const std::string& s) :std::string(s), m_isPureNum(getNumCharSize(s.c_str()) == s.size()), m_serial(atoi(s.c_str())) {}
        serialStr(const serialStr& s) :std::string(s), m_isPureNum(s.m_isPureNum), m_serial(s.m_serial) {}

        static size_t getNumCharSize(const char* str) 
        {
            size_t num = 0;
            while (0 <= str[num] && str[num] <= 9) num++;
            return num;
        };

        bool operator<(const serialStr& other) const
        {
            if(m_serial == other.m_serial){
                if (m_isPureNum && other.m_isPureNum) 
                    return false;

                size_t size = std::min(this->size(), other.size());
                return strncmp(this->c_str(), other.c_str(), size) < 0;
            }

            return m_serial < other.m_serial;
        }
        bool m_isPureNum = 0;
        size_t m_serial = 0;
    };

    std::set<serialStr> m_includeRule;
    std::set<serialStr> m_excludeRule;
    Rule m_defaultRule = include;
};

/* SolutionCase 因为转发函数需要使用字面值，所以无法完全使用模板抽象 */
#define DEFINE_SOLUTION_CASE(serial, keyFunc, ...)\
class SolutionCase##serial { public:\
    using type = std::tuple<__VA_ARGS__>; \
    static SolutionCase##serial& instance() { \
        static SolutionCase##serial inst; \
        return inst; \
    } \
    void registerCases();\
    template<typename... Args> \
    void setCases(Args&&... args) { (m_cases.push_back((type)args), ...); } \
    template<class Solution, class Case> \
    auto test(Solution& sln, Case&& cas) { \
        return run(sln, std::forward<Case>(cas), std::make_index_sequence<std::tuple_size<type>::value - 1>()); \
    } \
    template<class Solution, class Case, size_t ...i> \
    auto run(Solution& sln, Case&& cas, std::index_sequence<i...>) { \
        return sln.keyFunc(std::get<i + 1>(cas)...); \
    } \
    std::vector<type> m_cases;\
};\
using Case = SolutionCase##serial::type;

#define REGISTER_SOLUTION_CASE(serial, ...)\
void SolutionCase##serial::registerCases() { setCases(__VA_ARGS__); } \
static SolutionCaseRegistry<SolutionCase##serial> solutionCaseRegistry##serial;

#define SOLUTION_CLASS(serial, subSerial)\
Solution##serial##_##subSerial; \
class SolutionRegistry##serial##_##subSerial{ public: \
    SolutionRegistry##serial##_##subSerial(){ \
        const char* serialStr = #serial "_" #subSerial; \
        SolutionMgr::SolutionMap[serialStr] = make_unique<SolutionTestImpl<Solution##serial##_##subSerial, SolutionCase##serial>>(serialStr);\
    }\
};\
static SolutionRegistry##serial##_##subSerial solutionRegistry##serial##_##subSerial; \
class Solution##serial##_##subSerial

template<class T, class TC>
class SolutionTestImpl : public ISolutionTest
{
public:
    SolutionTestImpl(const char* serial) :m_serial(serial) {}

    virtual bool test()
    {
        auto caseCnt = TC::instance().m_cases.size();
        auto tp1 = std::chrono::steady_clock::now();

        size_t ret = testSolution();

        auto time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - tp1).count();

        if (ret != caseCnt) {
            std::cout << "\nQustion[" << m_serial << "] Test Case[" << ret + 1 << "]Fail!\n" << std::endl;
        }

        std::cout << "Qustion[" << m_serial << "] Test " << (ret ? "OK" : "Fail") << "! Test [" << ret << "] cases, Use [" << time << "] us" << std::endl;
        if (ret != caseCnt) {
            assert(false);
            return false;
        }
        else {
            return true;
        }
    }

    size_t testSolution() {
        if (!m_solutionPtr) m_solutionPtr = std::make_unique<T>();
        size_t i = 0;
        for (; i < TC::instance().m_cases.size(); i++) {
            auto ret = TC::instance().test(*m_solutionPtr, TC::instance().m_cases[i]);
            if (std::get<0>(TC::instance().m_cases[i]) != ret) {
                break;
            }
        }
        return i;
    }

private:
    std::string m_serial;
    std::unique_ptr<T> m_solutionPtr;
};

template<class TC>
class SolutionCaseRegistry
{
public:
    SolutionCaseRegistry()
    {
        TC::instance().registerCases();
    }
};

template <typename T, typename U>
struct isSameType : std::is_same<typename std::decay<T>::type, typename std::decay<U>::type>::type {};
