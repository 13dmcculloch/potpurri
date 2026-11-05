CC = gcc
CFLAGS =  
LDFLAGS = 

SRCS = typist.c 
OBJS = $(SRCS:.c=.o)
INCS = $(SRCS:.c=.h)
TARGET = typist 

.PHONY: all 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
$(OBJS): $(SRCS) $(INCS)
	$(CC) $(CFLAGS) -c $(SRCS)

.PHONY: clean
clean:
	rm $(TARGET) $(OBJS)

