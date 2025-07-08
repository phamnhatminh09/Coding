#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int cntnum(string st) {
    set<int> num;
    string s = "";
    
    for (char c : st) {
        if (isdigit(c)) s += c;
        else {
            if (!s.empty()) {
                num.insert(stoi(s));
                s = "";
            }
        }
    }
    if (!s.empty()) num.insert(stoi(s));

    return num.size();
}

void Solve() {
	string s;
	cin >> s;
	cout << cntnum(s);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}