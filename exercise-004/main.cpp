#include <stdio.h>   // stdio.h stellt unter anderem putc und stdout bereit.
#include "greet.h"   // Eigener Header: Hier wird das Makro ZEICHEN definiert.

/*
 * Aufgabe dieses kleinen Programms:
 * - Das Makro ZEICHEN aus greet.h verwenden
 * - Das Zeichen auf der Standardausgabe ausgeben
 * - Danach einen Zeilenumbruch ausgeben
 *
 * Die Datei ist sowohl als C- als auch als C++-Quelldatei nutzbar.
 * Sie wird in exercise-004 von CMake als C++-Programm gebaut.
 *
 * Wichtiger Zusammenhang fuer die README-Uebung:
 * - main.cpp oder main.c ist die Eingabe fuer Compiler und Assembler.
 * - greet.h wird durch den Praeprozessor in diese Datei eingefuegt.
 * - Der Aufruf von putc wird erst beim Linken mit der C-Bibliothek verbunden.
 */

int main(void)
{
    /*
     * Teil-A-Loesung:
     * Der Praeprozessor ersetzt das Makro ZEICHEN durch 'A'.
     * putc schreibt dieses Zeichen auf stdout.
     */
    putc(ZEICHEN, stdout);
    putc('\n', stdout);

    return 0;
}