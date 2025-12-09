#include <algorithm>
#include <format>
#include <iostream>
#include <vector>

void insertionSort(std::vector<int> &v);
void printVector(const std::vector<int> &v);
std::vector<int> BucketSort(std::vector<int> &v);


int main() {
    std::vector v = {10, 1, 12, 1, 10, 1, 5};    //previously called "data"
    std::vector<int> w = BucketSort(v); //0(n + k) from BucketSort. previously called "sorted"

    std::cout << "    Use 'w' to write out the vector 'v' in a sorted order:" << std::endl;
    for (int i = 0; i < w.size(); i++) {
        for(int j = w[i]; j > 0; j--){
            std::cout << i <<" ";
        }
    }
    std::cout << std::endl;
    //testing
    printVector(w);
    insertionSort(w); //gets 'sorted' which is size of k, insertion sort is O(k^2) in worst case. O(k^2) > O(n + k)
    printVector(w);

    return 0;
}

std::vector<int> BucketSort(std::vector<int> &v) {
    if (v.empty()) {
        // O(1)
        return {};
    }
    const int k = *std::ranges::max_element(v); //O(n)
    std::vector<int> w = std::vector(k + 1, 0); //O(k)

    for (const int i: v) {
        //O(n)
        w[i] += 1; //O(1) ish O(1N)
    }
    return w; //Overall complexity: O(n + k)
}

void insertionSort(std::vector<int> &v) {
    for (int i = 1; i < v.size(); i++) {
        //v size is k+1
        const int key = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > key) {
            //k again, so O(k^2) overall?
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key; // O(1) ?
        //printVector(v);
    }
}

void printVector(const std::vector<int> &v) {
    for (const int i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
