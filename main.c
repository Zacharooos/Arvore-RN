#include<stdio.h>
#include<stdlib.h>

struct rb{
	char cor;
	int info;
	struct rb *pai;
	struct rb *esq;
	struct rb *dir;
};

struct arvoreRB{
	struct rb *raiz;
};

void preorder(struct rb *no){
	if(no == NULL)
		return;

	printf("%d ", no->info);
	if(no->cor == 'p')
		puts("BLACK");
	else
		puts("RED");
	if(no->esq != NULL){
		printf("esq = %d   ", no->esq->info);
	}
	
	if(no->dir != NULL){
		printf("dir = %d", no->dir->info);
	}
	puts("");
	preorder(no->esq);
	preorder(no->dir);
}

void teste(struct rb *no){
	if(no == NULL)
		return;

	printf("%d, end: %p,	pai: %p		esq: %p		dir: %p		cor: ", no->info, no, no->pai, no->esq, no->dir);
	if(no->cor == 'p')
		puts("BLACK");
	else
		puts("RED");
	teste(no->esq);
	teste(no->dir);
}

void LeftRotate(struct rb *x){
	struct rb *aux;
	aux = x->dir;
	if(aux->esq != NULL){
		aux->esq->pai = x;
	}
	x->dir = aux->esq;
	aux->esq = x;
	aux->pai = x->pai;
	if(x->pai != NULL){
		if(x->pai->esq == x){
			x->pai->esq = aux;
		}
		else{
			x->pai->dir = aux;
		}
	}
	x->pai = aux;
//	puts("Rodou");
}

void RightRotate(struct rb *x){
	struct rb *aux;
	aux = x->esq;
	if(aux->dir != NULL){
		aux->dir->pai = x;
	}
	x->esq = aux->dir;
	aux->dir = x;
	aux->pai = x->pai;
	if(x->pai != NULL){
		if(x->pai->esq == x){
			x->pai->esq = aux;
		}
		else{
			x->pai->dir = aux;
		}
	}
	x->pai = aux;
//	puts("Rodou");
}

void ajuste(struct arvoreRB *arvore, struct rb *no){
	while(no->pai != NULL && no->pai->cor == 'v'){ //se o pai é preto, não precisa fazer nada
		if(no->pai == no->pai->pai->esq){//está na subarvore esquerda
			struct rb *tio = no->pai->pai->dir;
			if(tio != NULL && tio->cor == 'v'){ //pai vermelho e tio vermelho
				no->pai->cor = 'p';
				tio->cor = 'p';
				no->pai->pai->cor = 'v';
				no = no->pai->pai; //nó recebeu endereço do avô
			}
			else{ //pai vermelho e tio preto ou null (cor e rotações)
				if (no == no->pai->dir){
					no = no->pai;
					LeftRotate(no);
				}
				no->pai->cor = 'p';
				if(no->pai->pai != NULL){
					no->pai->pai->cor = 'v';
					RightRotate(no->pai->pai);
				}	
			}
		}
		else{ //está na subarvore direita
			//puts("subarvore direita");
			struct rb *tio = no->pai->pai->esq;
			if(tio != NULL && tio->cor == 'v'){ //pai vermelho e tio vermelho
				//puts("tio vermelho incio");
				no->pai->cor = 'p';
				tio->cor = 'p';
				no->pai->pai->cor = 'v';
				no = no->pai->pai;
				//puts("tio vermelho fim");
			}
			else{ //pai vermelho e tio preto ou null (rotações e alteração de cores)
				if(no == no->pai->esq){
					no = no->pai;
					RightRotate(no);
				}
				no->pai->cor = 'p';
				if(no->pai->pai !=NULL){
					no->pai->pai->cor = 'v';
					LeftRotate(no->pai->pai);
				}
			}
		}
	}
	if(no->pai == NULL)
		arvore->raiz = no;
	else if(no->pai->pai == NULL)
		arvore->raiz = no->pai;
	arvore->raiz->cor = 'p';
}

void inserir(struct arvoreRB *arvore, int k){
	struct rb *y = NULL;
	struct rb *x = arvore->raiz;
	while (x != NULL){
		y = x;
		if (k < x->info)
			x = x->esq;
		else
			x = x->dir;
	}
	struct rb *no = malloc(sizeof(struct rb));
	no->info = k;
	no->pai = y;

	if(y == NULL){
		arvore->raiz = no;
		arvore->raiz->cor = 'p';
		arvore->raiz->esq = NULL;
		arvore->raiz->dir = NULL;
		arvore->raiz->pai = NULL;
		return;
	}
	else if (no->info < y->info){
		y->esq = no;
	}
	else{
		y->dir = no;
	}

	no->esq = NULL;
	no->dir = NULL;
	no->cor = 'v';
//	printf("%d, end: %p,	pai: %p		esq: %p		dir: %p\n", no->info, no, no->pai, no->esq, no->dir);
//	printf("pai->%d, end: %p,	pai: %p		esq: %p		dir: %p\n", no->pai->info, no->pai, no->pai->pai, no->pai->esq, no->pai->dir);
	ajuste(arvore, no);

}

struct rb *busca_no(struct arvoreRB *arvore, int k){
	struct rb *aux = arvore->raiz;
	while(aux != NULL){
		if(k < aux->info){
			aux = aux->esq;
		}
		else{
			if(k == aux->info){
				break;
			}
			aux = aux->dir;
		}
	}
	return aux;
}

void remover(struct arvoreRB *arvore){
	struct rb *no = arvore->raiz;
	struct rb *aux;
	int verificar = 1;
	if(no == NULL){
		return;
	}
	while(no->esq != NULL){
		no = no->esq;
	}
	printf("%d\n", no->info);

	if(no->dir == NULL && no->pai == NULL){ //caso só exista a raiz
		free(no);
		arvore->raiz = NULL;
		return;
	}
	else if (no->dir != NULL && no->pai == NULL){ //caso só exista a raiz com filho direito
		arvore->raiz = no->dir;
		no->dir->pai = NULL;
		no->dir->cor = 'p';
		free(no);
		return;
	}

	if(no->pai != NULL)
		no->pai->esq = NULL;
	aux = no;


	//puts("ta nos ifs");
	if(no->cor == 'v'){ //se o nó for vermelho, não altera o balanceamento da árvore
		puts("caso 1");
		aux = no->pai;
		free(no);
		no = aux;
		verificar = 0;
		return;
	}
	else if(no->dir != NULL){ //caso o no tenha um filho da direita
		puts("caso 2");
		no->pai->esq = no->dir;
		no->dir->pai = no->pai;
		if(no->dir->cor == 'v'){
			no->dir->cor = 'p';
		}
		else{
			no->dir->cor = 'v';
		}
		no = no->pai;
		verificar = 0;
	}
	while(verificar == 1 && no->pai != NULL){
		if(no->pai->dir != NULL && no->pai->dir->cor == 'v'){ //irmao vermelho
			puts("caso 3.1");
			no->pai->dir->cor = 'p';
			no->pai->cor = 'v';
			LeftRotate(no->pai);
		}
		else if(no->pai->dir->dir != NULL && no->pai->dir->dir->cor == 'v'){ //caso o irmao tenha filho direito vermelho
			puts("caso 3.4");
			no = no->pai;
			char cor_aux;
			cor_aux = no->cor;
			no->cor = 'p';
			no->dir->dir->cor = 'p';
			no->dir->cor = cor_aux;
			LeftRotate(no);
			verificar = 0;
		}
		else if(no->pai->dir->esq != NULL && no->pai->dir->esq->cor == 'v'){ //caso o irmao tenha filho esquerdo vermelho
			puts("caso 3.3");
			aux = no;
			no = no->pai;
			char cor_aux = no->dir->cor;
			RightRotate(no->dir);
			no->dir->dir->cor = no->dir->cor;
			no->dir->cor = cor_aux;
			cor_aux = no->cor;
			no->cor = no->dir->cor;
			no->dir->dir->cor = no->dir->cor;
			no->dir->cor = cor_aux;
			LeftRotate(no);
			no = no->pai;
			verificar = 0;
		}
		else if((no->pai->esq == NULL || no->pai->esq->cor == 'p') && (no->pai->dir == NULL || no->pai->dir->cor == 'p')){ //irmao com dois filhos 'p' ou NULL
			puts("caso 3.2");
			no = no->pai;
			char cor_aux = no->cor;
			no->cor = 'p';
			no->dir->cor = 'v';
			if(cor_aux == 'v'){
				verificar = 0;
			}
		}
	}
	free(aux);
	//printf("no: %d, pai: %d\n", no->info, no->pai->info);

	if(no->pai == NULL){
		arvore->raiz = no;
		arvore->raiz->cor = 'p';
		return;
	}
	else if(no->pai->pai == NULL){
		arvore->raiz = no->pai;
		arvore->raiz->cor = 'p';
		//printf("raiz: %d\n", no->pai->info);
	}
	else if(no->pai->pai->pai == NULL){
		arvore->raiz = no->pai->pai;
		arvore->raiz->cor = 'p';
		// printf("raiz: %d\n", no->pai->info);
	}
	else if (no->pai->pai->pai->pai == NULL){
		arvore->raiz = no->pai->pai->pai;
		arvore->raiz->cor = 'p';
		// printf("raiz: %d\n", no->pai->info);
	}
	arvore->raiz->cor = 'p';
	printf("raiz = %d\n", arvore->raiz->info);
}

void desalocar(struct rb *no){
	if(no == NULL)
		return;

	desalocar(no->esq);
	desalocar(no->dir);
	free(no);
}

int main(){
	//inicializando a arvore RN
	struct arvoreRB arvore;
	arvore.raiz = NULL;
	int k;

//	Lendo os dados da entrada:
	while (scanf(" %d", &k) != EOF) {
		inserir(&arvore, k);
	}
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	remover(&arvore);
	// remover(&arvore);
	// remover(&arvore);
	// remover(&arvore);
	// remover(&arvore);
	// remover(&arvore);
	// remover(&arvore);
	// remover(&arvore);

	// inserir(&arvore, 30);
	// remover(&arvore);
	// inserir(&arvore, 41);
	// inserir(&arvore, 17);
	// inserir(&arvore, 34);
	// inserir(&arvore, 43);
	// remover(&arvore);
	// inserir(&arvore, 24);
	// inserir(&arvore, 25);
	// inserir(&arvore, 49);
	// inserir(&arvore, 32);
	// inserir(&arvore, 36);
	// remover(&arvore);
	puts("-/-/-/PREORDEM:-/-/-/");
	preorder(arvore.raiz);
	desalocar(arvore.raiz);

	return 0;
}
