#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *compressString(const char *s)
{
    if (s == NULL || strlen(s) == 0)
    {
        return NULL;
    }

    int len = strlen(s);
    int compressedLen = 0;
    // 遍历字符串计算压缩后的长度
    for (int i = 0, count = 1; i < len; ++i)
    {
        if (i + 1 < len && s[i] == s[i + 1])
        {
            ++count;
        }
        else
        {
            compressedLen += 1 + (count > 9 ? 2 : 1); // 字符 + 计数（1位或2位）
            count = 1;
        }
    }

    // 如果压缩后没有变短，则不压缩
    if (compressedLen >= len)
    {
        return strdup(s);
    }

    // 分配压缩后字符串的内存
    char *compressed = (char *)malloc(compressedLen + 1);
    if (compressed == NULL)
    {
        return NULL;
    }

    int j = 0;
    for (int i = 0, count = 1; i < len; ++i)
    {
        if (i + 1 < len && s[i] == s[i + 1])
        {
            ++count;
        }
        else
        {
            if (count > 9)
                compressed[j++] = '0' + count / 10;
            if (count != 1)
                compressed[j++] = '0' + count % 10;
            compressed[j++] = s[i];
            count = 1;
        }
    }
    compressed[j] = '\0'; // 确保字符串以null结尾

    return compressed;
}

int main()
{
    const char *input = "aabcccccaaa";
    char *output = compressString(input);
    if (output != NULL)
    {
        printf("Compressed string: %s\n", output);
        free(output); // 释放分配的内存
    }
    else
    {
        printf("Compression failed.\n");
    }
    return 0;
}