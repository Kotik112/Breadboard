#ifndef BREADBOARD_H
#define BREADBOARD_H

#include <stdio.h>
#include <stdbool.h>

#include "resistance.h"

typedef struct {
    int height;
    int width;
    /* Keep track of what cells are occupied.
    bool occupied; */
    //pointer to resistance here
} Breadboard;

Breadboard *create_breadboard(int height, int width);
int breadboard_add_resistance(Breadboard *bb_pointer, Resistance *res_pointer);

#endif