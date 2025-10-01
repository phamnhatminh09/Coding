#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("BIENSO.INP", "r", stdin);
#define write freopen("BIENSO.OUT", "w", stdout);
const ll N = 10000000LL;

void Solve() {
	string s;
	ll K;
	cin >> s >> K;

    int a = (s[0] - '0') * 10 + (s[1] - '0'), c = s[2] - 'A';
    ll b = stoll(s.substr(3));
    ll pos = a * 26LL * N + c * N + b;
    pos += K;

    ll b2 = pos % N;
    pos /= N;
    int c2 = pos % 26;
    pos /= 26;
    int a2 = pos;

    cout << setw(2) << setfill('0') << a2;
    cout << char('A' + c2);
    cout << setw(7) << setfill('0') << b2;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}