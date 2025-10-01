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
        string s;
        cin >> n >> s;
        
        vector<int> a;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'a') a.push_back(i);
        }
        
        ll resa = 0;
        if (!a.empty()) {
            vector<int> v;
            for (size_t j = 0; j < a.size(); j++) v.push_back(a[j] - (int)j);
            
            sort(v.begin(), v.end());
            int med = v[v.size() / 2];
            
            for (int x : v) resa += abs(x - med);
        }
        
        vector<int> b;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'b') b.push_back(i);
        }
        
        ll resb = 0;
        if (!b.empty()) {
            vector<int> v;
            for (size_t j = 0; j < b.size(); j++) v.push_back(b[j] - (int)j);
            
            sort(v.begin(), v.end());
            int med = v[v.size() / 2];
            
            for (int x : v) resb += abs(x - med);
        }
        
        cout << min(resa, resb) << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}