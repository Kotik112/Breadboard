#include <stdlib.h>
#include <string.h>
#include "breadboard.h"
#include "resistance.h"

/* Creates and returns a breadboard pointer */
Breadboard* bb_create_breadboard(const int width, const int height) {
    Breadboard* ptr = malloc(sizeof(Breadboard));
    if(ptr == NULL) {
        fprintf(stderr, "Failed to allocate memory for the breadboard. (create_resistance)\n");
        return NULL;
    }
    ptr->width = width;
    ptr->height = height;
    ptr->resistance_count = 0;
    ptr->resistances = malloc(sizeof(Resistance*) * ((height * width) / 2));
    if (ptr->resistances == NULL) {
        fprintf(stderr, "Failed to allocate memory for the resistances. (create_resistance)\n");
        return NULL;
    }
    return ptr;
}

enum bb_resistance_add_result bb_add_resistance(Breadboard* bb_pointer, Resistance* res_pointer) {
    // check if its within the board min/max rows/cols
    printf("Adding resistance row: %d, cols %d - %d\n", res_pointer->cell_row, 
                                        res_pointer->start_cell_col, res_pointer->end_cell_col);
    
    if(res_pointer->cell_row < 0 || res_pointer->cell_row > bb_pointer->height - 1) {
        fprintf(stderr, "Outside breadboard vertically.\n");
        return outside_breadboard;
    }

    if(res_pointer->start_cell_col < 0 || res_pointer->end_cell_col > bb_pointer->width - 1) {
        fprintf(stderr, "Outside breadboard horizontally.\n");
        return outside_breadboard;
    }

    // check if it overlaps
    for (int i = res_pointer->start_cell_col; i <= res_pointer->end_cell_col; i++) {
        if (is_resistance_on_breadboard(bb_pointer, res_pointer->cell_row, i)) {
            fprintf(stderr, "Overlappin at row: %d, col: %d\n", res_pointer->cell_row, i);
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

Resistance* bb_get_resistance_on_breadboard(Breadboard *bb_pointer, int row, int col) {
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

void bb_print_breadboard(Breadboard *bb_pointer) {
    printf("    ");
    for (int idx = 0; idx < bb_pointer->width; idx++) {
            printf(" %d ", idx+1);
    }
    printf("\n");
    for (int r = 0; r < bb_pointer->height; r++) {
        if (r <= 8) {printf(" %d  ", r+1);}
        else {printf(" %d ", r+1);}
    
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

void bb_move_resistors_up(Breadboard* bb, int index) {
    for (int i = index; i < bb->resistance_count-1; i++) {
        bb->resistances[i] = bb->resistances[i+1];
    }
}

/* Deletes a resistor from breadboard and frees its memory */
void bb_delete_resistor(Breadboard *bb, int index) {
    free(bb->resistances[index]);
    bb_move_resistors_up(bb, index);
    bb->resistance_count--;
}

/* Checks for any resistors on current column */
int bb_check_resistor_on_col(Breadboard* bb_pointer, int* current_column, int* current_row) {
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

bool bb_save_breadboard(char* filename, Breadboard* bb_pointer) {
    errno_t error_code;
    FILE* fp;
    
    /* Opens board.bin to save the board struct on. */
    error_code = fopen_s(&fp, filename, "wb");
    if (error_code != 0) {
        fprintf(stderr, "Error! Failed to open %s in wb mode!\n", filename);
        return false;
    }
    /* Temporarily saves resistances in tmp and sets resistances to NULL to avoid
                                        issues when re-reading the binary file.*/
    void *tmp = bb_pointer->resistances;
    bb_pointer->resistances = NULL;

    if (fwrite(bb_pointer, sizeof(Breadboard), 1, fp) != 1) {
        fprintf(stderr, "Error! Failed to write to file!\n");
        return false;
    }
    bb_pointer->resistances = tmp;
    fclose(fp);
    return true;
}

Breadboard* bb_read_from_file(char* filename) {
    FILE* fp;
    Breadboard* ptr = malloc(sizeof(Breadboard));
    if(ptr == NULL) {
        fprintf(stderr, "Error! Failed to allocate memory for the breadboard.\n");
        return NULL;
    }
    errno_t error_code = fopen_s(&fp, filename, "rb");
    if (error_code != 0) {
        fprintf(stderr, "Error! Failed to open %s in rb mode!\n", filename);
        return NULL;
    }
    
    ptr->resistances = malloc(sizeof(Resistance*) * ((ptr->height * ptr->width) / 2));
    if (ptr->resistances == NULL) {
        fprintf(stderr, "Error! Failed to allocate memory for the resistances.\n");
        return NULL;
    }

    fclose(fp);
    return ptr;
}

bool bb_save_resistances(char* filename, Breadboard* bb_pointer) {
    FILE* fp;
    /* Opens 'filename' to save the list of resistance pointers on. */
    errno_t error_code = fopen_s(&fp, filename, "wb");
    if (error_code != 0) {
        fprintf(stderr, "Error! Failed to open %s in wb mode!\n", filename);
        return false;
    }
    for (int i = 0; i < bb_pointer->resistance_count; i++) {
        if (fwrite(bb_pointer->resistances[i], sizeof(Resistance), 1, fp) != 1) {
            fprintf(stderr, "Error! Failed saving resistances!\n");
            return false;
        }
    }
    fclose(fp);

    return true;
}

bool bb_read_resistances_from_file(char* filename, Breadboard* bb_pointer) {
    FILE* fp;
    Breadboard* ptr = malloc(sizeof(Resistance));
    if(ptr == NULL) {
        fprintf(stderr, "Error! Failed to allocate memory for the breadboard.\n");
        return false;
    }
    errno_t error_code = fopen_s(&fp, filename, "rb");
    if (error_code != 0) {
        fprintf(stderr, "Error! Failed to open %s in rb mode!\n", filename);
        return false;
    }
    size_t res_count = (size_t) bb_pointer->resistance_count;
    size_t elements_written = fread(bb_pointer->resistances, sizeof(Resistance), bb_pointer->resistance_count, fp);
    if (elements_written != res_count) {
        fprintf(stderr, "Error! Failed to open %s in rb mode!\n", filename);
    }
    fclose(fp);
    return true;
}






