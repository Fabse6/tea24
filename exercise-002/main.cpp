#include <fmt/chrono.h>
#include <fmt/format.h>

#include "module.h"

auto main(int argc, char** argv) -> int
{
    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", argv[0]);

    fmt::print("\n\n\nTeil 1:\n\n");

    doSomethingStatic();
    doSomethingStatic();
    doSomethingStatic();


    fmt::print("\n\n\nTeil 2:\n\n");

    staticVariables();
    // moduleVariable ist in module.cpp als static definiert und hier daher
    // nicht sichtbar. Wird die folgende Zeile aktiviert, entsteht ein
    // Compilerfehler; try/catch kann das nicht abfangen.
    // fmt::print("moduleVariable: {}", moduleVariable);

    fmt::print("\n\n\nTeil 3\n\n");

    doSomethingStatic();
    staticVariables();
    staticConstVariables();
    return 0; /* exit gracefully*/
}

/*
 * 
 *
 * 1. static innerhalb einer Funktion
 * doSomethingStatic() initialisiert value genau einmal mit 56 und erhoeht
 * ihn bei jedem Aufruf. Daher steigt der Wert weiter, waehrend Adresse und
 * Lebensdauer der Variable gleich bleiben. Eine normale lokale Variable
 * wird bei jedem Aufruf neu angelegt und initialisiert; ihr Zustand bleibt
 * nicht zwischen Aufrufen erhalten.
 *
 * 2. static auf Modulebene
 * Eine Datei-scope-Variable mit static hat interne Bindung: Nur Funktionen
 * derselben Uebersetzungseinheit koennen sie direkt verwenden. Sie sollte
 * daher nicht in module.h deklariert werden. Eine nicht initialisierte
 * moduleCounter-Variable liegt typischerweise in .bss; moduleValue = 123
 * typischerweise in .data.
 *
 * 3. Speichersegmente
 * Nicht-null initialisierte veraenderbare globale/statische Variablen liegen
 * typischerweise in .data; nicht initialisierte oder null-initialisierte in
 * .bss. const-Daten wie moduleConst = 77 liegen typischerweise in .rodata,
 * sofern der Compiler sie dort ablegt und sie nicht veraenderbar sein muessen.
 * Das sind uebliche Konventionen, keine fuer jede Plattform garantierten
 * Regeln. Auch eine static-lokale Variable hat statische Lebensdauer; die
 * Variable aus doSomethingStatic() ist veraenderbar und initialisiert, also
 * typischerweise in .data.
 *
 * 4. Bonus: gleichnamige Variablen
 * Eine Datei-scope-Variable mit static in module.cpp und eine globale
 * Variable gleichen Namens in main.cpp sind verschiedene Objekte mit
 * verschiedenen Adressen. Die static-Variable ist nur in module.cpp
 * sichtbar; die globale Variable kann programmweit ueber ihre externe
 * Bindung verwendet werden.
 *
 * 5. Bonus: Include Guard und Header/Linker
 * Ein Include Guard verhindert, dass ein Header innerhalb derselben
 * Uebersetzungseinheit mehrfach verarbeitet wird. Definitionen globaler
 * Variablen in mehrfach eingebundenen Headern koennen Mehrfachdefinitionen
 * beim Linken verursachen; dort gehoeren meist Deklarationen wie extern hin,
 * waehrend die Definition genau einmal in einer .cpp-Datei steht. Fehlt zu
 * einer extern-Deklaration eine Definition, meldet der Linker ein nicht
 * aufgeloestes Symbol. Abweichende Funktionssignaturen passen nicht zur
 * Deklaration. const-Korrektheit ist einzuhalten: Ein const-Objekt darf
 * beispielsweise nicht ueber einen nicht-const-Zeiger veraendert werden.
 *
 * 6. Bonus: Null- und Nicht-Null-Initialisierung
 * Globale/statische a und b = 0 liegen oft in .bss, c = 1 typischerweise in
 * .data und const int d = 1 typischerweise in .rodata. Die genaue Zuordnung
 * haengt von Compiler, Plattform, Linker und Nutzbarkeit des Symbols ab;
 * deshalb prueft man sie mit size/nm statt sie als universell anzunehmen.
 */
