/* TODO:
1!  Comment relevent shit.
2!  Write it, cut it, paste it, save it, load it, check it, quick rewrite it
3!  Control input.
4!  Städa efter dig.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>

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

    bb_add_resistance(bb, new_resisor);
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
    int resistor_choice = get_int_input("Enter the index of the resistor you want to delete: \n");
    /* To adjust the number to its corresponding index. */
    resistor_choice--;
    bb_delete_resistor(bb, resistor_choice);
}



float resistance_between_points_rec(Breadboard* bb_pointer, const int x1, const int y1, const int x2, const int y2, int depth) {
    if (x1 == x2) {
        return 0;
    }
    
    float min_resistance = FLT_MAX;
    if (depth >= bb_pointer->width - 1) {
        return min_resistance;
    }

    for (int i = 0; i < bb_pointer->height; i++) {
        Resistance* res = bb_get_resistance_on_breadboard(bb_pointer, i, x1);
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

/*  */
float resistance_between_points(Breadboard* bb_pointer, const int x1, const int y1, const int x2, const int y2) {
    return resistance_between_points_rec(bb_pointer, x1, y1, x2, y2, 0);
}



/*  */
void calculate_resistance(Breadboard* bb_pointer) 
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
        printf("No patch found between points.\n");
    }
    else {
        printf("Resistance = %.3f\n", resistance);
    }
}


/*  */
bool save_to_file(Breadboard* bb_pointer) {
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

/*  */
void clean_up(Breadboard* bb_pointer) {
    for (int i = 0; i < bb_pointer->resistance_count; i++) {
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


Breadboard* create_new_breadboard(void) {
    int width = get_int_input("Enter the width of the breadboard: \n");
    int height = get_int_input("Enter the height of the breadboard: \n");

    Breadboard* ptr = bb_create_breadboard(width, height);

    return ptr;
}

void read_breadboard(Breadboard* bb_pointer) {
    void* tmp = bb_read_from_file("bb.bin");
    if (tmp != NULL) {
        bb_pointer = tmp;
    }
    bool check = bb_read_resistances_from_file("resistances.bin", bb_pointer);
    if (!check) {
        fprintf(stderr, "bb_read_res failed.\n");
    }
}

void save_breadboard(Breadboard* bb_pointer){
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
    printf("'5' - Creates a new breadboard.\n");
    printf("'6' - Open Breadboard from file.\n\n");
    printf("Press any key to continue...");
    getchar();
}

int main(void){
    /* Default board */
    Breadboard* bb = bb_create_breadboard(0,0);
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
            read_breadboard(bb);
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

