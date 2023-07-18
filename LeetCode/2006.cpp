#include "pch.h"

DEFINE_SOLUTION_CASE(2006, countKDifference, int, vector<int>, int);
REGISTER_SOLUTION_CASE(2006,
    Case(4,     { 1,2,2,1 },    1),
    Case(0,     { 1,3 },        3),
    Case(3,     { 3,2,1,5,4 },  2)
);

/* O(n^2) */
class SOLUTION_CLASS(2006, 1) {
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