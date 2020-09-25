main:../Acceptor.o ../Channel.o ../Eventloop.o 
	g++ -g test.cpp ../Acceptor.o ../Channel.o ../Eventloop.o -o main -std=c++11
Acceptor.o:../Acceptor.cpp ../Acceptor.h 
	g++ ../Acceptor.cpp -c ../Acceptor.o -std=c++11
Channel.o:../Channel.cpp ../Channel.h 
	g++ ../Channel.cpp -c ../Channel.o -std=c++11
Eventloop.o:../Eventloop.cpp ../Eventloop.h
	g++ ../Eventloop.cpp -c ../Eventloop.o -std=c++11

clean:
	rm ../*.o main

