#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

int tamanho=0;

struct ar{
	int valor;
	ar *pp;
	ar *aa;
	ar *cima;
};

int profAA=0;
int profPP=0;
int profTT;
int exec=0;


void preOrdem(ar * atual){
	system("cls");
	printf("\nExecuÁ„o na prÈ ordem\n 1 - Anterior\n 2 - PrÛximo\n 3 - Sair");
	
}


int profundidade (ar * atual) {
	ar *temp;
	ar *esq = NULL;
	ar *dir = NULL;
	temp = atual;
	int caa=0;
	int cpp=0;

	if(exec==0){
		if(atual->aa !=NULL){
		atual = atual->aa;
		while(atual->aa !=NULL){
			atual = atual->aa;
			caa++;
		}
		esq = atual;
		atual = temp;
		atual = atual->aa;
		
		while(atual->pp !=NULL){
			atual = atual->pp;
			cpp++;
		}
		dir = atual;
		atual = temp;

		if(cpp>caa){
			while(dir->cima !=NULL){
			dir = dir->cima;
				profAA++;
			}

		}else if(cpp<caa){
			while(esq->cima !=NULL){
			esq = esq->cima;
				profAA++;
			}
		
		
		}else{
			while(esq->cima !=NULL){
			esq = esq->cima;
				profAA++;
			}
		}
		caa=0;
		cpp=0;
		exec++;
		profundidade(temp);
		}else{
			exec++;
			profundidade(temp);
		}
		return 0;
	}else if(exec==1){
		if(atual->pp !=NULL){
		atual = atual->pp;
		while(atual->aa !=NULL){
			atual = atual->aa;
			caa++;
		}
		esq = atual;
		atual = temp;
		atual = atual->pp;
		
		while(atual->pp !=NULL){
			atual = atual->pp;
			cpp++;
		}
		dir = atual;
		atual = temp;

		if(cpp>caa){
			while(dir->cima !=NULL){
			dir = dir->cima;
				profPP++;
			}

		}else if(cpp<caa){
			while(esq->cima !=NULL){
			esq = esq->cima;
				profPP++;
			}
		
		
		}else{
			while(esq->cima !=NULL){
			esq = esq->cima;
				profPP++;
			}
		}
		caa=0;
		cpp=0;
		exec++;
		profundidade(temp);
		}else{
			exec++;
			profundidade(temp);
		}
		return 0;
	}else if(exec==2){
		if(profPP>profAA){
			profTT = profPP;
		}else if(profPP<profAA){
			profTT = profAA;
		}else if(profPP==profAA){
			profTT = profAA;
		}
		return 0;
	}
	

 
}
  



void inserirNull(ar **atual){
	ar *novo;
	int val;
	
	printf("\nDigite um valor inteiro:");
	scanf("%d", &val);

	novo = ((ar*)malloc(sizeof(ar)));
	novo->valor = val;
	novo->cima = NULL;
	novo->pp = NULL;
	novo->aa = NULL;
	*atual = novo; // Define como atual
	
	tamanho++;
	
	printf("\nValor inserido!\n\n");
	system("pause");
}

int inserir(ar **atual){
	ar *novo;
	ar *atualaux; 
	int val;
	
	printf("\nDigite um valor inteiro:");
	scanf("%d", &val);

	while((*atual)->cima != NULL){
		*atual = (*atual)->cima;
	}
	
	novo = ((ar*)malloc(sizeof(ar)));
	novo->valor = val;

	while(*atual != NULL){	
		if((*atual)->valor > val){	
			atualaux = *atual;
  			*atual = (*atual)->aa;
		} else if((*atual)->valor < val){
			atualaux = *atual;
			*atual = (*atual)->pp;
		} else if((*atual)->valor == val){
			printf("\nValor existente!\n");
			system("pause");
			return 0;
		}
	}
		
	if(atualaux->valor > val){
		atualaux->aa = novo;
	} else if(atualaux->valor < val){
		atualaux->pp = novo;
	}
	novo->cima = atualaux;
	novo->aa = NULL;
	novo->pp = NULL;
	
	*atual = novo;

	tamanho++;
	
	printf("\nValor inserido!\n\n");
	system("pause");
}



void removeFolha(ar **atual){
	ar *aux;
	aux = *atual;
	
	if(aux->valor > aux->cima->valor){
		aux->cima->pp = NULL;
	} else {
		aux->cima->aa = NULL;
	}
	
	*atual = aux->cima;
	free(aux);
	tamanho--;
}

void removerGalho(ar **atual){
	ar *aux;
	ar *raiz;
	
	raiz = *atual;
	
	while(raiz->cima != NULL){
		raiz = raiz->cima;
	}
	
	aux = *atual;
	
	if(aux->valor > raiz->valor){
		if(aux->pp == NULL){
			aux->cima->pp = aux->aa;
			aux->aa->cima = aux->cima;
		} else {
			aux->cima->pp = aux->pp;
			aux->pp->cima = aux->cima;
		}
	} else if(aux->valor < raiz->valor){
		if(aux->pp == NULL){
			aux->cima->aa = aux->aa;
			aux->aa->cima = aux->cima;	
		} else {
			aux->cima->aa = aux->pp;
			aux->pp->cima = aux->cima;
		}
	}
		
	*atual = aux->cima;
	free(aux);
	tamanho--;
}

void removerNo(ar **atual){
	ar *aux;
	ar *trocar;
	ar *auxatual;
	int m1;
	int m2;
	int i = 0;
	
	m1 = 0;
	m2 = 0;
	
	trocar = *atual;
	aux = *atual;
	auxatual = *atual;	

	if(aux->pp != NULL){
		auxatual = aux;
		aux = aux->pp;
		i = 1;
		while(aux->aa != NULL){
			auxatual = aux;
			aux = aux->aa;
			i = 0;
		}
		m1++; 
	} else {
		auxatual = aux;
		aux = aux->aa;
		i = 1;
		while(aux->pp != NULL){
			auxatual = aux;
			aux = aux->pp;
			i = 0;
		}		
		m2++;
	}

		if(m1 != 0){
			if(i == 1){
				if(aux->pp == NULL){ 
					trocar->valor = aux->valor;
					aux->cima->pp = NULL;
				} else if(aux->pp != NULL){ 
					trocar->valor = aux->valor;
					aux->cima->pp = aux->pp;
					aux->pp->cima = aux->cima;
				}
			}else{
				if(aux->pp == NULL){ 
					trocar->valor = aux->valor;
					aux->cima->aa = NULL;
				} else if(aux->pp != NULL){
					trocar->valor = aux->valor;
					aux->cima->aa = aux->pp;
					aux->pp->cima = aux->cima;
				}
			}
		}else if(m2 != 0){
			if(i == 1){
				if(aux->aa == NULL){ 
					trocar->valor = aux->valor;
					aux->cima->aa = NULL;
				} else if(aux->aa != NULL){
					trocar->valor = aux->valor;
					aux->cima->aa = aux->aa;
					aux->aa->cima = aux->cima;
				}
			}else {
				if(aux->aa == NULL){ 
					trocar->valor = aux->valor;
					aux->cima->pp = NULL;
				} else if(aux->aa != NULL){ 
					trocar->valor = aux->valor;
					aux->cima->pp = aux->aa;
					aux->aa->cima = aux->cima;
				}
			}
	}
		free(aux);
		tamanho--;
}

int main(){
	ar *atual = NULL;
	ar *raiz = NULL;
	
	
	
	
	int i = 0;
	int op;
	
	while(1){
	
		system("cls");
		setlocale(LC_ALL,"Portuguese");
		printf("Estrutura de Dados - ¡rvore B\n");
		
		printf("\n1 - Inserir\n2 - Remover\n3 - Valor Acima\n4 - Esquerda\n5 - Direita\n6 - Profundidade\n7 - PrÈ- Ordem\n8 - PÛs-Ordem\n9 - Ordem\n0 - Sair \n\n");
		

		if(tamanho==0){
			printf("¡rvore vazia!\nOpÁ„o:");
		}else{
			
			printf("Valor atual:%i\n",atual->valor);
			printf("OpÁ„o:");
		}
		scanf("%d", &op);
		
	
		
		if(op == 1){
			if(tamanho == 0){
				inserirNull(&atual);
			} else {
				inserir(&atual);
			}	
		}else if(op == 2){
			if(tamanho == 0){
				printf("\n¡rvore vazia!\n\n");
				system("pause");
				
			} else {
				if(atual->aa == NULL && atual->pp == NULL && atual->cima != NULL){
					removeFolha(&atual);
					
				} else if(atual->aa != NULL && atual->pp == NULL && atual->cima != NULL){
					removerGalho(&atual);
						
				}else if(atual->aa == NULL && atual->pp != NULL && atual->cima != NULL){	
					removerGalho(&atual);;
							
				} else if(atual->aa != NULL && atual->pp != NULL && atual->cima != NULL){
					removerNo(&atual);	
					
				} 
				printf("\nValor removido!\n");
				system("pause");
			}
		}else if(op == 3){
			if(atual->cima != NULL && atual->valor != NULL){
				atual = atual->cima;
			} else {
				printf("\nRaiz!\n");
				system("pause");	
			}
		}else if(op == 4){	
			if(atual->aa != NULL){
				atual = atual->aa;
			} else {
				printf("\nEsquerda vazia!\n");
				system("pause");	
			}
			
		}else if(op == 5){	
			if(atual->pp != NULL){			
				atual = atual->pp;
			}else{
				printf("\n Direita vazia!\n");
				system("pause");	
			}
				
		}else if(op == 6){
			exec=0;
			profAA=0;
			profPP=0;
			
			if(tamanho!=0){
				while(atual->cima != NULL){
					atual = atual->cima;
					
				}
				
				if(atual->cima == NULL){
					profundidade(atual);
					printf("\nA profundidade da ·rvore È de %i\n",profTT);
					profTT=0;
				}
				
			}else if(tamanho == 0){
					printf("\n¡rvore vazia\n");
			}
		
			
			system("pause");
			
		}else if(op == 7){
			
		}else if(op == 8){
			
		}else if(op == 9){
			
		}else if(op == 0){
			printf("\nFinalizando");
			for(i=0;i<3;i++){
			Sleep(600);
			printf(".");
			}
			break;
			
		}else{
			printf("\nOpcao invalida, tente novamente!\n");
			system("pause");
		}
	}
	
	return 0;
}
