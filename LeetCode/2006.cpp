#include "pch.h"
/*
给你一个整数数组 nums 和一个整数 k ，请你返回数对 (i, j) 的数目，满足 i < j 且 |nums[i] - nums[j]| == k 。

|x| 的值定义为：

如果 x >= 0 ，那么值为 x 。
如果 x < 0 ，那么值为 -x 。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/count-number-of-pairs-with-absolute-difference-k
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

DEFINE_SOLUTION_CASE(2006, countKDifference, int, vector<int>, int);
REGISTER_SOLUTION_CASE(2006,
    Case(4,     { 1,2,2,1 },    1),
    Case(0,     { 1,3 },        3),
    Case(3,     { 3,2,1,5,4 },  2)
);

/*
 * 本题优化思路在于如何利用好 i<j 这一条件从而转为线性计算
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