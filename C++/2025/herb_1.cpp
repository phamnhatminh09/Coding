#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<int> spf;

void sieve() {
    spf.resize(N);
    for (int i = 2; i < N; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            for (int j = i * 2; j < N; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
}

vector<int> get(int x) {
    vector<int> pr;
   
    if (x == 1) return pr;
    while (x != 1) {
        int p = spf[x];
        pr.push_back(p);
        
        while (x % p == 0) x /= p;
    }
    
    return pr;
}

void Solve() {
	sieve();

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        int res = 0;
        unordered_set<int> uset;
        int left = l;

        while (left <= r) {
            vector<int> pr = get(a[left]);
            bool check = false;
            for (int p : pr) {
                if (uset.count(p)) {
                    check = true;
                    break;
                }
            }
            
            if (check) {
                res++;
                uset.clear();
            }
            
            for (int p : pr) uset.insert(p);
            left++;
        }
        res++;
        cout << res << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}