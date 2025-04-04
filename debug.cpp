#include "akinator.h"

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
    char line[MAX_LINE_LENGTH];
    char* content;
    tree_element value;

    // Читаем значение узла
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        content = trim_whitespace(line);
        if (strlen(content) == 0) continue;

        // Обработка значения
        if (content[0] == '?') {  // Вопрос
            char* end = strchr(content + 1, '?');
            if (!end) return FILE_FORMAT_ERROR;
            *end = '\0';
            value = strdup(content + 1);
        }
        else if (content[0] == '`') {  // Объект
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

        // Создаем узел
        Errors err = CreateNode(Node, value);
        if (err != OK) return err;

        // Обработка поддеревьев
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



int main() {

    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, "Base.txt");
    BinaryTree *cur = Root;

    system("cls||clear");

    char buffer[ANSWER_BUFFER_SIZE] = {0};

    while (cur->left != NULL && cur->right != NULL) {
        printf("Это""%s""?", cur->value);

        assert(fgets(buffer, ANSWER_BUFFER_SIZE, stdin) != NULL); // TODO поставить проверку
        if (strcmp(buffer, "y") == 0) {
            cur = cur->left;
        }
        else if (strcmp(buffer, "n") == 0) {
            cur = cur->right;
        }
        else {
            assert(0); // TODO поправить на всевозможные ответы
        }

        assert(cur != NULL);
    }
    // PrintTree(Root);
    FreeTree(&Root);
    return 0;
}
