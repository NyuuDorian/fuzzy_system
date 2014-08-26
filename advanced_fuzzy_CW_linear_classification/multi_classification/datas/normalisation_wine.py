#!/usr/bin/python3.4
# -*-coding:Utf-8 -*-

import re

with open("wine.data", "r") as mon_fichier_lecture: 
	contenu = mon_fichier_lecture.read()
#	contenu=contenu.replace("?","1")
	tab=contenu.split("\n")
	contenu=",".join(tab)
	tab=contenu.split(",")

	tmp_min=[]
	tmp_max=[]

	for i, elt in enumerate(tab):
		#tmp_min=elt
		if elt!='' and i<14:
			tmp_min.append(float(elt))
			tmp_max.append(float(elt))
		elif elt!='':
			if tmp_min[i%14]>float(elt):
				tmp_min[i%14]=float(elt)
			if tmp_max[i%14]<float(elt):
				tmp_max[i%14]=float(elt)

	#print(tmp_min)
	#print(tmp_max)
	
	for i, elt in enumerate(tab):
		if(elt!=''):
			if(i%14!=0):
				tab[i]=str((float(tab[i])-tmp_min[i%14])/(tmp_max[i%14]-tmp_min[i%14])*(1-0)+0)


	
	#contenu=" ".join(tab)
	#print(contenu.replace(","," "))
#with open("breast_cancer_wisconsin_normalized.txt", "w") as mon_fichier_ecriture:
with open("wines_normalized.txt", "w") as mon_fichier_ecriture:
	#mon_fichier_ecriture.write("Premier test d'écriture dans un fichier via Python")
	mon_fichier_ecriture.write("178\n")
	mon_fichier_ecriture.write("13\n")
	mon_fichier_ecriture.write("3\n")
	for i, elt in enumerate(tab):
		if(i%14==0 and i!=0 and i<len(tab)-1):
			mon_fichier_ecriture.write("\n")
		if(i%14==13):
			mon_fichier_ecriture.write(str(i%14))
			mon_fichier_ecriture.write(" : ")	
			mon_fichier_ecriture.write(tab[i-13])
		elif(i<len(tab)-1):
			mon_fichier_ecriture.write(str(i%14))
			mon_fichier_ecriture.write(" : ")	
			mon_fichier_ecriture.write(tab[i+1])
		if(i%14!=13):
			mon_fichier_ecriture.write("\t")
		
#print(contenu)

#mon_fichier_lecture.close()
#mon_fichier_ecriture.close()

