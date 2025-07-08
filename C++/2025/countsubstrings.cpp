#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e6 + 5;
const int base = 31;
const ll MOD = 1000000003;

ll pw[N], hashT[N];

ll getHashT(int i,int j) {
    return (hashT[j] - hashT[i - 1] * pw[j - i + 1] + MOD * MOD) % MOD;
}

void Solve() {
	string S, T;
    cin >> S >> T;
    
    int lenT = S.size(), lenP = T.size();
    S = " " + S;
    T = " " + T;
    pw[0] = 1;
    
    for (int i = 1; i <= lenT; i++) pw[i] = (pw[i - 1] * base) % MOD;
     
    for (int i = 1; i <= lenT; i++) hashT[i] = (hashT[i - 1] * base + S[i] - 'a' + 1) % MOD;
    
    ll hashP = 0;
    for (int i = 1; i <= lenP; i++) hashP = (hashP * base + T[i] - 'a' + 1) % MOD;
    
    int cnt = 0;
    for (int i = 1; i <= lenT - lenP + 1; i++) {
    	if (hashP == getHashT(i, i + lenP - 1)) cnt++;
    }
        
    cout << cnt;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}