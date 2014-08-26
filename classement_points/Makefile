# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-Wall -std=c++11 -lm -lpthread -lX11 -o

#default:make
#all:make

make:logiciel_fuzzy.cpp
	$(CC) $(CFLAGS) logiciel_fuzzy.exe logiciel_fuzzy.cpp

launch:logiciel_fuzzy.exe
	./logiciel_fuzzy.exe

make_bis:test.cpp
	g++ -o aaa.exe test.cpp -lm -lpthread -lX11

make_ter:logiciel_fuzzy.cpp
	g++ -o logiciel_fuzzy.exe logiciel_fuzzy.cpp -lm -lpthread -lX11

clean:
	rm *.exe

#g++ -o aaa test.cpp -lm -lpthread -lX11
