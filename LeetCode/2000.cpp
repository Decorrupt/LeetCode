#include "pch.h"
/*
����һ���±�� 0 ��ʼ���ַ��� word ��һ���ַ� ch ���ҳ� ch ��һ�γ��ֵ��±� i ����ת word �д��±� 0 ��ʼ��ֱ���±� i ���������±� i �����Ƕ��ַ������ word �в������ַ� ch ������������κβ�����

���磬��� word = "abcdefd" �� ch = "d" ����ô��Ӧ�� ��ת ���±� 0 ��ʼ��ֱ���±� 3 ���������±� 3 ��������ַ��������� "dcbaefd" ��
���� ����ַ��� ��

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode.cn/problems/reverse-prefix-of-word
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/

DEFINE_SOLUTION_CASE(2000, reversePrefix, string, string, char);
REGISTER_SOLUTION_CASE(2000,
    Case("dcbaefd", "abcdefd", 'd'),
    Case("zxyxxe", "xyxzxe", 'z'),
    Case("abcd", "abcd", 'z')
);

class Solution(2000, 1) {
public:
    string reversePrefix(string word, char ch) {
        auto pos = word.find_first_of(ch);
        if (pos == string::npos) return word;

        string ret(word.size(), 0);
        for (size_t i = 0; i < word.size(); i++) {
            ret[i] = i <= pos ? word[pos - i] : word[i];
        }
        return ret;
    }
};

class Solution(2000, 2) {
public:
    string reversePrefix(string word, char ch) {
        int index = word.find(ch);
        if (index != string::npos) {
            reverse(word.begin(), word.begin() + index + 1);
        }
        return word;
    }
};