#ifndef RESISTANCE_H
#define RESISTANCE_H

#include <stdio.h>

#include "breadboard.h"

typedef struct {
    int start_cell_col;
    int end_cell_col;
    int cell_row;
    float resistance_value;
} Resistance;



#endif