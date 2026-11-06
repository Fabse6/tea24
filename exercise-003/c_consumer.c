#include <stdio.h>

#include <version/version_c_api.h>

int main(void)
{
    printf("Version from C: %s\n", version_full_c());
    return 0;
}
