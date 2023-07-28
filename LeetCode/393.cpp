#include "pch.h"

/*
����һ����ʾ���ݵ��������� data ���������Ƿ�Ϊ��Ч�� UTF-8 ���롣

UTF-8 �е�һ���ַ����ܵĳ���Ϊ 1 �� 4 �ֽڣ���ѭ���µĹ���

���� 1 �ֽ� ���ַ����ֽڵĵ�һλ��Ϊ 0 ������ 7 λΪ������ŵ� unicode �롣
���� n �ֽ� ���ַ� (n > 1)����һ���ֽڵ�ǰ n λ����Ϊ1���� n+1 λ��Ϊ 0 �������ֽڵ�ǰ��λһ����Ϊ 10 ��ʣ�µ�û���ἰ�Ķ�����λ��ȫ��Ϊ������ŵ� unicode �롣
���� UTF-8 ����Ĺ�����ʽ��

      Number of Bytes  |        UTF-8 octet sequence
                       |              (binary)
   --------------------+---------------------------------------------
            1          | 0xxxxxxx
            2          | 110xxxxx 10xxxxxx
            3          | 1110xxxx 10xxxxxx 10xxxxxx
            4          | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
x ��ʾ��������ʽ��һλ�������� 0 �� 1��

ע�⣺�������������顣ֻ��ÿ�������� ��� 8 ����Чλ �����洢���ݡ�����ζ��ÿ������ֻ��ʾ 1 �ֽڵ����ݡ�

- 1 <= data.length <= 2 * 104
- 0 <= data[i] <= 255
*/

DEFINE_SOLUTION_CASE(393, validUtf8, bool, vector<int>);
REGISTER_SOLUTION_CASE(393,
    Case(true, {192,130,1}),
    Case(false, {235,140,4 }),
    Case(false, {250, 145, 145, 145, 145})
);

class Solution(393, 1) {
public:
    struct mask {
        int flag;
        int result;
    };
    bool validUtf8(vector<int>&data) {
        
        mask maskList[] = { { 0b11 << 6,1 << 7 } ,{1 << 7,0},{0b111 << 5,0b11 << 6},{0b1111 << 4,0b111 << 5},{0b11111 << 3,0b1111 << 4} };

        auto codeSignleUtf8Char = [&maskList](int* str, size_t s, size_t& charSize)->bool {
            size_t i = 1;
            for (; i < sizeof(maskList) / sizeof(mask); i++) {
                if ((*str & maskList[i].flag) == maskList[i].result) 
                    break;
            }
            if (i > s || i >= sizeof(maskList) / sizeof(mask)) 
                return false;

            for (size_t j = 1; j < i; j++) {
                if ((*(str + j) & maskList[0].flag) != maskList[0].result) 
                    return false;
            }
            charSize = i;
            return true;
        };
        
        for (size_t i = 0, j = 0; i < data.size(); i += j) {
            bool ret = codeSignleUtf8Char(data.data() + i, data.size() - i, j);
            if (!ret) return ret;
        }

        return true;
    }
};

/*
���ߣ�����
���ӣ�https ://leetcode.cn/problems/utf-8-validation/solutions/1332558/c-by-su-yin-d-380h/
������ʵ��
*/
class Solution(393, 2) {
public:
    bool validUtf8(vector<int>& data) {
        int bitIndex = 0;//�����ж�data���ֽں�һ���м����ֽ�
        for (const int num : data) {
            if (bitIndex == 0) {
                if ((num >> 5) == 0b110) bitIndex = 1;
                else if ((num >> 4) == 0b1110) bitIndex = 2;
                else if ((num >> 3) == 0b11110) bitIndex = 3;
                else if (num >> 7) return false;
            }
            else {
                if ((num >> 6) != 0b10) return false;
                --bitIndex;
            }
        }
        return bitIndex == 0;
    }
};


