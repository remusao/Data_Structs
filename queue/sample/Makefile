CC = clang
CFLAGS = 
BINARY = queue


all: queue


queue: main.c queue.c
	${CC} ${CFLAGS} $^ -o ${BINARY}

clean:
	rm -frv queue
