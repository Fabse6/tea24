#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"


void changeValueByParameter(int val);
void changeValueByPointer(int* ptr);
void changeValueByReference(int& ref);

int main(int argc, char **argv) {

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/12.0/api/
     */
    fmt::print("Hello, {}!\n", tea::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */
    
    // Teil 0:
    fmt::println("Anzahl der Argumente: {}", argc);
    for(int i = 0; i < argc; i++)
    {
        fmt::println("argv[{}]: \"{}\"; Adresse: {}", i, argv[i], fmt::ptr(argv[i]));
    }

    // Teil 2:
    double x = 10;
    double *p = &x;
    fmt::println("\n\nWert von x: {}\nAdresse von x: {}", x, fmt::ptr(&x));
    fmt::println("Adresse, auf die p zeigt: {} \nWert, auf den p zeigt: {}\nAdresse von p: {}", fmt::ptr(p), *p, fmt::ptr(&p));

    *p = 10;

    fmt::println("\n\nWert von x: {}\nAdresse von x: {}", x, fmt::ptr(&x));
    fmt::println("Adresse, auf die p zeigt: {} \nWert, auf den p zeigt: {}\nAdresse von p: {}", fmt::ptr(p), *p, fmt::ptr(&p));


    // Teil 2:
    double* d = (double*)malloc(sizeof(double));
    *d = 3.1415;
    free(d);
    // oder 
    double* e = new double(3.1415);
    fmt::print("\n\nWert von d: {}", *d);
    delete e;

    // Teil 3:
    int value = 4711;

    fmt::println("\n\nWert von Value: {}\nAdresse von Value: {}", value, fmt::ptr(&value));
    changeValueByParameter(value);
    fmt::println("Wert von Value: {}\nAdresse von Value: {}", value, fmt::ptr(&value));

    fmt::println("\n\nWert von Value: {}\nAdresse von Value: {}", value, fmt::ptr(&value));
    changeValueByPointer(&value);
    fmt::println("Wert von Value: {}\nAdresse von Value: {}", value, fmt::ptr(&value));

    fmt::println("\n\nWert von Value: {}\nAdresse von Value: {}", value, fmt::ptr(&value));
    changeValueByReference(value);
    fmt::println("Wert von Value: {}\nAdresse von Value: {}", value, fmt::ptr(&value));

    return 0; /* exit gracefully*/
}

void changeValueByParameter(int val)
{
    fmt::println("[ChangeByParameter] Wert val: {}", val);
    val = 10;
    fmt::println("[ChangeByParameter] Wert val: {}", val);
}

void changeValueByPointer(int* ptr)
{
    fmt::println("[ChangeByPointer] Wert: {}\nAdresse: {}", *ptr, fmt::ptr(ptr));
    *ptr += 10;
    fmt::println("[ChangeByPointer] Wert: {}\nAdresse: {}", *ptr, fmt::ptr(ptr));
}

void changeValueByReference(int& ref) {
    fmt::println("[changeValueByReference] Wert von Value: {}",ref);
    ref += 10;
    fmt::println("[changeValueByReference] Wert von Value: {}",ref);
}
