#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("dienpheptinh.inp", "r", stdin);
#define write freopen("dienpheptinh.out", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
    ll a, b;
    cin >> a >> b;

    char ops[] = {'+', '-', '*'};
    
    if (a * a - a == b) cout << '*' << endl << '-';
    if (a * a + a == b) cout << '*' << endl << '+';
    
}

int main() {
    //read
    //write
    faster
    
    Solve();
    
    return 0;
}