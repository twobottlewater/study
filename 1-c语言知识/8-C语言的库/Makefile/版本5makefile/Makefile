CC=gcc
TARGET=main
SRCS=$(wildcard *.c) 
OBJS=$(patsubst %.c, %.o, $(SRCS))  
$(TARGET):$(OBJS)
	$(CC)  $(OBJS) -o $(TARGET)
clean:
	 rm $(TARGET) $(OBJS)