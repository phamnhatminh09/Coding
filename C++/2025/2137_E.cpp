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

int cal(int n, const vector<int>& counts) {
    for (int i = 0; i <= n; ++i) {
        if (counts[i] == 0) return i;
    }
    
    return n + 1; 
}

string cnt(const vector<int>& counts) {
    string s = "";
    
    for (size_t i = 0; i < counts.size(); ++i) {
        s += to_string(counts[i]);
        if (i < counts.size() - 1) s += ",";
    }
    
    return s;
}

void Solve() {
	int t;
    cin >> t;
    while (t--) {
        int n;
        ll k;
        cin >> n >> k;
        
        vector<int> a(n), v(n + 1, 0); 
        ll sum = 0;
        
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            v[a[i]]++;
            sum += a[i];
        }

        map<string, ll> m; 
        vector<vector<int>> state; 
        vector<ll> b;       

        state.push_back(v);
        b.push_back(sum);
        m[cnt(v)] = 0;

        ll x = 0, lim = k, y = (n < 2000) ? (2LL * n + 5) : 5000LL; 
        lim = min(k, y); 

        while (x < lim) {
            vector<int> c(n), temp(n + 1, 0);
            
            for(int val : a) {
                if (val >= 0 && val <= n) temp[val]++;
            }

            for (int i = 0; i < n; ++i) {
                int current_val_at_i = a[i];
                
                temp[current_val_at_i]--; 
                
                int mex_val = cal(n, temp);
                c[i] = mex_val;
                
                temp[current_val_at_i]++; 
            }

            a = c;
            
            sum = 0;
            fill(v.begin(), v.end(), 0);
            for (int i = 0; i < n; ++i) {
                sum += a[i];
                v[a[i]]++;
            }
            
            x++;

            string s = cnt(v);
            if (m.count(s)) {
                ll pre = m[s], len = x - pre, rem = k - x, step = rem % len;
                
                sum = b[pre + step];
                
                break;
            }
            
            m[s] = x;
            state.push_back(v);
            b.push_back(sum);
        }
        
        cout << sum << "\n";
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}

/*#include <bits/stdc++.h>

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

vector<int> cal(const vector<int>& a) {
    int n = a.size();
    vector<int> cnt(n + 3, 0);
    
    for (int v : a) ++cnt[v];
    
    int mex = 0;
    while (cnt[mex]) ++mex;
    
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        int v = a[i];
        b[i] = (v < mex && cnt[v] == 1) ? v : mex;
    }
    
    return b;
}

ll sum(const vector<int>& v) {
    ll s = 0;
    for (int x : v) s += x;
    return s;
}

void Solve() {
	int t;
	cin >> t;
	
    while (t--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<int> a(n);
        for (int &x : a) cin >> x;

        if (k == 0) {
            cout << sum(a) << '\n';
            continue;
        }

        vector<int> b = cal(a);
        ll sb = sum(b);
        if (k == 1) {
            cout << sb << '\n';
            continue;
        }

        vector<int> c = cal(b);
        ll sc = sum(c);
        cout << ((k & 1) ? sb : sc) << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}*/