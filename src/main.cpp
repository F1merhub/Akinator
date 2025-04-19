#include "akinator.h"

int main(int argc, char *argv[])
{
    const char* base_name = NULL;
    Errors error = OK;

    if (argc == 1)
    {
        base_name = "./Base/Base.txt";
    }

    else if (argc == 2)
    {
        base_name = argv[1];
    }

    error = Menu(base_name);
    PrintError(error);

    return error;
}
