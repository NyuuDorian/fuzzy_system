#!/usr/bin/python3.4
# -*-coding:Utf-8 -*-

import re

with open("pima-indians-diabetes.data", "r") as mon_fichier_lecture: 
	contenu = mon_fichier_lecture.read()
	#contenu=contenu.replace("?","1")
	tab=contenu.split("\n")
	contenu=",".join(tab)
	tab=contenu.split(",")
	#i=0
	#j=0
	tab_min=[]
	tab_max=[]

	for i in range(0,9):
		tab_min.append(float(tab[i]))
		tab_max.append(float(tab[i]))

	for i, elt in enumerate(tab):
		#tmp_min=elt
		if elt!='' and i%9!=8:
			if tab_min[i%9]>float(elt):
				tab_min[i%9]=float(elt)
			if tab_max[i%9]<float(elt):
				tab_max[i%9]=float(elt)

	#print(tmp_min)
	#print(tmp_max)
	
	for i, elt in enumerate(tab):
		if(elt!=''):
			if(i%9!=8):
				tab[i]=str((float(tab[i])-tab_min[i%9])/(tab_max[i%9]-tab_min[i%9])*(1-0)+0)

	
	#contenu=" ".join(tab)
	#print(contenu.replace(","," "))
#with open("breast_cancer_wisconsin_normalized.txt", "w") as mon_fichier_ecriture:
with open("pima-indians-diabetes_normalized.txt", "w") as mon_fichier_ecriture:
	#mon_fichier_ecriture.write("Premier test d'écriture dans un fichier via Python")
	mon_fichier_ecriture.write("768\n")
	mon_fichier_ecriture.write("8\n")
	mon_fichier_ecriture.write("2\n")
	for i, elt in enumerate(tab):
		if(i%9==0 and i!=0):
			mon_fichier_ecriture.write("\n")
		mon_fichier_ecriture.write(str(i%9))
		mon_fichier_ecriture.write(" : ")
		mon_fichier_ecriture.write(tab[i])
		mon_fichier_ecriture.write("\t")
		
#print(contenu)

#mon_fichier_lecture.close()
#mon_fichier_ecriture.close()

