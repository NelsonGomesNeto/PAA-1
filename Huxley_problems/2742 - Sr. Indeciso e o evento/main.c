#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <values.h>

unsigned int mod_binary_search(bool type, unsigned int *array, unsigned int pivot, unsigned int start, unsigned int end) {
    if(start == end) {
        return UINT_MAX;
    }

    unsigned int mid = (start + end) / 2;
    if(type) {
        if(array[mid] >= pivot) {
            printf("%d\n", array[mid]);
            unsigned int a = mod_binary_search(type, array, pivot, start, mid - 1);

            if(a == UINT_MAX) {
                return start;
            }
        }
        else {
            return mod_binary_search(type, array, pivot, mid + 1, end);
        }
    }
    else {
        if(array[mid] <= pivot) {
            unsigned int a = mod_binary_search(type, array, pivot, mid + 1, end);

            if(a == UINT_MAX) {
                return end;
            }
        }
        else {
            return mod_binary_search(type, array, pivot, start, mid - 1);
        }
    }
}

int main() {
    unsigned int n, i, q, aux;
    scanf("%u", &n);

    unsigned int *money = (unsigned int *) malloc(sizeof(int) *n);
    for(i = 0; i < n; i++) {
        scanf("%u", &money[i]);
    }

    unsigned int answers[2], size = n - 1;
    scanf("%u", &q);
    for(i = 0; i < q; i++) {
        scanf("%u", &aux);

        answers[0] = mod_binary_search(true, money, aux, 0, size);
        answers[1] = mod_binary_search(false, money, aux, 0, size);

        printf("%d %d\n", answers[0], answers[1]);
    }



    return 0;
}