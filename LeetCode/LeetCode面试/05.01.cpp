#include "../pch.h"

/*
给定两个整型数字 N 与 M，以及表示比特位置的 i 与 j（i <= j，且从 0 位开始计算）。

编写一种方法，使 M 对应的二进制数字插入 N 对应的二进制数字的第 i ~ j 位区域，不足之处用 0 补齐。具体插入过程如图所示。

题目保证从 i 位到 j 位足以容纳 M， 例如： M = 10011，则 i～j 区域至少可容纳 5 位。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/insert-into-bits-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

DEFINE_SOLUTION_CASE(ms_05_01, insertBits, int, int, int, int, int);
REGISTER_SOLUTION_CASE(ms_05_01,
    Case(1100, 1024, 19, 2, 6),
    Case(31, 0, 31, 0 ,4)
);


class Solution(ms_05_01, 1)
{
public:
    /* C++ 标准对有符号负数执行位移操作未未定义行为 */
    int insertBits(int N, int M, int i, int j) {
        unsigned int uintmax = UINT_MAX;
        unsigned int tmp = (j == 31 ? 0 : (uintmax << (j + 1))) | ~(uintmax << i);
        return (N & tmp) | (M << i);
    }
};