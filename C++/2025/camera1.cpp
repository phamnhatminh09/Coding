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
    vector<int> x(n);
    for (int i = 0; i < n; ++i) cin >> x[i];
    
    sort(x.begin(), x.end());

    vector<int> optimal;

    if (n % 2 == 1) optimal.push_back(x[n / 2]);
    else {
        int lmed = x[n / 2 - 1], rmed = x[n / 2];
        for (int pos = lmed; pos <= rmed; ++pos) {
            optimal.push_back(pos);
        }
    }
    
    cout << optimal.size() << "\n";
    for (int pos : optimal) cout << pos << " ";
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}