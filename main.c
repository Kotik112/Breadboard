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

/* argv[1] = width    &    argv[2] = height */
int main(int argc, char *argv[]){

    int width = get_int_input("Enter the width of the breadboard: \n");
    int height = get_int_input("Enter the height of the breadboard: \n");
    
    Breadboard* bb = create_breadboard(width, height);


    Resistance* r1 = create_resistance(2, 1, 4, 0.5);
    Resistance* r2 = create_resistance(2, 2, 5, 0.3);
    Resistance* r3 = create_resistance(3, 0, 3, 0.7);

    breadboard_add_resistance(bb, r1);
    breadboard_add_resistance(bb, r2);
    breadboard_add_resistance(bb, r3);

    print_breadboard(bb);


    return 0;
}

