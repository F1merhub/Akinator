#include "akinator.h"
#include "stack.h"
/*
    Создает узел по указателю на указатель равный null
    используем в Addnode

*/
Errors CreateNode(BinaryTree **Node, tree_element value)
{
    assert(Node != NULL && *Node == NULL);
    *Node = (BinaryTree*)calloc(1, sizeof(BinaryTree));

    if (*Node == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    (*Node)->value = value;
    (*Node)->left = NULL;
    (*Node)->right = NULL;

    return OK;
}

Errors FreeTree(BinaryTree **Node)
{
    assert(Node); // нулевой указатель может передать сам программист

    if (*Node == NULL)
    {
        return OK;
    }

    FreeTree(&((*Node)->left));
    FreeTree(&((*Node)->right));

    free((*Node)->value);
    free(*Node);
    *Node = NULL;

    return OK;
}

Errors AddNode(BinaryTree **Root, tree_element value)
{
    assert(Root != NULL);

    if (*Root == NULL)
    {
        return CreateNode(Root, value);
    }

    if (CompareValue(value, (*Root)->value) < 0)
    {
        return AddNode(&((*Root)->left), value);
    }
    else
    {
        return AddNode(&((*Root)->right), value);
    }

    return OK;
}

Errors AddNodeLoop(BinaryTree **Root, tree_element value)
{
    assert(Root != NULL);

    if (*Root == NULL)
    {
        return CreateNode(Root, value);
    }

    BinaryTree *cur = *Root;

    while (cur != NULL)
    {
        if (CompareValue(value, cur->value) < 0)
        {
            if (cur->left != NULL)
            {
                cur = cur->left;
            }
            else
            {
                return CreateNode(&(cur->left), value);
            }
        }
        else
        {
            if (cur->right != NULL)
            {
                cur = cur->right;
            }
            else
            {
                return CreateNode(&(cur->right), value);
            }
        }
    }

    return OK;
}

Stack* FindNodePath(const char* value, BinaryTree *Root) {
    assert(value != NULL);
    assert(Root != NULL);

    Stack* node_path = (Stack*)calloc(1, sizeof(Stack)); // TODO проверка
    stack_constructor(node_path, STACK_CAPACITY);
    FindNode(value, Root, node_path);
    return node_path;
}

int FindNode(const char* value, BinaryTree *Node, Stack* node_path) {
    assert(value != NULL);
    assert(Node != NULL);
    assert(node_path != NULL);

    stack_push(node_path, Node);

    if (strcmp(value, Node->value) == 0)
    {
        return 1;
    }

    else
    {
        if (Node->left != NULL && Node->right != NULL) {
            if (FindNode(value, Node->left, node_path) || FindNode(value, Node->right, node_path))
            {
                return 1;
            }

            else
            {
                stack_pop(node_path); // зачкем
                return 0;
            }
        }
        else if (Node->left == NULL && Node->right == NULL)
        {
            stack_pop(node_path);
            return 0;
        }

        return 0;
    }
}

BinaryTree* CheckObjectExistance(BinaryTree *Root, tree_element value) {

    if (Root == NULL || value == NULL) {
        return NULL;
    }
    else if (Root->value != NULL && CompareValue(Root->value, value) == 0) {
        return Root;
    }
    else {
        BinaryTree *temp = NULL;
        if ((temp = CheckObjectExistance(Root->left, value)) != NULL)
            return temp;
        else
        if ((temp = CheckObjectExistance(Root->right, value)) != NULL)
            return temp;
    }
    return NULL;
}

BinaryTree* FindNodeSortTree(BinaryTree *Root, tree_element value) // Подходит для сортирующего дерева, но не акинатора
{
    assert(Root != NULL);

    if (CompareValue(Root->value, value) == 0)  // Использование CompareValue
        return Root;

    if (CompareValue(value, Root->value) < 0)  // Использование CompareValue
    {
        return FindNodeSortTree(Root->left, value);
    }
    else
    {
        return FindNodeSortTree(Root->right, value);
    }

    return NULL;
}

Errors DeleteNode(BinaryTree **Root, tree_element value)
{
    assert(Root != NULL && *Root != NULL); // нельзя передавать нулевой указатель и нельзя, чтобы указатель указывал на несуществующий узел

    if (CompareValue(value, (*Root)->value) < 0)  // Использование CompareValue
    {
        return DeleteNode(&((*Root)->left), value);
    }
    else if (CompareValue(value, (*Root)->value) > 0)  // Использование CompareValue
    {
        return DeleteNode(&((*Root)->right), value);
    }
    else
    {
        if ((*Root)->left == NULL)
        {
            BinaryTree *temp = *Root;
            *Root = (*Root)->right;
            free(temp);
            temp = NULL;
        }
        else if ((*Root)->right == NULL)
        {
            BinaryTree *temp = *Root;
            *Root = (*Root)->left;
            free(temp);
            temp = NULL;
        }
        else
        {
            BinaryTree *minNode = (*Root)->right;
            while (minNode->left != NULL)
            {
                minNode = minNode->left;
            }

            (*Root)->value = minNode->value;
            return DeleteNode(&((*Root)->right), minNode->value);
        }
    }

    return OK;
}

int CompareValue(tree_element a, tree_element b) {
    switch (TREE_ELEM_TYPE) {
        case (INT):
            return (int)(a - b);
        case (STRING):
            return strcmp(a, b);
        default:
            {
                assert(0);
                return 0;
            }
    }
}

Errors TreeTraversal(BinaryTree *Node, int level)
{
    if (Node == NULL) {
        return OK;
    }

    // Сначала правое поддерево (чтобы вывод был сверху вниз)
    TreeTraversal(Node->right, level + 1);

    // Отступы для визуализации уровня
    for (int i = 0; i < level; i++) {
        printf("        ");
    }

    // Определяем тип узла по наличию потомков
    if (Node->left != NULL || Node->right != NULL) {
        // Узел-вопрос (есть потомки)
        printf("* %s\n", Node->value);
    } else {
        // Узел-объект (лист)
        printf("- %s\n", Node->value);
    }

    // Затем левое поддерево
    TreeTraversal(Node->left, level + 1);

    return OK;
}

// Функция-обертка для удобного вызова
Errors PrintTree(BinaryTree *Root)
{
    printf("\nTree Structor:\n");
    printf("====================\n");
    Errors result = TreeTraversal(Root, 0);
    printf("====================\n");
    return result;
}

Errors ReadTreeFromFile(BinaryTree** Root, const char* filename) {
    assert(Root != NULL);
    assert(filename != NULL);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return FILE_NOT_OPEN;
    }

    char line[MAX_LINE_LENGTH];

    while (1) {
        if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
            break;
        }
        char* clean_line = CutString(line);

        if (strlen(clean_line) > 0) {
            if (clean_line[0] == '[') {
                break;
            }
        }
    }

    Errors err = ParseTree(file, Root);
    fclose(file);
    return err;
}

Errors ParseTree(FILE* file, BinaryTree** Node) {
    char line[MAX_LINE_LENGTH];
    char* new_line;
    tree_element value;


    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        new_line = CutString(line); // нормальная часть строки
        if (strlen(new_line) == 0)
            continue;

        if (new_line[0] == '?') {
            char* end = strchr(new_line + 1, '?');
            if (!end)
                return FILE_FORMAT_ERROR;
            *end = '\0';
            value = strdup(new_line + 1);
            if (value == NULL) {
                return MEMORY_ALLOCATION_ERROR;
            }
        }
        else if (new_line[0] == '`') {
            char* end = strchr(new_line + 1, '`');
            if (!end)
                return FILE_FORMAT_ERROR;
            *end = '\0';
            value = strdup(new_line + 1);
            if (value == NULL) {
                return MEMORY_ALLOCATION_ERROR;
            }
        }
        else if (new_line[0] == ']') {
            return OK;
        }
        else {
            return FILE_FORMAT_ERROR;
        }


        Errors err = CreateNode(Node, value);
        if (err != OK)
            return err;


        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            new_line = CutString(line);
            if (strlen(new_line) == 0)
                continue;

            if (new_line[0] == '[') {
                if ((*Node)->right == NULL) {
                    err = ParseTree(file, &((*Node)->right));
                } else {
                    err = ParseTree(file, &((*Node)->left));
                }
                if (err != OK)
                    return err;
            }
            else if (new_line[0] == ']') {
                return OK;
            }
        }
        break;
    }
    return OK;
}

char* CutString(char* str) {
    while (isspace(*str)) // переставляем указатель на первй непробельный
        str++;
    char* end = str + strlen(str) - 1; // создаем указ на последний символ
    while (end > str && isspace(*end))
        end--;
    *(end + 1) = '\0';
    return str;
}

int GetAnswer() {
    char buffer[ANSWER_BUFFER_SIZE] = {0};
    while (1) {
        if(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) == NULL) {
            if (feof(stdin))
                printf("Некоректное слово, попробуйте еще раз\n");
            else
                printf("Ошибка стандартного потока ввода, попробуйте еще раз\n"); // NOTE или лучше ошибку?
        }
        else {
            int len = (int)strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') { // если все хорошо
                buffer[len-1] = '\0';
                if (buffer[0] == '\0') {
                    printf("Ошибка, введите ответ yes/no\n"
                           "Ваш ответ: ");
                }
                else if (strstr("yes", buffer) != NULL) {
                    return 1;
                }
                else if (strstr("no", buffer) != NULL) {
                    return 0;
                }
                else {
                    printf("Ошибка, введите ответ yes/no\n"
                           "Ваш ответ: ");
                }
            }
            else {
            printf("Введеное слово слишком большое, попробуйте еще раз\n"
                   "Ваш ответ: ");
            }
        }
    }
}

char* GetObject() {
    char *object_buffer = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
    if (object_buffer == NULL) {
        return object_buffer;
    }

    while (1) {
        if(fgets(object_buffer, MAX_LINE_LENGTH, stdin) == NULL) {
            if (feof(stdin))
                printf("Некоректное слово, попробуйте еще раз\n");
            else
                printf("Ошибка стандартного потока ввода, попробуйте еще раз\n"); // NOTE или лучше ошибку?
        }
        int len = (int)strlen(object_buffer);
        if (len > 0 && object_buffer[len - 1] == '\n') { // если все хорошо
            object_buffer[len-1] = '\0';
            return object_buffer;
        }
        else {
            printf("Введеное слово слишком большое, попробуйте еще раз\n"
                   "Ваш ответ: ");
        }
    }
}

void clean_console() {
    system("@cls||clear");
}
