/*
   Aluno: Victor Daniel Silva Aragao

   Contruindo um simulador em software de um computador simples

   Compilar (Windows): gcc -o simulador simulador.c memoria.c processador.c programa.c exibicao.c
   Executar: simulador.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "processador.h"
#include "exibicao.h"
#include "programa.h"

int main()
{
    PMEM m;
    PPROC p;
    char c;

    while(1) {
        system("cls");
        exibe_menu();
        printf("\nOpcao escolhida: ");
        c = getchar();
        switch(c) {
            case '1':
                printf("\n");
                m = aloca_memoria();
                p = aloca_processador();
                inicializa_simulador(p, m);
                escreve_programa(m);
                executa_instrucoes(p);
                printf("\nPressione uma tecla para continuar...\n");
                getch();
            break;
            case '2':
                printf("\n");
                m = aloca_memoria();
                p = aloca_processador();
                inicializa_simulador(p, m);
                programa_teste(m);
                executa_instrucoes(p);
                printf("\nPressione uma tecla para continuar...\n");
                getch();
            break;
            case '3':
                return 0;
            break;
        }
    }

    return 0;
}
