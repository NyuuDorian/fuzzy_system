#!/bin/sh
#testC on 50-80 confidence

./CWfuzzy_app data/NlearnC.txt data/NCerrorC.txt data/NtestC.txt 10

sleep 1

./CWfuzzy_app data/NlearnC.txt data/NCerrorC.txt data/NtestC.txt 20

sleep 1

./CWfuzzy_app data/NlearnC.txt data/NCerrorC.txt data/NtestC.txt 50

sleep 1

./CWfuzzy_app data/NlearnC.txt data/NCerrorC.txt data/NtestC.txt 100

sleep 1

./CWfuzzy_app data/NlearnC.txt data/NCerrorC.txt data/NtestC.txt 200

sleep 1

./CWfuzzy_app data/NlearnC.txt data/NCerrorC.txt data/NtestC.txt 500

sleep 1

./CWfuzzy_app data/NlearnC.txt data/NCerrorC.txt data/NtestC.txt 1000

sleep 1