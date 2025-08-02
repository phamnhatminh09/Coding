#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("MACHDNA.INP", "r", stdin);
#define write freopen("MACHDNA.OUT", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	string s;
	cin >> s;
	
	string dna;
	int i = 0;
	
	while (i < s.size()) {
		int cnt = 0;
		
		while (i < s.size() && isdigit(s[i])) {
			cnt = cnt * 10 + (s[i] - '0');
			i++;
		}
		
		if (i < s.size()) {
			char c = s[i];
			dna.append(cnt, s[i]);
			i++;
		}
	}
	
	string temp;
	for (char c : dna) {
		if (c == 'A') temp += 'T';
		else if (c == 'T') temp += 'A';
		else if (c == 'C') temp += 'G';
		else if (c == 'G') temp += 'C';
	}
	
	cout << temp;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}