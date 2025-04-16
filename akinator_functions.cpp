#include "akinator.h"
#include "stack.h"

Errors Menu(const char* base_name) {
    assert(base_name != NULL);

    // clean_console();
    printf("\nAkinatorGame\n"
           "(c) F1mer\n\n"
           "Выберите Режим\n"
           "[1] - Угадывание\n"
           "[2] - Определение\n"
           "[3] - Сравнение\n"
           "[4] - Распечатка Базы данных\n"
           "[5] - Выход\n"
           "Ваш ответ: ");

    int command = 0;
    command = GetMode(5);

    switch(command) {
        case(KEY_1):                                            // Акинатор
            CALL_AND_RETURN_ERROR(AkinatorMode(base_name));
            break;
        case(KEY_2):                                            // Определение
            CALL_AND_RETURN_ERROR(DefinitionMode(base_name));
            break;
        case(KEY_3):                                            // Сравнение
            CALL_AND_RETURN_ERROR(ComparingMode(base_name));
            break;
        case(KEY_4):                                            //  Распечатка базы
            CALL_AND_RETURN_ERROR(BaseDump(base_name));
            break;
        case(KEY_5):                                            // Выход
            printf("Спасибо за игру");
            break;
        default:
            assert(0);
            break;
    }

    return OK;
}

Errors BaseDump(const char *base_name) {
    assert(base_name);

    BinaryTree *Root = NULL;
    CALL_AND_RETURN_ERROR(ReadTreeFromFile(&Root, base_name));
    CALL_AND_RETURN_ERROR(TreeDumpDot(Root));
    system("dot -Tpng GraphDump\\dump.dot -o GraphDump\\dump.png");
    printf("\nБаза распечата в файл \n");
    FreeTree(&Root);
    CALL_AND_RETURN_ERROR(Menu(base_name));

    return OK;
}

Errors ComparingMenu(BinaryTree *Root, const char *base_name) {
    assert(Root != NULL);
    assert(base_name != NULL);

    printf("\nВыберите Режим:\n"
           "[1] - Начать заново\n"
           "[2] - Выход\n");
    printf("Ваш ответ: ");

    int command = 0;
    command = GetMode(2);

    switch(command) {
        case(KEY_1):
            clean_console();
            CALL_AND_RETURN_ERROR(Comparing(Root, base_name));
            break;
        case(KEY_2):
            FreeTree(&Root);
            CALL_AND_RETURN_ERROR(Menu(base_name));
            break;
        default:
            assert(0);
            break;
    }
    return OK;
}

Errors ComparingMode(const char *base_name) {
    assert(base_name != NULL);

    clean_console();
    BinaryTree *Root = NULL;
    CALL_AND_RETURN_ERROR(ReadTreeFromFile(&Root, base_name));
    CALL_AND_RETURN_ERROR(Comparing(Root, base_name));

    return OK;
}

Errors Comparing(BinaryTree *Root, const char *base_name) {
    assert((base_name != NULL) && (Root != NULL));

    printf("Введите 2 слова, которые вы хотите сравнить\n"
           "Первое слово: ");
    char *object1 = GetObject(); // TODO не забыть очистить память в конце
    NULL_CHECK_AND_RETURN(object1);

    printf("Второе слово: ");
    char *object2 = GetObject();
    NULL_CHECK_AND_RETURN(object2);

    clean_console();

    Stack *node_path1 = FindNodePath(object1, Root);
    Stack *node_path2 = FindNodePath(object2, Root);
    if (node_path1 == NULL || node_path2 == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }


    if (node_path1->size == 0)
        printf("Объект %s не найден в базе данных\n", object1);
    else if (node_path2->size == 0)
        printf("Объект %s не найден в базе данных\n", object2);
    else {
        printf("%s и %s схожи тем, что:\n", object1, object2);

        int index1 = 1;
        int index2 = 1;
        while(((node_path1->data)[index1 + 1] == (node_path2->data)[index2 + 1]) && (index1 < node_path1->size) && (index2 < node_path2->size)) {
            assert(index1 + 1 <= node_path1->size);
            assert(index2 + 1 <= node_path2->size);

            if ((node_path1->data[index1 + 1] == node_path1->data[index1]->left)) {
                printf("не %s, ", node_path1->data[index1]->value);
            }
            else if (node_path1->data[index1 + 1] == node_path1->data[index1]->right) {
                printf("%s, ", node_path1->data[index1]->value);
            }

            index1++;
            index2++;
        }
        if (index1 == 1)
            printf("Ничем");
        printf("\n");

        assert(index1 + 1 <= node_path1->size);
        assert(index2 + 1 <= node_path2->size);

        printf("%s отличается от %s тем, что:\n"
               "%s ", object1, object2, object1);

        while(index1 + 1 <= node_path1->size) {
            if ((node_path1->data[index1 + 1] == node_path1->data[index1]->left)) {
                printf("не %s, ", node_path1->data[index1]->value);
            }
            else if (node_path1->data[index1 + 1] == node_path1->data[index1]->right) {
                printf("%s, ", node_path1->data[index1]->value);
            }

            index1++;
        }

        printf("\nА %s отличается от %s тем, что:\n"
               "%s ", object2, object1, object2);

        while(index2 + 1 <= node_path2->size) {
            if ((node_path2->data[index2 + 1] == node_path2->data[index2]->left)) {
                printf("не %s, ", node_path2->data[index2]->value);
            }
            else if (node_path2->data[index2 + 1] == node_path2->data[index2]->right) {
                printf("%s, ", node_path2->data[index2]->value);
            }

            index2++;
        }
    }

    stack_destructor(node_path1);
    stack_destructor(node_path2);
    free(node_path1);
    free(node_path2);
    CALL_AND_RETURN_ERROR(ComparingMenu(Root, base_name));

    return OK;
}

Errors DefinitionMode(const char* base_name) {
    assert(base_name != NULL);

    clean_console();
    BinaryTree *Root = NULL;
    CALL_AND_RETURN_ERROR(ReadTreeFromFile(&Root, base_name));
    CALL_AND_RETURN_ERROR(Definition(Root, base_name));

    return OK;
}

Errors Definition(BinaryTree *Root, const char* base_name) {
    assert((base_name != NULL) && (Root != NULL));

    printf("Введите слово, определение которого хотите посмотреть\n"
           "Ваше слово: ");
    char *object = GetObject(); // NOTE не забыть очистить память в конце
    NULL_CHECK_AND_RETURN(object);

    clean_console();
    Stack *node_path = FindNodePath(object, Root);
    if (node_path == NULL)
        return MEMORY_ALLOCATION_ERROR;

    if (node_path->size == 0) {
        printf("Объект не найден в базе данных\n");
    }
    else {
        printf("\nВот определение объекта %s\n", object);
        printf("%s - это", object);
        for (int index = 1; index < node_path->size; ++index) {
            stk_assert(node_path);

            if ((node_path->data)[index]->left  == (node_path->data)[index + 1])
            {
                if (index != node_path->size - 1)
                    printf(" не %s,", (node_path->data)[index]->value);
                else
                    printf(" не %s.", (node_path->data)[index]->value);
            }

            if ((node_path->data)[index]->right == (node_path->data)[index + 1])
            {
                if (index != node_path->size - 1)
                    printf(" %s,", (node_path->data)[index]->value);
                else
                    printf(" %s.", (node_path->data)[index]->value);
            }
        }
        printf("\n\n");
    }

    stack_destructor(node_path); // содержмиое
    free(node_path); // сам указателть
    CALL_AND_RETURN_ERROR(DefinitionMenu(Root, base_name));
    return OK;
}

Errors DefinitionMenu(BinaryTree *Root, const char *base_name) {
    assert(Root != NULL);
    assert(base_name != NULL);

    printf("Выберите Режим:\n"
           "[1] - Начать заново\n"
           "[2] - Выход\n");
    printf("Ваш ответ: ");

    int command = 0;
    command = GetMode(2);

    switch(command) {
        case(KEY_1):
            clean_console();
            CALL_AND_RETURN_ERROR(Definition(Root, base_name));
            break;
        case(KEY_2):
            FreeTree(&Root);
            CALL_AND_RETURN_ERROR(Menu(base_name));
            break;
        default:
            assert(0);
    }
    return OK;
}

Errors AkinatorMode(const char* base_name) {

    assert(base_name != NULL);

    BinaryTree *Root = NULL;
    CALL_AND_RETURN_ERROR(ReadTreeFromFile(&Root, base_name));
    CALL_AND_RETURN_ERROR(Akinator(Root, base_name));

    return OK;
}

Errors Akinator(BinaryTree *Root, const char* base_name) {

    assert(base_name != NULL);
    assert(Root != NULL);

    printf("Добро Пожаловать в Акинатор\n"
           "Я буду спрашивать признак, а ты отвечай y/n\n");
    CALL_AND_RETURN_ERROR(AkinatorPlay(Root));
    CALL_AND_RETURN_ERROR(AkinatorMenu(Root, base_name));

    return OK;
}

Errors AkinatorMenu(BinaryTree *Root, const char* base_name) {

    printf("Выберите Режим\n"
            "[1] - Играть\n"
            "[2] - Сохранить Базу данных\n"
            "[3] - Выход\n"
            "Ваш ответ: ");

    int command = 0;
    command = GetMode(3);

    switch(command) {
        case(KEY_1):
            clean_console();
            CALL_AND_RETURN_ERROR(Akinator(Root, base_name));
            break;
        case(KEY_2): // TODO Сделать сохранение базы данных
            assert(0);
            break;
        case(KEY_3):
            FreeTree(&Root);
            CALL_AND_RETURN_ERROR(Menu(base_name));
            break;
        default:
            assert(0);
            break;
    }
    return OK;
}

Errors AkinatorPlay(BinaryTree *Root) {

    assert(Root != NULL);

    BinaryTree *cur = Root;

    while (cur->left != NULL || cur->right != NULL) {
        assert(cur->left != NULL && cur->right != NULL);

        printf("Это ""%s?\n"
               "Ваш ответ: ", cur->value);

        int answer = GetAnswer();
        switch (answer) {
            case(1):
                cur = cur->right;
                break;
            case(0):
                cur = cur->left;
                break;
            default:
                break;
        }

        assert(cur != NULL);
    }
    printf("Это ""%s?\n"
           "Ваш Ответ: ", cur->value);

    int answer = GetAnswer();
    switch (answer) {
        case(1):
            printf("\nЯ угадал!");
            break;
        case(0): {
            printf("Кто это был?\n"
            "Ваш Ответ: ");

            char *object_buffer = GetObject();
            NULL_CHECK_AND_RETURN(object_buffer);

            if (CheckObjectExistance(Root, object_buffer) != NULL) {
                printf("Объект был найден в базе данных\n"
                        "Попробуйте сыграть еще раз\n");
            }
            else {

                CreateNode(&(cur->right), NULL);
                CreateNode(&(cur->left), NULL);
                cur->right->value = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
                cur->left->value = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
                if (cur->right->value == NULL || cur->left->value == NULL)
                    return MEMORY_ALLOCATION_ERROR;

                strcpy(cur->right->value, object_buffer);
                strcpy(cur->left->value, cur->value);

                printf("Чем %s отличается от %s?\n"
                    "Ваш Ответ: ", cur->right->value, cur->value);

                cur->value = GetObject();
                NULL_CHECK_AND_RETURN(cur->value);
            }

            break;
        }
        default:
            break;
        }
    return OK;
}

int GetMode(int mode_count) {
    assert(mode_count > 0 && mode_count <= KEY_COUNT - KEY_1);

    int command = 0;
    while(1) {
        command = getchar();
        while(getchar() != '\n');
        if (command >= KEY_1 && command < KEY_1 + mode_count)
            return command;
        else
            printf("Неверная комманда, попробуйте еще раз\n"
                   "Ваш ответ: ");
    }
}

void PrintError(Errors error) {
    if (error != OK)
        printf(COLOR_RED"ERROR: %s", ErrorsDecoder(error));
}

const char* ErrorsDecoder(Errors error) {
    switch(error) {
        case OK:
            return "no errors";
        case MEMORY_ALLOCATION_ERROR:
            return "memory allocation error";
        case FILE_NOT_OPEN:
            return "file was not open";
        case FILE_FORMAT_ERROR:
            return "file has wrong format";
        case STDIN_ERROR:
            return "stdin input error";
        default:
            return "unknown error";
    }
}
