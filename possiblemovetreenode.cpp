#include "possiblemovetreenode.h"

PossibleMoveTreeNode::PossibleMoveTreeNode() {
    for (int i = 0; i < 50; ++i) sub[i] = nullptr;
    end = true;
    captured = 0;
}

PossibleMoveTreeNode::~PossibleMoveTreeNode() {
    for (int i = 0; i < 50; ++i) if (sub[i] != nullptr) delete sub[i];

}
