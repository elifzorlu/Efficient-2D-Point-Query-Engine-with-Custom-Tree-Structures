//
// Created by elif zorlu on 9.11.2025.
//

#ifndef TWODIMTREE_H
#define TWODIMTREE_H

#include "TwoDimTreeNode.h"

class TwoDimTree {
private:
    TwoDimTreeNode* root;

public:
    TwoDimTree(const Rectangle& extent);
    ~TwoDimTree();

    void insert(const Rectangle& rectangle);
    void search(int x, int y, List<Rectangle>& results);

private:
    void recursive_Insertion(TwoDimTreeNode* node, const Rectangle& rectangle);
    void recursive_Search(TwoDimTreeNode* node, int x, int y, List<Rectangle>& results);
    void clearTree(TwoDimTreeNode* node);
};

#endif
