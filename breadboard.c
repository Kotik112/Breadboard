#include <stdlib.h>
#include <string.h>
#include "breadboard.h"
#include "resistance.h"

/* Creates and returns a breadboard pointer */
Breadboard* create_breadboard(const int width, const int height) {
    Breadboard* ptr = malloc(sizeof(Breadboard));
    if(ptr == NULL) {
        printf("Failed to allocate memory for the breadboard. (create_resistance)\n");
        return NULL;
    }
    ptr->width = width;
    ptr->height = height;
    ptr->resistances = malloc(sizeof(Resistance*) * ((height * width) / 2));
    if (ptr->resistances == NULL) {
        printf("Failed to allocate memory for the resistances. (create_resistance)\n");
        return NULL;
    }
    //ptr->free_slot = malloc(sizeof(bool) * ((height * width) / 2));
    ptr->resistance_count = 0;
    return ptr;
}

enum resistance_add_result breadboard_add_resistance(Breadboard* bb_pointer, Resistance* res_pointer) {
    // check if its within the board min/max rows/cols
    printf("Adding resistance row: %d, cols %d - %d\n", res_pointer->cell_row, 
                                        res_pointer->start_cell_col, res_pointer->end_cell_col);
    
    if(res_pointer->cell_row < 0 || res_pointer->cell_row > bb_pointer->height - 1) {
        printf("Outside breadboard vertically.\n");
        return outside_breadboard;
    }

    if(res_pointer->start_cell_col < 0 || res_pointer->end_cell_col > bb_pointer->width - 1) {
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

Resistance* get_resistance_on_breadboard(Breadboard *bb_pointer, int row, int col) {
    // printf("Checking if there's a resistance ccovering %d, %d.\n", row, col);
    for (int i = 0; i < bb_pointer->resistance_count; i++) {
        if (bb_pointer->resistances[i]->cell_row == row) {

            int start_col = bb_pointer->resistances[i]->start_cell_col;
            int end_col = bb_pointer->resistances[i]->end_cell_col;

            if (start_col == col) {
                return bb_pointer->resistances[i];
            }
            if (end_col == col) {
                return bb_pointer->resistances[i];
            }

        }
    }
    return NULL;
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

void breadboard_move_resistors_up(Breadboard* bb, int index) {
    for (int i = index; i < bb->resistance_count-1; i++) {
        bb->resistances[i] = bb->resistances[i+1];
    }
}

void breadboard_delete_resistor(Breadboard *bb, int index) {
    free(bb->resistances[index]);
    breadboard_move_resistors_up(bb, index);
    bb->resistance_count--;
}

/* Checks for any resistors on current column */
int check_resistor_on_col(Breadboard* bb_pointer, int* current_column, int* current_row) {
    for(int i = 0; i < bb_pointer->resistance_count; i++) {
        if (bb_pointer->resistances[i]->cell_row == i) {
            continue;
        }
        if (bb_pointer->resistances[i]->start_cell_col == *current_column || bb_pointer->resistances[i]->end_cell_col == *current_column) {
            *current_column = travel_resistor(bb_pointer->resistances[i], *current_column);
            *current_row = bb_pointer->resistances[i]->cell_row;
        }
    }
    return -1;
}

bool save_breadboard(char* filename, Breadboard* bb_pointer) {
    errno_t error_code;
    FILE* fp_board;
    
    /* Opens board.bin to save the board struct on. */
    error_code = fopen_s(&fp_board, filename, "wb");
    if (error_code != 0) {
        printf("Error! Failed to open bb.bat in wb mode!");
    }
    size_t elements_written = fwrite(bb_pointer, sizeof(Breadboard), 1, fp_board);
    if (elements_written == 0) {
        return false;
    }
    fclose(fp_board);
    return true;
}






