#!/bin/sh
#testB on 50-80 confidence

./CWfuzzy_app data/NlearnB.txt data/NCerrorB.txt data/NtestB.txt 10

sleep 1

./CWfuzzy_app data/NlearnB.txt data/NCerrorB.txt data/NtestB.txt 20

sleep 1

./CWfuzzy_app data/NlearnB.txt data/NCerrorB.txt data/NtestB.txt 50

sleep 1

./CWfuzzy_app data/NlearnB.txt data/NCerrorB.txt data/NtestB.txt 100

sleep 1

./CWfuzzy_app data/NlearnB.txt data/NCerrorB.txt data/NtestB.txt 200

sleep 1

./CWfuzzy_app data/NlearnB.txt data/NCerrorB.txt data/NtestB.txt 500

sleep 1

./CWfuzzy_app data/NlearnB.txt data/NCerrorB.txt data/NtestB.txt 1000

sleep 1
