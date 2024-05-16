#if 0
#include <stdio.h>
#include <string.h>

void hton(float val, char *buf) {
    char *floatToChar = (char *)&val;  // 将 float 指针转换为 char 指针以访问单个字节
    // 逆序复制 float 的每个字节到 buf 中
    for (int i = 0; i < sizeof(float); i++) {
        buf[sizeof(float) - 1 - i] = floatToChar[i];
    }
}

int main() {
    float val = 1234.5678;
    char buf[4];  // 用于存储转换后的大端序浮点数

    hton(val, buf);  // 转换并存储

    // 输出转换结果，用于验证
    printf("Original float: %f\n", val);
    printf("Converted to big-endian bytes:\n");
    for (int i = 0; i < sizeof(float); i++) {
        printf("%02X ", (unsigned char)buf[i]);
    }
    printf("\n");

    return 0;
}
#endif
#include <stdio.h>

// 假设 int 类型占 4 个字节
void hton_int(int val, char *buf) {
    // 将 int 值转换为网络字节序（大端）
    unsigned char *ptr = (unsigned char *)&val;
    unsigned char temp;

    // 交换字节序
    temp = ptr[0]; ptr[0] = ptr[3]; ptr[3] = temp;
    temp = ptr[1]; ptr[1] = ptr[2]; ptr[2] = temp;

    // 将交换后的值复制到缓冲区
    memcpy(buf, &val, sizeof(int));
}

int main() {
    int host_endian = 0x12345678; // 假设这是小端格式的整数
    char big_endian[4];

    hton_int(host_endian, big_endian);

    printf("原始整数值（小端格式）：0x%x\n", host_endian);
    printf("转换后的整数值（大端格式）：");
    for (int i = 0; i < 4; ++i) {
        printf("%02x", (unsigned char)big_endian[i]);
    }
    printf("\n");

    return 0;
}
