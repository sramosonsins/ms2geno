/*modification of the code 'sample_stats' of R.R. Hudson (ms software) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MS2GENO  "\nms2geno: Convert ms to genotype file" \
"\nversion 20200415"

long int maxsites = 1000000 ;

char ** cmatrix(long int nsam,long int len);
void biggerlist(long int nsam, unsigned long nmax, char **list );
void usage(void);

int main(int argc, char *argv[])
{
    long int nsam, i, site, howmany  ;
    char **list, line[1001], slashline[1001]  ;
    FILE *pfin ;
    double *posit   ;
    long int   segsites, count  , nadv, probflag  ;
    double prob ;
    char dum[20], astr[100] ;
    long int segsub( long int nsam, long int segsites, char **list ) ;
    long int chrom_size;
    char file_in[1024];
    int nalleles;
    // arg = 1;
    
    //printf(MS2GENO);
    //printf("\n\nms2geno ");
    //while(arg < argc) {
    //    printf("%s ",argv[arg]);
    //    arg++;
    //}
    //printf("\n");
    
    if(argc < 4) {
        usage();
        exit(1);
    }
    
    //collect arguments:
    chrom_size = atol(argv[1]);
    nsam = atol(argv[2]);
    howmany = atol(argv[3]);
    
    if(argc == 5) {
        strcpy( file_in, argv[4]);
        if (!(pfin = fopen(file_in,"r"))) {
            printf("Error reading the input file %s\n",file_in);
            usage();
            exit(1);
        }
    }
    else  pfin = stdin ;

    /* read in first two lines of output  (parameters and seed) */
    fgets( line, 1000, pfin);
    if(*line != '/') {
        sscanf(line," %s  %ld %ld", dum,  &nsam, &howmany);
        fgets( line, 1000, pfin);
        if( argc > 1 ) {
            nadv = atoi( line ); //argv[1] ) ;
        }
    }

    list = cmatrix(nsam,maxsites+1);
    posit = (double *)malloc( maxsites*sizeof( double ) ) ;

    printf("Chr Pos ");
    for( i = 0; i < nsam/2; i++ ) printf("IND%ld ",i+1);
    printf("\n");
    
    count=0;
    probflag = 0 ;
    while( howmany-count++ ) {
        /* read in a sample */
        do {
            if( fgets( line, 1000, pfin) == NULL ){
                exit(0);
            }
            if( line[0] == '/' )  strcpy(slashline,line+2);
        } while ( (line[0] != 's') && (line[0] != 'p' ) ) ;

        if( line[0] == 'p'){
            sscanf( line, "  prob: %lf", &prob );
            probflag = 1 ;
            if( fgets( line, 1000, pfin) == NULL ){
                exit(0);
            }
        }
        sscanf( line, "  segsites: %ld", &segsites );
        if( segsites >= maxsites){
            maxsites = segsites + 10 ;
            posit = (double *)realloc( posit, maxsites*sizeof( double) ) ;
            biggerlist(nsam,maxsites, list) ;
        }
        if( segsites > 0) {
            fscanf(pfin," %s", astr);
            for( i=0; i<segsites ; i++) fscanf(pfin," %lf",posit+i) ;
            for( i=0; i<nsam;i++) fscanf(pfin," %s", list[i] );
        }
        
        for( site = 0; site < segsites; site++ ) {
            printf("%ld %.0f ",count,(posit[site]*chrom_size));
            for( i = 0; i < nsam; i += 2 ) {
                nalleles = (list[i][site]-48) + (list[i+1][site]-48);
                printf("%d ",nalleles);
            }
            printf("\n");
        }
    }
    printf("\n");
}

/* allocates space for gametes (character strings) */
char ** cmatrix(long int nsam,long int len)
{
    long int i;
    char **m;
    if( ! ( m = (char **) malloc( (unsigned)( nsam*sizeof( char* )) ) ) )
    perror("alloc error in cmatrix") ;
    for( i=0; i<nsam; i++) {
        if( ! ( m[i] = (char *) malloc( (unsigned) (len*sizeof( char )) )))
        perror("alloc error in cmatric. 2");
    }
    return( m );
}

void biggerlist(long int nsam, unsigned long nmax, char **list )
{
    long int i;
    maxsites = nmax  ;
    for( i=0; i<nsam; i++){
        list[i] = (char *)realloc( list[i],maxsites*sizeof(char) ) ;
        if( list[i] == NULL ) perror( "realloc error. bigger");
    }
}

void usage(void)
{
    printf(MS2GENO);
    printf("\n\nUsage:");
    printf("\nms2geno [chrom length] [nsam (2xind)] [iterations] [name_file OR stdin]");
    printf("\nResults to stdout");
    printf("\n\n");
}

