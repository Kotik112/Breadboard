// Arman Iqbal 09-11-21

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

/* 
Height and width of the breadboard. 
'resistor_count' keeps track of the number of resistors connected to the breadboard.
resistances contains resistor_t* that point to resistor_t pointers allocated on the heap. */
typedef struct Breadboard{
    int height;
    int width;
    int resistor_count;
    resistor_t** resistances;
} breadboard_t;

/* Creates and returns a breadboard pointer. */
breadboard_t* bb_create_breadboard(int width, int height);

/* Adds a resistance to to the breadboard.  */
enum bb_resistance_add_result bb_add_resistance(breadboard_t* bb_pointer, resistor_t* res_pointer);

/* Checks if there is a resistance on the breadboard at the given row and column. */
bool is_resistance_on_breadboard(breadboard_t *bb_pointer, int row, int col);

/* Returns the resistance pointer of reachable resistors from given position */
resistor_t* bb_get_resistance_on_breadboard(breadboard_t *bb_pointer, int row, int col);

/* Prints the breadboard. */
void bb_print_breadboard(breadboard_t* bb_pointer);

/* Deletes a resistor from breadboard and frees its memory */
void bb_delete_resistor(breadboard_t* bb, int index);

/* Sorts resistors after performing a 'delete_resistor'. */
void bb_move_resistors_up(breadboard_t* bb, int index);

/* Saves the the breadboard to a binary file. */
bool bb_save_breadboard(char* filename, breadboard_t* bb_pointer);

/* Reads the breadboard from a binary file. */
breadboard_t* bb_read_breadboard_from_file(char* filename, breadboard_t *bb_pointer);

/* Saves all resistors to a binary file. */
bool bb_save_resistances(char* filename, breadboard_t* bb_pointer);

/* Reads the resistors from a binary file. */
bool bb_read_resistances_from_file(char* filename, breadboard_t* bb_pointer);
#endif