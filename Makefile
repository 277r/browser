SOURCES=main.o
SRC = $(wildcard ./*/*.cpp)
CPPFLAGS = -Wno-write-strings 
OBJ = ${SRC:.cpp=.o}

# need more flags
# -L/usr/lib/gcc/x86_64-linux-gnu/8/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../x86_64-linux-gnu/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../../lib/ -L/lib/x86_64-linux-gnu/ -L/lib/../lib/ -L/usr/lib/x86_64-linux-gnu/ -L/usr/lib/../lib/ -L/usr/lib/gcc/x86_64-linux-gnu/8/../../../ -L/lib/
LDFLAGS = -ldeflate -lstdc++ -lssl -lcrypto
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