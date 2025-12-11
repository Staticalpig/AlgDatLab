#include <algorithm>
#include <iostream>
#include <vector>

void insertionSort(std::vector<int> &v);
void printVector(const std::vector<int> &v);
std::vector<int> BucketSort(std::vector<int> &v);

int main() {
    //the original vector used as input
    std::vector v = {10, 1, 12, 1, 10, 1, 5};
    std::cout << "Original vector 'v': \n";
    printVector(v);
    std::vector<int> w = BucketSort(v);

    insertionSort(w);
    //printVector(w);
    return 0;
}

std::vector<int> BucketSort(std::vector<int> &v) {
    if (v.empty()) {
        return {};
    }
    //find the biggest element in v, and create a vector w of size (k+1) initialized to 0
    const int k = *std::ranges::max_element(v);
    std::vector<int> w = std::vector(k + 1, 0);

    //count frequency of each element in v by increasing the corresponding index in w
    for (const int i: v) {
        w[i] += 1;
    }

    //print out v in a sorted order using w
    std::cout << "    Use 'w' to write out the vector 'v' in a sorted order:" << std::endl;
    for (int i = 0; i < w.size(); i++) {
        for(int j = w[i]; j > 0; j--){
            std::cout << i <<" ";
        }
    }
    std::cout << std::endl;
    return w;
}

void insertionSort(std::vector<int> &v) {
    for (int i = 1; i < v.size(); i++) {
        const int key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

void printVector(const std::vector<int> &v) {
    for (const int i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
