CXX = g++ -g
CXXFLAGS = -Wall -g -std=c++0x


OBJ = rc4.o

rc4Test: $(OBJ)
		$(CXX) rc4.o -o rc4Test

rc4.o: rc4.c rc4.h 

clean:
	rm -f rc4.o rc4Test
