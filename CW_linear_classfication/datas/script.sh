#!/bin/bash

if [ ! -e $comp.sys.ibm.pc.hardware.txt ]
then
	touch comp.sys.ibm.pc.hardware.txt
	touch comp.sys.mac.hardware.txt
else
	rm comp.sys.ibm.pc.hardware.txt
	rm comp.sys.mac.hardware.txt
	touch comp.sys.ibm.pc.hardware.txt
	touch comp.sys.mac.hardware.txt
fi

cd comp.sys.ibm.pc.hardware

ls | wc -l > ../comp.sys.ibm.pc.hardware.txt 
ls >> ../comp.sys.ibm.pc.hardware.txt

cd ../comp.sys.mac.hardware

ls | wc -l > ../comp.sys.mac.hardware.txt
ls >> ../comp.sys.mac.hardware.txt
