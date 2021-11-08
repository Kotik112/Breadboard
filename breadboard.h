#ifndef BREADBOARD_H
#define BREADBOARD_H

#include <stdio.h>
#include <stdbool.h>
#include "resistance.h"

enum bb_resistance_add_result {
    success = 0,
    overlapping = 1,
    outside_breadboard = 2
};

typedef struct Breadboard{
    int height;
    int width;
    int resistance_count;
    Resistance** resistances;
} Breadboard;

/* Creates and returns a breadboard pointer. */
Breadboard* bb_create_breadboard(int width, int height);
/* Adds a resistance to to the breadboard.  */
enum bb_resistance_add_result bb_add_resistance(Breadboard* bb_pointer, Resistance* res_pointer);
/* Checks if there is a resistance on the breadboard. */
bool is_resistance_on_breadboard(Breadboard *bb_pointer, int row, int col);

/*  */
Resistance* bb_get_resistance_on_breadboard(Breadboard *bb_pointer, int row, int col);

/* Prints the breadboard. */
void bb_print_breadboard(Breadboard* bb_pointer);

/* Deletes a resistor from breadboard and frees its memory */
void bb_delete_resistor(Breadboard* bb, int index);

/* Sorts resistors after performing a 'delete_resistor'. */
void bb_move_resistors_up(Breadboard* bb, int index);

/*  */
int bb_check_resistor_on_col(Breadboard* bb_pointer, int* current_column, int* current_row);

/*  */
bool bb_save_breadboard(char* filename, Breadboard* bb_pointer);

/*  */
Breadboard* bb_read_from_file(char* filename, Breadboard *bb_pointer);

/*  */
bool bb_save_resistances(char* filename, Breadboard* bb_pointer);

/*  */
bool bb_read_resistances_from_file(char* filename, Breadboard* bb_pointer);
#endif