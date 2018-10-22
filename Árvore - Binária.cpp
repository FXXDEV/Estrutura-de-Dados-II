#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

struct ar{
	int valor;
	ar *pp;
	ar *aa;
	ar *cima;
};

int tamanho=0;
int profAA=0;
int profPP=0;
int profTT;
int exec=0;
int execP=0;
int cont=0;
int vet[50];
int tag = 1;
int count = 0; 
bool profTTeste = false;

void percorre_dir(ar *atual){//percorrer direita
	ar *aux;
	aux = atual;
	if(aux != NULL){
		count++;
		if(profTTeste == false){
			printf("%i ", aux->valor);
		}
		percorre_dir(aux->aa);
	} 
	if(count > profTT){
		profTT = count;
	}
	aux = atual;
	if(aux !=NULL){
		percorre_dir(aux->pp);
		count--;
	} 
}

void percorre_esq(ar *atual){//percorrer esquerda
	ar *aux;
	aux = atual;
	if(aux != NULL){
		percorre_esq(aux->aa);
		printf("%i ", aux->valor);
	} 
	aux = atual;
	if(aux !=NULL){
		percorre_esq(aux->pp);
	} 
}


ar* visitar_raiz(ar *atual){
	ar *aux;
	ar *raiz;

	raiz = atual;
	
	while(raiz->cima != NULL){
		raiz = raiz->cima;
	}
	
	return raiz;
}



int profundidade(ar *atual){
	profTT = 0;
	profTTeste = true;
	
	if(tamanho == 0){
		profTTeste = false;
		return profTT;
	} else {
		ar *aux;
	
		aux = visitar_raiz(atual);
		count = 0;
		
		percorre_dir(aux->aa); // Percorrer Esquerda
		percorre_dir(aux->pp); // Percorrer Direita
	
		profTTeste = false;
		return profTT;
	}
}


int altura(ar* atual){
	 if (atual == NULL) {
       return 0;
   	 } else {
   	
   		int profAA = altura(atual->aa);
   		int profPP = altura(atual->pp);
   		
   		if (profAA > profPP) {
   			return 1 + profAA;
		} else {
			return 1 + profPP;
		}
   }
}

int desbalanceado(ar** atual) {
	ar * aux;
	aux = *atual;

	if (atual == NULL) {
		return 0;
	} else {
		return ( altura(aux->pp) - altura(aux->aa));
	}
}


int preOrdem(ar *atual){
	ar *temp;
	temp=atual;
    if(temp != NULL){
    	vet[cont]=temp->valor;
    	cont++;
        preOrdem(atual->aa);
        preOrdem(atual->pp);
    }
    return 0;
}

int posOrdem(ar *atual){
	ar *temp;
	temp=atual;
	
	if(temp != NULL){
        posOrdem(atual->aa);
        posOrdem(atual->pp);
        vet[cont]=temp->valor;
    	cont++;
    }
	return 0;
}

int emOrdem(ar *atual){
	ar *temp;
	temp=atual;
	if(temp!=NULL){
		emOrdem(temp->aa);
		vet[cont] = temp->valor;
		cont++;
		emOrdem(temp->pp);
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
		printf("Estrutura de Dados - Árvore B\n");
		
		printf("\n1 - Inserir\n2 - Remover\n3 - Valor Acima\n4 - Esquerda\n5 - Direita\n6 - Profundidade\n7 - Pré- Ordem\n8 - Pós-Ordem\n9 - Em Ordem\n10 - Desbalanceamento \n0 - Sair \n\n");
		

		if(tamanho==0){
			printf("Árvore vazia!\nOpção:");
		}else{
			
			printf("Valor atual:%i\n",atual->valor);
			printf("Opção:");
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
				printf("\nÁrvore vazia!\n\n");
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
					printf("\nA profundidade da árvore é de %i\n",profTT);
					profTT=0;
				}
				
			}else if(tamanho == 0){
					printf("\nÁrvore vazia\n");
			}
		
			
			system("pause");
			
		}else if(op == 7){
			cont=0;
			
			
			if(tamanho!=0){
				while(atual->cima != NULL){
					atual = atual->cima;
					
				}
				
				if(atual->cima == NULL){
					preOrdem(atual);
					printf("Valores na pré ordem\n");
					for(int i=0;i<cont;i++){
						printf("[%i] ",vet[i]);
				
					};
					printf("\n");
				}
				
				}else if(tamanho == 0){
					printf("\nÁrvore vazia\n");
				}
		
			system("pause");
			
		}else if(op == 8){
			cont=0;
			
			
			if(tamanho!=0){
				while(atual->cima != NULL){
					atual = atual->cima;
					
				}
				
				if(atual->cima == NULL){
					posOrdem(atual);
					printf("Valores na pós ordem\n");
					for(int i=0;i<cont;i++){
						printf("[%i] ",vet[i]);
				
					};
					printf("\n");
				}
				
				}else if(tamanho == 0){
					printf("\nÁrvore vazia\n");
				}
		
			system("pause");
			
		}else if(op == 9){
			cont=0;
			
			
			if(tamanho!=0){
				while(atual->cima != NULL){
					atual = atual->cima;
					
				}
				
				if(atual->cima == NULL){
				
					emOrdem(atual);
					printf("Valores na pós ordem\n");
					for(int i=0;i<cont;i++){
						printf("[%i] ",vet[i]);
				
					};
					printf("\n");
				}
				
				}else if(tamanho == 0){
					printf("\nÁrvore vazia\n");
				}
		
			system("pause");
			
		}else if(op==10){
				if(tamanho!=0){
				while(atual->cima != NULL){
					atual = atual->cima;
					
				}
			printf("\nElemento desbalanceado por:%i unidades\n", desbalanceado(&atual));	
			}else{
				printf("\nInsira elementos");
			}
			
			system("pause");
			
		
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
