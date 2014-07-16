#!/usr/bin/python3.4
#-*-coding:utf-8-*-

import re
import os

#print "root prints out directories only from what you specified"
#print "dirs prints out sub-directories from root"
#print "files prints out all files from root and directories"
#print "*" * 20
for root, dirs, files in os.walk("/home/julien/fuzzy_system/CW_linear_classfication/datas/comp.sys.ibm.pc.hardware"):
        print("ROOT\n")
        print(root)
        print("DIRS\n")
        print(dirs)
        print("FILES\n")
        print(files)

for i, elt in enumerate(files):
        print(elt)

        with open("/home/julien/fuzzy_system/CW_linear_classfication/datas/comp.sys.ibm.pc.hardware/"+elt, "r") as file_ibm:
                #TODO
                contenu_file_ibm = file_ibm.read()

                contenu_file_ibm=contenu_file_ibm.replace("?"," ")
                contenu_file_ibm=contenu_file_ibm.replace(":"," ")
                contenu_file_ibm=contenu_file_ibm.replace(">"," ")
                contenu_file_ibm=contenu_file_ibm.replace("<"," ")
                contenu_file_ibm=contenu_file_ibm.replace(","," ")
                contenu_file_ibm=contenu_file_ibm.replace(";"," ")
                contenu_file_ibm=contenu_file_ibm.replace("("," ")
                contenu_file_ibm=contenu_file_ibm.replace(")"," ")
                contenu_file_ibm=contenu_file_ibm.replace("'"," ")
                contenu_file_ibm=contenu_file_ibm.replace("="," ")
                contenu_file_ibm=contenu_file_ibm.replace("-"," ")
                contenu_file_ibm=contenu_file_ibm.replace("_"," ")
                contenu_file_ibm=contenu_file_ibm.replace('"'," ")
                contenu_file_ibm=contenu_file_ibm.replace("!"," ")
                contenu_file_ibm=contenu_file_ibm.replace("*"," ")
                contenu_file_ibm=contenu_file_ibm.replace("#"," ")
                contenu_file_ibm=contenu_file_ibm.replace("/"," ")
                contenu_file_ibm=contenu_file_ibm.replace("\\"," ")
                contenu_file_ibm=contenu_file_ibm.replace("."," ")
                contenu_file_ibm=contenu_file_ibm.replace("~"," ")
                contenu_file_ibm=contenu_file_ibm.replace("%"," ")
                contenu_file_ibm=contenu_file_ibm.replace("^"," ")
                contenu_file_ibm=contenu_file_ibm.replace("|"," ")
                contenu_file_ibm=contenu_file_ibm.replace("@"," ")


        with open("test_ibm.txt", "w") as new_file_ibm:
                new_file_ibm.write(contenu_file_ibm)
		

"""with open("comp.sys.ibm.pc.hardware.txt", "r") as file_ibm:
	#TODO
	contenu_file_ibm = file_ibm.read()

#not the good file to modify
	
with open("comp.sys.mac.hardware.txt", "r") as file_mac:
	#TODO
"""

#mon_fichier_lecture.close()
#mon_fichier_ecriture.close()
