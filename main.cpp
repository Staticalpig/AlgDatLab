#include <algorithm>
#include <format>
#include <iostream>
#include <vector>


std::vector<int> BucketSort(std::vector<int> &v) {
    if (v.empty()) {
        return {};
    }

    const int k = *std::ranges::max_element(v);

    std::vector<int> w = std::vector<int>(k + 1, 0);

    for (const int i : v) {
        w[i] +=1;
    }

    return w;
}


int main() {

    std::vector<int> data = {20,20,1,25, 0, 0, 0, 0};
    std::vector<int> sorted = BucketSort(data);

    std::cout << sorted.size() << std::endl;
    std::cout << "[POS]:[AMOUNT]" << std::endl;

    for (int i = 0; i < sorted.size(); ++i) {
        std::cout << std::format("{}:{}\n", i, sorted[i]);
    }
    std::cout << std::endl;

    return 0;
}