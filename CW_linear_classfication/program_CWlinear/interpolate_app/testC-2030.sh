#!/bin/sh
#testC on 20-30 confidence

./interpolate_app data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 10

sleep 1

./interpolate_app data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 20

sleep 1

./interpolate_app data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 50

sleep 1

./interpolate_app data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 100

sleep 1

./interpolate_app data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 200

sleep 1

./interpolate_app data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 500

sleep 1

./interpolate_app data/NlearnC.txt data/N20_30_C.txt data/Ntest10-30C.txt 1000