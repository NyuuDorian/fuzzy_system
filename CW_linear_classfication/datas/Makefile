# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-Wall -std=c++11 -o

#default:make
#all:make

make:create_various_rotates_datas.cpp
	$(CC) $(CFLAGS) create_various_rotates_datas.exe create_various_rotates_datas.cpp
#make:creation_jeu_de_donnees.cpp
	#$(CC) $(CFLAGS) creation_jeu_de_donnees.exe creation_jeu_de_donnees.cpp

##make:creation_jeu_donnee_bis.cpp
	##$(CC) $(CFLAGS) creation_jeu_donnee_bis.exe creation_jeu_donnee_bis.cpp

launch:create_various_rotates_datas.exe
	./create_various_rotates_datas.exe 1
	./create_various_rotates_datas.exe 2
	./create_various_rotates_datas.exe 3
	./create_various_rotates_datas.exe 4
	./create_various_rotates_datas.exe 5

make_bis:create_various_rotates_datas_breast.cpp
	$(CC) $(CFLAGS) create_datas_breast.exe create_various_rotates_datas_breast.cpp

launch_bis:create_datas_breast.exe
	./create_datas_breast.exe test1 2000

clean:
	rm *.exe
