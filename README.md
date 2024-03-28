# ms2geno version 20200615

###Converting ms files into genotype files (useful to generate input file for Rsbki)

Sebastian E. Ramos-Onsins

#### Usage:
	ms2geno [chrom length] [nsam (2xind)] [iterations] [name_file OR stdin]

Results are sent to stdout

#### Compile:

	cd ./source
	gcc *.c -lm -o ../bin/ms2geno -O3 -Wall

#### Example:

	../bin/ms2geno 1000000 100 10 ../example/ms_example.txt > ../results/ms_example.geno.txt
	../bin/ms2geno 1000000 1000 1 ../example/slim.output_s10.p2.txt > ../results/slim.output_s10.p2.geno.txt

Examples of input and output files are included in the package.