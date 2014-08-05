# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-Wall -std=c++11 -o

#default:make
#all:make

make:algo.cpp
	$(CC) $(CFLAGS) algo.exe algo.cpp

launch:algo.exe
	#./algo.exe 1
	#./algo.exe 2
	#./algo.exe 3
	#./algo.exe 4
	#./algo.exe 5
	#./algo.exe output_bis_2
	#./algo.exe test1 2>err.txt
	#./algo.exe test2 2>err2.txt
	./algo.exe 7 2>err2.txt

clean:
	rm *.exe
