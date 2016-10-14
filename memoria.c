#include <stdlib.h>
#include <stdio.h>
#include "memoria.h"

PMEM aloca_memoria()
{
    PMEM m = (PMEM) malloc(sizeof(MEM));
    if(!m) {
		printf("\nMemoria insuficiente!\n");
		exit(1);
    }
    m->posicao = m->valor;
    return m;
}
