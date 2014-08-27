# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-Wall -std=c++11 -o

#default:make
#all:make

make:algo_fuzzy_advanced.cpp
	$(CC) $(CFLAGS) algo_fuzzy_advanced.exe algo_fuzzy_advanced.cpp

launch:algo_fuzzy_advanced.exe
	#./algo_fuzzy.exe breast_cancer_wisconsin_normalized 2>breast_cancer_wisconsin_normalized.txt
	#./algo_fuzzy.exe breast_cancer_wisconsin_normalized_2_debug
	./algo_fuzzy.exe breast_cancer_wisconsin_modified_normalized 2 4
	./algo_fuzzy.exe breast_cancer_wisconsin_normalized 2 4
#	./algo_fuzzy.exe abalone_normalized
	./algo_fuzzy.exe transfusion_normalized 2 4
	./algo_fuzzy.exe pima-indians-diabetes_normalized 2 4

make_bis:algo_fuzzy.cpp
	$(CC) $(CFLAGS) algo_fuzzy.exe algo_fuzzy.cpp

launch_bis:algo_fuzzy.exe
	#./algo_fuzzy.exe breast_cancer_wisconsin_normalized 2>breast_cancer_wisconsin_normalized.txt
	#./algo_fuzzy.exe breast_cancer_wisconsin_normalized_2_debug
	./algo_fuzzy.exe breast_cancer_wisconsin_modified_normalized 2 4
	./algo_fuzzy.exe breast_cancer_wisconsin_normalized 2 4
#	./algo_fuzzy.exe abalone_normalized
	./algo_fuzzy.exe transfusion_normalized 2 4
	./algo_fuzzy.exe pima-indians-diabetes_normalized 2 4

clean:
	rm *.exe
