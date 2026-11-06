#include <fmt/format.h>

#include <version/version.h>

int main()
{
    fmt::print("Project: {}\n", projectName());
    fmt::print("Version: {}.{}.{}\n", major(), minor(), patch());
    fmt::print("Full: {}\n", fullVersion());

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
 */