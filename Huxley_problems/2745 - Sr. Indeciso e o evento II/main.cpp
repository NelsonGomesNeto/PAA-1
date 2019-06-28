#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegmenteTree {
    private:
        vector<pair<long,long>> *segTree;
        vector<long> *values;

    public:
        explicit SegmenteTree(vector<long> *array) {
            segTree = new vector<pair<long,long>>;
            values = new vector<long>;

            values->push_back(-1);
            for(long & i : *array) {
                values->push_back(i);
            }

            segTree->resize((values->size() * 4) +1);

            build(1, 1, values->size());
        }

        void build(int idx, int left, int right)
        {
//            cout << idx << " | " << left << " | " << right << endl;
            pair<long, long> p;
            if (right - left < 2)
            {
//                cout << "End " << idx << endl;
                p.first = values->at(left);
                p.second = values->at(left);

                segTree->at(idx) = p;
                return;
            }

            int mid = (left+right)  / 2;
            build(idx * 2, left, mid);
            build(idx * 2+1, mid, right);

//            cout << "sum " << segTree->at(idx*2) + segTree->at(idx*2+1) << endl;

            segTree->at(idx).first = segTree->at(idx*2).first + segTree->at(idx*2+1).first;

            if(segTree->at(idx * 2).second < segTree->at(idx * 2 + 1).second) {
                segTree->at(idx).second = segTree->at(idx * 2).second;
            }
            else {
                segTree->at(idx).second = segTree->at(idx * 2 + 1).second;
            }
        }


        pair<long, long> sum(int x, int y, int idx, int left, int right)
        {
            pair<long, long> a;
            if (x >= right || y <= left)
            {
                a.first = 0;
                a.second = INT64_MAX;
                return a;
            }
            if (x <= left && y >= right)
            {
                a.first = segTree->at(idx).first;
                a.second = segTree->at(idx).second;

                return a;
            }

            long mid = (left + right) / 2;
            a = sum(x, y, idx * 2, left, mid);
            pair <long , long> b = sum(x, y, idx * 2 + 1, mid, right);

            a.first = a.first + b.first;

            if(b.second < a.second) {
               a.second = b.second;
            }

            return a;
        }


        void modify(int pos, int value, int idx, int left, int right)
        {
            segTree->at(idx).first += ( value - values->at(pos));

            if (right - left < 2) {
                values->at(pos)  = value;
                segTree->at(idx).second = value;
                return;
            }
            int mid = (left+right) / 2;


            if (pos < mid) {
                modify(pos, value, idx*2, left, mid);
            }
            else {
                modify(pos, value, idx*2+1, mid, right);
            }

            if(segTree->at(idx * 2).second < segTree->at(idx * 2 + 1).second) {
                segTree->at(idx).second = segTree->at(idx * 2).second;
            }
            else {
                segTree->at(idx).second = segTree->at(idx * 2 + 1).second;
            }
        }

        long getSizeValues() {
            return values->size();
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
    delete array;

    cin >> q;
    char c;
    for(i = 0; i < q; i ++) {
        cin >> c >> a >> b;

        if(c == 'Q') {
            pair<long, long> p = segTree->sum(a + 1, b + 2, 1, 1, segTree->getSizeValues());
            cout << p.first << " " << p.second << "\n";
        }
        else {
            segTree->modify(a + 1, b, 1, 1, segTree->getSizeValues());
        }
    }


    return 0;
}