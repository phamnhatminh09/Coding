#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool div3(const string &s) {
    int sum = 0, pos = 1;
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] == '1') {
            if (pos % 2 == 1) sum += 1;
            else sum -= 1;
        }
        
        pos++;
    }
    
    return sum % 3 == 0;
}

string largbin(int cnt0, int cnt1) {
    string res;
    
    while (cnt1 > 0 || cnt0 > 0) {
        if (cnt1 > 0) {
            res += '1';
            cnt1--;
            if (cnt0 > 0) {
                res += '0';
                cnt0--;
            }
        }
        else {
            res += '0';
            cnt0--;
        }
    }
    
    return res;
}

string Solve(const string &bits) {
    int cnt0 = 0, cnt1 = 0;
    for (char bit : bits) {
        if (bit == '0') cnt0++;
        else cnt1++;
    }

    if (cnt1 > cnt0 + 1) return "NO";

    string maxx = largbin(cnt0, cnt1);
    if (div3(maxx)) return maxx;
    
    return "NO";
}

int main() {
	//read
	//write
    faster
    
    string s;
    while (getline(cin, s)) {
        string res = Solve(s);
        cout << res << '\n';
    }
    
    return 0;
}