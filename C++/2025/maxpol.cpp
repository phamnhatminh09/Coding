#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

char arr[N];
string s[N];

bool cmp(string x, string y){
    while (x.size() < y.size()) x= "0" + x;
    while (x.size() > y.size()) y= "0" + y;
    return x >= y;
}

void Solve() {
	int n;
    cin>>n;
    
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = n + 1; i <= 2 * n; i++) arr[i] = arr[i - n];
    
    for (int i = 1; i <= 2 * n; i++) {
        s[i] = "";
        if (i <= n) {
            for (int j = 0; j < n; j++) s[i] += arr[i + j];
        }
        else{
            for (int j = 0; j < n; j++) s[i] += arr[i - j];
        }
    }
    
    sort (s + 1, s + 2 * n + 1, cmp);
    cout << s[1];
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}