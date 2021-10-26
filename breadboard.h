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
    Resistance** resistances;
    int resistance_count;

} Breadboard;

Breadboard *create_breadboard(int width, int height);
enum resistance_add_result breadboard_add_resistance(Breadboard *bb_pointer, Resistance* res_pointer);
bool is_resistance_on_breadboard(Breadboard *bb_pointer, int row, int col);
void print_breadboard(Breadboard *bb_pointer);
#endif