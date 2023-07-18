#pragma once
#include "pch.h"

DEFINE_SOLUTION_CASE(2164, sortEvenOdd, vector<int>, vector<int>);
REGISTER_SOLUTION_CASE(2164,
    Case({ 2, 3, 4, 1 }, { 4, 1, 2, 3 }),
    Case({ 2, 1 }, { 2, 1 })
);

/* �ռ临�Ӷȼ�������������㷨����±��� */
class SOLUTION_CLASS(2164, 1)
{
public:
    vector<int> sortEvenOdd(vector<int>& nums)
    {
        /* int���黹��int*����Ŀռ临�Ӷ���ͬ */
        vector<int> evenNums, oddNums;
        for (size_t i = 0; i < nums.size(); i++) {
            i % 2 == 0 ? push_back(evenNums, nums[i]) : push_back(oddNums, nums[i]);
        }

        sort(evenNums.begin(), evenNums.end());
        sort(oddNums.begin(), oddNums.end(), desCmp);

        vector<int> ret;
        /* ż���±������С��Ȼ���ڵ��������±������С */
        for (size_t i = 0; i < evenNums.size(); i++) {
            ret.push_back(evenNums[i]);
            if (i < oddNums.size())
                ret.push_back(oddNums[i]);
        }

        return ret;
    }

    template<class T, typename V>
    void push_back(T& vector, V val)
    {
        vector.push_back(val);
    }

    static bool desCmp(int a1, int a2) {
        return a1 > a2;
    }
};


//
//class SolutionCase2164
//{
//public:
//    using type = std::tuple<std::vector<int>, std::vector<int>>;
//
//    static SolutionCase2164& instance() {
//        static SolutionCase2164 inst;
//        return inst;
//    }
//
//    void registerCases();
//
//    template<typename... Args>
//    void setCases(Args&&... args) { (m_cases.push_back((type)args), ...); }
//
//    template<class Solution, class Case>
//    auto test(Solution& sln, Case&& cas) {
//        return run(sln, std::forward<Case>(cas), std::make_index_sequence<std::tuple_size<type>::value - 1>());
//    }
//
//    template<class Solution, class Case, size_t ...i>
//    auto run(Solution& sln, Case&& cas, std::index_sequence<i...>) {
//        return sln.sortEvenOdd(std::get<i + 1>(cas)...);
//    }
//
//    std::vector<type> m_cases;
//};
//using Case = SolutionCase2164::type;
//
//void SolutionCase2164::registerCases()
//{
//    setCases(Case({ 2, 3, 4, 1 }, { 4, 1, 2, 3 }), Case({ 2, 1 }, { 2, 1 }));
//}
//
//
//static SolutionCaseRegistry<SolutionCase2164> registry;
//
//template<class T>
//class solutionRegistry
//{
//public:
//    solutionRegistry() { T::registerSolution(); }
//};