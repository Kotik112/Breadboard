#ifndef BREADBOARD_H
#define BREADBOARD_H

#include <stdio.h>
#include <stdbool.h>
#include "resistance.h"

enum resistance_add_result {
    success = 0,
    overlapping = 1,
    outside_breadboard = 2
};

typedef struct {
    int height;
    int width;
    Resistance** resistances;   //Define to an array? resistances[MAX_RES_NR]
    int resistance_count;

} Breadboard;

/* Creates and returns a breadboard pointer. */
Breadboard* create_breadboard(int width, int height);
/* Adds a resistance to to the breadboard.  */
enum resistance_add_result breadboard_add_resistance(Breadboard *bb_pointer, Resistance* res_pointer);
/* Checks if there is a resistance on the breadboard. */
bool is_resistance_on_breadboard(Breadboard *bb_pointer, int row, int col);

Resistance* get_resistance_on_breadboard(Breadboard *bb_pointer, int row, int col);

/* Prints the breadboard. */
void print_breadboard(Breadboard* bb_pointer);
/*  */
void breadboard_delete_resistor(Breadboard* bb, int index);
/*  */
void breadboard_move_resistors_up(Breadboard* bb, int index);

int check_resistor_on_col(Breadboard* bb_pointer, int* current_column, int* current_row);

#endif