#include <version/version.h>
#include <version_config.h>
#include <string>

const char* projectName()
{
    return VERSION_LIB_NAME;
}

int major()
{
    return VERSION_LIB_VERSION_MAJOR;
}

int minor()
{
    return VERSION_LIB_VERSION_MINOR;
}

int patch()
{
    return VERSION_LIB_VERSION_PATCH;
}

std::string fullVersion()
{
    return std::string(projectName()) + "-" +
           std::to_string(major()) + "." +
           std::to_string(minor()) + "." +
           std::to_string(patch());
}