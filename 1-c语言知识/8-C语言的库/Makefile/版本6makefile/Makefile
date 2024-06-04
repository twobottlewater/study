CC=gcc
TARGET=main
SRCS=$(wildcard *.c) 
OBJS=$(patsubst %.c, %.o, $(SRCS))  

$(TARGET):$(OBJS)
	$(CC) -o $@ $^
%.o:%.c
	$(CC) -o $@ -c $<
#clean是目标，但是他没有依赖。这个是伪目标
clean:
	 rm $(TARGET) $(OBJS)