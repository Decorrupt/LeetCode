#include "../pch.h"

/*
���������������� N �� M���Լ���ʾ����λ�õ� i �� j��i <= j���Ҵ� 0 λ��ʼ���㣩��

��дһ�ַ�����ʹ M ��Ӧ�Ķ��������ֲ��� N ��Ӧ�Ķ��������ֵĵ� i ~ j λ���򣬲���֮���� 0 ���롣������������ͼ��ʾ��

��Ŀ��֤�� i λ�� j λ�������� M�� ���磺 M = 10011���� i��j �������ٿ����� 5 λ��

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode.cn/problems/insert-into-bits-lcci
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/

DEFINE_SOLUTION_CASE(ms_05_01, insertBits, int, int, int, int, int);
REGISTER_SOLUTION_CASE(ms_05_01,
    Case(1100, 1024, 19, 2, 6),
    Case(31, 0, 31, 0 ,4)
);


class Solution(ms_05_01, 1)
{
public:
    /* C++ ��׼���з��Ÿ���ִ��λ�Ʋ���δδ������Ϊ */
    int insertBits(int N, int M, int i, int j) {
        unsigned int uintmax = UINT_MAX;
        unsigned int tmp = (j == 31 ? 0 : (uintmax << (j + 1))) | ~(uintmax << i);
        return (N & tmp) | (M << i);
    }
};