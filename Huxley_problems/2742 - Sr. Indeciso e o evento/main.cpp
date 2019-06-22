#include <iostream>

using namespace std;

unsigned int mod_bs_0(unsigned int *array, unsigned int pivot, unsigned int start, unsigned int end) {
    unsigned int mid = (start + end) / 2;

    if(start == end) {
        return mid;
    }


    if(array[mid] >= pivot) {
        return mod_bs_0(array, pivot, start, mid - 1);
    }
    else {
        return mod_bs_0(array, pivot, mid + 1, end);
    }
}

unsigned int mod_bs_1(unsigned int *array, unsigned int pivot, unsigned int start, unsigned int end, unsigned int size) {
    unsigned int mid = (start + end) / 2;

    if(start == end) {
        return mid;
    }

    if(array[mid] <= pivot) {
        if(array[mid + 1] <)
        return mod_bs_1(array, pivot, mid + 1, end, size);
    }
    else {
        return mod_bs_1(array, pivot, start, mid - 1, size);
    }
}

int main() {
    unsigned int n, i, q, aux, answer, size;
    cin >> n;
    size = n - 1;

    unsigned int *money = new unsigned int[n];
    for(i = 0; i < n; i++) {
        cin >> money[i];
    }

    cin >> q;
    for(i = 0; i < q; i++) {
        cin >> aux;

        answer = mod_bs_0(money, aux, 0, size);
        cout << answer << " ";
        answer = mod_bs_1(money, aux, 0, size, n);
        cout << answer << "\n";
    }

    delete [] money;
    return 0;
}