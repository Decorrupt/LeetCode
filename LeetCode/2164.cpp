#pragma once
#include "pch.h"
#include "solution.h"

/* �ռ临�Ӷȼ�������������㷨����±��� */
class Solution2164_1
{
    DEFINE_PARAM1_TYPE(sortEvenOdd, vector<int>, vector<int>)
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