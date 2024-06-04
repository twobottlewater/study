#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 获取文件大小
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    off_t offset = file_size;
    ssize_t bytes_read;

    while (offset > 0) {
        // 计算读取的字节数
        off_t chunk_size = (offset > BUFFER_SIZE) ? BUFFER_SIZE : offset;

        // 移动文件指针到要读取的块的起始位置
        offset -= chunk_size;
        if (lseek(fd, offset, SEEK_SET) == -1) {
            perror("lseek");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // 读取数据
        bytes_read = read(fd, buffer, chunk_size);
        if (bytes_read == -1) {
            perror("read");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // 输出读取的数据
        for (ssize_t i = bytes_read - 1; i >= 0; i--) {
            putchar(buffer[i]);
        }
    }

    close(fd);
    return 0;
}
