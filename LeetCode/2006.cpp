#include "pch.h"
/*
����һ���������� nums ��һ������ k �����㷵������ (i, j) ����Ŀ������ i < j �� |nums[i] - nums[j]| == k ��

|x| ��ֵ����Ϊ��

��� x >= 0 ����ôֵΪ x ��
��� x < 0 ����ôֵΪ -x ��

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode.cn/problems/count-number-of-pairs-with-absolute-difference-k
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/

DEFINE_SOLUTION_CASE(2006, countKDifference, int, vector<int>, int);
REGISTER_SOLUTION_CASE(2006,
    Case(4,     { 1,2,2,1 },    1),
    Case(0,     { 1,3 },        3),
    Case(3,     { 3,2,1,5,4 },  2)
);

/*
 * �����Ż�˼·����������ú� i<j ��һ�����Ӷ�תΪ���Լ���
 */

/* O(n^2) */
class Solution(2006, 1) {
public:
    int countKDifference(vector<int>&nums, int k) {
        size_t i = 0;
        size_t j = 0;
        int ret = 0;

        for (; i < nums.size(); i++) {
            for (j = i + 1; j < nums.size(); j++) {
                int cal = nums[i] - nums[j];
                if (cal == k || cal == -k) ret++;
            }
        }
        return ret;
    }
};

/* O(n) */
class Solution(2006, 2) {
public:
    int countKDifference(vector<int>&nums, int k) {
        int ret = 0;
        unordered_map<int, size_t> numCntMap;

        auto addMatchCnt = [&](int num) {
            if (auto it = numCntMap.find(num); it != numCntMap.end())
                ret += (int)it->second;
        };

        for (size_t i = 0; i < nums.size(); i++) {
            int num = nums[i];
            int indexLow = num - k;
            int indexHigh = num + k;

            addMatchCnt(indexHigh);
            addMatchCnt(indexLow);

            numCntMap[num]++;
        }
        return ret;
    }
};