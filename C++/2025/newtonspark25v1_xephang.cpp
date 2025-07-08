#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int a, b;
    cin >> a >> b;

    int len;
    if (a > b) len = 2 * b + 1;
    else if (b > a) len = 2 * a + 1;
    else len = a + b;

    cout << len;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}