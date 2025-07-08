#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
    string n;
    long long k;
    cin >> n >> k;

    int sum = 0;
    for (char c : n) sum += c - '0';

    long long res = sum * (k + 1);
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}