// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#pragma once
#include <vector>

class Tree {
public:
    struct Node {
        char value;
        std::vector<Node*> children;
        Node(char v = '\0') : value(v) {}
    };
private:
    Node* root;
    std::vector<char> elems; 
    void buildFrom(Node* parent, const std::vector<char>& remaining);
    void clear(Node* node);
public:
    explicit Tree(const std::vector<char>& in);
    ~Tree();
    Node* getRoot() const { return root; }
    const std::vector<char>& getElems() const { return elems; }
};

std::vector<std::vector<char>> getAllPerms(Tree& tree);
std::vector<char> getPerm1(Tree& tree, int num);
std::vector<char> getPerm2(Tree& tree, int num);

#endif  // INCLUDE_TREE_H_
