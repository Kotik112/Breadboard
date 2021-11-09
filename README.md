# Breadboard

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

        ------------------------------------------------------------------------------------------------------------------

Uppgift 1 - C Program

1 Uppgift

Uppgiften är att göra en enkel modellering av ett kopplingsdäck, “breadboard”. Kopplingsdäcket skall vara rektangulärt och dess storlek 
skall kunna sättas,antingen i build time eller run time. Kopplingsdäckets hål har kontakt vertikalt, dvs alla hål i en kolumn har elektrisk kontakt.
Du får själv välja hur du skriver ut kopplingsdäcket, men det skall vara en tydlig visuell representation.

2 Krav för godkänt

  2.1 Allmänna krav
- Koden skall vara uppdelad i moduler (filer) på ett genomtänkt sätt. 
- Koden skall kompilera utan varningar med -Wall.
Koden skall komma med en instruktion för hur man kompilerar och kör den. Det kan vara en Makefile, ett shell-skript eller bara en textfil med instruktioner.
Dataflödena i programmet skall vara genomtänkta. Onödig minneskopiering skall undvikas.
- Minnet skall hanteras korrekt, minne man har fått av malloc skall frias med free.

  2.2 Krav på lösningen
Användaren skall kunna placera ut resistorer på däcket horisontellt. Man skall inte kunna sätta mer än en komponent i ett hål.
Resistorer får heller inte överlappa.
Användaren skall kunna ta bort en resistor.

3 Krav för väl godkänt

Alla krav för godkänt skall vara uppfyllda.
Användaren skall kunna kontrollera om två punkter på kopplingsdäcket har kontakt (genom resistorerna).

4 Extra uppgifter

För den som vill utmana sig själv.
- Användaren skall kunna spara sitt kopplingsdäck till en fil, och läsa in det igen (med alla resistorer på plats, så klart).
- Räkna ut den totala resistansen mellan två punkter.


