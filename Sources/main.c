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

printf(" Funcao cpu\n ");

pc=0;// inicializa o pc..

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

if(ri==0x00){
//ir para passo zero
}


//[0001]0000 = 0x10
if(ri==0x10){ //LDR
	rem=rdm;
	rdm=memoria[rem];
	ac= rdm;
	//ir para zero
}


//[0010]0000 = 0x20
if(ri==0x20){ //STR
	rem=rdm;
	rdm= ac;
	memoria[rem]=rdm;
	//ir para zero
}


//[0011]0000 = 0x30
if(ri==0x30){ //ADD
	rem=rdm;
	rdm=memoria[rem];
	ac= ac+rdm;
	//ir para zero
}


//[0100]0000 = 0x40
if(ri==0x40){ //SUB
	rem=rdm;
	rdm=memoria[rem];
	ac= ac-rdm;
	//ir para zero
}


//[0101]0000 = 0x50
if(ri==0x50){ //MUL
	rem=rdm;
	rdm=memoria[rem];
	ac= ac*rdm;
	//ir para zero
}

//[0110]0000 = 0x60
if(ri==0x60){ //DIV
	rem=rdm;
	rdm=memoria[rem];
	ac= ac/rdm;
	//ir para zero
}

//[0101]0000 = 0x70
if(ri==0x70){ //NOT
	rem=rdm;
	rdm=memoria[rem];
	ac= ~ac;
	//ir para zero
}

//[1000]0000 = 0x80
if(ri==0x80){ //AND
	rem=rdm;
	rdm=memoria[rem];
	ac= ac & memoria[rdm];
	//ir para zero
}


//[1001]0000 = 0x90
if(ri==0x90){ //OR
	rem=rdm;
	rdm=memoria[rem];
	ac= ac | memoria[rem];
	//ir para zero
}


//[1010]0000 = 0xA0;
if(ri==0xA0){ //XOR
	rem=rdm;
	rdm=memoria[rem];
	ac= ac ^ memoria[rdm];
	//ir para zero
}

//[1011]0000 = 0xB0
if(ri==0xB0){ //JMP
	pc= rdm;
	//ir para zero
}


//[1100]0000 = 0xC0
if(ri==0xC0){ //JEQ
	if(ac==0){
		pc=rdm;
	}
	//ir para zero
}

//[1101]0000 = 0xD0
if(ri==0xD0){ //JG
	if(ac>0){
		pc=rdm;
	}
	//ir para zero
}

//[1110]0000 = 0xE0
if(ri==0xE0){ //JL
	if(ac<0){
		pc=rdm;
	}
	//ir para zero
}

//[1111]0000 = 0xF0
if(ri==0xF0){ //HLT


	//ir para Halted
}



}



/** @} */



