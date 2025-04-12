#include "akinator.h"
#include "stack.h"

int main() {
    BinaryTree *Root = NULL;
    ReadTreeFromFile(&Root, "Base.txt");
    TreeDumpDot(Root);
    Compairing(Root, "Base.txt");

    return 0;
}

Errors Compairing(BinaryTree *Root, const char *base_name) {
    assert((base_name != NULL) && (Root != NULL));

    printf("Введите 2 слова, которые вы хотите сравнить\n"
           "Первое слово: ");
    char *object1 = GetObject(); // TODO не забыть очистить память в конце
    printf("Второе слово: ");
    char *object2 = GetObject();

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

    return OK;
}
