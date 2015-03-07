nn: nn.cpp 
	g++ -o nn nn.cpp
run: nn
	cat iris.dat iristest.dat | ./nn
tar:
	tar -cvf nn.tar nn.cpp makefile
