#include <iostream>

#define MAX_RANGE 10000000000

using namespace std;

double makeTravel(double fuel, short  weight, short taken_off[], short take_off[], unsigned short size) {
    unsigned short i;

    fuel -= (fuel + weight) / taken_off[0];

    for(i = 1; i < size; i++) {
        fuel -= (fuel + weight) / take_off[i];
        fuel -= (fuel + weight) / taken_off[i];
    }

    fuel -= (fuel + weight) / take_off[0];

    return fuel;
}

double biSearch(double start, double end, short taken_off[], short take_off[], unsigned short size, unsigned short weight) {
    double mid, aux;
    while(start != end) {
        mid = (start + end) / 2.0;
        aux = makeTravel(mid, weight, taken_off, take_off, size);
//        cout << start << " | " << end << " | " << mid << " | " << aux << "\n";

        if(aux >= -0.000000001 && aux <= 0.000000001) {
            return mid;
        }

        if(aux < 0) {
            start = mid + 0.000000001;
        }
        else {
            end = mid - 0.000000001;
        }
    }
}

int main() {
    unsigned  short i;
    short n = -1, m = -1;
    cin >> n;
    cin >> m;

    short taken_off[n];
    short take_off[n];

    for(i = 0; i < n; i++) {
        cin >> taken_off[i];
    }

    for(i = 0; i < n; i++) {
        cin >> take_off[i];
    }

    double aux = makeTravel(MAX_RANGE, m, taken_off, take_off, n);
    if(aux < 0) {
        cout << -1;
    }
    else if(aux > 0) {
        printf("%.2lf", biSearch(0, MAX_RANGE, taken_off, take_off, n, m));
    }
    else {
        cout << MAX_RANGE;
    }


    return 0;
}