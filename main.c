/* TODO:
 1!     Decide wether to use struct or 2D array for breadboard.
 2!     Can argv[] casted to int? Or straight up declated integer in main argument?
 3!     Define the breadboard at run-time OR build-time.
 4!     Lös problemet med resistance pekare.
 */

#include <stdio.h>
#include <stdbool.h>
#include "resistance.h"
#include "breadboard.h"

#define BB_WIDTH 10
#define BB_HEIGHT 10

/* argv[1] = width    &    argv[2] = height */
int main(int argc, char *argv[]){

    int width, height;
    printf("Enter the width of the breadboard: ");
    fgets(width, sizeof(width), stdin);
    printf("Enter the height of the breadboard: ");
    fgets(height, sizeof(height), stdin);

    Breadboard breadboard;
    breadboard.width = width;
    breadboard.height = height;




    return 0;
}