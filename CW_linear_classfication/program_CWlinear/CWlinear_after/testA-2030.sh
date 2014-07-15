#!/bin/sh
#testA on 20-30 confidence

./CWlinear_after data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 10

sleep 1

./CWlinear_after data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 20

sleep 1

./CWlinear_after data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 50

sleep 1

./CWlinear_after data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 100

sleep 1

./CWlinear_after data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 200

sleep 1

./CWlinear_after data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 500

sleep 1

./CWlinear_after data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 1000