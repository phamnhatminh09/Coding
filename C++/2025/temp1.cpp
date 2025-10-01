#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 2e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int MOD = 1e9 + 7;

int n, k;
int a[N];
ll dp[N];

struct FenwickTree {
    vector<int> bit;
    int n;

    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    int query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }
};

int count_inversions(vector<int>& v) {
    vector<int> temp = v;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());

    FenwickTree ft(temp.size());
    int res = 0;
    for (int i = v.size() - 1; i >= 0; --i) {
        int pos = lower_bound(temp.begin(), temp.end(), v[i]) - temp.begin() + 1;
        res += ft.query(pos - 1);
        ft.update(pos, 1);
    }
    return res;
}

void Solve() {
	cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        vector<int> current;
        ll sum = 0;
        int inv = 0;
        for (int j = i; j >= 1; --j) {
            current.insert(current.begin(), a[j]);
            inv += count_inversions(current);
            if (inv > k) break;
            sum = (sum + dp[j - 1]) % MOD;
        }
        dp[i] = sum;
    }

    cout << dp[n] << "\n";
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}