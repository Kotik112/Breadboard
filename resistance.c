#include <stdio.h>
#include <stdlib.h>
#include "resistance.h"

Resistance* create_resistance(int row, int col_start, int col_end, float value) {
    Resistance * res_ptr = malloc(sizeof(Resistance));
    if(res_ptr == NULL) {
        fprintf(stderr, "Failed to allocate memory for the resistor.\n");
        return NULL;
    }
    res_ptr->cell_row = row;
    res_ptr->start_cell_col = col_start;
    res_ptr->end_cell_col = col_end;
    res_ptr->resistance_value = value;

    return res_ptr;
}

int travel_resistor(Resistance* resistor, const int start_col) {
    if (start_col == resistor->start_cell_col) {
        return resistor->end_cell_col;
    }
    else if (start_col == resistor->end_cell_col) {
        return resistor->start_cell_col;
    }
    else {
        return -1;
    }
    
}



