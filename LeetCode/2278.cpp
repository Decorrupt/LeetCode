#include "pch.h"

/*
����һ���ַ��� s ��һ���ַ� letter �������� s �е��� letter �ַ���ռ�� �ٷֱ� ������ȡ������ӽ��İٷֱȡ�

ʾ�� 1��
���룺s = "foobar", letter = "o"
�����33
���ͣ�
������ĸ 'o' ���ַ��� s ��ռ���İٷֱ��� 2 / 6 * 100% = 33% ������ȡ�������Է��� 33 ��

ʾ�� 2��
���룺s = "jjjj", letter = "k"
�����0
���ͣ�
������ĸ 'k' ���ַ��� s ��ռ���İٷֱ��� 0% �����Է��� 0 ��

��ʾ��
1 <= s.length <= 100
s ��СдӢ����ĸ���
letter ��һ��СдӢ����ĸ
*/

DEFINE_SOLUTION_CASE(2278, percentageLetter, int, string, char);
REGISTER_SOLUTION_CASE(2278,
    Case(33, "foobar",'o'),
    Case(0,"jjjj",'k')
);

class Solution(2278,1) {
public:
    int percentageLetter(string s, char letter) {
        double letterSize = 0;
        for (auto c : s) {
            if (c == letter) letterSize++;
        }

        auto percent = (int)(letterSize * 100 / s.size());
        return percent;
    }
};

