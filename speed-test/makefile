CC = gcc
CFLAGS =  
LDFLAGS = 

SRCS = speed_test.c
OBJS = $(SRCS:.c=.o)
INCS = $(SRCS:.c=.h)
TARGET = speed-test 

.PHONY: all 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
$(OBJS): $(SRCS) $(INCS)
	$(CC) $(CFLAGS) -c $(SRCS)

.PHONY: clean
clean:
	rm $(TARGET) $(OBJS)

