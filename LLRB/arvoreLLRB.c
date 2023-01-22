#include <stdlib.h>
#include <stdio.h>

//=================================//
// Declaração da Struct node       //
//=================================//

// Adotaremos as cores 0 = preto e 1 = vermelho

typedef struct node{
	int prioridade;
	int cor;
	struct node *esq;
	struct node *dir;
}node;

//=================================//
// Funções Auxiliares              //
//=================================//

// Função TrocarCor
void aux_trocarCor(node *no){
	// Troca a cor do nó passado
	if (no->cor == 0){
		no->cor = 1;
	} else {
		no->cor = 0;
	}

	// Troca a cor do filho esquerdo, se ele existir.
	if (no->esq != NULL){
		if (no->esq->cor == 0){
			no->esq->cor = 1;
		} else {
			no->esq->cor = 0;
		}
	}

	// Troca a cor do filho direito, se ele existir.
	if (no->dir != NULL){
		if (no->dir->cor == 0){
			no->dir->cor = 1;
		} else {
			no->dir->cor = 0;
		}
	}
}

// Função retorna cor
int aux_cor(node *no){
	if(no == NULL){
		return 0;
	} else {
		return no->cor;
	}
}

//=================================//
// Funções de Rotação              //
//=================================//

node *rot_esq(node *no){
	node *aux = no->dir;
	no->dir = aux->esq;
	aux->esq = no;

	aux->cor = no->cor;
	no->cor = 1;

	return aux;
}

node *rot_dir(node *no){
	node *aux = no->esq;
	no->esq = aux->dir;
	aux->dir = no;

	aux->cor = no->cor;
	no->cor = 1; // p

	return aux;
}

//=================================//
// Funções de Balanceamento        //
//=================================//

node *mov_esqRed(node *no){
	aux_trocarCor(no);						// Recebe o nó e aplica a função de trocar cores nele.

	if(aux_cor(no->dir->esq) == 1){			// Se o filho a esquerda do direito é vermelho:
		no->dir = rot_dir(no->dir);			// Aplica a rotação direita no filho direito
		no = rot_esq(no);					// Aplica a rotação esquerda no pai
		aux_trocarCor(no);					// Aplica troca cor
	}

	return no;
}

node *mov_dirRed(node *no){
	aux_trocarCor(no);						// Recebe o nó e aplica a função de trocar cores nele.

	if(aux_cor(no->esq->esq) == 1){			// Se o filho a esquerda do filho esquerdo é vermelho:
		no = rot_dir(no);					// Aplica a rotação direira no pai
		aux_trocarCor(no);					// Aplica troca cor
	}

	return no;
}

node *mov_balancear(node *no){
	if(aux_cor(no->dir) == 1){				// Houve violação na regra especial do LLRB, onde o nó direito é vermelho!
		no = rot_esq(no);
	}
											// Caso abaixo é quando o filho da esquerda E o neto da esquerda são vermelhos.
	if((no->esq != NULL) && (aux_cor(no->esq) == 1) && (aux_cor(no->esq->esq) == 1)){
		no = rot_dir(no);
	}

	if((aux_cor(no->esq) == 1) && (aux_cor(no->dir)) == 1){
		aux_trocarCor(no);
	}

	return no;
}

//=================================//
// Funções de I/O                  //
//=================================//

node *io_criarArv(node *no, int prioridade){
    if(no == NULL){							// Caso nó seja NULL, criamos um novo NÓ.
		node *aux = (node*)malloc(sizeof(no));

		aux->prioridade = prioridade;
		aux->cor = 0;
		aux->esq = NULL;
		aux->dir = NULL;

		return aux;
	} else {
	    puts("Já existe raiz!");
	}
}

node *io_inserir(node *no, int prioridade){
	if(no == NULL){							// Caso nó seja NULL, criamos um novo NÓ.
		node *aux = (node*)malloc(sizeof(no));

		aux->prioridade = prioridade;
		aux->cor = 1;
		aux->esq = NULL;
		aux->dir = NULL;

		return aux;
	}

	// Percorrendo a árvore recursivamente
	if(prioridade < no->prioridade){
		no->esq = io_inserir(no->esq, prioridade);
	} else if (prioridade > no->prioridade){
		no->dir = io_inserir(no->dir, prioridade);
	}

	// Ajustes feitos recursivamente.
	if((aux_cor(no->dir) == 1) && (aux_cor(no->esq) == 0)){
		no = rot_esq(no);
	}

	if((aux_cor(no->esq) == 1) && (aux_cor(no->esq->esq) == 1)){
		no = rot_dir(no);
	}

	if((aux_cor(no->esq) == 1) && (aux_cor(no->dir) == 1)){
		aux_trocarCor(no);
	}

	return no;

}

node *io_removerMenor(node *raiz){
	if(raiz->esq == NULL){
		free(raiz);
		return NULL;
	}

	if((aux_cor(raiz->esq) == 0) && (aux_cor(raiz->esq->esq) == 0)){
		raiz = mov_esqRed(raiz);
	}

	raiz->esq = io_removerMenor(raiz->esq);
	return mov_balancear(raiz);
}

//=================================//
// Funções de percursão            //
//=================================//

void preOrdem(node *raiz, int altura){
    if(raiz == NULL){
        return;
    } else {
        printf("%d , h= %d e cor: %d\n", raiz->prioridade, altura, raiz->cor);
        preOrdem(raiz->esq, altura+1);
        preOrdem(raiz->dir, altura+1);
    }

}

//=================================//
// Função Main                     //
//=================================//

int main(){

	node *raiz = NULL;
	raiz = io_criarArv(raiz, 10);
	raiz = io_inserir(raiz, 11);
	raiz = io_inserir(raiz, 9);
	raiz = io_inserir(raiz, 1);
	raiz = io_inserir(raiz, 12);
	raiz = io_inserir(raiz, 13);
	raiz = io_inserir(raiz, 15);
	raiz = io_inserir(raiz, 5);
	raiz = io_inserir(raiz, 8);
	raiz = io_inserir(raiz, 0);
	raiz = io_inserir(raiz, 20);
	
	

	raiz = io_removerMenor(raiz);
	raiz = io_removerMenor(raiz);
	raiz = io_removerMenor(raiz);
	raiz = io_removerMenor(raiz);
	raiz = io_removerMenor(raiz);
	raiz->cor = 0;
	
	raiz = io_removerMenor(raiz);
	raiz->cor = 0;
	
	raiz = io_removerMenor(raiz);
	raiz->cor = 0;
	
	raiz = io_removerMenor(raiz);
	raiz->cor = 0;
	
	raiz = io_removerMenor(raiz);
	raiz->cor = 0;
	
	raiz = io_removerMenor(raiz);
	raiz->cor = 0;
	
	raiz = io_removerMenor(raiz);
	raiz->cor = 0;
	
	preOrdem(raiz, 0);
	return 0;
	
	
}

//!No raiz preto definido na criação, pode ser necessário redefinilo a cada ciclo.