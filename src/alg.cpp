// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>

void Tree::buildFrom(Node* parent, const std::vector<char>& remaining) {
    if (remaining.empty()) return;
    for (size_t i = 0; i < remaining.size(); i++) {
        char pick = remaining[i];
        Node* child = new Node(pick);
        parent->children.push_back(child);
        std::vector<char> next;
        next.reserve(remaining.size() - 1);
        for (size_t j = 0; j < remaining.size(); j++) {
            if (j == i) continue;
            next.push_back(remaining[j]);
        }
        buildFrom(child, next);
    }
}
void Tree::clear(Node* node) {
    if (!node) return;
    for (Node* ch : node->children) {
        clear(ch);
    }
    delete node;
}
Tree::Tree(const std::vector<char>& in) : root(new Node()), elems(in) {
    std::sort(elems.begin(), elems.end());
    buildFrom(root, elems);
}
Tree::~Tree() {
    clear(root);
}
static void collectAll(Tree::Node* node,
    std::vector<char>& current,
    std::vector<std::vector<char>>& out) {
    if (!node) return;
    if (node->children.empty()) {
        out.push_back(current);
        return;
    }
    for (Tree::Node* ch : node->children) {
        current.push_back(ch->value);
        collectAll(ch, current, out);
        current.pop_back();
    }
}
std::vector<std::vector<char>> getAllPerms(Tree& tree) {
    std::vector<std::vector<char>> out;
    std::vector<char> current;
    if (tree.getElems().empty()) {
        out.push_back(std::vector<char>{});
        return out;
    }
    collectAll(tree.getRoot(), current, out);
    return out;
}

std::vector<char> getPerm1(Tree& tree, int num) {
    if (num <= 0) {
        throw std::invalid_argument("num must be >= 1");
    }
    auto perms = getAllPerms(tree);
    if (num > (int)perms.size()) {
        throw std::out_of_range("num is too large");
    }
    return perms[(size_t)num - 1];
}
static int countPerms(Tree::Node* node) {
    if (!node) return 0;
    if (node->children.empty()) return 1; 
    int sum = 0;
    for (Tree::Node* ch : node->children) {
        sum += countPerms(ch);
    }
    return sum;
}
std::vector<char> getPerm2(Tree& tree, int num) {
    if (num <= 0) {
        throw std::invalid_argument("num must be >= 1");
    }
    int total = countPerms(tree.getRoot());
    if (num > total) {
        throw std::out_of_range("num is too large");
    }
    Tree::Node* cur = tree.getRoot();
    std::vector<char> result;
    while (!cur->children.empty()) {
        for (size_t i = 0; i < cur->children.size(); i++) {
            Tree::Node* ch = cur->children[i];
            int cnt = countPerms(ch);
            if (num > cnt) {
                num -= cnt;
            } else {
                result.push_back(ch->value);
                cur = ch;
                break;
            }
        }
    }
    return result;
}
