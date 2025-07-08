#include <bits/stdc++.h>
#include <climits>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
    int n;
    cin >> n;

    vector<int> A(n + 1), prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
        prefix[i] = prefix[i - 1] + A[i];
    }

    int maxres = INT_MIN, maxsum1 = INT_MIN, minsum2 = INT_MAX, maxsum3 = INT_MIN;

    for (int x1 = 1; x1 <= n; ++x1) {
        maxsum1 = max(maxsum1, prefix[x1]);
        for (int x2 = x1 + 1; x2 <= n; ++x2) {
            minsum2 = min(minsum2, prefix[x2 - 1] - prefix[x1]);
            for (int x3 = x2 + 1; x3 <= n; ++x3) {
                maxsum3 = max(maxsum3, prefix[x3 - 1] - prefix[x2]);
                int sum4 = prefix[n] - prefix[x3 - 1];
                int res = maxsum1 - minsum2 + maxsum3 - sum4;
                maxres = max(maxres, res);
            }
        }
    }

    cout << maxres;
}

int main() {
    faster
    
    Solve();
    
    return 0;
}