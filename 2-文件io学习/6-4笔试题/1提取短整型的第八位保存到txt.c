#include <stdio.h>

void save_to_file(const char* filename, const unsigned short arr[], size_t length) {
    FILE *file = fopen(filename, "w");
    if(file == NULL) 
	{
        perror("Error opening file");
        return;
    }

    for(size_t i = 0; i < length; ++i) 
	{
		//将十六进制数转换为二进制并提取最后两位数字
		unsigned short bin_digts=(arr[i]&0xff)%100;
		//将二进制数字格式化为十六进制字符串
		char hex_str[3];
		sprintf(hex_str,"%02hhx",bin_digts);
        fprintf(file, "%s", hex_str);
    }

    fclose(file);
}

int main() {
    unsigned short str[] = {0x00, 0x02, 0x03, 0x10, 0x20, 0x30};

    save_to_file("123.txt", str, sizeof(str)/sizeof(str[0]));

    return 0;
}