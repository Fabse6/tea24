#include <version/version.h>
#include <version/version_c_api.h>

#include <string>

extern "C" const char* version_full_c(void)
{
    static const std::string version = fullVersion();
    return version.c_str();
}
