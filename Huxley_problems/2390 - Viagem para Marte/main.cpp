#include <iostream>

using namespace std;

#define INTERVAL 1000

short *count_sort(short *array, short size) {
    auto new_array = new short[size];
    auto count = new short[INTERVAL] {0};
    unsigned  int i;

    for(i = 0; i < size; i ++) {
        count[array[i]]++;
    }

    for(i = 1; i < size; i++) {
        count[i] += count[i - 1];
    }

    for(i = size - 1; i >= 0; i--) {
        new_array[count[array[i]]] = array[i];
        count[array[i]]--;
    }

    delete [] count;
    return  new_array;
}

int main() {
    unsigned int i;
    short n, m;
    cin >> n >> m;

    auto a_s = new short[n];
    auto b_s = new short[n];
    short *o_a_s, *o_b_s;

    for(i = 0; i < n; i++) {
        cin >> a_s[i];
    }
    o_a_s = count_sort(a_s, n);

    for(i = 0; i < n; i++) {
        cin >> b_s[i];
    }
    o_b_s =  count_sort(b_s, n);

    return 0;
}