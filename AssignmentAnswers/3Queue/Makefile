all: queuetest

queuetest: queue.o queuetest.o
	gcc queue.o queuetest.o -o queuetest

queuetest.o: queuetest.c queue.h
	gcc -c queuetest.c

queue.o: queue.c queue.h
	gcc -c queue.c

clean:
	rm -f *.o queuetest