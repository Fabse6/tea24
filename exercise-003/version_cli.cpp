#include <fmt/format.h>

#include <version/version.h>

int main()
{
    fmt::print("Project: {}\nVersion: {}\n", projectName(), fullVersion());
    return 0;
}
