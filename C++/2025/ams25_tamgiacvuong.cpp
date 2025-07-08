#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e7 + 11;

long long isp[N];
map<int, int> m;
vector<int> prime;

void sieve(int n){
    for (int i = 2; i <= n; i++) isp[i] = true;
    
    isp[0] = false; isp[1] = false;
    
    for (int i = 2; i <= n; i++) {
        if (isp[i]) {
            for (int j = i * 2; j <= n; j += i) isp[j] = false;
        }
    }
    for(int i = 2; i <= n; i++) {
        if(isp[i]) prime.push_back(i);
    }
}

void Solve() {
	int n;
    cin >> n;
    if(n <= 3e7){
        int cnt = 0;
        n *= n;
        for(int i = 1; i <= (int)(sqrt(n)); ++i){
            if(n % i == 0){
                int rem = n / i;
                if((i + rem) % 2 == 0 && i != rem) cnt++;
            }
        }
        cout << cnt;
        return;
    }
    else{
        if(n % 2 == 0) n /= 2;
        for(auto v : prime) {
            while(n % v == 0) {
                m[v]++;
                n/=v;
            }
        }
        if(n > 1) m[n]++;
        
        int ans = 1;
        
        for(auto v : m){
            ans *= (v.second * 2 + 1);
        }
        cout << ans / 2;
        return;
    }
}

int main() {
	//read
	//write
    faster
    
    sieve(1e7);
    Solve();
    
    return 0;
}