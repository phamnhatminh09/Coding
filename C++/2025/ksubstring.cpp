#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
int cnt[N];

void Solve() {
	int n;
    cin >> n;
    
    cout << 6 << " " << 10 << " " << 15 << " ";
    n -= 3;
    
    vector<int> arr;
    for (int i = 2; i <= 2000; i++) {
        int t1 = i * 6, t2 = i * 10, t3 = i * 15;
        if (t1 <= 1e4) arr.push_back(t1);
        if (t2 <= 1e4) arr.push_back(t2);
        if (t3 <= 1e4) arr.push_back(t3);
    }
    
    for(auto v : arr){
        if(cnt[v] == 0 && n > 0){ 
            cout << v << " ";
            cnt[v]++;
            n--;
        }
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}