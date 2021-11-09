// Arman Iqbal 09-11-21

#ifndef RESISTANCE_H
#define RESISTANCE_H

#include <stdio.h>

typedef struct Resistance{
    int start_cell_col;
    int end_cell_col;
    int cell_row;
    float resistance_value;
} resistor_t;

/* Creates a resistance pointer and returns it. */
resistor_t* create_resistance(int row, int col_start, int col_end, float value);

/* Spits out the colums number of the opposite end of the resistor */
int travel_resistor(resistor_t* resistor, const int start_col);    
#endif