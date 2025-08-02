#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("smod.inp", "r", stdin);
#define write freopen("smod.out", "w", stdout);
const ll N = 1e5 + 5;

void find(int x, int y, int m, ll n, vector<int>& seq, int& a, int& b) {
    unordered_map<int, int> mp;
    seq.clear();
    
    int curr = x;
    for (int i = 0; i < n; ++i) {
        if (mp.count(curr)) {
            a = mp[curr];
            b = i - a;
            return;
        }
        
        mp[curr] = i;
        seq.push_back(curr);
        curr = (curr * x + y) % m;
    }
    
    a = -1;
    b = 0;
}

void Solve() {
	ll n;
    int x, y, m;
    cin >> n >> x >> y >> m;
    
    vector<int> seq;
    int a, b;
    find(x, y, m, n, seq, a, b);
    
    unordered_map<int, ll> freq;
    if (a == -1) for (int num : seq) freq[num]++;
    else {
        for (int i = 0; i < a; ++i) freq[seq[i]]++;
        
        ll cnt = (n - a) / b, rem = (n - a) % b;
        for (int i = a; i < a + b; ++i) {
            freq[seq[i]] += cnt;
            
            if (i < a + rem) freq[seq[i]]++;
        }
    }

    vector<pair<int, ll>> v(freq.begin(), freq.end());
    sort(v.begin(), v.end());

    ll res = 0, index = 1;
    for (const auto& t : v) {
        ll cnt = t.second, val = t.first;
        res = (res + (val * ((index + index + cnt - 1) * cnt / 2 % m)) % m) % m;
        index += cnt;
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