#include <iostream>
#include <vector>

using namespace std;

class SegmenteTree {
    private:
        vector<long> segTree;

    public:
        SegmenteTree(vector<long> array) {
            vector<long> temp;
            temp.push_back(-1);

            for(long & i : array) {
                temp.push_back(i);
            }
        }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}