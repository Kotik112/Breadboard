# Breadboard
Uppgift 1 - C Prog

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
