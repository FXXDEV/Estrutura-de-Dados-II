#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#define MAX 10


struct stGrafo{
	int cor = 0;
	int tag = 0;
	int tamanho =0;
	int incidencia;
};

int mat = 0;
struct stGrafo grafo[MAX][MAX];
int maxGrafo(stGrafo[MAX][MAX]);


int main(){	
  	setlocale(LC_ALL, "Portuguese");
	
	int cor=0,grafMax=0,corMax=0;
	int mat=0;
	
	printf("Digite o valor do para o tamanho da matriz X,Y:");
	scanf("%d",&mat);
	
	if(mat>MAX){
		printf("Por favor, digite valores menores que 10\n");
		system("pause");
		main();
	}else{
		
		for(int i=0;i<mat;i++){	
			for(int j=0;j<mat;j++){
				printf("Incidência de i:%i em j:%i? ", i+1, j+1);
				scanf("%i", &grafo[i][j].incidencia);
				if(grafo[i][j].incidencia>0){
					grafo[i][0].tamanho = (grafo[i][0].tamanho)+1;
				}
	
			}
	
		}
		system("cls");
		for(int i=0;i<mat;i++){
			printf("\nNó %d do grafo tem incidências: ", i+1);
			for(int j=0;j<mat;j++){
				printf("%d ", grafo[i][j].incidencia);
			}
			printf("\n");
		}
		
		printf("\nMaior inciência: %d\n\n", maxGrafo(grafo));
	
			
		for(int i=0;i<mat;i++){
			grafMax = maxGrafo(grafo);
			
			for(int j=0;j<mat;j++){
				if((grafo[grafMax][0].cor==grafo[j][0].cor)&&(grafo[grafMax][j].incidencia>0)){
					cor++;
				
				}
			}
			grafo[grafMax][0].cor = cor;
			
			if(cor > corMax){
				corMax=cor;
			}
			cor=0;
		}
		
	printf("\nQuantidade de cores necessárias para que não haja cores identicas no mesmo nó é:%d\n\n", corMax);

	}
	
		
	return 0;
}

int maxGrafo(stGrafo[MAX][MAX]){
	
	int max=0,i; 
	
	for(i=0;i<MAX;i++){
		if(((grafo[i][0].tamanho)>max)&&(grafo[i][0].tag==0)){
			max = i+1;
			grafo[i][0].tag = 1;
		}
	}
	return max;

}



