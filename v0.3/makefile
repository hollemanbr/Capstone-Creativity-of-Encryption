CXX = g++ -g
CXXFLAGS = -Wall -g -std=c++0x


OBJ = rc4Alt.o

rc4Test: $(OBJ)
		$(CXX) rc4Alt.o -o rc4Test

rc4Alt.o: rc4Alt.c rc4.h 

clean:
	rm -rf rc4.o rc4Test
