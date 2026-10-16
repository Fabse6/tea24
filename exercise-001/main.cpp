#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void foo();

int globalVar = 1;
static int globalVarStatic = 1;
const int globalVarConst = 1;
int globalVarZero = 0;
static int globalVarZeroStatic = 0;
const int globalVarZeroConst = 0;
int globalVarNothing;
static int globalVarNothingStatic;
// const int globalVarNothingConst;

int main(int argc, char **argv) {

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/12.0/api/
     */
    fmt::print("Hello, {}!\n", tea::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */

    // Teil 1: 
    fmt::println("\nGlobal\n");
    fmt::println("[Beliebig] Adresse: {}", fmt::ptr(&globalVar));
    fmt::println("[Zero] Adresse: {}", fmt::ptr(&globalVarZero));
    fmt::println("[Nothing] Adresse: {}", fmt::ptr(&globalVarNothing));
    fmt::println("[Beliebig Static] Adresse: {}", fmt::ptr(&globalVarStatic));
    fmt::println("[Zero Static] Adresse: {}", fmt::ptr(&globalVarZeroStatic));
    fmt::println("[Nothing Static] Adresse: {}", fmt::ptr(&globalVarNothingStatic));
    fmt::println("[Beliebig Const] Adresse: {}", fmt::ptr(&globalVarConst));
    fmt::println("[Zero Const] Adresse: {}", fmt::ptr(&globalVarZeroConst));
    // fmt::println("[Nothing Const] Adresse: {}", fmt::ptr(&globalVarNothingConst));


    // Teil 2: 
    fmt::println("\nLokal\n");
    int localVar = 1;
    int localVarZero = 0;
    int localVarNothing;
    static int localVarStatic = 1;
    static int localVarZeroStatic = 1;
    static int localVarNothingStatic;
    const int localVarConst = 1;
    const int localVarZeroConst = 0;
    fmt::println("[Beliebig] Adresse: {}", fmt::ptr(&localVar));
    fmt::println("[Zero] Adresse: {}", fmt::ptr(&localVarZero));
    fmt::println("[Nothing] Adresse: {}", fmt::ptr(&localVarNothing));
    fmt::println("[Beliebig Static] Adresse: {}", fmt::ptr(&localVarStatic));
    fmt::println("[Zero Static] Adresse: {}", fmt::ptr(&localVarZeroStatic));
    fmt::println("[Nothing Static] Adresse: {}", fmt::ptr(&localVarNothingStatic));
    fmt::println("[Beliebig Const] Adresse: {}", fmt::ptr(&localVarConst));
    fmt::println("[Zero Const] Adresse: {}", fmt::ptr(&localVarZeroConst));
    


    // Teil 3: 
    fmt::println("\nDynamische allozierte Variablen\n");
    int* heapVar = new int(3);
    fmt::println("Adresse: {}", fmt::ptr(heapVar));

    // Teil 4:
    fmt::println("\nFunktionen\n");
    fmt::println("Adresse: {}", fmt::ptr(&foo));

    // Zusatz: Beschreibung des Arbeitsspeichers
    
/******************************************************************************
 * FAZIT: Speicherverwaltung und Arbeitsspeicher-Layout in der Mikrocomputertechnik
 ******************************************************************************
 * 
 * 1. Speicherorte der verschiedenen Variablentypen:
 *    - Lokale Variablen (automatisch): 
 *      Werden auf dem STACK gespeichert. Ihre Lebensdauer ist an den 
 *      jeweiligen Funktions-Scope gebunden.
 *    - Globale & Statische Variablen (auch lokale static): 
 *      Werden im DATA-/BSS-Segment gespeichert. Sie existieren während der 
 *      gesamten Laufzeit des Programms.
 *    - Konstanten (const): 
 *      Liegen im geschützten READ-ONLY / TEXT-Segment, um unbeabsichtigtes 
 *      Überschreiben zu verhindern.
 *    - Dynamisch allokierte Variablen (malloc/new): 
 *      Werden auf dem HEAP gespeichert und müssen manuell verwaltet werden.
 *    - Programmcode (Funktionen): 
 *      Befindet sich ebenfalls im TEXT-Segment.
 * 
 * 2. Warum ist die Unterscheidung zwischen Stack und Heap wichtig?
 *    - Stack: Sehr schneller Zugriff, automatische Speicherfreigabe beim 
 *      Verlassen einer Funktion. Allerdings ist die Größe stark begrenzt 
 *      (Gefahr des "Stack Overflow").
 *    - Heap: Bietet flexiblen, dynamisch anpassbaren Speicherplatz für große 
 *      oder zur Compile-Zeit noch unbekannte Datenmengen. Erfordert jedoch 
 *      eine manuelle Verwaltung (Gefahr von "Memory Leaks" oder "Dangling Pointers").
 * 
 * 3. Die Rolle von Zeigern (Pointers):
 *    - Zeiger speichern reine Speicheradressen (wie die oben gemessenen Hex-Werte).
 *    - Sie schlagen die Brücke zwischen dem Stack und dem Heap, da dynamisch 
 *      auf dem Heap erstellter Speicher ausschließlich über Zeiger referenziert 
 *      und angesprochen werden kann.
 *    - Zudem ermöglichen sie Call-by-Reference, um große Datenstrukturen effizient 
 *      ohne unnötiges Kopieren an Funktionen zu übergeben.
 * 
 * 4. Skizze des Arbeitsspeichers (von hohen zu niedrigen Adressen):
 * 
 *    +---------------------------------------+  <- Hohe Adressen (z. B. 0x7fff...)
 *    | STACK                                 |  (Wächst nach UNTEN)
 *    | - Lokale Variablen                    |  - Automatische Verwaltung
 *    +---------------------------------------+
 *    |                  |                    |
 *    |                  v                    |
 *    |                  .                    |
 *    |                  ^                    |
 *    |                  |                    |
 *    | HEAP                                  |  (Wächst nach OBEN)
 *    | - Dynamischer Speicher (malloc/new)   |
 *    +---------------------------------------+
 *    | DATA- & BSS-SEGMENT                   |
 *    | - Globale & statische Variablen       |
 *    +---------------------------------------+
 *    | TEXT- / CODE-SEGMENT                  |
 *    | - Programmcode (Funktionen)           |
 *    | - Globale Konstanten (Read-Only)      |
 *    +---------------------------------------+  <- Niedrige Adressen (z. B. 0x0040...)
 ******************************************************************************/
    
    

    return 0; /* exit gracefully*/
}

void foo() { fmt::print("Hello from foo!\\n"); }