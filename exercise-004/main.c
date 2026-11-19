#include <stdio.h>   // stdio.h stellt unter anderem putc und stdout bereit.
#include "greet.h"   // Eigener Header: Hier wird das Makro ZEICHEN definiert.

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