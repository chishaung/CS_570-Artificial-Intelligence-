kmeans: kmeans.cpp 
	g++ -o kmeans kmeans.cpp
run: kmeans
	cat setone.dat | ./kmeans
	cat settwo.dat | ./kmeans
	cat setsimple.dat | ./kmeans
tar:
	tar -cvf kmeans.tar kmeans.cpp makefile
