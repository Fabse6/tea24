#ifndef VERSION_VERSION_H
#define VERSION_VERSION_H
#include <string>
const char* projectName();
int major();
int minor();
int patch();
std::string fullVersion();
#endif