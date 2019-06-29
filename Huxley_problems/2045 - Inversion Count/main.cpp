#include <iostream>
#include <vector>

using namespace std;

unsigned merge(long array[], long temp_array[], unsigned left, unsigned mid, unsigned right) {
    unsigned i = left, j = right, k = mid, inv_count = 0;

    while(i <= mid && j <= right) {
        if(array[i] <= array[j]) {
            temp_array[k++] = array[i++];
        }
        else {
            temp_array[k++] = array[j++];
            inv_count += (mid - i);
        }
    }

    while(i <= mid) {
        temp_array[k++] = array[i++];
    }

    while(j <= right) {
        temp_array[k++] = array[j++];
    }

    for(i = left; i <= right; i++) {
        array[i] = temp_array[i];
    }

    return inv_count;
}

unsigned _ct(long array[], long temp_array[],  unsigned left, unsigned right) {
    unsigned mid, inv_count = 0;

    if(right > left) {
        mid = (left + right) / 2;

        inv_count = _ct(array, temp_array, left, mid);
        mid++;
        inv_count += _ct(array, temp_array, mid, right);
        inv_count +=  merge(array, temp_array, left, mid, right);
    }

    return inv_count;
}

unsigned countInversion(long array[], unsigned size) {
    long temp_array[size];
    return _ct(array, temp_array, 0, size - 1);
}

int main() {
    unsigned i, j, n, t;

    cin >> n;

    vector<long> array;
    for(i = 0; i < n; i++) {
        cin >> t;

        array.resize(t);
        for(j = 0; j < t; j++) cin >> array.at(j);

        cout << countInversion(&array[0], t) << endl;
    }

    return 0;
}