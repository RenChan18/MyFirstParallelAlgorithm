CC = gcc

CFLAGS = -Wall -g

SRC = src/main.c
TARGET = array_sum

OPTION_NUMBER ?= 1
RAND_RANGE ?= 100
ARRAY_SIZE ?= 100000
THREADS_NUM ?= 5
LOOP_NUM ?= 100000


all:
	$(CC) $(CFLAGS) -DOPTION_NUMBER=$(OPTION_NUMBER) -DRAND_RANGE=$(RAND_RANGE) \
	-DARRAY_SIZE=$(ARRAY_SIZE) -DTHREADS_NUM=$(THREADS_NUM) -DLOOP_NUM=$(LOOP_NUM) \
	-o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
