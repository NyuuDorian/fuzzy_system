#!/usr/bin/python3.4
# -*-coding:Utf-8 -*-

import re

with open("breast-cancer-wisconsin_bis.data", "r") as mon_fichier_lecture: 
	contenu = mon_fichier_lecture.read()
	contenu=contenu.replace("?","1")
	tab=contenu.split("\n")
	contenu=",".join(tab)
	tab=contenu.split(",")
	i=0
	for i, elt in enumerate(tab):
		#print(int(elt))
		if(i>2 && int(tab[i])>10):
			del tab[i]
		if(i>2 && (i-3)%10=0):
			tab[i]=str((int(tab[i])-1)/9)
		i++

	
	#contenu=" ".join(tab)
	#print(contenu.replace(","," "))
with open("breast-cancer-wisconsin_ter.data", "w") as mon_fichier_ecriture:
	#mon_fichier_ecriture.write("Premier test d'écriture dans un fichier via Python")
	#mon_fichier_ecriture.write("699\n")
	#mon_fichier_ecriture.write("10\n")
	#mon_fichier_ecriture.write("2\n")
	for i, elt in enumerate(tab):
		if(i<3):
			mon_fichier_ecriture.write(tab[i])
		else:
			for j in len(8)
				mon_fichier_ecriture.write(contenu.replace(","," ").replace("?", "1"))
		i++
#print(contenu)

#mon_fichier_lecture.close()
#mon_fichier_ecriture.close()
