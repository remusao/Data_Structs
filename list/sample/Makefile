CC = clang
CFLAGS = 
BINARY = list


all: list


list: main.c list.c
	${CC} ${CFLAGS} $^ -o ${BINARY}

clean:
	rm -frv list
