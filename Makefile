CCFLAGS= -Wall -g
CC= g++ 

all: testSensor clean
testQuery: TestQuery clean

TestQuery: mainTestQuery.o cmdline.o QueryNetwork.o Query.o Result.o SensorNetwork.o Sensor.o
	$(CC) $(CCFLAGS) -o TestQuery mainTestQuery.o cmdline.o Query.o QueryNetwork.o Result.o SensorNetwork.o Sensor.o

testSensor: main.o cmdline.o SensorNetwork.o Sensor.o
	$(CC) $(CCFLAGS) -o testArray main.o cmdline.o SensorNetwork.o Sensor.o

main.o: main.cpp Array.h cmdline.h 
	$(CC) $(CCFLAGS) -c main.cpp -o main.o 

mainTestQuery.o: mainTestQuery.cpp Array.h sensor.h SensorNetwork.h cmdline.h Query.h QueryNetwork.h
	$(CC) $(CCFLAGS) -c mainTestQuery.cpp -o mainTestQuery.o 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CCFLAGS) -c cmdline.cc -o cmdline.o 

SensorNetwork.o: SensorNetwork.cpp SensorNetwork.h sensor.h Array.h
	$(CC) $(CCFLAGS) -c SensorNetwork.cpp -o SensorNetwork.o 

Sensor.o: sensor.cpp sensor.h Array.h
	$(CC) $(CCFLAGS) -c sensor.cpp -o Sensor.o

Query.o: Query.cpp Query.h Array.h SensorNetwork.h Result.h
	$(CC) $(CCFLAGS) -c Query.cpp -o Query.o

QueryNetwork.o: QueryNetwork.cpp QueryNetwork.h Query.h SensorNetwork.h Array.h
	$(CC) $(CCFLAGS) -c QueryNetwork.cpp -o QueryNetwork.o

Result.o: Result.cpp Result.h
	$(CC) $(CCFLAGS) -c Result.cpp -o Result.o



Tests: 
	./testArray -i testAnda.txt > salida.txt
	diff -q salida.txt salAnda.txt
	./testArray -i testDifDim.txt > salida.txt
	diff -q salida.txt salDifDim.txt
	./testArray -i testLet.txt > salida.txt
	diff -q salida.txt salLet.txt
	./testArray -i testNoP.txt > salida.txt
	diff -q salida.txt salNoP.txt

TestValgrind:
	valgrind --leak-check=full ./testArray -i testAnda.txt
	valgrind --leak-check=full ./testArray -i testDifDim.txt
	valgrind --leak-check=full ./testArray -i testLet.txt
	valgrind --leak-check=full ./testArray -i testNoP.txt

clean:
	$(RM) *.o 
