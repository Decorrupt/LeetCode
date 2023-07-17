#pragma once
#include "pch.h"
#include "solution.h"

class SolutionCase2164
{
public:
    using type = std::tuple<vector<int>, vector<int>>;
    using T = type;

    static SolutionCase2164& instance() {
        static SolutionCase2164 inst;
        return inst;
    }

    template<class T, typename... Args>
    auto test(T& sln, Args&&... args) 
    { 
        return sln->sortEvenOdd(std::forward<Args>(args)...);
    }

    std::vector<T> m_cases;
};

class SolutionCase2164Registry
{
    SolutionCase2164Registry()
    {
        SolutionCase2164::instance().m_cases.push_back(
            SolutionCase2164::T({2, 3, 4, 1}, { 4, 1, 2, 3 })
        );
    }
};

/* �ռ临�Ӷȼ�������������㷨����±��� */
class Solution2164_1
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

DEFINE_SOLUTION_TEST_BEGIN(2164_1)
REGISTRY_SOLUTION_TEST_PARAM(ResultType, vector<int>{2, 3, 4, 1 }, vector<int>{ 2, 1 });
REGISTRY_SOLUTION_TEST_PARAM(Param1Type, vector<int>{4, 1, 2, 3 }, vector<int>{ 2, 1 });
DEFINE_SOLUTION_TEST_END(2164_1)