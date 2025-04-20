planet_test.exe: planet_test.cpp planet.h planet.o
	g++ -std=c++17 -o planet_test.exe planet_test.cpp planet.o

planet.o: planet.cpp planet.h
	g++ -c -std=c++17 planet.cpp

clean:
	del /Q *.o *.exe 2> nul || rm -f *.o *.exe

