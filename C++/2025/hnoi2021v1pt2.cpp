#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

string findmulti30(string n) {
    sort(n.rbegin(), n.rend());
    if (n.find('0') == string::npos) return "-1"; 
    int sum = 0;
    for (char c : n) sum += c - '0';
    if (sum % 3 != 0) return "-1";
    return n;
}


void Solve() {
	string n;
	cin >> n;
	cout << findmulti30(n);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}