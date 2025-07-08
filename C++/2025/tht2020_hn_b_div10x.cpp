#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const int N = 1e9;

int check(long long x, int f) {
    int cnt = 0;
    while (x % f == 0) {
        x /= f;
        cnt++;
    }
    return cnt;
}

void Solve() {
	int n, x;
    cin >> n >> x;

    vector<pair<int, int>> fact(n);
    for (int i = 0; i < n; ++i) {
        long long a;
        cin >> a;
        int c2 = check(a, 2);
        int c5 = check(a, 5);
        fact[i] = {c2, c5};
    }
    
    vector<vector<int>> dp(1005, vector<int>(1005, N));
    dp[0][0] = 0;

    for (auto [c2, c5] : fact) {
        vector<vector<int>> temp = dp;
        
        for (int i = 0; i < 1005; ++i) {
            for (int j = 0; j < 1005; ++j) {
                if (dp[i][j] < N) {
                    int ni = min(1004, i + c2);
                    int nj = min(1004, j + c5);
                    temp[ni][nj] = min(temp[ni][nj], dp[i][j] + 1);
                }
            }
        }

        dp = temp;
    }

    int res = N;
    for (int i = x; i < 1005; ++i) {
        for (int j = x; j < 1005; ++j) res = min(res, dp[i][j]);
    }

    if (res == N) cout << -1;
    else cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

pair<int, int> countFactors(long long num) {
    int count2 = 0, count5 = 0;
    while (num % 2 == 0) {
        count2++;
        num /= 2;
    }
    while (num % 5 == 0) {
        count5++;
        num /= 5;
    }
    return {count2, count5};
}

int main() {
    int N, X;
    cin >> N >> X;
    vector<long long> a(N);
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    // Initialize DP table: dp[i][j] = minimal number of elements to get at least i 2s and j 5s
    vector<vector<int>> dp(X + 1, vector<int>(X + 1, INT_MAX));
    dp[0][0] = 0;

    for (int k = 0; k < N; ++k) {
        auto [cnt2, cnt5] = countFactors(a[k]);
        // We need to update the DP table in reverse to avoid overwriting
        for (int i = X; i >= 0; --i) {
            for (int j = X; j >= 0; --j) {
                if (dp[i][j] != INT_MAX) {
                    int new_i = min(i + cnt2, X);
                    int new_j = min(j + cnt5, X);
                    if (dp[new_i][new_j] > dp[i][j] + 1) {
                        dp[new_i][new_j] = dp[i][j] + 1;
                    }
                }
            }
        }
    }

    if (dp[X][X] == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << dp[X][X] << endl;
    }

    return 0;
}
*/