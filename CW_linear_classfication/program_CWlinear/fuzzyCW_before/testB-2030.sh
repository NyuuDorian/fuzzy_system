#!/bin/sh
#testB on 20-30 confidence

./CWfuzzy_before data/NlearnB.txt data/N20_30_B.txt data/Ntest10-30B.txt 10

sleep 1

./CWfuzzy_before data/NlearnB.txt data/N20_30_B.txt data/Ntest10-30B.txt 20

sleep 1

./CWfuzzy_before data/NlearnB.txt data/N20_30_B.txt data/Ntest10-30B.txt 50

sleep 1

./CWfuzzy_before data/NlearnB.txt data/N20_30_B.txt data/Ntest10-30B.txt 100

sleep 1

./CWfuzzy_before data/NlearnB.txt data/N20_30_B.txt data/Ntest10-30B.txt 200

sleep 1

./CWfuzzy_before data/NlearnB.txt data/N20_30_B.txt data/Ntest10-30B.txt 500

sleep 1

./CWfuzzy_before data/NlearnB.txt data/N20_30_B.txt data/Ntest10-30B.txt 1000

sleep 1

mv *.txt /outputB20-30/