#include <vector>
using namespace std;

class Tree {
   public:
    Tree(int w, char c);
    Tree(int w, Tree* t1, Tree* t2);
    ~Tree();
    int getWeight() const;
    void printTree(vector<char>& bitString) const;

   private:
    Tree* left;
    Tree* right;
    int weight;
    char c;
};