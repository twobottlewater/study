CC = gcc
CFLAGS = -Wall -Wextra -Werror

# 获取当前文件夹下的所有.c文件
SRCS := $(wildcard *.c)

# 将.c文件列表转换为.o文件列表
OBJS := $(SRCS:.c=.o)

# 目标规则
air: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译.c文件为.o文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f air $(OBJS)
