#include <cmath>
#include <iostream>
#include <map>

int recursiveT(const int n) {
    if (n <= 1) {
        return n;
    }
    const int result = recursiveT(static_cast<int>(std::ceil(n / 2.0))) + recursiveT(n - 1) + n;
    return result;
}

int recursiveMap(const int n, std::pmr::map<int, int> &memo) {
    if (n <= 1) {
        return n;
    }
    if (const auto it = memo.find(n); it != memo.end()) {
        return it->second;
    }
    const int result = recursiveMap(static_cast<int>(std::ceil(n / 2.0)), memo) +
                       recursiveMap(n - 1, memo) + n;
    memo[n] = result;
    return result;
}

int main() {
    constexpr int n = 2;
    const int result = recursiveT(n);
    std::cout << "T(" << n << ") = " << result << std::endl;

    std::pmr::map<int, int> memo = {};
    const int memoResult = recursiveMap(n, memo);
    std::cout << "Memoized T(" << n << ") = " << memoResult << std::endl;

    return 0;
}