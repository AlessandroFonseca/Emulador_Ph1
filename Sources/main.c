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

	printf("Hello World\n");
	while(!feof(arq))/// feof retorna true quando arq chegou no fim...
	{
		fscanf( arq ,"%x %x", &endereco, &dado);
		memoria[endereco] = dado;
		printf("%x = %x\n", endereco,dado);
	}


	fclose(arq);
	return 0;

}







/** @} */

