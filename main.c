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
    float resistance_value = get_int_input("Enter the resistance value of the resistor:\n");

    Resistance* new_resisor = create_resistance(row, col_start, col_end, resistance_value);

    breadboard_add_resistance(bb, new_resisor);
}

void print_resistors(Breadboard* bb) {
    printf("*****   RESISTORS   *****\n");
    for (int i = 0; i < bb->resistance_count; i++) {
        printf("%d: Row: %d, Start column: %d, End column: %d, Resistance value: %.2f.\n",
        i+1, bb->resistances[i]->cell_row, bb->resistances[i]->start_cell_col,
        bb->resistances[i]->end_cell_col, bb->resistances[i]->resistance_value);
    }
    printf("\n");
} 

void delete_resistor(Breadboard* bb) {
    print_resistors(bb);
    int resistor_choice = get_int_input("Enter the resistor you want to delete. (Number): \n");
    
    /* To adjust the number to its corresponding index. */
    resistor_choice--;

    delete_resistance(bb->resistances[resistor_choice]);
    /* Note: Need to double check this section! */
    bb->resistance_count--;
}

bool check_circuit(Breadboard* bb_pointer, const int check_row, const int check_col) {
    for(int i = 0; i < bb_pointer->resistance_count; i++) {
        /* Check if chosen row has a resistor(1) end-point */
        if(bb_pointer->resistances[i]->cell_row == check_row) {
            /* Checks is the chosen column has a resistor(1) end-point */
            if(bb_pointer->resistances[i]->start_cell_col == check_col && bb_pointer->resistances[i]->end_cell_col == check_col) {
                /* If found, loop over all resostors again and check for any other resistors are at the same column */
                for (int j = 0; j < bb_pointer->resistance_count; j++) {
                    /* Checks the other end of resistor(1) and checks if that end has any other resistors at that column. */
                    if (bb_pointer->resistances[i]->end_cell_col == bb_pointer->resistances[j]->start_cell_col || 
                                bb_pointer->resistances[i]->end_cell_col == bb_pointer->resistances[j]->end_cell_col) {
                        //int row = bb_pointer->resistances[j]->end_cell_col;
                        //check_circuit(bb_pointer, bb_pointer->resistances[i]->cell_row, bb_pointer->resistances[j]->end_cell_col);
                    }
                }
            }
        }
    }
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
            printf("WIP: Check Circuit.\n");
            break;

         case 5:
            printf("WIP: Check Resistance.\n");
            break;

        case 6:
            printf("EXIT. (WIP: Save to file).\n");
            //clean_up();  free() the malloc
            loop_status = false;
            break;
        
        default:
            printf("Incorrect input. You must choose between 1-6.\n");
            break;
        }
    }
    


//      FOR TESTING PURPOSES
/*     Resistance* r1 = create_resistance(2, 1, 4, 0.5);
    Resistance* r2 = create_resistance(2, 2, 5, 0.3);
    Resistance* r3 = create_resistance(3, 0, 3, 0.7);

    breadboard_add_resistance(bb, r1);
    breadboard_add_resistance(bb, r2);
    breadboard_add_resistance(bb, r3); */

    


    return 0;
}

