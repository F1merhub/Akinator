#include "akinator.h"

int main(int argc, char *argv[])
{
    const char* base_name = NULL;

    if (argc == 1)
    {
        base_name = "Base.txt";
    }

    else if (argc == 2)
    {
        base_name = argv[1];
    }

    // Menu(base_name);
    BinaryTree *Root = NULL;

    ReadTreeFromFile(&Root, base_name);

    PrintTree(Root);

    TreeDumpDot(Root);

    FreeTree(&Root);

    return 0;
}

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
    return OK;
}

Errors ReadTreeFromFile(BinaryTree** Root, const char* filename) {
    assert(Root != NULL);
    *Root = NULL; // Явная инициализация
    assert(filename != NULL);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return FILE_ERROR;
    }

    // Ищем начало дерева
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (strstr(line, "[")) break;
    }

    Errors err = ParseSubtree(file, Root);
    fclose(file);

    if (err == OK && *Root == NULL) {
        err = FILE_FORMAT_ERROR;
    }
    return err;
}

Errors ParseSubtree(FILE* file, BinaryTree** Node) {
    char line[MAX_LINE_LENGTH];
    char* content;
    char* string_value = NULL; // Отдельная переменная для strdup

    // 1. Чтение значения узла
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        content = trim_whitespace(line);
        if (strlen(content) == 0) continue;

        // Обработка значения
        if (content[0] == '?' && content[1] == '?') {
            char* end = strrchr(content, '?');
            if (!end || end == content+1) return FILE_FORMAT_ERROR;
            *end = '\0';
            string_value = strdup(content + 2);
        }
        else if (content[0] == '`' && content[1] == '`') {
            char* end = strrchr(content, '`');
            if (!end || end == content+1) return FILE_FORMAT_ERROR;
            *end = '\0';
            string_value = strdup(content + 2);
        }
        else if (content[0] == ']') {
            return OK;
        }
        else {
            return FILE_FORMAT_ERROR;
        }
        break;
    }

    if (!string_value) return FILE_FORMAT_ERROR;

    // 2. Создание узла
    Errors err = CreateNode(Node, string_value);
    if (err != OK) {
        free(string_value); // Освобождаем ТОЛЬКО если не удалось создать узел
        return err;
    }

    // 3. Обработка поддеревьев
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        content = trim_whitespace(line);
        if (strlen(content) == 0) continue;

        if (content[0] == '[') {
            if ((*Node)->left == NULL) {
                err = ParseSubtree(file, &(*Node)->left);
            } else {
                err = ParseSubtree(file, &(*Node)->right);
            }
            if (err != OK) return err;
        }
        else if (content[0] == ']') {
            return OK;
        }
        else {
            return FILE_FORMAT_ERROR;
        }
    }

    return OK;
}

char* trim_whitespace(char* str) {
    char* end;
    // Удаляем пробелы в начале
    while(isspace(*str)) str++;
    // Удаляем пробелы в конце
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    *(end+1) = '\0';
    return str;
}
