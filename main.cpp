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

    Menu(base_name);
    // BinaryTree *Root = NULL;

    // ReadTreeFromFile(&Root, base_name);

    // PrintTree(Root);

    // TreeDumpDot(Root);

    // FreeTree(&Root);

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

    BinaryTree *Root = NULL

    int command = 0;
    scanf("%d", &command);

    switch(command) {
        case(GUESSING):

            break;
        case(BASE_DUMP):

            break;
        case(EXIT):

            break;
        default:
            assert(0); // TODO не рассматриваю другие значения
    }

    return OK;
}

Error Akinator() {




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
    char line[MAX_LINE_LENGTH];
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
