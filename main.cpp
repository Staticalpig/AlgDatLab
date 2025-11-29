#include <algorithm>
#include <format>
#include <iostream>
#include <vector>

void insertionSort(std::vector<int> &v);
void printVector(const std::vector<int> &v);
std::vector<int> BucketSort(std::vector<int> &v);


int main() {
    std::vector<int> data = {20,20,1,25, 0, 0, 0, 0};
    std::vector<int> sorted = BucketSort(data); //0(n + k) from BucketSort

    std::cout << sorted.size() << std::endl;
    std::cout << "[POS]:[AMOUNT]" << std::endl;

    for (int i = 0; i < sorted.size(); ++i) {
        std::cout << std::format("{}:{}\n", i, sorted[i]);
    }
    std::cout << std::endl;

    //testing
    //printVector(sorted);
    insertionSort(sorted);      //gets 'sorted' which is size of k, insertion sort is O(k^2) in worst case. O(k^2) > O(n + k)
    printVector(sorted);

    return 0;
}

std::vector<int> BucketSort(std::vector<int> &v) {
    if (v.empty()) {
        return {};
    }

    const int k = *std::ranges::max_element(v);         //O(n)

    std::vector<int> w = std::vector<int>(k + 1, 0);    //O(k)

    for (const int i : v) {                             //O(n)
        w[i] +=1;
    }

    return w;                                           //Overall complexity: O(n + k)
}

void insertionSort(std::vector<int> &v) {
    for (int i = 1; i < v.size(); i++) {    //v size is k+1
        int key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > key) {      //k again, so O(k^2) overall?
            //std::cout << std::format("Swapping {} and {} at v[{}]\n", v[j], v[j + 1], i);
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
        printVector(v);
    }
}

void printVector(const std::vector<int> &v) {
    for (const int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}