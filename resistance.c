#include <stdio.h>
#include <stdlib.h>
#include "resistance.h"

Resistance* create_resistance(int row, int col_start, int col_end, float value) {
    Resistance * res_ptr = malloc(sizeof(Resistance));
    if(res_ptr == NULL) {
        printf("Failed to allocate memory for the resistor. (create_resistance)\n");
        return -1;
    }
    res_ptr->cell_row = row;
    res_ptr->start_cell_col = col_start;
    res_ptr->end_cell_col = col_end;
    res_ptr->resistance_value = value;

    return res_ptr;
}

int delete_resistance(Resistance* resistor) {
    //free(resistor);
}