#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    int i, n, m, a, b;
    cin >> n;
    cin >> m;

    int cost[n];
    for(i = 0; i < n; i++) {
        cin >> cost[i];
    }

    int count = 0;
    for(i = 0; i < m; i++) {
        cin >> a >> b;
        a--;
        b--;

        if(cost[a] < cost[b]) {
            count += cost[a];
        }
        else {
            count += cost[b];
        }
    }

    cout << count << "\n";
    return 0;
}