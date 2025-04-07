#include "akinator.h"

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
        return ALLOC_ERROR;
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

BinaryTree* FindNode(BinaryTree *Root, tree_element value) // рекурсивный поиск
{
    assert(Root != NULL);

    if (CompareValue(Root->value, value) == 0)  // Использование CompareValue
        return Root;

    if (CompareValue(value, Root->value) < 0)  // Использование CompareValue
    {
        return FindNode(Root->left, value);
    }
    else
    {
        return FindNode(Root->right, value);
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
            return a - b;
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
        return FILE_ERROR;
    }

    // Пропускаем начальные пустые строки
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char* trimmed = trim_whitespace(line);
        if (strlen(trimmed) == 0) continue;
        if (trimmed[0] == '[') break;
    }

    Errors err = ParseSubtree(file, Root);
    fclose(file);
    return err;
}

Errors ParseSubtree(FILE* file, BinaryTree** Node) { // FIXME переработать 3 функции считывания дерева
    char line[MAX_LINE_LENGTH];                    // TODO проверить 
    char* content;
    tree_element value;


    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        content = trim_whitespace(line);
        if (strlen(content) == 0) continue;


        if (content[0] == '?') {
            char* end = strchr(content + 1, '?');
            if (!end) return FILE_FORMAT_ERROR;
            *end = '\0';
            value = strdup(content + 1);
        }
        else if (content[0] == '`') {
            char* end = strchr(content + 1, '`');
            if (!end) return FILE_FORMAT_ERROR;
            *end = '\0';
            value = strdup(content + 1);
        }
        else if (content[0] == ']') {
            return OK;
        }
        else {
            return FILE_FORMAT_ERROR;
        }


        Errors err = CreateNode(Node, value);
        if (err != OK) return err;


        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            content = trim_whitespace(line);
            if (strlen(content) == 0) continue;

            if (content[0] == '[') {
                if ((*Node)->right == NULL) {
                    err = ParseSubtree(file, &((*Node)->right));
                } else {
                    err = ParseSubtree(file, &((*Node)->left));
                }
                if (err != OK) return err;
            }
            else if (content[0] == ']') {
                return OK;
            }
        }
        break;
    }
    return OK;
}

char* trim_whitespace(char* str) {
    while (isspace(*str)) str++;
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

void AddNewTreeObject(BinaryTree *cur, char *buffer, char *feature_buffer) { // указатель на узел, Кто это был, затем признак
    assert(cur != NULL && buffer != NULL && feature_buffer != NULL);
    CreateNode(&(cur->left), cur->value);
    CreateNode(&(cur->right), buffer);
    cur->value = feature_buffer;
}
