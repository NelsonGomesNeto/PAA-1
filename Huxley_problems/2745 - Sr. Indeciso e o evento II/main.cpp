#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long min(long a, long b) {
    if(a < b) {
        return a;
    }
    else {
        return b;
    }
}

class SegmenteTree {
    private:
        vector<long> *segTree;
        vector<long> *values;

    public:
        explicit SegmenteTree(vector<long> *array) {
            segTree = new vector<long>;
            values = new vector<long>;

            values->push_back(-1);
            for(long & i : *array) {
                values->push_back(i);
            }

            segTree->resize((values->size() * 4) +1);

            build(1, 1, values->size() - 1);
        }

        void build(int idx, int left, int right)
        {
            if (right - left < 2)
            {
                segTree->at(idx) = segTree->at(left);
                return;
            }
            int mid = (left+right)  / 2;
            build(idx * 2, left, mid);
            build(idx * 2+1, mid, right);
            segTree->at(idx) = segTree->at(idx*2) + segTree->at(idx*2+1);
        }


        long sum(int x, int y, int idx, int left, int right)
        {
            if (x >= right || y <= left)
            {
                return 0;
            }
            if (x <= left && y >= right)
            {
                return segTree->at(idx);
            }

            long mid = (left + right) / 2;
            return 	sum(x, y, idx * 2, left, mid) +
                      sum(x, y, idx * 2 + 1, mid, right);
        }


        void modify(int pos, int value, int idx, int left, int right)
        {
            segTree->at(idx) += ( value - segTree->at(pos));
            if (right - left < 2) {
                values->at(pos)  = value;
                return;
            }
            int mid = (left+right) / 2;

            if (pos < mid) {
                modify(pos, value, idx*2, left, mid);
            }
            else {
                modify(pos, value, idx*2+1, mid, right);
            }
        }

        long getSizeValues() {
            return values->size();
        }

        void print() {
            for(auto &i : *segTree) {
                cout << i << " ";
            }

            cout << "\n";
        }
};

int main() {
    unsigned int n, q, i;
    long a, b;
    auto *array = new vector<long>;
    cin >> n;

    for(i = 0; i < n; i++) {
        cin >> a;
        array->push_back(a);
    }
    auto *segTree = new SegmenteTree(array);
    segTree->print();
    delete array;

    cin >> q;
    char c;
    for(i = 0; i < q; i ++) {
        cin >> c >> a >> b;

        if(c == 'Q') {
            long p = segTree->sum(a, b, 1, 1, segTree->getSizeValues() - 1);
            cout << p << "\n";

//            cout << p.first << " " << p.second << "\n";
        }
        else {
            segTree->modify(a, b, 1, 1, segTree->getSizeValues() - 1 );
        }
    }


    return 0;
}