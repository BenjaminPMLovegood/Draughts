#ifndef POSSIBLEMOVETREENODE_H
#define POSSIBLEMOVETREENODE_H

struct PossibleMoveTreeNode {
    PossibleMoveTreeNode();
    ~PossibleMoveTreeNode();

    bool end;
    PossibleMoveTreeNode *sub[50];

    int captured;
};

#endif  // POSSIBLEMOVETREENODE_H
