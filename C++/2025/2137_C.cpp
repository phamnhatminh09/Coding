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
	int t;
	cin >> t;
	
	while (t--) {
		int a, b;
		cin >> a >> b;
		
		if (a % 2 == 0 && b % 2 == 0) {
			cout << a * (b / 2) + 2 << '\n';
			continue;
		}
		else if (a % 2 == 0 && b % 2 != 0) {
			cout << -1 << '\n';
			continue;
		}
		else if (a % 2 != 0 && b % 2 != 0) {
			cout << a * b + 1 << '\n';
			continue;
		}
		else {
			if (b % 4 == 2) {
				cout << - 1 << '\n';
				continue;
			}
			else {
				cout << a * (b / 2) + 2 << '\n';
				continue;
			}
		}
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}


/*
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
	int t;
	cin >> t;
	
	while (t--) {
	    ll a, b;
	    cin >> a >> b;
	    
	    if (b % 2 != 0) {
	        if (a % 2 == 0) cout << "-1\n";
	        else cout << a * b + 1 << '\n';
	    }
	    else {
	        if (a % 2 == 0) cout << max(a + b, a * (b / 2) + 2) << '\n';
	        else {
	            ll x = a * 2 + b / 2, y = a * (b / 2) + 2;
	            
	            if (x % 2 == 0 && y % 2 == 0) cout << max(x, y) << '\n';
	            else if (x % 2 == 0) cout << x << '\n';
	            else if (y % 2 == 0) cout << y << '\n';
	            else cout << "-1\n";
	        }
	    }
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}
*/