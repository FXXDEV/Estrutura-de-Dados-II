#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX 10

int mat[MAX][MAX];
int vet[MAX];
int val=0;

void percorre(int val);

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	printf("\nDigite o número de vertices\n");
	scanf("%i",&val);
	
	printf("\nDigite a matriz de adjacencia do grafo\n");
	if(val>MAX){
		printf("Por favor, digite valores menores que 10\n");
		system("pause");
		main();
		
	}else{
		
	 for(int i=0;i<val;i++){
	 	 for(int j=0;j<val;j++){
	 	 	if(i==j){
				mat[i][j]=0;
			}else{
				printf("Incidência de i:%d em j:%d? ", i+1, j+1);
				scanf("%i",&mat[i][j]);	
			}
	 	 		 
		  }
           
	 }
	 
	 for(int i=0; i<val; i++){
	 	vet[i]=0;
	 }
      
     percorre(0);
      
    printf("\nVetor:");
	for(int i=0;i<val;i++){
		printf("%i ", vet[i]);
	}
	
	}
	
	return 0;

}

void percorre(int val){
	
	printf("%i",val);
	
	vet[val]=1;
	
	for(int j=0;j<val;j++){
		 if(!vet[j]&&mat[val][j]==1){
		 	percorre(j);
		 }
    
	}
      
	
}
