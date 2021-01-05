// Inclusão das bibliotecas no programa
#include "libQsExt.h"

//Função de alocação de um novo registro
void criaReg(void* ch, Registro* R){
    (*R).chave = ch;
}

//Realiza a leitura do registro Superior
void LeSup(FILE **ArqLEs, char* nomeArq, Registro **UltLido, int *Ls, bool *OndeLer){
	(*ArqLEs) = fopen(nomeArq, "rb");
	if((*ArqLEs) == NULL){
		printf("Arquivo não pode ser lido");
	}else{
		fseek((*ArqLEs), (*Ls) * sizeof(Registro), SEEK_SET);
		fread((*UltLido), sizeof(Registro), 1, *ArqLEs);
		(*Ls)--;
		(*OndeLer) = false;
	}
	fclose(*ArqLEs);
}

//Realiza a leitura do registro Inferior
void LeInf(FILE **ArqLi, char* nomeArq, Registro **UltLido, int *Li, bool *OndeLer){
	(*ArqLi) = fopen(nomeArq, "rb");
	if((*ArqLi) == NULL){
		printf("\nArquivo não pode ser lido.\n");
	}else{
		fseek((*ArqLi), (*Li) * sizeof(Registro), SEEK_SET);
		fread((*UltLido), sizeof(Registro), 1, *ArqLi);
		(*Li)++;
		(*OndeLer) = true;
	}
	fclose(*ArqLi);
}

//Sobre escreve o registro com o maior valor representado na Area
void EscreveMax(FILE **ArqLEs, char* nomeArq, Registro *R, int *Es){
	(*ArqLEs) = fopen(nomeArq, "r+b");
	if((*ArqLEs) == NULL){
		printf("\nArquivo não pode ser escrito.\n");
	}else{
		fseek(*ArqLEs, (*Es) * sizeof(Registro), SEEK_SET);
		fwrite(R, sizeof(Registro), 1, *ArqLEs);
		(*Es)--;
	}
	fclose(*ArqLEs);
}

//Sobre escreve o registro com o menor valor representado na Area
void EscreveMin (FILE **ArqEi, char* nomeArq, Registro *R, int *Ei){
	(*ArqEi) = fopen(nomeArq, "r+b");
	if((*ArqEi) == NULL){
		printf("\nArquivo não pode ser escrito.\n");
	}else{
		fseek(*ArqEi, (*Ei) * sizeof(Registro), SEEK_SET);
		fwrite(R, sizeof(Registro), 1, *ArqEi);
		(*Ei)++;
	}
	fclose(*ArqEi);
}

//Retira o maior registro da área
void RetiraMax(Registro *Area, Registro *R, int *NRArea){
    memcpy(R, &Area[(*NRArea) - 1], sizeof(Registro));
    (*NRArea)--;   
}

//Retira o menor registro da Area
void RetiraMin(Registro *Area, Registro *R, int *NRArea){
	memcpy(R, &Area[0], sizeof(Registro));
	//Deixar a Area na forma correta
	for(int j=0; j<((*NRArea)-1); j++)
		(Area[j]).chave = (Area[j+1]).chave;
	//(Area[(*NRArea - 1)]).chave = NULL;
	(*NRArea)--;
}

//Insere o ultimo valor lido na area de forma ordenada
void inserirArea(Registro *Area, Registro *UltLido, int *NRArea, int(*comp)(void*, void*)){
	int j = (*NRArea);
	while(j > 0){
		//if(Area[j-1].chave > UltLido->chave)
		if(comp(Area[j-1].chave, UltLido->chave) == 1)
			memcpy(&Area[j], &Area[j-1], sizeof(Registro));
		else
			break;
		j--;
	}
	memcpy(&Area[j], UltLido, sizeof(Registro));
	(*NRArea)++;
}

//Realiza o particionamento do arquivo de registros
void Particiona(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, char* nomeArq, Registro *Area, int Esq, int Dir, int *i, int *j, void* LimInf, void* LimSup, int(*comp)(void*, void*)){
	int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0;
	bool OndeLer = true;

	Registro *UltLido, *R;
	R = (Registro*)calloc(1, sizeof(Registro));
	UltLido = (Registro*)calloc(1, sizeof(Registro));

	(*i) = Esq -1;
	(*j) = Dir +1;

	while(Ls >= Li){
		//Preenchendo os primeiros valores de leitura na Area
		while(NRArea < (TAM_AREA-1)){
			if(OndeLer == true){
				LeSup(ArqLEs, nomeArq, &UltLido, &Ls, &OndeLer);
			}
			else if(OndeLer == false){
				LeInf(ArqLi, nomeArq, &UltLido, &Li, &OndeLer);
			}
			inserirArea(Area, UltLido, &NRArea, comp);
		}
		
		// Agora sera lido o TamArea-ésimo registro
		if((Ls == Es) && (OndeLer == false))
			LeSup(ArqLEs, nomeArq, &UltLido, &Ls, &OndeLer);
		else if((Li == Ei) && (OndeLer == true))
			LeInf(ArqLi, nomeArq, &UltLido, &Li, &OndeLer);
		else if (OndeLer == true)
			LeSup(ArqLEs, nomeArq, &UltLido, &Ls, &OndeLer);
		else if (OndeLer == false)
			LeInf(ArqLi, nomeArq, &UltLido, &Li, &OndeLer);

		//Caso o TamArea-ésimo registro seja maior que LimSup
		if (comp(UltLido->chave, LimSup) == 1){
			(*j) = Es;
			EscreveMax(ArqLEs, nomeArq, UltLido, &Es);
		//Caso o TamArea-ésimo registro seja menor que LimInf
		}else if(comp(UltLido->chave, LimInf) == -1){
			(*i) = Ei;
			EscreveMin(ArqEi, nomeArq, UltLido, &Ei);
		//Caso o TamArea-ésimo registro esteja entre o LimInf e o LimSup
		}else{
			inserirArea(Area, UltLido, &NRArea, comp);
		}
		//Liberando a Area de armazenamento que está cheia
		if(NRArea == TAM_AREA){
			if(Ei-Esq < Dir-Es){
				RetiraMin(Area, R, &NRArea);
				EscreveMin(ArqEi, nomeArq, R, &Ei);
				LimInf = R->chave;
			}else{
				RetiraMax(Area, R, &NRArea);
				EscreveMax(ArqLEs, nomeArq, R, &Es);
				LimSup = R->chave;
			}
		}
	}
	//Passar o restante dos registros da área de armazenamento para o arquivo
	while(Ei <= Es){
		RetiraMin(Area, R, &NRArea);
		EscreveMin(ArqEi, nomeArq, R, &Ei);
	}
}

void QuickSortExterno (FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, char* nomeArq, int Esq, int Dir, void* LimInf, void* LimSup, int(*comp)(void*, void*)){
	int i, j;	
	//Area de armazenamento interno
	Registro *Area = (Registro*)calloc(TAM_AREA, sizeof(Registro));

	if(Dir - Esq < 1) return;

	Particiona(ArqLi, ArqEi, ArqLEs, nomeArq, Area, Esq, Dir, &i, &j, LimInf, LimSup, comp);
	if(i - Esq < Dir - j){
		//Ordena primeiro subarquivo menor
		QuickSortExterno(ArqLi, ArqEi, ArqLEs, nomeArq, Esq, i, LimInf, LimSup, comp);
		QuickSortExterno(ArqLi, ArqEi, ArqLEs, nomeArq, j, Dir, LimInf, LimSup, comp);
	}
	else{
		//Ordena primeiro o subarquivo maior
		QuickSortExterno(ArqLi, ArqEi, ArqLEs, nomeArq, j, Dir, LimInf, LimSup, comp);
		QuickSortExterno(ArqLi, ArqEi, ArqLEs, nomeArq, Esq, i, LimInf, LimSup, comp);
	}
}

//Realiza a exibição do arquivo com as chaves dos Registros (sendo possível conferir se a ordenação foi realizada com sucesso)
void imprimeArq(FILE *ArqLi, char* nomeArq, void(*imp)(void*)){
    Registro R;
    printf("\n");

    ArqLi = fopen(nomeArq, "rb");
	if(ArqLi == NULL){
    	printf("Arquivo não pode ser lido.");
    }else{
		while(fread(&R, sizeof(Registro), 1, ArqLi)){ //Alterar para um int size que o usuario programador deve apresentar
			printf(" ["); imp(R.chave); printf("]");
		}
	}
	fclose(ArqLi);
	printf("\n");
}