#ifndef PROCESSADOR_H
#define PROCESSADOR_H
#include "memoria.h"
/* Conjunto de instrucoes */
#define NOP		0
#define STA		16
#define LDA		32
#define ADD		48
#define OR		64
#define AND		80
#define NOT		96
#define JMP		128
#define JN		144
#define JZ		160
#define HLT		240
/* Codigos de condicao do registrador de estado (flags) */
#define Z 1
#define N 2

typedef struct s_processador PROC; // Struct PROC
struct s_processador {
	unsigned char pc;   // Contador de programa
    unsigned char ac;   // Acumulador
    unsigned char ri;   // Registro de instrucao
    unsigned char *rm;  // Registrador de memoria (Registrador de dados e enderecos da memoria)
    unsigned char flag; // Registrador de estado (flags Z e N)
};

typedef PROC *PPROC; // Ponteiro da struct PROC

PPROC aloca_processador();
void inicializa_simulador(PPROC p, PMEM m);
int executa_simulador(PPROC p);
int executa_instrucoes(PPROC p);
void atualiza_flag(PPROC p);
void instrucao_nop();
void instrucao_sta(PPROC p);
void instrucao_lda(PPROC p);
void instrucao_add(PPROC p);
void instrucao_or(PPROC p);
void instrucao_and(PPROC p);
void instrucao_not(PPROC p);
void instrucao_jmp(PPROC p);
void instrucao_jn(PPROC p);
void instrucao_jz(PPROC p);
void instrucao_hlt(PPROC p);

#endif
