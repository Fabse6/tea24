#include <version/version.h>

int main()
{
    if (!isAtLeast(0, 0, 0))
    {
        return 1;
    }

    if (!isAtLeast(0, 0, 1))
    {
        return 1;
    }

    if (isAtLeast(0, 0, 2))
    {
        return 1;
    }

    if (isAtLeast(0, 1, 0))
    {
        return 1;
    }

    if (isAtLeast(1, 0, 0))
    {
        return 1;
    }

    return 0;
}
