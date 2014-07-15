#!/bin/sh
#testA on 50-80 confidence

./CWfuzzy_app data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 10

sleep 1

./CWfuzzy_app data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 20

sleep 1

./CWfuzzy_app data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 50

sleep 1

./CWfuzzy_app data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 100

sleep 1

./CWfuzzy_app data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 200

sleep 1

./CWfuzzy_app data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 500

sleep 1

./CWfuzzy_app data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 1000

sleep 1