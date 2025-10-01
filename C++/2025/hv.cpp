#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const int mod = 1e9 + 7;
const ll inv2 = 500000004;
const ll inv6 = 166666668;
// tao thich bu cac cho huhu
void Solve() {
	ll n, m;
	cin >> n >> m;
	
	ll l = min(n, m), cnt1 = (n + 1) % mod;
	cnt1 = cnt1 * ((m + 1) % mod) % mod;
	cnt1 = cnt1 * (l % mod) % mod;
	
	ll a = l % mod, b = (l + 1) % mod, sum1 = a * b % mod;
	sum1 = sum1 * inv2 % mod;
	ll cnt2 = (n % mod + m % mod + 2) % mod;
	cnt2 = cnt2 * sum1 % mod;
	
	ll c = (l * 2 + 1) % mod, sum2 = a * b % mod;
	sum2 = sum2 * c % mod;
	sum2 = sum2 * inv6 % mod;
	
	ll res = (cnt1 - cnt2 + sum2) % mod;
	if (res < 0) res += mod;
	res %= mod;
	
	cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}