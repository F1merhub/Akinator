#include "akinator.h"
#include "stack.h"

int main() {

}

int GetChar() {
    int command = 0;
    while (1) {
        command = getchar();
        while (getchar() != '\n');
        switch(command) {
            case(KEY_1): // Акинатор
            case(KEY_2): // Определение
            case(KEY_3):
            case(KEY_4): // TODO распечатка
            case(KEY_5): // Выход
                return command;
            default:
                printf("Неверная комманда, попробуйте еще раз");
                break;
        }
    }
}
