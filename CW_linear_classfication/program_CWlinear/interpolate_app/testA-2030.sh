#!/bin/sh
#testA on 20-30 confidence

./interpolate_app data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 10

sleep 1

./interpolate_app data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 20

sleep 1

./interpolate_app data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 50

sleep 1

./interpolate_app data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 100

sleep 1

./interpolate_app data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 200

sleep 1

./interpolate_app data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 500

sleep 1

./interpolate_app data/NlearnA.txt data/N20_30_A.txt data/Ntest10-30A.txt 1000

sleep 1
