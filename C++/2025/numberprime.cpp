#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    
    return true;
}

void gen(const string& s, unordered_set<int>& uset, string curr, vector<bool>& v) {
    if (!curr.empty()) {
        int num = stoi(curr);
        if (check(num)) uset.insert(num);
    }

    for (int i = 0; i < s.size(); ++i) {
        if (!v[i]) {
            v[i] = true;
            gen(s, uset, curr + s[i], v);
            v[i] = false;
        }
    }
}

int cnt(const string& s) {
    unordered_set<int> uset;
    vector<bool> v(s.size(), false);
    gen(s, uset, "", v);
    return uset.size();
}

void Solve() {
	int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        cout << cnt(s) << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}