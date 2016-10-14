#ifndef MEMORIA_H
#define MEMORIA_H
#define TAMANHO_MEMORIA 256

typedef struct s_memoria MEM; // Struct MEM
struct s_memoria {
    unsigned char valor[TAMANHO_MEMORIA]; // Dado ou instrucao
    unsigned char *posicao; // Posicao de memoria
};

typedef MEM *PMEM; // Ponteiro da struct MEM

PMEM aloca_memoria();

#endif
