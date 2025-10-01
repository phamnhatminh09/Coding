#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

char dfind(ll k) {
    ll len = 1, cnt = 5, sum = 5;

    while (k > sum) {
        len++;
        cnt *= 5;
        sum += cnt * len;
    }

    k -= (sum - cnt * len);
    ll x = (k - 1) / len, temp = (k - 1) % len;

    ll n = 0;
    for (ll i = 0; i < len; ++i) {
        for (ll j : {1, 3, 5, 7, 9}) {
            ll st = pow(5, len - i - 1);	
            if (x >= st) x -= st;
            else {
                n = n * 10 + j;
                break;
            }
        }
    }

    string s = to_string(n);
    return s[temp];
}

void Solve() {
	ll k;
    cin >> k;
    cout << dfind(k) << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}