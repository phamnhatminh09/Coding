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
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.size() >= 2) {
            int x = st.top();
            st.pop();
            int y = st.top();
            
            if (x < y && x < a[i]) continue;
            else {
                st.push(x);
                break;
            }
        }
        st.push(a[i]);
    }
    
    cout << st.size();
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}