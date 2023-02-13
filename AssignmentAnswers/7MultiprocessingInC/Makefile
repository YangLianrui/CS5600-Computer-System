all: test

test: polybius.o hw7.o
	gcc polybius.o hw7.o -o test

hw7.o: hw7.c polybius.h
	gcc -c hw7.c

polybius.o: polybius.c polybius.h
	gcc -c polybius.c

clean:
	rm -f *.o test output*