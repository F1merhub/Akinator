#include "akinator.h"

Errors Menu(const char* base_name) {
    assert(base_name != NULL);

    printf("\nAkinatorGame\n"
           "(c) F1mer\n\n"
           "Chose game mode\n"
           "[1] - guessing\n"
           "[2] - dump\n"
           "[3] - exit\n\n");

    int command = getchar();
    printf("\n %d", command);


}
