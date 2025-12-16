//
// Created by elif zorlu on 8.11.2025.
//

#include "TwoDimTreeNode.h"

TwoDimTreeNode::TwoDimTreeNode(const Rectangle& extent)
    : Extent(extent), TopLeft(nullptr), TopRight(nullptr),
      BottomLeft(nullptr), BottomRight(nullptr)
{
}