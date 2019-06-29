#include <iostream>

using namespace std;

class OrdArray {
    private:
        long *array;
        unsigned size;
        long inv_count;

        void _merge(long *temp_array, long left, long mid, long right) {
            int i = left;
            int j = right;
            int k = mid;

            while ((i <= mid - 1) && (j <= right)) {
                if(array[i] < array[j]) {
                    temp_array[k++] = array[i++];
                }
                else {
                    temp_array[k++] = array[j++];
                    inv_count += (mid - i);
                }
            }

            while(i <= mid - 1) {
                temp_array[k++] = array[i++];
            }

            while(j <= right) {
                temp_array[k++] = array[j++];
            }

            for (i = left; i <= right; i++)
                array[i] = temp_array[i];
        }

        void _mergeSort(long *temp_array, long left, long right) {
            if(left >= right) return;

            long mid = (left + right) / 2;
            _mergeSort(temp_array, left, mid);
            _mergeSort(temp_array, mid + 1, left);

            _merge(temp_array, left, mid + 1, right);
        }

    public:
        explicit OrdArray(const long *array_get) {
            size = (sizeof(array_get) / sizeof(array_get[0])) + 1;
            array = new long[size];
            inv_count = -1;

            for(unsigned i = 0; i < size; i++) array[i] = array_get[i];
        }

        void countInversion() {
            auto temp_array = new long[size];
            inv_count = 0;
            _mergeSort(temp_array, 0 , size - 1);
        }

        long getInvCount() {
            return inv_count;
        }

        long *getArray() {
            unsigned size = (sizeof(array) / sizeof(array[0]));
            auto new_array = new long[size];

            for(unsigned i = 0; i < size; i++) new_array[i] = array[i];
        }
};

int main() {
    unsigned i, j, n, t;

    cin >> n;

    OrdArray *aux;
    for(i = 0; i < n; i++) {
        cin >> t;
        long array[t];

        for(j = 0; j < t; j++) cin >> array[j];

        aux = new OrdArray(array);
        aux->countInversion();

        cout << aux->getInvCount() << endl;
    }

    return 0;
}