#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void Solve() {
	int n, k;
	cin >> n >> k;
	
	vector<int> v(n);
	for (int i = 0; i < n; ++i) v[i] = i + 1;
	
	for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            cout << "? " << v[j] << " " << v[j + 1] << endl;
            cout.flush();
            
            string s;
            cin >> s;
            
            if (s == to_string(v[j + 1])) swap(v[j], v[j + 1]);
        }
    }
	
	cout << "! 1 1\n";
	sort(v.begin(), v.begin() + k);
	for (int i = 0; i < k; ++i) cout << v[i] << ' ';
	cout << '\n';
	cout.flush();
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}