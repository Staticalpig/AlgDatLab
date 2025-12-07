#ifndef NULL
#define NULL 0
#endif
#include "Tree.h"

struct TreeWrapper {
    TreeWrapper() {
        tree = NULL;
    }
    TreeWrapper(Tree* t) {
        tree = t;
    }
    bool operator<(const TreeWrapper& tw) const {
        return tree->getWeight() > tw.tree->getWeight();
    }
    Tree* tree;
};