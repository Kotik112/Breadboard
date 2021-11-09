/* 
C/C++ Programmering:
Uppgift 1 - Skapa en breadboard

Arman Iqbal 
09-11-21
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>

#include "resistance.h"
#include "breadboard.h"


int get_int_input(const char* text) {
    char input[10]; 
   
    printf(text);
    fgets(input, sizeof(input), stdin);
    return atoi(input);
}


/* Creates a new resistor and adds it to the breadboard. */
void new_resistor(breadboard_t* bb) {

    int row = get_int_input("At what row would you like to place the resistor?: ");
    int col_start = get_int_input("Enter the column you would like the resistor start at: "); 
    int col_end = get_int_input("Enter the column you would like the resistor end: ");
    float resistance_value; 
    printf("Enter the resistance value of the resistor: ");
    if (scanf("%f", &resistance_value) != 1) {
        fprintf(stdin, "Error! You did not enter a floating point number!\n");
    }       
    getc(stdin); //removes new line from stdin.

    /* Adjusts the offset of 1 from input. */
    row--;
    col_start--;
    col_end--;

    resistor_t* new_resisor = create_resistance(row, col_start, col_end, resistance_value);
    if (new_resisor == NULL) {
        fprintf(stderr, "Error! Create_resistance failed!\n");
    }

    bb_add_resistance(bb, new_resisor);
}

/* Prints all resistors attached to the breadboard. */
void print_resistors(breadboard_t* bb) {
    printf("**********   RESISTORS   **********\n");
    for (int i = 0; i < bb->resistor_count; i++) {
        printf("%d: Row: %d, Start column: %d, End column: %d, Resistance value: %.2f.\n",
        i+1, 
        bb->resistances[i]->cell_row+1, 
        bb->resistances[i]->start_cell_col+1,
        bb->resistances[i]->end_cell_col+1, 
        bb->resistances[i]->resistance_value
        );
    }
    printf("\n");
} 

/* Deletes a resistor. */
void delete_resistor(breadboard_t* bb) {
    print_resistors(bb);
    int resistor_choice = get_int_input("Enter the index of the resistor you want to delete: \n");
    /* To adjust the number to its corresponding index. */
    resistor_choice--;
    bb_delete_resistor(bb, resistor_choice);
}


/* The actual logic for the recursive function to check resistances */
float resistance_between_points_rec(breadboard_t* bb_pointer, const int x1, const int y1, const int x2, const int y2, int depth) {
    if (x1 == x2) {
        return 0;
    }
    
    float min_resistance = FLT_MAX;
    if (depth >= bb_pointer->width - 1) {
        return min_resistance;
    }

    for (int i = 0; i < bb_pointer->height; i++) {
        resistor_t* res = bb_get_resistance_on_breadboard(bb_pointer, i, x1);
        if (res != NULL) {
            float followed_resistance = res->resistance_value;
            int dest_col = travel_resistor(res, x1);
            followed_resistance += resistance_between_points_rec(bb_pointer, dest_col, i, x2, y2, ++depth);
            if (followed_resistance < min_resistance) {
                min_resistance = followed_resistance;
            }
        }
    }
    return min_resistance;
}

/* Recursive function that counts the total resistance between two points on the breadboard */
float resistance_between_points(breadboard_t* bb_pointer, const int x1, const int y1, const int x2, const int y2) {
    return resistance_between_points_rec(bb_pointer, x1, y1, x2, y2, 0);
}



/* Calculates the resistance between two points on the breadboard chosen by the user. */
void calculate_resistance(breadboard_t* bb_pointer) 
{
    int start_col = get_int_input("Enter the start colum: \n");
    int start_row = get_int_input("Enter the start row: \n");
    int end_col = get_int_input("Enter the end colum: \n");
    int end_row = get_int_input("Enter the end row: \n");

    /* Adjust user input to the correct index on breadboard. Offset of 1 */
    start_col--; 
    start_row--; 
    end_col--; 
    end_row--;

    float resistance = resistance_between_points(bb_pointer, start_col, start_row, end_col, end_row);
    if (resistance == FLT_MAX) {
        printf("No path found between points.\n");
    }
    else {
        printf("Resistance = %.3f\n", resistance);
    }
}


/*  */
bool save_to_file(breadboard_t* bb_pointer) {
    bool status_check;
    status_check = bb_save_resistances("resistances.bin", bb_pointer);
    if (status_check == false) {
        printf("Save Resistances failed!\n");
        return false;
    }
    printf("Saved resistances file!\n");

    status_check = bb_save_breadboard("bb.bin", bb_pointer);
    if (status_check == false) {
        printf("Save breadboard failed!\n");
        return false;
    }
    return true;
}

/* Frees up allocated */
void clean_up(breadboard_t* bb_pointer) {
    for (int i = 0; i < bb_pointer->resistor_count; i++) {
        free(bb_pointer->resistances[i]);
    }
    free(bb_pointer);
}

/*  */
void print_main_menu(void) {
    printf("**********   MAIN MENU    **********\n");
    printf("1.  Show breadboard and a list of resistors.\n");
    printf("2.  Insert a resistor.\n");
    printf("3.  Delete a resistor.\n");
    printf("4.  Calculate the resistance and connection between two points.\n");
    printf("5.  Create a new breadboard.\n");
    printf("6.  Open Breadboard from file.\n");
    printf("7.  Save Breadboard to file.\n");
    printf("8.  Exit without saving.\n\n");   
}


breadboard_t* create_new_breadboard(void) {
    int width = get_int_input("Enter the width of the breadboard: \n");
    int height = get_int_input("Enter the height of the breadboard: \n");

    breadboard_t* ptr = bb_create_breadboard(width, height);

    return ptr;
}

breadboard_t* read_breadboard(breadboard_t* bb_pointer) {
    breadboard_t* new_bb_pointer = bb_read_breadboard_from_file("bb.bin", bb_pointer);
    if (new_bb_pointer == NULL) {
        printf("bb_read_from_file failed!\n");
        return NULL;
    }
    printf("Breadboard we read is %d x %d with %d resistors.\n", new_bb_pointer->height, new_bb_pointer->width, new_bb_pointer->resistor_count);

    bool check = bb_read_resistances_from_file("resistors.bin", new_bb_pointer);
    if (!check) {
        fprintf(stderr, "bb_read_res failed.\n");
        return NULL;
    }
    return new_bb_pointer;
}

void save_breadboard(breadboard_t* bb_pointer){
    bool check = bb_save_resistances("resistors.bin", bb_pointer);
    if (!check) {
        fprintf(stderr, "Save resistors failed.\n");
    }
    check = bb_save_breadboard("bb.bin", bb_pointer);
    if (!check) {
        fprintf(stderr, "Save breadboard failed.\n");
    }

}

void print_intro(void) {
    printf("Welcome to the breadboard simulator!\n");
    printf("Start by either creating a new breadboard or opening one from file (if saved).\n");
    printf("Press any key to continue...");
    getchar();
    printf("\n\n\n");
}

int main(void){
    /* Default board */
    breadboard_t* bb = bb_create_breadboard(0,0);
    print_intro();

    bool loop_status = true;
    while (loop_status)
    {
        print_main_menu();
        int user_choice = get_int_input("Enter your choice (1 - 8): \n");
        switch (user_choice)
        {
        case 1:
        /* "Show breadboard" menu. */
            bb_print_breadboard(bb); 
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
            calculate_resistance(bb);
            break;

         case 5:
        /* Create a new breadboard. */
            bb = create_new_breadboard();
            break;

        case 6:
        /* Create a breadboard from file. */
            bb = read_breadboard(bb);
            break;

        case 7:
        /* Save breadboard to file. */
            save_breadboard(bb);
            break;

        case 8:
            clean_up(bb);
            exit(0);
            break;
        
        default:
            printf("Incorrect input. You must choose between 1-6.\n");
            break;
        }
    }
    return 0;
}

