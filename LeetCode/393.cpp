#include "pch.h"

/*
给定一个表示数据的整数数组 data ，返回它是否为有效的 UTF-8 编码。

UTF-8 中的一个字符可能的长度为 1 到 4 字节，遵循以下的规则：

对于 1 字节 的字符，字节的第一位设为 0 ，后面 7 位为这个符号的 unicode 码。
对于 n 字节 的字符 (n > 1)，第一个字节的前 n 位都设为1，第 n+1 位设为 0 ，后面字节的前两位一律设为 10 。剩下的没有提及的二进制位，全部为这个符号的 unicode 码。
这是 UTF-8 编码的工作方式：

      Number of Bytes  |        UTF-8 octet sequence
                       |              (binary)
   --------------------+---------------------------------------------
            1          | 0xxxxxxx
            2          | 110xxxxx 10xxxxxx
            3          | 1110xxxx 10xxxxxx 10xxxxxx
            4          | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
x 表示二进制形式的一位，可以是 0 或 1。

注意：输入是整数数组。只有每个整数的 最低 8 个有效位 用来存储数据。这意味着每个整数只表示 1 字节的数据。

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
作者：苏隐
链接：https ://leetcode.cn/problems/utf-8-validation/solutions/1332558/c-by-su-yin-d-380h/
更简洁的实现
*/
class Solution(393, 2) {
public:
    bool validUtf8(vector<int>& data) {
        int bitIndex = 0;//用于判断data首字节后一共有几个字节
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


