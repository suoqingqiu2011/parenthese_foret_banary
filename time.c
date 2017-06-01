#include "stdio.h"
#include "stdlib.h"
#include "errno.h" 
#include "time.h"
#include "parenthese_foret_binary(modifier).c"

int main(){
	int m,n,k=0;
    Mytree myt;
	clock_t start, finish;  
   double  duration; 
    char *a;
    a=(char*)malloc(n*sizeof(char*));
	int nombre_catalan;

    printf("Taper le nombre des sommets:\n");
    scanf("%d",&n);

    myt.n_sommet=n;

	char strings[10000][100];
	char color[10000][100];

    a[0]=')';
    m=(2*n)-1;

    printf("les  parentheses:\n");
   
   start = clock();  
   recompose_p(&myt,a,k,n,m,strings,color);
   finish = clock();  
   duration = (double)(finish - start) / CLOCKS_PER_SEC;  
   printf( "%f seconds\n", duration );  
   system("pause");  
    
	
	nombre_catalan=Catalan(n);
	Catalan(n);
	printf("Le nombre de catalan est: %d \n",nombre_catalan);
	stock(strings,color,n);
	
	shell(nombre_catalan);

   //printf("%d \n",m); bug
    free(a);

	return 0;
}
