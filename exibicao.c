#include <stdio.h>
#include "exibicao.h"

void exibe_menu()
{
    printf("+--------------------------------------------------+\n");
    printf("|        SIMULADOR DE UM COMPUTADOR SIMPLES        |\n");
    printf("+--------------------------------------------------+\n");
    printf("|             Escolha uma opcao abaixo:            |\n");
    printf("|               1 - Escrever programa              |\n");
    printf("|               2 - Programa de teste              |\n");
    printf("|               3 - Sair                           |\n");
    printf("+--------------------------------------------------+\n");
}

void exibe_processador(PPROC p)
{
    if(p->pc == 0) {
        printf("+--------------------------------------------------+\n");
        printf("|                   PROCESSADOR                    |\n");
    }
	printf("+--------------------------------------------------+\n");
    printf("|    AC = %3d  RI = %3d  PC = %3d  N = %1d  Z = %1d    |\n",
			p->ac, p->ri, p->pc, p->flag >> Z , p->flag & ~N);           // p->flag = 0 ou p->flag = 1 ou p->flag = 2; Z = 1, N = 2
	printf("+--------------------------------------------------+\n");
}

