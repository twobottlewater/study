CC = arm-linux-gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread -lm

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: main

main: $(OBJS)
	$(CC)$(LDFLAGS) $^ -o$@

%.o: %.c
	$(CC)$(CFLAGS) -c $< -o$@

clean:
	rm -f *.o main

.PHONY: clean
