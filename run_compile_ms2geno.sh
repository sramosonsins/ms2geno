#run example:
set -x

cd ./source
gcc *.c -lm -o ../bin/ms2geno -O3 -Wall

cd ..

