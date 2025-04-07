#include <bits/stdc++.h>
#include "lossFunctions.hpp"

using namespace std;

struct dule;


signed main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    int k;
    cin >> k;
    int q;
    cin >> q;
    vector<string> lessons(k);
    for (int i = 0; i < k; i++) {
        cin >> lessons[i];
    }
    vector<string> names(q);
    for (int i = 0; i < q; i++) {
        cin >> names[i];
    }
    vector<int> gr(q);
    for (int i = 0; i < q; i++) {
        cin >> gr[i];
    }
    vector<vector<vector<int>>> a(n);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        a[i].resize(cur);
        for (int j = 0; j < cur; j++) {
            a[i][j].resize(k);
            for (int f = 0; f < k; f++) {
                cin >> a[i][j][f];
            }
        }
    }
    int mxW, mxS;
    cin >> mxW >> mxS;
    dule victory = dule(n, k, q, lessons, names,  gr, a, mxW, mxS);
    victory.OTZHIGAY_TRATATATATA();
    victory.output();
    cout << endl << victory.getLoss();
    return 0;
}

