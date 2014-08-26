# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-Wall -std=c++11 -o

#default:make
#all:make

make:algo_fuzzy_advanced_multi_classification.cpp
	$(CC) $(CFLAGS) algo_fuzzy_advanced_multi_classification.exe algo_fuzzy_advanced_multi_classification.cpp

launch:algo_fuzzy_advanced_multi_classification.exe
	#./algo_fuzzy.exe breast_cancer_wisconsin_normalized 2>breast_cancer_wisconsin_normalized.txt
	#./algo_fuzzy.exe breast_cancer_wisconsin_normalized_2_debug
	./algo_fuzzy_advanced_multi_classification.exe breast_cancer_wisconsin_normalized 2 4
	./algo_fuzzy_advanced_multi_classification.exe breast_cancer_wisconsin_modified_normalized 2 4
#	./algo_fuzzy_advanced_multi_classification.exe abalone_normalized
	./algo_fuzzy_advanced_multi_classification.exe transfusion_normalized 2 4
	./algo_fuzzy_advanced_multi_classification.exe pima-indians-diabetes_normalized 2 4
	./algo_fuzzy_advanced_multi_classification.exe abalone_normalized_multiclass 2 3
	./algo_fuzzy_advanced_multi_classification.exe iris_corrected_normalized 2 8
	./algo_fuzzy_advanced_multi_classification.exe wines_normalized 2 5

clean:
	rm *.exe
