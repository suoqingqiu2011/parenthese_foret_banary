#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"

#define MaxNbfile 1000

int index1=1;
int index2=1;

int nb_arbre=0;
char file[MaxNbfile];

// depoter des donnees dans des fichiers .gv pour dessiner des graphes 
void stock(char **strings,char **color,int n){
	FILE *fp;
	int i,j;
	
	for(i=0;i<nb_arbre;i++){
		sprintf(file,"binarytree%d.gv",i);
		fp=fopen(file,"wa+");
	
		fprintf(fp,"graph G {\n\tnodesep=0.3;\n\tranksep=0.2;\n\tmargin=0.1;\n\tnode [shape=circle];\n\tedge [arrowsize=0.8];\n\t0;\n" );
			
			for(j=0;j<n-1;j++){		
				fprintf(fp,"\t%s;\n",color[index1+j]);
				//printf("fich %d index 1-- : %d\n",i,index1+j);
			}index1=(n-1)*(i+1)+1;
			//printf("index 1 : %d\n",index1);

			for(j=0;j<n-1;j++){		
				fprintf(fp,"\t%s;\n",strings[index2+j]);
				//printf("fich %d index 2 --: %d\n",i,index2+j);
			}index2=(n-1)*(i+1)+1;
			//printf("index 2 : %d\n",index2);
				
			
		fprintf(fp,"\n}");
	fclose(fp);	
	}
}

int  Catalan(int n){ 
	if(n==1) return 1; 
	else
	return Catalan(n-1)*2*(2*n-1)/(n+1); 
}

void shell(int nombre_catalan){
	int i;
	char shells[100];
	/*system("gcc arbre_parenthese.c -o arbre_parenthese");
	system("./arbre_parenthese");*/
	printf("le nombre des abres generes pour dessiner: %d\n",nombre_catalan);	
	for(i=0;i<nombre_catalan;i++){
		//sprintf(shells,"dot binarytree%d.gv|gvpr -c -f t.gv|neato -n -Tpng -o binarytree%d.png",i,i);
		sprintf(shells,"dot -Tgif binarytree%d.gv -o binarytree%d.gif",i,i);
		system(shells);

	}
}
