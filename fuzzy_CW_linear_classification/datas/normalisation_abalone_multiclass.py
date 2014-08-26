#!/usr/bin/python3.4
# -*-coding:Utf-8 -*-

import re

with open("abalone.data", "r") as mon_fichier_lecture: 
	contenu = mon_fichier_lecture.read()
	#contenu=contenu.replace('I','M')
	tab=contenu.split("\n")
	contenu=",".join(tab)
	tab=contenu.split(",")
	i=0
	j=0
		
	tab_min=[0.075, 0.055, 0.000, 0.002, 0.001, 0.001, 0.002, 1]
	tab_max=[0.815, 0.650, 1.130, 2.826, 1.488, 0.760, 1.005, 29]

	#print(tmp_min)
	#print(tmp_max)
	
	for i, elt in enumerate(tab):
		if(elt!=''):
			if(i%9==0):
				if(tab[i]=='F'):
					tab[i]='0'
				if(tab[i]=='M'):
					tab[i]='1'
				if(tab[i]=='I'):
					tab[i]='2'
			else:				
				tab[i]=str((float(tab[i])-tab_min[i%9-1])/(tab_max[i%9-1]-tab_min[i%9-1])*(1-0)+0)
				

	
	#contenu=" ".join(tab)
	#print(contenu.replace(","," "))
#with open("breast_cancer_wisconsin_normalized.txt", "w") as mon_fichier_ecriture:
with open("abalone_normalized_multiclass.txt", "w") as mon_fichier_ecriture:
	#mon_fichier_ecriture.write("Premier test d'écriture dans un fichier via Python")
	mon_fichier_ecriture.write("4177\n")
	mon_fichier_ecriture.write("8\n")
	mon_fichier_ecriture.write("3\n")
	for i, elt in enumerate(tab):
		if(i%9==0 and i!=0):
			mon_fichier_ecriture.write("\n")
		mon_fichier_ecriture.write(str(i%9))
		mon_fichier_ecriture.write(" : ")
		if(i%9==8):
			mon_fichier_ecriture.write(tab[i-8])
		elif(i<len(tab)-1):
			mon_fichier_ecriture.write(tab[i+1])
		mon_fichier_ecriture.write("\t")
		
#print(contenu)

#mon_fichier_lecture.close()
#mon_fichier_ecriture.close()

