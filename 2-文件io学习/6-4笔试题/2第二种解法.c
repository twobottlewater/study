#include <stdio.h>

void save_to_file(const char* filename, const unsigned short arr[], size_t length) 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (size_t i = 0; i < length; ++i) 
	{
        // 提取低8位
        unsigned short lower_8_bits = arr[i] & 0xff;
        // 将其格式化为两位十六进制字符串
        fprintf(file, "%02x", lower_8_bits);
    }

    fclose(file);
}

int main() {
    unsigned short str[] = {0x00, 0x02, 0x03, 0x10, 0x20, 0x30};

    save_to_file("123.txt", str, sizeof(str)/sizeof(str[0]));

    return 0;
}