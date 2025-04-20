planet_test.exe: planet_test.cpp planet.h planet.o
	g++ -std=c++17 -o planet_test.exe planet_test.cpp planet.o -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lsfml-graphics -lsfml-window -lsfml-system

planet.o: planet.cpp planet.h
	g++ -c -std=c++17 planet.cpp -IC:/msys64/mingw64/include

clean:
	del /Q *.o *.exe 2> nul || rm -f *.o *.exe
