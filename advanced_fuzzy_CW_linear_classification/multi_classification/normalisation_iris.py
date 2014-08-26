#!/usr/bin/python3.4
# -*-coding:Utf-8 -*-

"""
Summary Statistics:
	         			 Min  Max   Mean    SD    Class  Correlation
   sepal length: 4.3  7.9   5.84  0.83    0.7826   
    sepal width: 2.0  4.4   3.05  0.43   -0.4194
   petal length: 1.0  6.9   3.76  1.76    0.9490  (high!)
    petal width: 0.1  2.5   1.20  0.76    0.9565  (high!)

"""




import re

with open("iris.corrected.data", "r") as mon_fichier_lecture: 
	contenu = mon_fichier_lecture.read()
	#contenu=contenu.replace('I','M')
	tab=contenu.split("\n")
	contenu=",".join(tab)
	tab=contenu.split(",")
	i=0
	j=0

	tab_min=[4.3, 2.0, 1.0, 0.1]
	tab_max=[7.9, 4.4, 6.9, 2.5]

	#print(tmp_min)
	#print(tmp_max)
	
	for i, elt in enumerate(tab):
		if(elt!=''):
			if(i%5==4):
				if(tab[i]=='Iris-setosa'):
					tab[i]='0'
				if(tab[i]=='Iris-versicolor'):
					tab[i]='1'
				if(tab[i]=='Iris-virginica'):
					tab[i]='2'
			else:				
				tab[i]=str((float(tab[i])-tab_min[i%5])/(tab_max[i%5]-tab_min[i%5])*(1-0)+0)
				

	
	#contenu=" ".join(tab)
	#print(contenu.replace(","," "))
#with open("breast_cancer_wisconsin_normalized.txt", "w") as mon_fichier_ecriture:
with open("iris_corrected_normalized.txt", "w") as mon_fichier_ecriture:
	#mon_fichier_ecriture.write("Premier test d'écriture dans un fichier via Python")
	mon_fichier_ecriture.write("150\n")
	mon_fichier_ecriture.write("4\n")
	mon_fichier_ecriture.write("3\n")
	for i, elt in enumerate(tab):
		if(i%5==0 and i!=0):
			mon_fichier_ecriture.write("\n")
		if(i<len(tab)-1):
			mon_fichier_ecriture.write(str(i%5))
			mon_fichier_ecriture.write(" : ")	
			mon_fichier_ecriture.write(tab[i])
		if(i%5!=4):
			mon_fichier_ecriture.write("\t")
		
#print(contenu)

#mon_fichier_lecture.close()
#mon_fichier_ecriture.close()

