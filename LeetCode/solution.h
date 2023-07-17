#pragma once

#include "pch.h"

enum ParamType {
    ResultType = 0,
    Param1Type,
    Param2Type,
    Param3Type
};

#define DEFINE_KEY_FUNC(func) \
public:\
    template<typename... Args>\
    auto test(Args&&... args) { return func(std::forward<Args>(args)...); }

#define DEFINE_PARAM1_TYPE(func, resultType, param1Type) \
    DEFINE_KEY_FUNC(func)   \
    static constexpr size_t ParamSize = 1;\
    using result = resultType;\
    using param1 = param1Type;

#define DEFINE_PARAM2_TYPE(func, resultType, param1Type, param2Type) \
    DEFINE_KEY_FUNC(func)   \
    static constexpr size_t ParamSize = 2;\
    using result = resultType;\
    using param1 = param1Type;\
    using param2 = param2Type;

#define DEFINE_PARAM3_TYPE(func, resultType, param1Type, param2Type, param3Type) \
    DEFINE_KEY_FUNC(func)   \
    static constexpr size_t ParamSize = 3;\
    using result = resultType;\
    using param1 = param1Type;\
    using param2 = param2Type;\
    using param3 = param3Type;

#define DEFINE_SOLUTION_TEST_BEGIN(serial)  \
class registerSolution##serial { public:    \
    registerSolution##serial() { \
        auto ptr = std::make_unique<SolutionTestImpl<Solution##serial>>(#serial);

#define DEFINE_SOLUTION_TEST_END(serial)\
        SolutionMgr::SolutionMap.insert({ "Solution" #serial ,std::move(ptr)});\
    }};\
    registerSolution##serial registrySolution##serial##Instance;

#define REGISTRY_SOLUTION_TEST_PARAM(type, ...)\
    ptr->setParamList<type>(__VA_ARGS__);

class ISolutionTest
{
public:
    virtual bool test() = 0;
};

class SolutionMgr {
public:
    enum Rule {
        exclude, 
        include
    };

    SolutionMgr() {}
    SolutionMgr(Rule def) :m_defaultRule(def) {}

    void RunTest()
    {
        if (m_defaultRule == include) {
            for (auto& i : SolutionMap) {
                if(m_excludeRule.find(i.first) == m_excludeRule.end())
                    i.second->test();
            }
        }
        else {
            for (auto& i : m_includeRule) {
                if (m_excludeRule.find(i) == m_excludeRule.end()) {
                    auto it = SolutionMap.find(i);
                    if (it != SolutionMap.end())
                        it->second->test();
                }
            }
        }
    }

    void setDefaultRule(Rule def) { m_defaultRule = def; };

    template<Rule rule, typename... Args>
    void setRule(Args&&... args)
    {
        if constexpr (rule == include)
            (m_includeRule.insert(args), ...);
        else
            (m_excludeRule.insert(args), ...);
    }

    static inline map<string, unique_ptr<ISolutionTest>> SolutionMap;

private:
    set<string> m_includeRule;
    set<string> m_excludeRule;
    Rule m_defaultRule = include;
};

template <typename T, typename U>
struct isSameType : std::is_same<typename std::decay<T>::type, typename std::decay<U>::type>::type {};

template<class T, size_t N>
class paramList {};

template<class T, size_t N = T::ParamSize>
class SolutionTestImpl : public ISolutionTest
{
public:
    SolutionTestImpl(const string& serial) :m_serial(serial) {}

    virtual bool test()
    {
        auto tp1 = chrono::steady_clock::now();

        size_t ret = testSolution();

        auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - tp1).count();

        if (ret != m_param.m_result.size()) {
            std::cout << "\nQustion[" << m_serial << "] Test Case[" << ret + 1 << "]Fail!\n" << std::endl;
        }

        std::cout << "Qustion[" << m_serial << "] Test " << (ret ? "OK" : "Fail") << "! Test [" << ret << "] cases, Use [" << time << "] us" << std::endl;
        if (ret != m_param.m_result.size()) {
            assert(false);
            return false;
        }
        else {
            return true;
        }
    }

    size_t testSolution() {

        static_assert(N>=1&& N<=3, "Not Support More Param!!");

        for (size_t i = 0; i < m_param.m_param1.size(); i++) {
            if constexpr (N == 1) {
                auto ret = m_solution.test(m_param.m_param1[i]);
                if (ret != m_param.m_result[i]) { return i; }
            }
            else if constexpr (N == 2) {
                auto ret = m_solution.test(m_param.m_param1[i], m_param.m_param2[i]);
                if (ret != m_param.m_result[i]) { return i; }
            }
            else if constexpr (N == 3) {
                auto ret = m_solution.test(m_param.m_param1[i], m_param.m_param2[i], m_param.m_param3[i]);
                if (ret != m_param.m_result[i]) { return i; }
            }

        }
        return m_param.m_result.size();
    }

    template<size_t Type, typename... Args>
    void setParamList(Args&&... args)
    {
        if constexpr (Type == ResultType) {
            (m_param.m_result.push_back((typename T::result)args), ...);
        }
        else if constexpr (Type == Param1Type) {
            (m_param.m_param1.push_back((typename T::param1)args), ...);
        }
        else if constexpr (Type == Param2Type) {
            (m_param.m_param2.push_back((typename T::param1)args), ...);
        }
        else if constexpr (Type == Param3Type) {
            (m_param.m_param3.push_back((typename T::param1)args), ...);
        }
    }

private:
    string m_serial;
    T m_solution;
    paramList<T, N> m_param;
};

template<class T>
class paramList<T, 1>
{
public:
    using result = T::result;
    using param1 = T::param1;

    std::vector<param1> m_param1;
    std::vector<result> m_result;
};

template<class T>
class paramList<T, 2>
{
public:
    using result = T::result;
    using param1 = T::param1;
    using param2 = T::param2;

    std::vector<param1> m_param1;
    std::vector<param2> m_param2;
    std::vector<result> m_result;
};

template<class T>
class paramList<T, 3>
{
public:
    using result = T::result;
    using param1 = T::param1;
    using param2 = T::param2;
    using param3 = T::param3;


    std::vector<param1> m_param1;
    std::vector<param2> m_param2;
    std::vector<param3> m_param3;
    std::vector<result> m_result;
};