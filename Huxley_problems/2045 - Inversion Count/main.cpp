#include <iostream>

using namespace std;

long countInversion(const long array[], const unsigned left, const unsigned right) {
    unsigned inv_count = 0;

    if(right > left) {
        unsigned  i = left, j = right, mid = (left + right) / 2;
        inv_count = countInversion(array, left, mid);
        mid++;
        inv_count += countInversion(array, mid, right);

        while (i < mid && j <= right) {
            if (array[i] > array[j]) {
                j++;
                inv_count += (mid - i);
            } else {
                i++;
            }
        }
    }

    return inv_count;
}

int main() {
    unsigned i, j, n, t;

    cin >> n;

    for(i = 0; i < n; i++) {
        cin >> t;
        long array[t];
        for(j = 0; j < t; j++) cin >> array[j];
        cout << countInversion(array, 0, t - 1) << endl;
    }

    return 0;
}