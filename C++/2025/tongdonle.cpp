#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	
    int n;
    cin >> n;

    vector<int> A(n);
    map<int, int> m;
    
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
        m[A[i]]++;
    }

    ll sum = 0;
    
    for (int i = 0; i < n; ++i) {
        if (m[A[i]] == 1) sum += A[i];
    }

    cout << sum;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}