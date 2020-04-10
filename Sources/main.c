/**
 * @addtogroup main
 *
 * @details Este arquivo contém a funcao principal do programa
 *
 * @details <b>Histórico</b>
 * \n 1-04-2020 Alessandro Fonseca Criacao do arquivo
 *
 */

/** @{ */
#include <stdio.h>


int memoria[256];
int sombra [256];
int pc;
int ri;
int rdm;
int rem;
int ac;



void cpu(void);




/**
 * @brief funcao principal do programa
 *
 * @details Esta funcao e chamada quando inicia o programa
 *
 * @details <b>Historico</b>
 * \n 01-04-2020 Alessandro Fonseca Criacao da funcao
 *
 */
int main(int argc, char** argv) {
	int endereco,dado;
	FILE * arq;
	arq = fopen("/Users/alessandrofonseca/Desktop/arquivo_entrada.txt", "r");
	if(arq == NULL) /// se nao conseguiu abrir o arquivo...
	{
		printf("Nao conseguiu Abrir o Arquivo\n");
		return 0;
	}

	printf("Arquivo Aberto\n");
	while(!feof(arq))/// feof retorna true quando arq chegou no fim...
	{

		fscanf( arq ,"%x %x", &endereco, &dado);
		memoria[endereco] = dado;
		sombra [endereco] = dado;
		printf("%x = %x\n", endereco,dado);
	}


	fclose(arq);
	cpu();// chamada função cpu..
	return 0;

}

/**
 * @brief funcao CPU
 *
 * @details Esta funcao executa o conteúdo do vetor que foi carregado pelo arquivo
 *
 * @details <b>Historico</b>
 * \n 07-04-2020 Alessandro Fonseca Criacao da funcao
 *
 */
void cpu(void){

	int i;
	int cont=0;
	printf("Funcao cpu\n");

	pc=0;// inicializa o pc..

	while(1)
	{
		rem=pc;
		rdm= memoria[rem];// o indice do vetor é o endereço da nossa memória
		pc=pc+1;
		ri=rdm;

		//[0000]0000 = 0x00
		//[0111]0000 = 0x70
		//[1111]0000 = 0xF0
		if(ri!=0x00 && ri!=0x70 && ri!=0xf0){ // se a instrução ocupa 01 endereço de memória
			rem=pc;
			rdm= memoria[rem];
			pc=pc+1;
		}

		if(ri==0x00){ //NOP
		//ir para passo zero
			printf("NOP;\n");
			cont++;
			continue;
		}


		//[0001]0000 = 0x10
		if(ri==0x10){ //LDR
			printf("LDR %02x;\n", rdm);
			rem=rdm;
			rdm=memoria[rem];
			ac= rdm;
			//ir para zero
			cont++;
			continue;
		}


		//[0010]0000 = 0x20
		if(ri==0x20){ //STR
			printf("STR %02x;\n", rdm);
			rem=rdm;
			rdm= ac;
			memoria[rem]=rdm;
			//ir para zero
			cont++;
			continue;
		}


		//[0011]0000 = 0x30
		if(ri==0x30){ //ADD
			printf("ADD %02x;\n", rdm);
			rem=rdm;
			rdm=memoria[rem];
			ac= ac+rdm;
			//ir para zero
			cont++;
			continue;
		}


		//[0100]0000 = 0x40
		if(ri==0x40){ //SUB
			printf("SUB %02x;\n", rdm);
			rem=rdm;
			rdm=memoria[rem];
			ac= ac-rdm;
			//ir para zero
			cont++;
			continue;
		}


		//[0101]0000 = 0x50
		if(ri==0x50){ //MUL
			printf("MUL %02x;\n", rdm);
			rem=rdm;
			rdm=memoria[rem];
			ac= ac*rdm;
			//ir para zero
			cont++;
			continue;
		}

		//[0110]0000 = 0x60
		if(ri==0x60){ //DIV
			printf("DIV %02x;\n", rdm);
			rem=rdm;
			rdm=memoria[rem];
			ac= ac/rdm;
			//ir para zero
			cont++;
			continue;
		}

		//[0101]0000 = 0x70
		if(ri==0x70){ //NOT
			printf("NOT;\n");
			ac= ~ac;
			//ir para zero
			cont++;
			continue;
		}

		//[1000]0000 = 0x80
		if(ri==0x80){ //AND
			printf("AND %02x;\n", rdm);
			rem=rdm;
			rdm=memoria[rem];
			ac= ac & memoria[rdm];
			//ir para zero
			cont++;
			continue;
		}


		//[1001]0000 = 0x90
		if(ri==0x90){ //OR
			printf("OR %02x;\n", rdm);
			rem=rdm;
			rdm=memoria[rem];
			ac= ac | memoria[rem];
			//ir para zero
			cont++;
			continue;
		}


		//[1010]0000 = 0xA0;
		if(ri==0xA0){ //XOR
			printf("XOR %02x;\n", rdm);
			rem=rdm;
			rdm=memoria[rem];
			ac= ac ^ memoria[rdm];
			//ir para zero
			cont++;
			continue;
		}

		//[1011]0000 = 0xB0
		if(ri==0xB0){ //JMP
			printf("JMP %02x;\n", rdm);
			pc= rdm;
			//ir para zero
			cont++;
			continue;
		}


		//[1100]0000 = 0xC0
		if(ri==0xC0){ //JEQ
			printf("JEQ %02x;\n", rdm);
			if(ac==0){
				pc=rdm;
			}
			//ir para zero
			cont++;
			continue;
		}

		//[1101]0000 = 0xD0
		if(ri==0xD0){ //JG
			printf("JG %02x;\n", rdm);
			if(ac>0){
				pc=rdm;
			}
			//ir para zero
			cont++;
			continue;
		}

		//[1110]0000 = 0xE0
		if(ri==0xE0){ //JL
			printf("JL %02x;\n", rdm);
			if(ac<0){
				pc=rdm;
			}
			//ir para zero
			cont++;
			continue;
		}

		//[1111]0000 = 0xF0
		if(ri==0xF0){ //HLT
			printf("HLT;\n");
			cont++;
			break;
			//ir para Halted
		}

	}//while...
	printf("\n");
	printf("%d instructions executed\n", cont);
	printf("\n");
	printf("Registers:\n");
	printf("AC: %02x\n", ac);
	printf("PC: %02x\n", pc);
	printf("\n");
	printf("Memory:\n");
	for(i=128;i<255;i++){
		if(sombra[i] != memoria[i]){
			printf("%02x %02x\n", i,memoria[i]);
		}
	}

}



/** @} */



