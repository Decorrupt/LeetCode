#include "pch.h"

DEFINE_SOLUTION_CASE(2164, sortEvenOdd, vector<int>, vector<int>);
REGISTER_SOLUTION_CASE(2164,
    Case({ 2, 3, 4, 1 },    { 4, 1, 2, 3 }),
    Case({ 2, 1 },          { 2, 1 })
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