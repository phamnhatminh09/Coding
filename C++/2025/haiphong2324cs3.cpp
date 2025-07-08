#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int check(int a[], int n, int s) {
    int l = 0, sum = 0, len = n + 1;

    for (int r = 0; r < n; r++) {
        sum += a[r];

        while (sum >= s) {
            len = min(len, r - l + 1);
            sum -= a[l];
            l++;
        }
    }
    
    return (len == n + 1) ? -1 : len;
}

void Solve() {
    int n, s;
    cin >> n >> s;
    int a[n];

    for (int i = 0; i < n; i++) cin >> a[i];

    cout << check(a, n, s) << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}