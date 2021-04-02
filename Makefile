SOURCES=main.o
SRC = $(wildcard ./*/*.cpp)

# disable gcc string warnings because it works and it's just "it's not allowed by iso standard" i do not care. this is the easiest way without having to rewrite all my functions and it works just as intended
CPPFLAGS = -Wno-write-strings 
OBJ = ${SRC:.cpp=.o}

# need more flags
# -L/usr/lib/gcc/x86_64-linux-gnu/8/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../x86_64-linux-gnu/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../../lib/ -L/lib/x86_64-linux-gnu/ -L/lib/../lib/ -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/../lib/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../ -L/lib/
LDFLAGS = -ldeflate -lstdc++ -lssl -lcrypto  -lglfw -lGL -lGLEW -pthread
CC = g++
LD = ld

IncludeSearches = /usr/local/include

# doesn't seem to work, linker issue
#${OBJ}: ${SRC}
#	${CC} ${CPPFLAGS} -c $< -o $@ 


build: ${OBJ}
	
	${CC} ${LDFLAGS} ${CPPFLAGS} main.cpp ${OBJ}  -o browser.out

clean:
	rm ${OBJ} browser.out

cleanobj:
	rm ${OBJ}


%.o : %.cpp
	$(CC) ${LDFLAGS} $(CPPFLAGS) -c $< -o $@

run: build
	./browser.out