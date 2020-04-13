#run example:
set -x

cd ./source
gcc *.c -lm -o ../bin/ms2geno -O3 -Wall

time ../bin/ms2geno 1000000 100 10 ../example/ms_example.txt > ../results/ms_example.geno.txt
time ../bin/ms2geno 1000000 1000 1 ../example/slim.output_s10.p2.txt > ../results/slim.output_s10.p2.geno.txt

cd ..

