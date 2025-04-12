#include "akinator.h"
#include "stack.h"

Errors Menu(const char* base_name) {
    assert(base_name != NULL);

    clean_console();
    printf("\nAkinatorGame\n"
           "(c) F1mer\n\n"
           "Chose game mode\n"
           "[1] - Угадывание\n"
           "[2] - Определение\n"
           "[3] - Сравнение\n"
           "[4] - Распечатка Базы данных\n"
           "[5] - Выход\n"
           "Ваш ответ: ");

    int command = 0;
    command = GetChar();

    switch(command) {
        case(KEY_1): // Акинатор
            AkinatorMode(base_name);
            break;
        case(KEY_2): {// Определение
                Errors error = DefinitionMode(base_name);
                if (error != OK)
                    return error;
            break;
        }
        case(KEY_3):
            ComparingMode(base_name);
            break;
        case(KEY_4):// TODO распечатка
            assert(0);
            break;
        case(KEY_5): // Выход
            printf("Спасибо за игру");
            break;
        default:
            assert(0);
    }

    return OK;
}

Errors ComparingMenu(BinaryTree *Root, const char *base_name) {
    assert(Root != NULL);
    assert(base_name != NULL);

    printf("Выберите Режим:\n"
           "[1] - Начать заново\n"
           "[2] - Выход\n");
    printf("Ваш ответ: ");

    int command = 0;
    command = GetChar();

    switch(command) {
        case(KEY_1):
            clean_console();
            Comparing(Root, base_name);
            break;
        case(KEY_2):
            FreeTree(&Root);
            Menu(base_name);
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
    ReadTreeFromFile(&Root, base_name);
    Comparing(Root, base_name);
    return OK;
}

Errors Comparing(BinaryTree *Root, const char *base_name) {
    assert((base_name != NULL) && (Root != NULL));

    printf("Введите 2 слова, которые вы хотите сравнить\n"
           "Первое слово: ");
    char *object1 = GetObject(); // TODO не забыть очистить память в конце
    printf("Второе слово: ");
    char *object2 = GetObject();
    clean_console();

    Stack *node_path1 = FindNodePath(object1, Root);
    Stack *node_path2 = FindNodePath(object2, Root);

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
               "%s", object2, object1, object2);

        while(index2 + 1 <= node_path2->size) {
            if ((node_path2->data[index2 + 1] == node_path2->data[index2]->left)) {
                printf("не %s, ", node_path2->data[index2]->value);
            }
            else if (node_path2->data[index2 + 1] == node_path2->data[index2]->right) {
                printf(" %s,", node_path2->data[index2]->value);
            }

            index2++;
        }
    }

    stack_destructor(node_path1);
    stack_destructor(node_path2);
    free(node_path1);
    free(node_path2);
    ComparingMenu(Root, base_name);

    return OK;
}

Errors DefinitionMode(const char* base_name) {
    assert(base_name != NULL);
    clean_console();
    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, base_name);
    return Definition(Root, base_name);
}

Errors Definition(BinaryTree *Root, const char* base_name) {
    assert((base_name != NULL) && (Root != NULL));

    printf("Введите слово, определение которого хотите посмотреть\n"
           "Ваше слово: ");
    char *object = GetObject(); // NOTE не забыть очистить память в конце
    clean_console();
    Stack *node_path = FindNodePath(object, Root);
    if (node_path == NULL)
        return ALLOCATION_ERROR;
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
    DefinitionMenu(Root, base_name);
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
    command = GetChar();

    switch(command) {
        case(KEY_1):
            clean_console();
            Definition(Root, base_name);
            break;
        case(KEY_2):
            FreeTree(&Root);
            Menu(base_name);
            break;
        default:
            assert(0);
    }
    return OK;
}

Errors AkinatorMode(const char* base_name) {

    assert(base_name != NULL);

    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, base_name); // TODO проверка на нормальное дерево
    clean_console();
    Akinator(Root, base_name);

    return OK;
}

void Akinator(BinaryTree *Root, const char* base_name) {

    assert(base_name != NULL);
    assert(Root != NULL);

    printf("Добро Пожаловать в Акинатор\n"
           "Я буду спрашивать признак, а ты отвечай y/n\n");
    AkinatorPlay(Root);
    printf("\n");
    AkinatorMenu(Root, base_name);
}

void AkinatorMenu(BinaryTree *Root, const char* base_name) {

    printf("Выберите Режим\n"
            "[1] - Играть\n"
            "[2] - Сохранить Базу данных\n"
            "[3] - Выход\n"
            "Ваш ответ: ");

    int command = 0;
    command = GetChar();

    switch(command) {
        case(KEY_1):
            clean_console();
            Akinator(Root, base_name);
            break;
        case(KEY_2): // TODO Сделать сохранение базы данных
            assert(0);
            break;
        case(KEY_3):
            FreeTree(&Root);
            Menu(base_name);
            break;
        default:
            assert(0);
            break;
    }
}

void AkinatorPlay(BinaryTree *Root) {

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
            if (CheckObjectExistance(Root, object_buffer) != NULL) {
                printf("Объект был найден в базе данных\n"
                        "Попробуйте сыграть еще раз\n");
            }
            else {
                CreateNode(&(cur->right), NULL);
                CreateNode(&(cur->left), NULL);
                cur->right->value = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
                cur->left->value = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));

                strcpy(cur->right->value, object_buffer);
                strcpy(cur->left->value, cur->value);

                printf("Чем %s отличается от %s?\n"
                    "Ваш Ответ: ", cur->right->value, cur->value);

                cur->value = GetObject();
            }

            break;
        }
        default:
            break;
        }

}
