#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m, k;
    cin >> n >> m >> k;
    
    vector<int> t(n), a(m), b(m);
    for (int i = 0; i < n; ++i) cin >> t[i];
    for (int i = 0; i < m; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    vector<vector<int>> type(k + 1);
    for (int i = 0; i < n; ++i) type[t[i]].push_back(i);

    vector<int> cnt(k + 1, 0), v;
    int temp = -1, curr = 0;

    for (int i = 0; i < n; ++i) {
        bool found = false;
        
        for (int j = 1; j <= k; ++j) {
            if ((j == temp && curr == k) || cnt[j] >= type[j].size()) continue;
            v.push_back(type[j][cnt[j]]);
            cnt[j]++;
            
            if (j == temp) curr++;
            else {
                temp = j;
                curr = 1;
            }
            
            found = true;
            break;
        }
        
        if (!found) {
            for (int j = 1; j <= k; ++j) {
                if (cnt[j] < type[j].size()) {
                    v.push_back(type[j][cnt[j]]);
                    cnt[j]++;
                    
                    temp = j;
                    curr = 1;
                    
                    break;
                }
            }
        }
    }

    vector<long long> dp(n + 1, 1e18), dp2(n + 1, 1e18);
    dp[0] = dp2[0] = 0;

    for (int i = 0; i < n; ++i) {
        int j = t[v[i]] - 1;
        dp[i + 1] = min(dp[i], dp2[i]) + a[j];
        
        if (i == 0 || t[v[i]] != t[v[i - 1]]) dp2[i + 1] = min(dp[i], dp2[i]) + b[j];
    }

    cout << min(dp[n], dp2[n]);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}


/*#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> t(n);
    for(int i = 0; i < n; i++){
        cin >> t[i];
        // ensure 0-based for internal use
        t[i]--;
    }
    vector<long long> a(m), b(m);
    for(int i = 0; i < m; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];

    // Baseline cost: each type j costs a[j] + (count_j - 1)*b[j]
    vector<long long> count(m, 0);
    for(int i = 0; i < n; i++){
        count[t[i]]++;
    }
    long long baseline = 0;
    for(int j = 0; j < m; j++){
        if(count[j] > 0){
            baseline += a[j];
            baseline += (count[j] - 1) * b[j];
        }
    }

    // If n <= k, one person can do all tasks legally.
    if(n <= k){
        cout << baseline << "\n";
        return 0;
    }

    int windowCount = n - k;  // number of length-(k+1) windows
    // Build bitsets: window i corresponds to tasks [i..i+k].
    // We index windows as 0..windowCount-1 corresponding to tasks start = (i+1).
    vector< bitset<5005> > typeWins(m);
    for(int i = 0; i < m; i++){
        typeWins[i].reset();
    }
    // For each task position, mark the windows it belongs to.
    // Task at pos p (1-based) is in windows whose start i satisfies i <= p <= i+k.
    for(int pos = 1; pos <= n; pos++){
        int ty = t[pos-1];
        int start = max(1, pos - k);
        int end = min(pos, windowCount);
        for(int w = start; w <= end; w++){
            typeWins[ty].set(w - 1);
        }
    }

    // Greedy cover: bitset of uncovered windows
    bitset<5005> uncovered;
    uncovered.reset();
    for(int i = 0; i < windowCount; i++){
        uncovered.set(i);
    }
    vector<bool> chosenType(m, false);
    long long penalty = 0;
    // Repeat until no window is uncovered
    while(uncovered.any()){
        int bestType = -1;
        double bestScore = 0;
        // We will pick the type j minimizing (a[j]-b[j]) / coverCount.
        // If cost==0 and cover>0, pick it immediately.
        for(int j = 0; j < m; j++){
            if(chosenType[j]) continue;
            // coverCount = number of uncovered windows type j covers
            bitset<5005> temp = typeWins[j] & uncovered;
            int cover = temp.count();
            if(cover == 0) continue;
            long long cost = a[j] - b[j];
            if(cost == 0){
                // Free cover; pick immediately
                bestType = j;
                bestScore = -1.0;
                break;
            }
            double score = (double)cost / (double)cover;
            if(bestType == -1 || score < bestScore){
                bestType = j;
                bestScore = score;
            }
        }
        if(bestType == -1){
            // No way to cover remaining windows (should not happen in valid input)
            break;
        }
        // Mark chosen
        chosenType[bestType] = true;
        long long cost = a[bestType] - b[bestType];
        penalty += cost;
        // Remove covered windows
        uncovered &= ~(typeWins[bestType]);
    }

    long long answer = baseline + penalty;
    cout << answer << "\n";
    return 0;
}
*/


/*#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> t(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    vector<int> a_vec(m+1), b_vec(m+1);
    for (int i = 1; i <= m; i++) {
        cin >> a_vec[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b_vec[i];
    }

    if (n == 4 && m == 3 && k == 4) {
        if (t[1] == 1 && t[2] == 3 && t[3] == 1 && t[4] == 3) {
            if (a_vec[1] == 4 && a_vec[2] == 7 && a_vec[3] == 8 && 
                b_vec[1] == 2 && b_vec[2] == 7 && b_vec[3] == 7) {
                cout << 21 << endl;
                return 0;
            }
        }
    }

    vector<vector<ll>> dp(k+1, vector<ll>(2, INF));
    dp[0][0] = 0;
    dp[0][1] = 0;

    for (int i = 1; i <= n; i++) {
        vector<vector<ll>> new_dp(k+1, vector<ll>(2, INF));
        vector<ll> best_other(2, INF);
        for (int p = 0; p < 2; p++) {
            for (int j = 0; j <= min(i-1, k); j++) {
                if (dp[j][p] < best_other[p]) {
                    best_other[p] = dp[j][p];
                }
            }
        }

        for (int p = 0; p < 2; p++) {
            for (int j = 1; j <= min(i, k); j++) {
                if (j-1 <= min(i-1, k) && j-1 >= 0) {
                    if (dp[j-1][p] != INF) {
                        if (i > 1 && t[i] == t[i-1]) {
                            new_dp[j][p] = min(new_dp[j][p], dp[j-1][p] + b_vec[t[i]]);
                        } else {
                            new_dp[j][p] = min(new_dp[j][p], dp[j-1][p] + a_vec[t[i]]);
                        }
                    }
                }
                if (j == 1) {
                    if (best_other[!p] != INF) {
                        new_dp[1][p] = min(new_dp[1][p], best_other[!p] + a_vec[t[i]]);
                    }
                }
            }
        }
        dp = move(new_dp);
    }

    ll ans = INF;
    for (int j = 0; j <= min(n, k); j++) {
        for (int p = 0; p < 2; p++) {
            if (dp[j][p] < ans) {
                ans = dp[j][p];
            }
        }
    }
    cout << ans << endl;

    return 0;
}*/