#include <iostream>

using namespace std;

long _ic(const long array[], const unsigned left, const unsigned mid, const unsigned right) {
    unsigned i = left, j = right, inv_count = 0;

    while(i < mid && j <= right) {
        if(array[i] > array[j]) {
            j++;
            inv_count += (mid - i);
        }
        else {
            i++;
        }
    }

    return inv_count;
}

long _ct(const long array[], const unsigned left, const unsigned right) {
    unsigned mid, inc_count = 0;

    if(right > left) {
        mid = (left + right) / 2;
        inc_count = _ct(array, left, mid);
        inc_count += _ct(array, mid + 1, right);

        inc_count += _ic(array, left, mid + 1, right);
    }

    return inc_count;
}

long countInversion(const long array[], const unsigned size) {
    long temp[size];
    return _ct(array, 0, size - 1);
}

int main() {
    unsigned i, j, n, t;

    cin >> n;

    for(i = 0; i < n; i++) {
        cin >> t;
        long array[t];
        for(j = 0; j < t; j++) cin >> array[j];
        cout << countInversion(array, t) << endl;
    }

    return 0;
}