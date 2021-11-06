/* TODO:
1!  Solve how to handle deletion.
2!  Solve check circuit.
3!  
4!  Use free() to clean up all mem alloc after yourself.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "resistance.h"
#include "breadboard.h"

int get_int_input(const char *text) {
    char input[10]; 
   
    printf(text);
    fgets(input, sizeof(input), stdin);
    return atoi(input);
}


void new_resistor(Breadboard* bb) {
    int row = get_int_input("At what row would you like to place the resistor?:\n");
    int col_start = get_int_input("Enter the column you would like the resistor start at:\n"); 
    int col_end = get_int_input("Enter the column you would like the resistor end:\n");
    float resistance_value; 
    printf("Enter the resistance value of the resistor:\n");
    scanf("%f", &resistance_value);
    //check input
    getchar(); //removes new line from stdin.

    Resistance* new_resisor = create_resistance(row, col_start, col_end, resistance_value);
    if (new_resisor == NULL) {
        //Vad gör jag här?
    }

    breadboard_add_resistance(bb, new_resisor);
}

void print_resistors(Breadboard* bb) {
    printf("*****   RESISTORS   *****\n");
    for (int i = 0; i < bb->resistance_count; i++) {
        printf("%d: Row: %d, Start column: %d, End column: %d, Resistance value: %.2f.\n",
        i+1, 
        bb->resistances[i]->cell_row, 
        bb->resistances[i]->start_cell_col,
        bb->resistances[i]->end_cell_col, 
        bb->resistances[i]->resistance_value
        );
    }
    printf("\n");
} 

void delete_resistor(Breadboard* bb) {
    print_resistors(bb);
    int resistor_choice = get_int_input("Enter the resistor you want to delete. (Number): \n");
    /* To adjust the number to its corresponding index. */
    resistor_choice--;

    breadboard_delete_resistor(bb, resistor_choice);
    
}


bool check_circuit(Breadboard* bb_pointer) 
{
    int start_col = get_int_input("Enter the start colum: \n");
    int start_row = get_int_input("Enter the start row: \n");
    int end_col = get_int_input("Enter the end colum: \n");
    int* current_row = &start_row;
    int* current_column = &start_col;

    int whileloop_var = 1;
    while (whileloop_var)
    {
        int result = check_resistor_on_col(bb_pointer, current_column, current_row);
        if (result == -1) {
            printf("Circuit not complete. \n");
            whileloop_var = 0;
            return false;
        }
        if (*current_column == end_col) {
            whileloop_var = 0;
            return true;
        }   
    }
    return false;   
}

bool save_breadboard(char* filename[25], Breadboard* bb_pointer) {
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

bool save_resistances(char* filename[25], Breadboard* bb_pointer) {
    errno_t error_code;
    FILE* fp_resistances;
    /* Opens resistances.bin to save the array of resistance pointers on. */
    error_code = fopen_s(&fp_resistances, filename, "wb");
    if (error_code != 0) {
        printf("Error! Failed to open board.bat in wb mode!");
    }

    size_t elements_written = fwrite(bb_pointer->resistances, sizeof(Resistance), bb_pointer->resistance_count, fp_resistances);
    if (elements_written == 0) {
        return false;
    }
    fclose(fp_resistances);

    return true;
}

bool save_to_file(Breadboard* bb_pointer) {
    bool status_check;
    status_check = save_resistances("resistances.bin", bb_pointer);
    if (status_check == false) {
        printf("Save Resistances failed!\n");
        return false;
    }
    printf("Saved resistances file!\n");

    status_check = save_breadboard("bb.bin", bb_pointer);
    if (status_check == false) {
        printf("Save breadboard failed!\n");
        return false;
    }
    return true;
}

void clean_up(Breadboard* bb_pointer) {
    free(bb_pointer->resistances);
    free(bb_pointer);
}

void print_main_menu(void) {
    printf("**********   MAIN MENU    **********\n");
    printf("1.  Show breadboard and a list of resistors.\n");
    printf("2.  Insert a resistor.\n");
    printf("3.  Delete a resistor.\n");
    printf("4.  Check if two points has complete circuit.\n");
    printf("5.  Check the total resistance between two points.\n");
    printf("6.  Exit.\n"); //Eventually save to file.
}

int main(void){

    int width = get_int_input("Enter the width of the breadboard: \n");
    int height = get_int_input("Enter the height of the breadboard: \n");
    
    Breadboard* bb = create_breadboard(width, height);

    print_breadboard(bb);

    bool loop_status = true;
    while (loop_status)
    {
        print_main_menu();
        int user_choice = get_int_input("Enter your choice (1 - 4): \n");
        switch (user_choice)
        {
        case 1:
            /* "Show breadboard" menu. */
            print_breadboard(bb); 
            print_resistors(bb);
            break;

        case 2:
            /* "Insert a resistor" menu. */
            new_resistor(bb);
            break;

        case 3:
            /* "Delete a resistor" menu. */
            delete_resistor(bb);
            break;

        case 4:
            /* Check if two points has complete circuit. */
            check_circuit(bb);
            break;

         case 5:
            printf("WIP: Check Resistance.\n");
            break;

        case 6:
            printf("EXIT. (WIP: Save to file).\n");
            save_to_file(bb);
            loop_status = false;
            clean_up(bb);
            break;
        
        default:
            printf("Incorrect input. You must choose between 1-6.\n");
            break;
        }
    }
    return 0;
}

