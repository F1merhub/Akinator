#include "akinator.h"

int main() {
    int command = 0;
    command = getchar();
    char buffer[ANSWER_BUFFER_SIZE] = {0};
    system("@cls||clear");
    assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL);
    printf("%s", buffer);
    return 0;
}
