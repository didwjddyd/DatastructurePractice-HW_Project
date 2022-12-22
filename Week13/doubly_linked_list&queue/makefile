main.out: Queue.o DLinkedList.o main.cpp
	g++ Queue.o DLinkedList.o main.cpp -o main.out -std=c++14

Queue.o: Queue.h Queue.cpp
	g++ -c Queue.cpp -std=c++14

DLinkedList.o: DLinkedList.h DLinkedList.cpp
	g++ -c DLinkedList.cpp -std=c++14

clean:
	rm -rf *.o
