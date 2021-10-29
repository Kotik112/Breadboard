#include <stdlib.h>
#include "breadboard.h"
#include "resistance.h"

/* Creates and returns a breadboard pointer */
Breadboard* create_breadboard(const int width, const int height) {
    Breadboard* ptr = malloc(sizeof(Breadboard));
    if(ptr == NULL) {
        printf("Failed to allocate memory for the breadboard. (create_resistance)\n");
        return -1;
    ptr->width = width;
    ptr->height = height;
    ptr->resistances = malloc(sizeof(Resistance*) * ((height * width) / 2));
    /*  */
    //ptr->free_slot = malloc(sizeof(bool)*((height*width)/2));
    ptr->resistance_count = 0;
    return ptr;
}

enum resistance_add_result breadboard_add_resistance(Breadboard *bb_pointer, Resistance* res_pointer) {
    // check if its within the board min/max rows/cols
    printf("Adding resistance row: %d, cols %d - %d\n", res_pointer->cell_row, res_pointer->start_cell_col, res_pointer->end_cell_col);
    
    if(res_pointer->cell_row < 0 || res_pointer->cell_row > bb_pointer->height-1) {
        printf("Outside breadboard vertically.\n");
        return outside_breadboard;
    }

    if(res_pointer->start_cell_col < 0 || res_pointer->end_cell_col > bb_pointer->width-1) {
        printf("Outside breadboard horizontally.\n");
        return outside_breadboard;
    }

    // check if it overlaps
    for (int i = res_pointer->start_cell_col; i <= res_pointer->end_cell_col; i++) {
        if (is_resistance_on_breadboard(bb_pointer, res_pointer->cell_row, i)) {
            printf("Overlappin at row: %d, col: %d\n", res_pointer->cell_row, i);

            return overlapping;
        }
    }

    // put resistance pointer into breadboard pointer array
    bb_pointer->resistances[bb_pointer->resistance_count] = res_pointer;
    // bump up the number of resistenaces on breadboard by one
    bb_pointer->resistance_count++;
    // return success
    return success;
}

bool is_resistance_on_breadboard(Breadboard *bb_pointer, int row, int col) {
    // printf("Checking if there's a resistance ccovering %d, %d.\n", row, col);
    for (int i = 0; i < bb_pointer->resistance_count; i++) {
        // printf("Resistance %d\n", i);
        if (bb_pointer->resistances[i]->cell_row == row) {

            int start_col = bb_pointer->resistances[i]->start_cell_col;
            int end_col = bb_pointer->resistances[i]->end_cell_col;

            // printf("start col %d\n", start_col);
            // printf("end col %d\n", end_col);

            for (int c = start_col; c <= end_col; c++) {
                // printf("column %d\n", c);
                if (c == col) {
                    return true;
                }
            }

        }
    }
    return false;
}

void print_breadboard(Breadboard *bb_pointer) {
    for (int r = 0; r < bb_pointer->height; r++) {
        for (int c = 0; c < bb_pointer->width; c++) {
            if (is_resistance_on_breadboard(bb_pointer, r, c)) {
                printf(" X ");
            }
            else {
                printf(" O ");
            }
        }
        printf("\n");
    }
    printf("\n");
}






