#ifndef PALAVRA_H
#define PALAVRA_H

#include "set.h"

typedef struct
{
    char *valor;
    Set *postagens;
} Palavra;

#endif