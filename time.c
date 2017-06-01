#include "stdio.h"
#include "stdlib.h"
#include "errno.h" 
#include "time.h"
#include "parenthese_foret_binary_main.c"

int main(){
	int m,n,k=0;
    Mytree myt;
	clock_t start, finish;  
   double  duration; 
    char *a;
    a=(char*)malloc(10000*sizeof(char*)+1);
	int nombre_catalan;

    printf("Taper le nombre des sommets:\n");
    scanf("%d",&n);

    myt.n_sommet=n;

	int n1=10000,n2=100,i;
     char **strings;
	strings=malloc(sizeof(char*)*n1+1);
	for (i = 0; i < n1; i++){
		strings[i]=malloc(sizeof(char)*n2+1);
	}

     char **color;
	color=malloc(sizeof(char*)*n1+1);
	for (i = 0; i < n1; i++){
		color[i]=malloc(sizeof(char)*n2+1);
	}

    a[0]=')';
    m=(2*n)-1;

    printf("les  parentheses:\n");
   
   start = clock();  
   recompose_p(&myt,a,k,n,m,strings,color);
   finish = clock();  
   duration = (double)(finish - start) / CLOCKS_PER_SEC;  
   printf( "%f seconds\n", duration );  
   system("pause");  
    
	/*
	nombre_catalan=Catalan(n);
	Catalan(n);
	printf("Le nombre de catalan est: %d \n",nombre_catalan);
	stock(strings,color,n);
	
	shell(nombre_catalan);*/

  
        free(a);
	free(strings);
	free(color);
	return 0;
}
