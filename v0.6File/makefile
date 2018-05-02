CXX = g++ -g
CXXFLAGS = -Wall -g -std=c++0x


OBJ = rc4Alt.o
FOBJ = rc4File.o

rc4Test: $(OBJ)
		$(CXX) rc4Alt.o -o rc4Test

rc4Alt.o: rc4Alt.c rc4.h 


clean:
	rm -f rc4.o rc4Test
	rm -f encryptedFile.txt
	rm -f inputTest.c.txt
