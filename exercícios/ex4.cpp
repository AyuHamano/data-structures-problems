#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
 
class No
{
private:
	No *esq, *dir;
	int chave;

public:
	No(int chave)
	{
		this->chave = chave;
		esq = NULL;
		dir = NULL;
	}

	int getChave()
	{
		return chave;
	}
	
	// funções getters e setters

	No* getEsq()
	{
		return esq;
	}

	No* getDir()
	{
		return dir;
	}

	void setEsq(No *no)
	{
		esq = no;
	}

	void setDir(No *no)
	{
		dir = no;
	}
	void setEsqNull() {
		esq = NULL;
	}
	void setDirNull() {
		dir = NULL;
	}
};

class Arvore
{
private:
	No *raiz;
	
    No *no_sucessor(No *apaga) { // O parametro é a referencia para o No que deseja-se apagar
        No *paidosucessor = apaga;
        No *sucessor = apaga;
        No *atual = apaga->getDir(); 
     
        while (atual != NULL) { // enquanto nao chegar no Nó mais a esquerda
            paidosucessor = sucessor;
            sucessor = atual;
            atual = atual->getEsq(); // caminha para a esquerda
         } 
         
        if (sucessor != apaga->getDir()) { 
            paidosucessor->setEsq(sucessor->getDir());
            sucessor->setDir(apaga->getDir());  
        }
        return sucessor;
    }
  

public:
	Arvore()
	{
		raiz = NULL;
	}
	void inicializar() {
	    raiz = NULL;
	}

	void inserir(int chave)
	{
		if(raiz == NULL) {
			raiz = new No(chave); // cria um novo nó
		}
		else {
			inserirAux(raiz, chave);
		}
	}

	void inserirAux(No *no, int chave)
	{
		// se for menor, então insere à esquerda
		if(chave < no->getChave()) {
			// verifica se a esquerda é nulo
			if(no->getEsq() == NULL) {
				No *novo_no = new No(chave);
				no->setEsq(novo_no); // seta o novo_no à esquerda
			}
			else {
				// senão, continua percorrendo recursivamente
				inserirAux(no->getEsq(), chave);
			}
		}
		// se for maior, então insere à direita
		else if(chave > no->getChave())
		{
			// verifica se a direita é nulo
			if(no->getDir() == NULL) {
				No *novo_no = new No(chave);
				no->setDir(novo_no); // seta o novo_no à direita
			}
			else {
				// senão, continua percorrendo 
				inserirAux(no->getDir(), chave);
			}
		}

	}
	
	bool buscaBinaria(int chave) {
        if (raiz == NULL) {
            cout << chave << " nao existe" <<"\n";
            
        } 
        No *noAtual = raiz;  // começa a procurar desde raiz
        
        while (noAtual->getChave() != chave) { // enquanto nao encontrou
        
            if(chave < noAtual->getChave() ){ 
                noAtual = noAtual->getEsq();// caminha para esquerda
                
            } 
            else {
                noAtual = noAtual->getDir(); // caminha para direita
                
            } 
            if (noAtual == NULL) {
                cout << chave << " nao existe" << "\n";
                return false;
            } 
        } 
        cout << chave << " existe" << "\n";
        return true;
  }

    bool removeNo(int chave) {
        
        if (getRaiz() == NULL) {
	    	return false; // se arvore vazia
	    } 
        No *atual = raiz;
        No *pai = raiz;
        bool filho_esq = true;
    
        while (atual->getChave() != chave) { 
            pai = atual;
            if(chave < atual->getChave() ) { 
                atual = atual->getEsq();
                filho_esq = true; 
            }
            else { 
                atual = atual->getDir(); 
                filho_esq = false; 
            }
            if (atual == NULL) {
	    		return false; // encontrou uma folha -> sai
	    	} 
        } 
    
        if (atual->getEsq() == NULL && atual->getDir() == NULL) {
        	if (atual == raiz ) {
	    		raiz = NULL; // se é raiz
	    	}
          	else if (filho_esq) {
	    		pai->setEsqNull(); // se for filho a esquerda do pai
	    	} 
            else pai->setDirNull(); // se for filho a direita do pai
        }
    
        else if (atual->getDir() == NULL) {
        	if (atual == raiz) {
	    		raiz = atual->getEsq(); 
	    	} 
        	else if (filho_esq) {
	    		pai->setEsq(atual->getEsq()); // se for filho a esquerda do pai
	    	} 
            else pai->setDir(atual->getEsq());
        }
        
        // Se é pai e nao possui um filho a esquerda, substitui pela subarvore a esquerda
        else if (atual->getEsq() == NULL) {
    
        	if (atual == raiz) {
	    		raiz = atual->getDir();
	    	} 
        	else if (filho_esq) {
	    		pai->setEsq(atual->getDir());
	    	} 
                
	    	else {
	    		pai->setDir(atual->getDir()); 
	    	}
        }
    
        else {
            No *sucessor = no_sucessor(atual);
        
        	if (atual == raiz) {
	    		raiz = sucessor;
	    	} 
        	else if(filho_esq) {
	    		pai->setEsq(sucessor); 
	    	}
            else {
                pai->setDir(sucessor);
            } 
             
        sucessor->setEsq(atual->getEsq()); // acertando o ponteiro a esquerda do sucessor agora que ele assumiu 
                                  
    }
  }
 
  No* getRaiz()
	{
		return raiz;
	}

	void emOrdem(No* no)
	{
		if(no != NULL) {
			emOrdem(no->getEsq());
			cout << no->getChave() << " ";
			emOrdem(no->getDir());
		}
	}
	void preOrdem(No* no)
	{
		if(no != NULL) {
		    cout << no->getChave() << " ";
			preOrdem(no->getEsq());
			preOrdem(no->getDir());
		}
	}
	void postOrdem(No* no)
	{
		if(no != NULL) {
			postOrdem(no->getEsq());
			postOrdem(no->getDir());
			cout << no->getChave() << " ";
		}
	}
};

int main()
{
	Arvore arv;
	string comando;
	int n;  
	
	 while (cin >> comando) {

	   if(comando == "I") {
	       cin >> n;
	       arv.inserir(n);
	   }
	   else if(comando == "R") {
	       cin >> n;
		   arv.removeNo(n);
	       //cout << "removendo...\n";
	   }
	   else if(comando == "P") {
	       cin>>n;
	       arv.buscaBinaria(n);
	   }
	   else if(comando == "INFIXA") {
	       arv.emOrdem(arv.getRaiz());
	       std::cout << '\n';
	   }
	   else if(comando == "PREFIXA") {
	       arv.preOrdem(arv.getRaiz());
	       std::cout << '\n';
	   }
	   else if(comando == "POSFIXA") {
	       arv.postOrdem(arv.getRaiz());
	       std::cout << '\n';
	   }
	}  
	return 0;
}