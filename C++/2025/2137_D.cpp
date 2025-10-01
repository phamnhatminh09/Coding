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
		int n;
	    bool check = 1;
	    cin >> n;
	    
	    vector<int> b(n);
	    for (int i = 0; i < n; i++) cin >> b[i];
	    
	    vector<int> freq(n+1, 0);
	    for (int i = 0; i < n; i++) if (b[i] <= n) freq[b[i]]++;
	    
	    for (int i = 1; i <= n; i++) if (freq[i] % i != 0) check = 0;
	    
	    vector<vector<int>> v(n + 1);
	    for (int i = 0; i < n; i++) v[b[i]].push_back(i);
	    
	    int next_id = 1;
	    vector<int> a(n);
	    
	    for (int i = 1; i <= n; i++) {
	        if (v[i].empty()) continue;
	        
	        int x = v[i].size() / i;
	        
	        for (int g = 0; g < x; g++) {
	            int id = next_id++;
	            
	            for (int j = 0; j < i; j++) a[v[i][g * i + j]] = id;
	        }
	    }
	    
	    
	    if (!check) cout << - 1 << '\n';
	    else {
	    	for (int i = 0; i < n; i++) cout << a[i] << " ";
		    cout << '\n';
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