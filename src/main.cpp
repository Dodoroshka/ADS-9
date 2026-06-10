// Copyright 2022 NNTU-CS
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"
static void printPerm(const std::vector<char>& p) {
    for (char c : p) std::cout << c;
    std::cout << "\n";
}
static int64_t factorialLL(int n) {
    int64_t res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}
static std::vector<char> makeAlphabet(int n) {
    std::vector<char> a;
    for (int i = 0; i < n; ++i) {
        a.push_back(static_cast<char>('A' + i));
    }
    return a;
}
int main() {
    {
        std::vector<char> in = { '1', '2', '3', '4' };
        PMTree tree(in);
        std::cout << "Demo for alphabet {1,2,3,4}\n";
        std::cout << "All permutations:\n";
        auto perms = getAllPerms(tree);
        for (size_t i = 0; i < perms.size(); ++i) {
            std::cout << (i + 1) << ": ";
            printPerm(perms[i]);
        }
        std::cout << "\n";
    }
    std::cout << "n\tgetAllPerms(ms)\tgetPerm1(ms)\tgetPerm2(ms)\n";
    int nMin = 1, nMax = 15;
    std::mt19937 rng(12345);

    for (int n = nMin; n <= nMax; ++n) {
        PMTree tree(makeAlphabet(n));
        int64_t totalPerms = factorialLL(n);
        std::uniform_int_distribution<int64_t> dist(1, totalPerms);
        int64_t num = dist(rng);

        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(tree);
        auto stop = std::chrono::high_resolution_clock::now();
        double timeAll =
            std::chrono::duration<double, std::milli>(stop - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm1(tree, static_cast<int>(num));
        stop = std::chrono::high_resolution_clock::now();
        double timeP1 =
            std::chrono::duration<double, std::milli>(stop - start).count();

        start = std::chrono::high_resolution_clock::now();
        getPerm2(tree, static_cast<int>(num));
        stop = std::chrono::high_resolution_clock::now();
        double timeP2 =
            std::chrono::duration<double, std::milli>(stop - start).count();
        std::cout << n << "\t" << timeAll
            << "\t\t" << timeP1 << "\t\t" << timeP2
            << "\n";
    }
    return 0;
}
