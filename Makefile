all: raw unique

raw: PlanetRawPtrTest.exe

PlanetRawPtrTest.exe: PlanetRawPtrTest.cpp PlanetRawPtr.h PlanetRawPtr.o
	g++ -std=c++17 -o PlanetRawPtrTest.exe PlanetRawPtrTest.cpp PlanetRawPtr.o

PlanetRawPtr.o: PlanetRawPtr.cpp PlanetRawPtr.h
	g++ -c -std=c++17 PlanetRawPtr.cpp

unique: PlanetUniquePtrTest.exe

PlanetUniquePtrTest.exe: PlanetUniquePtrTest.cpp PlanetUniquePtr.h PlanetUniquePtr.o
	g++ -std=c++17 -o PlanetUniquePtrTest.exe PlanetUniquePtrTest.cpp PlanetUniquePtr.o

PlanetUniquePtr.o: PlanetUniquePtr.cpp PlanetUniquePtr.h
	g++ -c -std=c++17 PlanetUniquePtr.cpp

clean:
	del /Q *.o *.exe 2> nul || rm -f *.o *.exe

