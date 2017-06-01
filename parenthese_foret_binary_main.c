#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"

#include "depot_catalon_shell.c"


#define MaxNumSom 100 //limiter nombre de sommets qu'on peut inserer
#define NonArc 8888
#define Racine 0  //il y a un point dans la racine
#define ArcFils1 1  //il y a un arc à gauche
#define ArcFils2 2
#define bug printf(" i'am here %d \n",__LINE__);

typedef struct TREE{
	int arc[MaxNumSom][MaxNumSom];
	int n_sommet;
}Mytree;


int pt=1;


//traduire les forêts aux arbres binaires
void binary(Mytree *myt,char **strings,char **color){
    int *b;
	int n2=10000;
    b=(int*)malloc(sizeof(int*)*n2+1);
	int pt1=pt;
	int pere_tmp;	
	
    int i,j,k=0,m,n,m_tmp;
    for(i=0;i<(myt->n_sommet);i++){
        for(j=0;j<(myt->n_sommet);j++){
            if((myt->arc[i][j])==Racine){ //chercher tous les points dans la racine
                b[k]=j;
                k+=1;
            }
        }
    }
    printf("\nArbre binaire:\n");
    printf("%d est le racine\n",b[0]);
    if(k>1){
        for(i=1;i<=k-1;i++){
            printf("%d est le fils droit de %d\n",b[i],b[i-1]); //b[i] et b[i-1] sont dans la racine de forêt, on les lie pour construire la brache à droit
		sprintf((color[pt]),"%d [style=\"filled\",fillcolor=\"red\"]",b[i]);
		sprintf((strings[pt]),"%d -- %d",b[i-1],b[i]);
		//printf("color[%d] %s strings[%d] %s\n",pt,color[pt],pt,strings[pt]);
		pt++;
        }
    }
    m=k; //apres finir à parcourir les noeds dans la racine ,on continue dépôter les datas à partir de l'index 'k'
    for(i=0;i<(myt->n_sommet);i++){
        
        for(j=0;j<(myt->n_sommet);j++){
           if(myt->arc[i][j]==ArcFils1){ 
              b[m]=j;
			pere_tmp=j;
		    printf("%d est le fils gauche de %d\n",b[m],i);

		    sprintf((color[pt]),"%d [style=\"filled\",fillcolor=\"green\"]",b[m]);
	         sprintf((strings[pt]),"%d -- %d",i,b[m]);
		    //printf("color[%d] %s strings[%d] %s\n",pt,color[pt],pt,strings[pt]);
		    pt++;
              m+=1;
		 }
	
		  if(myt->arc[i][j]==ArcFils2){ //il y a un seul fils à droit
			b[m]=j;
			
			printf("%d est le fils droit de %d\n",b[m],pere_tmp);
	
			sprintf((color[pt]),"%d [style=\"filled\",fillcolor=\"red\"]",b[m]);
			sprintf((strings[pt]),"%d -- %d",pere_tmp,b[m]);
			//printf("color[%d] %s strings[%d] %s\n",pt,color[pt],pt,strings[pt]);
			pere_tmp=j;
			pt++;
			m+=1;		
		  }	    
        }   
    }
	for(i=pt1;i<pt;i++){
		//printf("%s %s\n",strings[i],color[i]);
	}printf("==================================\n");
	free(b);
}


//traduire des parentheses aux forêts avec des numeros de noeuds 
int forets(Mytree *myt,char *a,int n,char **strings,char **color){
    int i=1,j=0;
    int num_sommet=0;
    int compteur_p=0; //a[1]=='(',je compte en 1
  
    int *tmp;
    tmp=(int*)malloc(n*sizeof(int*)+1);

    while(i<=2*n){
        if(a[i]=='('&&i==1){  // son fils à gauche //le 1er element 'a[i-1]' est a[1] 
		     
			compteur_p=1;
		      //printf("compteur1: %d \n",compteur_p);  
			tmp[compteur_p-1]=num_sommet-1;
			//printf("num1 %d tmp[%d] %d\n",num_sommet-1,compteur_p-1,tmp[compteur_p-1]);
			
			if(tmp[compteur_p-1]==-1){
				
		       	printf("# %d est dans la racine #\n",num_sommet);
				myt->arc[num_sommet][num_sommet]=Racine;     
			}
			compteur_p++;
			num_sommet++;

			  //printf("----------------\n");
        }else if(a[i]==')'){ 
		
	     compteur_p--;

		//printf("compteur2: %d\n",compteur_p);
		//printf("----------------\n");
	   }else if(a[i-1]==')'&&a[i]=='('){
				//printf("compteur %d\n",(compteur_p));
				//printf("num %d tmp[%d] %d\n",num_sommet-1,compteur_p-1,tmp[compteur_p-1]);
				if(compteur_p-1==0){
					printf("# %d est dans la racine #\n",num_sommet);
					myt->arc[num_sommet][num_sommet]=Racine;  
				}else{
					printf("# %d est un autre fils de %d #\n",num_sommet,tmp[compteur_p-1]);	
					myt->arc[tmp[compteur_p-1]][num_sommet]=ArcFils2;
					//printf("num %d tmp[%d] %d\n",num_sommet-1,compteur_p-1,tmp[compteur_p-1]);
				}
				compteur_p++;
				//printf("compteur3: %d \n",compteur_p);
		       num_sommet++;
		       //printf("----------------\n");
	
		}else if(a[i-1]=='('&&a[i]=='(') {
			tmp[compteur_p-1]=num_sommet-1;
			//printf("num3 %d tmp[%d] %d\n",num_sommet-1,compteur_p-1,tmp[compteur_p-1]);

			printf("# %d est le 1er fils de %d #\n",num_sommet,tmp[compteur_p-1]);	
			myt->arc[tmp[compteur_p-1]][num_sommet]=ArcFils1;


			compteur_p++;
			//printf("compteur4: %d \n",compteur_p);
			  num_sommet++;
			 // printf("----------------\n");
		}
	   
    i++;
    }
	compteur_p-=1;
    printf(" ------------------\n ");
    printf("  compteur :%d \n",compteur_p);
    if(compteur_p!=0){
       return errno; //verifier si tous les parentheses sont bien fermes
    }else{
	printf(" pas d'erreurs\n");
    }
    printf(" ------------------\n");

    for(i=0;i<(myt->n_sommet);i++){
        for(j=0;j<(myt->n_sommet);j++){
            if(myt->arc[i][j]!=NonArc){
                printf("arc[%d][%d]:%d \n",i,j,myt->arc[i][j]);
            }
        }
    }
	free(tmp);
    binary(myt,strings,color);
}



// imprimer des parentheses
void print_p(char *a,int n,int nb_arbre){
    int i;
    printf("Tree %d: ",nb_arbre);
     for(i=1;i<=(2*n);i++){
         printf("%c",a[i]);
    }printf("\n");

}

//construire des arbres avec des parentheses
void recompose_p(Mytree *myt,char *a,int k,int n,int m,char **strings,char **color){
    int i,j,valide=0;
    for(k=1;k<=n;k++){
            a[(2*k)-1]='(';
            a[2*k]=')';
    }
    P2: if(a[m]=='('){
        for(k >m;k<=(2*n); k++){

           if( a[k]==')'){ valide=1;}
           else valide=0;
        }

        if (valide==1 ){
            print_p(a,n,nb_arbre++);
            for(i=0;i<(myt->n_sommet);i++){
                for(j=0;j<(myt->n_sommet);j++){
                myt->arc[i][j]=NonArc;
                }
            }
            printf("forets:\n");
            forets(myt,a,n,strings,color);
            printf("====================================\n");
        }
    };

    a[m]=')';
    if(a[m-1]==')'){
        a[m-1]='(';
        m=m-1;
        goto P2;
    }
    else{
        j=m-1;
        k=2*n-1;
        while(a[j]=='('){
            a[j]=')';
            a[k]='(';
            j=j-1;
            k=k-2;
        }
    }
    if(j==0){
        return;
    }else{
    a[j]='(';
    m=2*n-1;
    goto P2;
    }

}


int main(){
	int m,n,k=0;
    Mytree myt;

    char *a;
    a=(char*)malloc(n*sizeof(char*));
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
    recompose_p(&myt,a,k,n,m,strings,color);
	
	nombre_catalan=Catalan(n);
	Catalan(n);
	printf("Le nombre de catalan est: %d \n",nombre_catalan);
	stock(strings,color,n);
	
	shell(nombre_catalan);

   //printf("%d \n",m);
    free(a);
	free(strings);
	free(color);
	return 0;
}

