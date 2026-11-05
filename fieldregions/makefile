CC = gcc
CFLAGS =  
LDFLAGS = -lm

SRCS = fieldregions.c
OBJS = $(SRCS:.c=.o)
INCS = $(SRCS:.c=.h)
TARGET = fieldregions

.PHONY: all 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
$(OBJS): $(SRCS) $(INCS)
	$(CC) $(CFLAGS) -c $(SRCS)

.PHONY: clean
clean:
	rm $(TARGET) $(OBJS)

