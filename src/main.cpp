// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "tree.h"

static void printPerm(const std::vector<char>& p) {
    for (char c : p) std::cout << c;
    std::cout << "\n";
}


static long long factorialLL(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

static std::vector<char> makeAlphabet(int n) {
    std::vector<char> a;
    for (int i = 0; i < n; i++) {
        a.push_back(static_cast<char>('A' + i));
    }
    return a;
}

template <typename Func>
static double measureMs(Func fn) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    fn();
    auto stop = high_resolution_clock::now();
    duration<double, std::milli> diff = stop - start;
    return diff.count();
}

int main() {
    {
        std::vector<char> in = { '1','2','3' };
        Tree tree(in);

        std::cout << "Demo for alphabet {1,2,3}\n";
        std::cout << "All perms:\n";
        auto perms = getAllPerms(tree);
        for (size_t i = 0; i < perms.size(); i++) {
            std::cout << (i + 1) << ": ";
            printPerm(perms[i]);
        }
        std::cout << "\n";
    }

    std::cout << "Experiment: time vs alphabet size n\n";
    std::cout << "Columns: n, num, time(getAllPerms), time(getPerm1), time(getPerm2)\n";


    int nMin = 1;
    int nMax = 9;

    std::mt19937 rng(12345);

    for (int n = nMin; n <= nMax; n++) {
        std::vector<char> alphabet = makeAlphabet(n);
        Tree tree(alphabet);

        long long totalPerms = factorialLL(n);

        std::uniform_int_distribution<long long> dist(1, totalPerms);
        long long num = dist(rng);

        double tAll = measureMs([&]() {
            auto perms = getAllPerms(tree);
            (void)perms; 
            });

        double tPerm1 = measureMs([&]() {
            auto p = getPerm1(tree, (int)num);
            (void)p;
            });

        double tPerm2 = measureMs([&]() {
            auto p = getPerm2(tree, (int)num);
            (void)p;
            });

        std::cout << n << ", " << num << ", "
            << tAll << " ms, "
            << tPerm1 << " ms, "
            << tPerm2 << " ms\n";
    }

    return 0;
}
