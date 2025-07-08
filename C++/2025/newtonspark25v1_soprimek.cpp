#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll MAX = 2e6 + 10;
vector<bool> isp;

void sieve(int n) {
    isp.resize(n + 1, true);
    isp[0] = isp[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (isp[i]) {
            for (int j = i * i; j <= n; j += i) isp[j] = false;
        }
    }
}

bool isp_k(int k, int p) {
    int start = max(2, p - k), end = p + k;
    for (int num = start; num <= end; ++num) {
        if (isp[num]) return true;
    }
    return false;
}

void Solve() {
	int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    int temp = 0;
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
        temp = max(temp, v[i].second + v[i].first);
    }

    sieve(temp);

    for (const auto& q : v) {
        int k = q.first;
        int p = q.second;
        cout << (isp_k(k, p) ? 1 : 0) << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}