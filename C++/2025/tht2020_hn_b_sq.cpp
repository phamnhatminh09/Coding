#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll cal(ll a, ll b, ll N) {
    ll r = a % b;
    if (r == 0) return 0;

    unordered_map<ll, int> check;
    vector<int> d;
    vector<ll> rem;
    int start = -1, len = 0;

    for (int i = 0; i < N; ++i) {
        if (check.count(r)) {
            start = check[r];
            len = i - start;
            break;
        }
        check[r] = i;
        r *= 10;
        int dig = r / b;
        d.push_back(dig);
        rem.push_back(r % b);
        r %= b;
    }

    if (start == -1) {
        ll sum = 0;
        for (int d : d) sum += d;
        return sum;
    }
    else {
        ll sum = 0, total;
        for (int i = 0; i < start; ++i) sum += d[i];
        for (int i = start; i < start + len; ++i) total += d[i];

        ll rd = N - start, full = rd / len;
        sum += full * total;
        int remain = rd % len;
        for (int i = 0; i < remain; ++i) sum += d[start + i];

        return sum;
    }
}

void Solve() {
    long long a, b, N;
    cin >> a >> b >> N;

    cout << cal(a, b, N);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}