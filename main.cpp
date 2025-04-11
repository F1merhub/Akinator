#include "akinator.h"

int main(int argc, char *argv[])
{
    const char* base_name = NULL;

    if (argc == 1)
    {
        base_name = "Base.txt";
    }

    else if (argc == 2)
    {
        base_name = argv[1];
    }

    Menu(base_name);

    return 0;
}
