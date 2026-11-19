#include <fmt/format.h>

#include <version/version.h>

int main()
{
    fmt::print("Project: {}\n", projectName());
    fmt::print("Version: {}.{}.{}\n", major(), minor(), patch());
    fmt::print("Full: {}\n", fullVersion());
    fmt::print("At least 0.0.1: {}\n", isAtLeast(0, 0, 1));

    return 0;
}

/*
 * Fazit:
 * Header und configure_file:
 * - version/version.h ist der öffentliche Bibliotheks-Header: Er beschreibt
 *   die API, die Programme wie dieses verwenden.
 * - version_config.h wird beim CMake-Konfigurieren aus version_config.h.in
 *   erzeugt. Er enthält die konkreten Projekt-/Versionswerte und wird nur von
 *   version.cpp gebraucht.
 * - configure_file setzt Platzhalter wie @PROJECT_VERSION_MAJOR@ ein, damit
 *   Versionsdaten zentral aus der CMake-Projektkonfiguration kommen.
 *
 * PUBLIC, PRIVATE und Include-Pfade:
 * - PUBLIC bedeutet: Einstellung gilt für das aktuelle Target und wird an
 *   Targets weitergereicht, die es verwenden.
 * - PRIVATE gilt nur für das aktuelle Target. INTERFACE würde nur für dessen
 *   Nutzer gelten.
 * - In libs/version/CMakeLists.txt ist der include/-Pfad PUBLIC, weil Nutzer
 *   von version den Header <version/version.h> finden müssen.
 * - Der Pfad zum generierten version_config.h ist dort PRIVATE, weil nur
 *   version.cpp diesen internen Header einbindet. So wird kein unnötiges
 *   Implementierungsdetail an Nutzer weitergegeben.
 * - In exercise-003/CMakeLists.txt sind version und fmt::fmt PRIVATE
 *   gelinkt: Dieses Executable braucht beide, gibt seine Abhängigkeiten aber
 *   nicht an weitere Targets weiter. Das liegt nicht daran, dass fmt extern
 *   und version selbst erstellt ist; entscheidend ist, wer die Abhängigkeit
 *   benötigt.
 *
 * CMake-Verzeichnisse:
 * - CMAKE_CURRENT_SOURCE_DIR und CMAKE_CURRENT_BINARY_DIR werden von CMake
 *   automatisch gesetzt. Sie zeigen auf das Quell- bzw. Build-Verzeichnis
 *   des gerade verarbeiteten CMakeLists.txt.
 * - Bei libs/version/CMakeLists.txt ist der Source-Ordner also libs/version;
 *   CMAKE_CURRENT_BINARY_DIR ist der zugehörige Ordner unter build/. Dort
 *   wird version_config.h erzeugt. Der Include-Pfad dafür bleibt PRIVATE,
 *   solange der öffentliche Header ihn nicht selbst einbindet.
 * - Die Quelldatei src/version.cpp muss das version-Target kennen: Sie steht
 *   als Quelle in add_library(version STATIC src/version.cpp). CMake kompiliert
 *   sie und erstellt daraus libversion.a.
 * - exercise-003 muss den Pfad zu version.cpp nicht kennen. Es linkt gegen das
 *   CMake-Target version; dadurch kennt CMake die Abhängigkeit und bindet das
 *   erzeugte Bibliotheks-Artefakt beim Linken ein. Die .cpp-Implementierung
 *   bleibt so ein internes Detail der Bibliothek.
 *
 * Warum keine string-Library beim Linken:
 * - std::string gehoert zur C++-Standardbibliothek. <string> ist der Header
 *   fuer die Deklarationen; die benoetigte C++-Laufzeitbibliothek wird vom
 *   C++-Compiler und CMake-Target automatisch beim Linken beruecksichtigt.
 * - Deshalb gibt es kein separates string::string-Target, das hier wie
 *   fmt::fmt eingetragen werden muesste. fmt ist eine zusaetzliche Bibliothek
 *   ausserhalb des C++-Standards und wird deshalb explizit eingebunden.
 * - Wenn die Implementierung von version fmt verwendet, gehoert
 *   target_link_libraries(version PRIVATE fmt::fmt) in
 *   libs/version/CMakeLists.txt. PRIVATE haelt fmt aus der oeffentlichen
 *   Compile-Schnittstelle heraus. Bei einer statischen Bibliothek muss das
 *   Programm, das sie letztlich verwendet, fmt trotzdem linken: CMake reicht
 *   diese reine Link-Abhaengigkeit beim Verlinken des Verbrauchers weiter,
 *   ohne fmt-Include-Pfade als oeffentliches Interface weiterzugeben.
 * - Falls ein oeffentlicher Header von version fmt-Typen verwendet, muss fmt
 *   PUBLIC sein, damit Nutzer sowohl die Include-/Compile-Anforderungen als
 *   auch die Link-Abhaengigkeit erhalten.
 *
 * Statische und dynamische Bibliotheken:
 * - Eine statische Bibliothek (z. B. libversion.a) wird beim Linken in das
 *   Programm eingebunden. Das Programm enthaelt dann den benoetigten
 *   Bibliothekscode und kann normalerweise ohne die separate .a-Datei laufen.
 * - Eine dynamische Bibliothek (z. B. libversion.so) bleibt eine eigene Datei
 *   und wird zur Laufzeit geladen. Das Programm muss sie beim Start finden,
 *   sonst kann es nicht laufen.
 * - Statisch: einfacher zu verteilen, aber Bibliothekscode steckt in jedem
 *   Programm, das ihn nutzt; fuer ein Update muss das Programm neu gelinkt
 *   werden. Dynamisch: mehrere Programme koennen eine Bibliothek gemeinsam
 *   nutzen und sie separat aktualisieren, aber Deployment und Laufzeit muessen
 *   die passende Bibliotheksdatei bereitstellen.
 * - In CMake erzeugt add_library(version STATIC ...) eine statische und
 *   add_library(version SHARED ...) eine dynamische Bibliothek.
 * - Hier werden beide Varianten gebaut: version_cli nutzt version (statisch),
 *   version_shared_cli nutzt version_shared (dynamisch). Auf Linux sind die
 *   Artefakte .a und .so; Windows verwendet typischerweise .lib bzw. .dll mit
 *   einer Import-.lib. Embedded-Systeme nutzen oft statische Bibliotheken,
 *   weil sie kontrolliert deployt werden und haeufig keinen dynamischen
 *   Loader haben.
 *
 * Bonus: Vergleich und Wiederverwendung:
 * - isAtLeast vergleicht Major, Minor und Patch der Reihe nach. version_tests
 *   prueft Gleichheit sowie Versionen darunter und darueber; die Tests lassen
 *   sich mit CTest ausfuehren.
 * - version_cli ist ein zweiter Nutzer derselben statischen Bibliothek und
 *   version_shared_cli demonstriert den dynamischen Link. Beide rufen dieselbe
 *   API auf statt Versionscode zu kopieren.
 *
 * Bonus: C-API und Name Mangling:
 * - version_full_c ist in version_c_api.h in extern "C" deklariert und in
 *   C++ implementiert. c_consumer.c wird als C kompiliert und ruft sie auf.
 * - C++ mangelt Funktionsnamen, damit zum Beispiel ueberladene Funktionen
 *   unterschiedliche Symbole erhalten. extern "C" stellt fuer diese Funktion
 *   C-Linkage mit einem C-kompatiblen Symbolnamen bereit.
 * - Mit nm -C build/lib/libversion.a sieht man demanglete C++-Symbole; nm
 *   build/lib/libversion.a zeigt die rohen Symbole einschliesslich
 *   version_full_c. readelf -Ws build/bin/c_consumer zeigt Symbole des
 *   Programms. Die genaue Ausgabe ist compiler- und plattformabhaengig.
 *
 * Bonus: typische Fehler, Ursache und Fix:
 * - Header nicht eingebunden: Compiler meldet z. B. "projectName was not
 *   declared in this scope". Ursache: Deklaration nicht sichtbar. Fix:
 *   #include <version/version.h>.
 * - Bibliothek nicht gelinkt: Linker meldet z. B. "undefined reference to
 *   fullVersion()". Ursache: Deklaration ist sichtbar, Implementierung fehlt
 *   beim Linken. Fix: target_link_libraries(app PRIVATE version).
 * - Include-Verzeichnis nur PRIVATE: Verbraucher meldet z. B. "version/
 *   version.h: No such file or directory". Ursache: Include-Pfad ist nicht an
 *   den Verbraucher propagiert. Fix: den oeffentlichen include/-Pfad mit
 *   PUBLIC angeben.
 * - Pfad zum generierten Header fehlt: version.cpp meldet z. B.
 *   "version_config.h: No such file or directory". Ursache: configure_file
 *   erzeugt den Header im Build-Verzeichnis, aber dieses Verzeichnis fehlt
 *   beim Kompilieren im Include-Pfad. Fix: CMAKE_CURRENT_BINARY_DIR fuer das
 *   Bibliotheks-Target als PRIVATE Include-Verzeichnis hinzufuegen.
 *   Die exakten Formulierungen variieren je nach Compiler und Linker.
 *
 * Bonus: kurze Theorieantworten:
 * - Statisch: benoetigter Code wird ins Programm gelinkt; dynamisch: eine
 *   separate Laufzeitbibliothek wird geladen.
 * - Typische Endungen: Linux/Unix .a und .so; Windows .lib und .dll (bei
 *   dynamischen Bibliotheken oft zusaetzlich eine Import-.lib).
 * - Mikrocontroller-Projekte verwenden haeufig statische Bibliotheken, da
 *   Deployment und Laufzeit kontrolliert sind und kein dynamischer Loader
 *   vorausgesetzt werden kann.
 * - Name Mangling kodiert C++-Informationen in Symbolnamen; extern "C"
 *   deaktiviert es fuer die betreffende Funktion und erleichtert die Nutzung
 *   aus C.
 *
 * Warum __cplusplus im C-API-Header abgefragt wird:
 * - version_c_api.cpp definiert die Funktion mit extern "C". Das legt die
 *   C-Linkage und den von C erwarteten Symbolnamen fuer die Implementierung
 *   fest.
 * - Der Header wird aber sowohl von C- als auch von C++-Dateien eingebunden.
 *   C kennt die Syntax extern "C" nicht. __cplusplus ist vom C++-Compiler
 *   vordefiniert; deshalb umschliesst der Header die Syntax mit #ifdef. C++
 *   bekommt die passende C-Linkage-Deklaration, C eine normale Deklaration.
 *
 * Mehrere Quelldateien und gleiche Funktionsnamen:
 * - CMake kompiliert jede .cpp-Datei einzeln zu einer Objektdatei und packt
 *   diese in die Bibliothek. Der Linker verbindet spaeter Aufrufe mit den
 *   passenden Definitionen; CMake waehlt nicht beliebig eine Funktion aus.
 * - Mehrere Deklarationen derselben Funktion sind erlaubt, wenn sie zur
 *   Definition passen. Zwei Definitionen desselben extern sichtbaren Symbols
 *   verursachen normalerweise einen "multiple definition"-Linkerfehler.
 * - Gleichnamige C++-Funktionen koennen unterschiedliche Symbole haben, wenn
 *   sie in verschiedenen Namespaces liegen oder verschiedene Parameter
 *   (Overloads) besitzen. Eine Datei-lokale Funktion mit static hat interne
 *   Sichtbarkeit und kollidiert nicht mit einer gleichnamigen Funktion in
 *   einer anderen .cpp-Datei.
 * - In dieser Bibliothek definiert version.cpp fullVersion(); die Datei
 *   version_c_api.cpp ruft sie nur auf. Der Aufruf ist keine zweite
 *   Definition, daher gibt es keinen Namenskonflikt.
 */