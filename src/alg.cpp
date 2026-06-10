// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <vector>

PMTree::PMTree(const std::vector<char>& input) : source(input) {
  root = new Node(0);
  std::vector<char> ordered = input;
  std::sort(ordered.begin(), ordered.end());
  for (char symbol : ordered) {
    std::vector<char> remainder = ordered;
    remainder.erase(std::find(remainder.begin(), remainder.end(), symbol));
    Node* descendant = construct(remainder);
    descendant->value = symbol;
    root->branches.push_back(descendant);
  }
}
PMTree::~PMTree() {
  erase(root);
}
PMTree::Node* PMTree::construct(const std::vector<char>& remaining) {
  Node* current = new Node(0);
  if (remaining.empty()) return current;
  std::vector<char> ordered = remaining;
  std::sort(ordered.begin(), ordered.end());
  for (char symbol : ordered) {
    std::vector<char> remainder = ordered;
    remainder.erase(std::find(remainder.begin(), remainder.end(), symbol));
    Node* descendant = construct(remainder);
    descendant->value = symbol;
    current->branches.push_back(descendant);
  }
  return current;
}
void PMTree::erase(Node* vertex) {
  if (!vertex) return;
  for (PMTree::Node* child : vertex->branches) {
    erase(child);
  }
  delete vertex;
}
static void depthWalk(PMTree::Node* current,
                      std::vector<char>& buffer,
                      std::vector<std::vector<char>>& collection,
                      int depth, int maxDepth) {
  if (depth == maxDepth) {
    collection.push_back(buffer);
    return;
  }
  for (PMTree::Node* next : current->branches) {
    buffer.push_back(next->value);
    depthWalk(next, buffer, collection, depth + 1, maxDepth);
    buffer.pop_back();
  }
}
std::vector<std::vector<char>> getAllPerms(PMTree& container) {
  std::vector<std::vector<char>> collection;
  std::vector<char> buffer;
  int totalCount = static_cast<int>(container.getSource().size());
  for (PMTree::Node* first : container.getRoot()->branches) {
    buffer.push_back(first->value);
    depthWalk(first, buffer, collection, 1, totalCount);
    buffer.pop_back();
  }
  return collection;
}
size_t factorial(int number) {
  if (number <= 1) return 1;
  size_t result = 1;
  for (int i = 2; i <= number; ++i) {
    result *= i;
  }
  return result;
}
std::vector<char> getPerm1(PMTree& container, int position) {
  auto allPermutations = getAllPerms(container);
  int total = static_cast<int>(allPermutations.size());
  if (position <= 0 || position > total) {
    return {};
  }
  return allPermutations[position - 1];
}
std::vector<char> getPerm2(PMTree& container, int position) {
  int total = static_cast<int>(container.getSource().size());
  if (position <= 0 || static_cast<size_t>(position) > factorial(total)) {
    return {};
  }
  std::vector<char> result;
  int remainder = position - 1;
  PMTree::Node* current = container.getRoot();
  for (int step = 0; step < total; ++step) {
    int blockSize = static_cast<int>(factorial(total - step - 1));
    int index = remainder / blockSize;
    remainder %= blockSize;
    if (index >= static_cast<int>(current->branches.size())) {
      return {};
    }
    current = current->branches[index];
    result.push_back(current->value);
  }
  return result;
}
