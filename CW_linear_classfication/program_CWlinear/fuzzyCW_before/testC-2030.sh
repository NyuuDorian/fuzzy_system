#!/bin/sh
#testC on 20-30 confidence

./CWfuzzy_before data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 10

sleep 1

./CWfuzzy_before data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 20

sleep 1

./CWfuzzy_before data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 50

sleep 1

./CWfuzzy_before data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 100

sleep 1

./CWfuzzy_before data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 200

sleep 1

./CWfuzzy_before data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 500

sleep 1

./CWfuzzy_before data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 1000

sleep 1

mv *.txt /outputC20-30/