#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "processador.h"
#include "programa.h"

void escreve_programa(PMEM m)
{
    unsigned int endereco, instrucao, i;
    char strinst[4];
    printf("+--------------------------------------------------+\n");
    printf("|               ESCREVER PROGRAMA                  |\n");
    printf("+--------------------------------------------------+\n");
    printf("|     Endereco: endereco de memoria (0 ate 255)    |\n");
    printf("|     Instrucao: instrucao ou dado                 |\n");
    printf("|     Codigo =  0   -> NOP                         |\n");
    printf("|     Codigo =  16  -> STA ender                   |\n");
    printf("|     Codigo =  32  -> LDA ender                   |\n");
    printf("|     Codigo =  48  -> ADD ender                   |\n");
    printf("|     Codigo =  64  -> OR  ender                   |\n");
    printf("|     Codigo =  80  -> AND ender                   |\n");
    printf("|     Codigo =  96  -> NOT                         |\n");
    printf("|     Codigo =  128 -> JMP ender                   |\n");
    printf("|     Codigo =  144 -> JN  ender                   |\n");
    printf("|     Codigo =  160 -> JZ  ender                   |\n");
    printf("|     Codigo =  240 -> HLT                         |\n");
    printf("|     Encerramento do programa: instrucao HLT      |\n");
    printf("+--------------------------------------------------+\n");
    while(1) {
        printf("\n");
        printf("Endereco: ");
        scanf("%d", &endereco);
        printf("Instrucao: ");
        scanf("%s", strinst);

        for(i=0; i < strlen(strinst); i++){  // Caso o usuario digitar a instrucao em minusculo, converte para maiusculo
            strinst[i] = toupper(strinst[i]);
        }

        printf("\n+------------------------------+\n");
        printf("|Endereco: %3d - Instrucao: %3s|\n", endereco, strinst);
        printf("+------------------------------+\n");

        instrucao = compara_instrucao(strinst);
        if(instrucao > 255)
        {
            printf("\n\nMEM overflow!\n");
            exit(1);
        }
        (*(m->posicao + endereco) = instrucao); // Busca instrucao: p->ri = *(p->rm + p->pc);

        if(instrucao == HLT) break;
    }
    printf("\n\n");
}

/* Compara a instrucao ou dado digitado e retorna o seu inteiro */
int compara_instrucao(char *instrucao)
{
    int inst = 0;
    if(strcmp(instrucao, "NOP") == 0) return NOP;
    if(strcmp(instrucao, "STA") == 0) return STA;
    if(strcmp(instrucao, "LDA") == 0) return LDA;
    if(strcmp(instrucao, "ADD") == 0) return ADD;
    if(strcmp(instrucao, "OR" ) == 0) return OR;
    if(strcmp(instrucao, "AND") == 0) return AND;
    if(strcmp(instrucao, "NOT") == 0) return NOT;
    if(strcmp(instrucao, "JMP") == 0) return JMP;
    if(strcmp(instrucao, "JN" ) == 0) return JN;
    if(strcmp(instrucao, "JZ" ) == 0) return JZ;
    if(strcmp(instrucao, "HLT") == 0) return HLT;

    inst = atoi(instrucao);
    if((inst > -1) || (inst < 256) ) return inst;
}

void programa_teste(PMEM m)
{
    printf("+--------------------------------------------------+\n");
    printf("|                PROGRAMA DE TESTE                 |\n");

    /* Teste NOP/LDA/ADD/STA */
    (*(m->posicao + 0) = NOP);   // Operacao NOP no endereco 0
    (*(m->posicao + 1) = LDA);   // Operacao LDA no endereco 1
    (*(m->posicao + 2) = 128);   // Valor que existe no endereco 128 vai ser atribuido ao acumulador no endereco 2
    (*(m->posicao + 3) = ADD);   // Operacao ADD no endereco 3
    (*(m->posicao + 4) = 129);   // Adicao entre o valor que existe no endereco 129 e o que existe no endereco 2 (acumulador). Resultado colocado no endereco 4
    (*(m->posicao + 5) = STA);   // Operacao STA no endereco 5
    (*(m->posicao + 6) = 130);   // Armazenamento do resultado do acumulador no endereco 130
    /* Teste LDA/JZ */
    (*(m->posicao + 7) = LDA);   // Operacao LDA no endereco 7
    (*(m->posicao + 8) = 131);   // Valor que existe no endereco 131 vai ser atribuido ao acumulador no endereco 8
    (*(m->posicao + 9) = JZ);    // Operacao JZ no endereco 9
    (*(m->posicao + 10) = 100);  // Desvia para o endereco 100
    /* Teste LDA/JN */
    (*(m->posicao + 100) = LDA); // Operacao LDA no endereco 100
    (*(m->posicao + 101) = 132); // Valor que existe no endereco 132 vai ser atribuido ao acumulador no endereco 101
    (*(m->posicao + 102) = JN);  // Operacao JN no endereco 102
    (*(m->posicao + 103) = 11);  // Desvia para o endereco 11
    /* Teste NOP/JMP */
    (*(m->posicao + 11) = NOP);  // Operacao NOP no endereco 11
    (*(m->posicao + 12) = JMP);  // Operacao JMP no endereco 12
    (*(m->posicao + 13) = 110);  // Desvia para o endereco 110
    /* Teste NOT/JMP */
    (*(m->posicao + 110) = NOT); // Operacao NOT no endereco 110
    (*(m->posicao + 111) = JMP); // Operacao JMP no endereco 111
    (*(m->posicao + 112) = 14);  // Desvia para o endereco 14
    /* Teste LDA/OR/AND/HLT */
    (*(m->posicao + 14) = LDA);  // Operacao LDA no endereco 14
    (*(m->posicao + 15) = 133);  // Valor que existe no endereco 133 vai ser atribuido ao acumulador no endereco 15
    (*(m->posicao + 16) = OR);   // Operacao OR no endereco 16
    (*(m->posicao + 17) = 134);  // OR entre o valor que existe no endereco 134 e o que existe no endereco 15 (acumulador). Resultado colocado no endereco 17
    (*(m->posicao + 18) = AND);  // Operacao AND no endereco 18
    (*(m->posicao + 19) = 133);  // AND entre o valor que existe no endereco 133 e o que existe no endereco 17 (acumulador). Resultado colocado no endereco 19
    (*(m->posicao + 20) = HLT);  // Termino de execucao no endereco 20
    /* Dados */
    (*(m->posicao + 128) = 1);   // No endereco 128 existe o valor 1
    (*(m->posicao + 129) = 2);   // No endereco 129 existe o valor 2
    (*(m->posicao + 131) = 0);   // No endereco 131 existe o valor 0
    (*(m->posicao + 132) = -1);  // No endereco 132 existe o valor -1
    (*(m->posicao + 133) = 1);   // No endereco 133 existe o valor 1
    (*(m->posicao + 134) = 2);   // No endereco 134 existe o valor 2
}
