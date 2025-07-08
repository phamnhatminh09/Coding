#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
    long long n, x, y, m;
    cin >> n >> x >> y >> m;
    
    vector<long long> A;
    unordered_map<long long, int> seen;
    int cyc_st = -1, cyc_len = 0;

    long long curr = x;
    for (int i = 0; i < n; ++i) {
        if (seen.find(curr) != seen.end()) {
            cyc_st = seen[curr];
            cyc_len = i - cyc_st;
            break;
        }
        
        seen[curr] = i;
        A.push_back(curr);
        curr = (curr + y) % m;
    }
    
    long long res = 0;
    if (cyc_st != -1) {
        for (int i = 0; i < cyc_st; ++i) res = (res + A[i] * (i + 1)) % m;
        
        long long cycle_sum = 0;
        for (int i = cyc_st; i < cyc_st + cyc_len; ++i) cycle_sum = (cycle_sum + A[i] * (i + 1)) % m;
        
        long long cycles = (n - cyc_st) / cyc_len;
        res = (res + cycle_sum * cycles) % m;
        
        long long rem = (n - cyc_st) % cyc_len;
        for (int i = 0; i < rem; ++i) {
            int idx = cyc_st + i;
            res = (res + A[idx] * (cyc_st + i + 1)) % m;
        }
    }
    else {
        for (int i = 0; i < n; ++i) res = (res + A[i] * (i + 1)) % m;
    }
    
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}