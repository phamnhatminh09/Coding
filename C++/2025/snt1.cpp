#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(int x) {
    if (x <= 1) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(x); i += 2) {
        if (x % i == 0) return false;
    }
    
    return true;
}

int pr(int x) {
    if (x <= 2) return 2;
    int temp = x;
    
    if (temp % 2 == 0) temp++;
    while (!check(temp)) temp += 2;
    
    return temp;
}

void Solve() {
	int n, x;
    cin >> n >> x;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    int cnt = 0;
    vector<int> v;
    
    for (int i = 0; i < n; ++i) {
        if (check(a[i])) cnt++;
        else {
            int x = pr(a[i]);
            v.push_back(x - a[i]);
        }
    }

    sort(v.begin(), v.end());

    for (int i : v) {
        if (x >= i) {
            x -= i;
            cnt++;
        }
        else break;
    }

    cout << cnt;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}