#ifndef RESISTANCE_H
#define RESISTANCE_H

#include <stdio.h>

typedef struct {
    int start_cell_col;
    int end_cell_col;
    int cell_row;
    float resistance_value;
} Resistance;

Resistance *create_resistance(int row, int col_start, int col_end, float value);
    
#endif