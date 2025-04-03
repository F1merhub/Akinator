#include "akinator.h"

int main()
{
    BinaryTree *Root = NULL;

    AddNode(&Root, "“My uncle’s goodness is extreme,");
    AddNode(&Root, "If seriously he hath disease;");
    AddNode(&Root, "He hath acquired the world’s esteem");
    AddNode(&Root, "And nothing more important sees;");
    AddNode(&Root, "A paragon of virtue he!");
    AddNode(&Root, "But what a nuisance it will be,");
    AddNode(&Root, "Chained to his bedside night and day");
    AddNode(&Root, "Without a chance to slip away.");
    AddNode(&Root, "Ye need dissimulation base");
    AddNode(&Root, "A dying man with art to soothe,");
    AddNode(&Root, "Beneath his head the pillow smooth,");
    AddNode(&Root, "And physic bring with mournful face,");
    AddNode(&Root, "To sigh and meditate alone:");
    AddNode(&Root, "When will the devil take his own!”");

    TreeDumpDot(Root);

    FreeTree(&Root);

    return 0;
}


