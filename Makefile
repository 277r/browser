SOURCES=main.o
SRC = $(wildcard ./*/*.cpp)
CPPFLAGS = -Wno-write-strings
OBJ = ${SRC:.cpp=.o}

# need more flags
LDFLAGS =-L/usr/lib/gcc/x86_64-linux-gnu/8/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../x86_64-linux-gnu/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../../lib/ -L/lib/x86_64-linux-gnu/ -L/lib/../lib/ -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/../lib/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../ -L/lib/ -L/usr/lib/ -lstdc++ -lm -lgcc_s -lgcc -lc -lgcc_s -lgcc
CC = g++
LD = ld



objects: ${OBJ}
	${CC} ${CPPFLAGS} -c $< -o $@

build: objects
	
	${CC} main.cpp ${OBJ} ${CPPFLAGS} -o browser.out

clean:
	rm ${OBJ} browser.out