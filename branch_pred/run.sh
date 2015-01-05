cp $1.h predictor.h
cp $1.c predictor.c
make clean
make
cp predictor $1
