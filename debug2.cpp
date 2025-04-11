#include "akinator.h"

int main() {
    int command = 0;
    command = getchar();
    char buffer[30] = {0};
    fgets(buffer, 20, stdin);
    printf("%d\n", command);
    printf("%s", buffer);
    return 0;
}
