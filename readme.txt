Important: The program was written on Windows and has not been tested on any other operating systems.

1. Compilation
    To compile the program simply run the makefile included in the zip file.
    Output executable will be called "bb.exe" on Windows. Change to "bb.out" on Unix based OS.
    (remove the -g flag from the makefile if it causes issues on another OS)

2. Menu and Output
    The program by default creates an unusable '0 * 0' breadboard. The user has to either create a new breadboard (Option 5 on menu) 
    or read a previously saved breadboard state from file (Option 6 on menu).

**********   MAIN MENU    **********
1.  Show breadboard and a list of resistors.
2.  Insert a resistor.
3.  Delete a resistor.
4.  Calculate the resistance and connection between two points.
5.  Create a new breadboard.
6.  Open Breadboard from file.
7.  Save Breadboard to file.
8.  Exit without saving.
     
     
4. Output from "Calculate the resistance and connection between two points"
    
The output from this acts as follows.
- "No path found between points" if no path was found.
- "Resistance = 0.000" if start and end col are the same.
- "Resistance = x.xxx" if a connection was found. The x represent the eventual output.
