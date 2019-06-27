#include <bits/stdc++.h>

using namespace std;

bool comparePair (pair<int, int> p1, pair <int, int> p2) {
    return p1.second < p2.second;
}

int main() {
    int n, i;

    cin >> n;

    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }

    vector<pair<int, int>> pares;

    for(i = 0; i < n; i++) {
        pair<int, int> p;
        cin >> p.first;
        cin >> p.second;

        pares.push_back(p);
    }

    sort(pares.begin(), pares.end(), comparePair);

    int count = 0;
    int aux = 0;
    for(i = 0; i < pares.size(); i ++) {
        if (pares.at(i).first >= aux) {
            count ++;
            aux = pares.at(i).second;
        }
    }

    cout << count << "\n";

    return 0;
}