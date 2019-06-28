#include <iostream>
#include <vector>

using namespace std;

bool Pair(long item) {
    return item % 2 == 0;
}

class SegmenteTree {
private:
    vector<long > *segTreePair;
    vector<long > *segTreeOdd;
    vector<long > *values;

    long travel(vector<long > *segTree, long x, long y, long idx, long left, long right)
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
        return travel(segTree, x, y, idx * 2, left, mid) + travel(segTree, x, y, idx * 2 + 1, mid, right);
    }


    void print(vector<long> *segTree) {
        for(long &e : *segTree) {
            cout << e << " ";
        }

        cout << endl;
    }

public:
    explicit SegmenteTree(vector<long > *array) {
        segTreePair = new vector<long >;
        segTreeOdd = new vector<long >;
        values = new vector<long >;

        values->push_back(-1);
        for (long &i : *array) {
            values->push_back(i);
        }

        for(long i = 0; i < (values->size() * 4) + 1; i++) {
            segTreePair->push_back(-1);
            segTreeOdd->push_back(-1);
        }

        build(1, 1, values->size());
    }

    void build(long idx, long left, long right) {
        if (right - left < 2) {

            if (Pair(values->at(left))) {
                segTreePair->at(idx) = 1;
                segTreeOdd->at(idx) = 0;
            } else {
                segTreePair->at(idx) = 0;
                segTreeOdd->at(idx) = 1;
            }

            return;
        }

        long mid = (left + right) / 2;
        long le = idx * 2;
        long re = le + 1;

        build(le, left, mid);
        build(re, mid, right);

        segTreePair->at(idx) = segTreePair->at(le) + segTreePair->at(re);
        segTreeOdd->at(idx) = segTreeOdd->at(le) + segTreeOdd->at(re);
    }

    void modification(long pos, long value, long idx, long left, long right)
    {
        if (right - left < 2) {
            values->at(pos) = value;

            if (Pair(value)) {
                segTreePair->at(idx) = 1;
                segTreeOdd->at(idx) = 0;
            } else {
                segTreePair->at(idx) = 0;
                segTreeOdd->at(idx) = 1;
            }
            return;
        }
        long mid = (left+right) / 2;


        if (pos < mid) {
            modification(pos, value, idx*2, left, mid);
        }
        else {
            modification(pos, value, idx*2+1, mid, right);
        }

        long le = idx * 2;
        long re = le + 1;
        segTreePair->at(idx) = segTreePair->at(le) + segTreePair->at(re);
        segTreeOdd->at(idx) = segTreeOdd->at(le) + segTreeOdd->at(re);
    }

    long amountPair(long x, long y, long idx, long left, long right) {
        return travel(segTreePair, x, y, idx, left, right);
    }

    long amountOdd(long x, long y, long idx, long left, long right) {
        return travel(segTreeOdd, x, y, idx, left, right);
    }

    long getSizeValues() {
        return values->size();
    }

    void printPair() {
        print(segTreePair);
    }

    void printOdd() {
        print(segTreeOdd);
    }

    void print() {
        cout << endl << endl;
        printPair();
        cout << endl << endl;
        printOdd();
        cout << endl << endl;
    }
 };

int main() {
    long n = 0, i, q, a, b, c;
    cin >> n;

    vector<long> *array = new vector<long>;
    long aux;
    for(i = 0; i < n; i++) {
        cin >> aux;
        array->push_back(aux);
    }

    cin >> q;
    SegmenteTree *segTree = new SegmenteTree(array);
    delete array;

//    segTree->print();

    for(i = 0; i < q; i++) {
        cin >> a >> b >> c;

        switch(a) {
            case 0:
                segTree->modification(b, c, 1, 1, segTree->getSizeValues());
//                segTree->print();
                break;

            case 1:
                cout << segTree->amountPair(b, c + 1, 1, 1, segTree->getSizeValues()) << endl;
                break;

            case 2:
                cout << segTree->amountOdd(b, c + 1, 1, 1, segTree->getSizeValues()) << endl;
                break;

            default:
                cout << "Error" << endl;
        }
    }

    return 0;
}