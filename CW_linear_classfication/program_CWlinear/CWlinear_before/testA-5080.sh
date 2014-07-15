#!/bin/sh
#testA on 50-80 confidence

./CWlinear data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 10

sleep 1

./CWlinear data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 20

sleep 1

./CWlinear data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 50

sleep 1

./CWlinear data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 100

sleep 1

./CWlinear data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 200

sleep 1

./CWlinear data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 500

sleep 1

./CWlinear data/NlearnA.txt data/NCerrorA.txt data/NtestA.txt 1000