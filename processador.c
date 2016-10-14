#include <stdio.h>
#include <stdlib.h>
#include "processador.h"
#include "exibicao.h"

PPROC aloca_processador()
{
    PPROC p = (PPROC) malloc(sizeof(PROC));
    if(!p) {
		printf("\nNao foi possivel inicializar o PROC!\n");
        exit(1);
    }
    p->pc = 0;
    p->ac = 0;
    p->ri = 0;
    p->rm = NULL;
    p->flag = 0;
    return p;
}

void inicializa_simulador(PPROC p, PMEM m)
{
	if((p == NULL) || (m == NULL)) {
		printf("\nPROC ou MEM nulo!\n");
        exit(1);
	}

	p->rm = m->posicao; // Recebe 1 dado/instrucao pra cada posicao, existindo 256 posicoes, ou seja 256 dados/instrucoes
                        // Convencao utilizada: Enderecos de 0 ate 127 = Codigos do programa, Enderecos de 128 ate 255 = Dados do programa
}

int executa_simulador(PPROC p)
{
	if(p == NULL) {
		printf("\nPROC nao inicializado!\n");
        exit(1);
	}

	if(p->rm == NULL) {
		printf("\nMEM nao inicializado!\n");
        exit(1);
	}

    /* Busca instrucao */
    p->ri = *(p->rm + p->pc); // REM <- PC; RI <- RDM
                              // *(p->rm + p->pc): acessa o conteúdo do p->rm na posicao do p->pc, pois p->rm = m->posicao = posicao 0

    if(p->ri == NOP || p->ri == STA || p->ri == LDA || p->ri == ADD || p->ri == OR || p->ri == AND ||
       p->ri == NOT || p->ri == JMP || p->ri == JN || p->ri == JZ || p->ri == HLT) {
        exibe_processador(p);
    }

    /* Incrementa pc */
    p->pc++; // PC <- PC + 1

    /* Decodifica instrucao */
    switch (p->ri) {
        case NOP:
            instrucao_nop(p); // NOP = 00000000 = 0
        break;
        case STA:
            instrucao_sta(p); // STA = 00010000 = 16
        break;
        case LDA:
            instrucao_lda(p); // LDA = 00100000 = 32
        break;
        case ADD:
            instrucao_add(p); // ADD = 00110000 = 48
        break;
        case OR:
            instrucao_or(p);  // OR = 01000000 = 64
        break;
        case AND:
            instrucao_and(p); // AND = 01010000 = 80
        break;
        case NOT:
            instrucao_not(p); // NOT = 01100000 = 96
        break;
        case JMP:
            instrucao_jmp(p); // JMP = 10000000 = 128
        break;
        case JN:
            instrucao_jn(p); // JN = 10010000 = 144
        break;
        case JZ:
            instrucao_jz(p); // JZ = 10100000 = 160
        break;
        case HLT:
            instrucao_hlt(p); // HLT = 11110000 = 240
            return 0;
        break;
        default:
            printf("Instrucao nao reconhecida!\n");
            exit(1);
        break;
    }

    return 1; // Entra no while do executa_instrucoes(PPROC p)
}

int executa_instrucoes(PPROC p)
{
	while(1) {
        if(executa_simulador(p) == 0) {
            return 0;
        }
	}
}

void atualiza_flag(PPROC p)
{
    p->flag = 0; // p->flag = 0
	((p->ac == 0) && (p->flag = (p->flag | Z))) ||  // Atualiza Z; p->flag = 1
	((p->ac >  127) && (p->flag = (p->flag | N)));  // Atualiza N; p->flag = 2
}

void instrucao_nop(PPROC p) {
 // Nao realiza operacao
}

void instrucao_sta(PPROC p)
{
	p->ri = *(p->rm + p->pc); // Busca instrucao do ender
	*(p->rm + p->ri) = p->ac; // REM <- RDM; RDM <- AC
	exibe_processador(p);
	p->pc++;
}

void instrucao_lda(PPROC p)
{
	p->ri = *(p->rm + p->pc); // Busca instrucao do ender
	p->ac = *(p->rm + p->ri); // REM <- RDM; AC <- RDM
	atualiza_flag(p);
	exibe_processador(p);
	p->pc++;
}

void instrucao_add(PPROC p)
{
	p->ri = *(p->rm + p->pc);         // Busca instrucao do ender
	p->ac = p->ac + *(p->rm + p->ri); // REM <- RDM; AC <- AC + RDM
	atualiza_flag(p);
	exibe_processador(p);
	p->pc++;
}

void instrucao_or(PPROC p)
{
	p->ri = *(p->rm + p->pc);         // Busca instrucao do ender
	p->ac = p->ac | *(p->rm + p->ri); // REM <- RDM; AC <- AC OR RDM
	atualiza_flag(p);
	exibe_processador(p);
	p->pc++;
}

void instrucao_and(PPROC p)
{
	p->ri = *(p->rm + p->pc);         // Busca instrucao do ender
	p->ac = p->ac & *(p->rm + p->ri); // REM <- RDM; AC <- AC AND RDM
	atualiza_flag(p);
	exibe_processador(p);
	p->pc++;
}

void instrucao_not(PPROC p)
{
	p->ac = (~p->ac)+1; // AC <- NOT(AC); Representado em complemento de 2
	atualiza_flag(p);
}

void instrucao_jmp(PPROC p)
{
	p->ri = *(p->rm + p->pc); // Busca instrucao do ender
	exibe_processador(p);
	p->pc = p->ri;            // PC <- RDM
}

void instrucao_jn(PPROC p)
{
	p->ri = *(p->rm + p->pc); // Busca instrucao do ender
	exibe_processador(p);
	if (p->flag == N) {
		p->pc = p->ri;       // PC <- RDM
	}
	else {
		p->pc++;
	}
}

void instrucao_jz(PPROC p)
{
	p->ri = *(p->rm + p->pc); // Busca instrucao do ender
	exibe_processador(p);
	if (p->flag == Z) {
		p->pc = p->ri;       // PC <- RDM
	}
	else {
		p->pc++;
	}
}

void instrucao_hlt(PPROC p)
{
    printf("|               TERMINO DE EXECUCAO                |\n");
    printf("+--------------------------------------------------+\n");
}
