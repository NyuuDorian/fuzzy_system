#!/usr/bin/python3.4
# -*-coding:Utf-8 -*-

import re

with open("breast-cancer-wisconsin.data", "r") as mon_fichier_lecture: 
	contenu = mon_fichier_lecture.read()
	contenu=contenu.replace("?","1")
	tab=contenu.split("\n")
	contenu=",".join(tab)
	tab=contenu.split(",")
	i=0
	j=0
	tmp_min=int(tab[i])
	tmp_max=int(tab[i])
	for i, elt in enumerate(tab):
		#tmp_min=elt
		if elt!='':
			if i%11==0 and tmp_min>int(elt):
				tmp_min=int(elt)
			if i%11==0 and tmp_max<int(elt):
				tmp_max=int(elt)

	#print(tmp_min)
	#print(tmp_max)
	
	for i, elt in enumerate(tab):
		if(elt!=''):
			if(i%11==0):
				tab[i]=str((int(tab[i])-tmp_min)/(tmp_max-tmp_min)*(1-0)+0)
				j+=1
			elif(j==10):
				if(tab[i]=='2'):
					tab[i]='0'
				elif(tab[i]=='4'):
					tab[i]='1'
				else: 
					print("Error")
					print(elt)
					print(i)
				j=0
			else:
				tab[i]=str((int(tab[i])-1)/9)
				j+=1

	
	#contenu=" ".join(tab)
	#print(contenu.replace(","," "))
with open("breast_cancer_wisconsin_normalized.txt", "w") as mon_fichier_ecriture:
	#mon_fichier_ecriture.write("Premier test d'écriture dans un fichier via Python")
	mon_fichier_ecriture.write("699\n")
	mon_fichier_ecriture.write("10\n")
	mon_fichier_ecriture.write("2\n")
	for i, elt in enumerate(tab):
		if(i%11==0 and i!=0):
			mon_fichier_ecriture.write("\n")
		mon_fichier_ecriture.write(tab[i])
		mon_fichier_ecriture.write("\t")
		
#print(contenu)

#mon_fichier_lecture.close()
#mon_fichier_ecriture.close()

