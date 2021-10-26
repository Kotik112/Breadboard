/* TODO:
 1!     Decide wether to use struct or 2D array for breadboard.
 2!     Can argv[] casted to int? Or straight up declated integer in main argument?
 3!     Define the breadboard at run-time OR build-time.
 4!     Lös problemet med resistance pekare.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "resistance.h"
#include "breadboard.h"


int get_int_input(char *text) {
    char input[10]; 
   
    printf(text);
    fgets(input, sizeof(input), stdin);
    return atoi(input);
}
void print_main_menu(void) {
    printf("**********   MAIN MENU    **********\n");
    printf("1.  Show breadboard.\n");
    printf("2.  Insert a resistor.\n");
    printf("3.  Delete a resistor.\n");
    printf("4.  Check if two points has complete circuit.\n\n");
    //printf("5.  Check the total resistance between two points.\n");
    //printf("6.  Save breadboard to file.\n");
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
            /* Show breadboard. */

            break;

        case 2:
            /* Insert a resistor. */

            break;

        case 3:
            /* Delete a resistor. */

            break;

        case 4:
            /* Check if two points has complete circuit. */

            break;

         case 5:
            printf("WIP: Check Resistance.\n");
            break;

        case 6:
            printf("WIP: Save to file.\n");
            break;
        
        default:
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

