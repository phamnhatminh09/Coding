#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(const string& s) {
    stack<char> st;
    
    for (char c : s) {
        if (c == '(') st.push(c);
        else if (c == ')') {
            if (st.empty() || st.top() != '(') return false;
            st.pop();
        }
    }
    
    return st.empty();
}


void Solve() {
	string s;
	cin >> s;
	
	if (check(s)) cout << "YES";
	else cout<< "NO";
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}