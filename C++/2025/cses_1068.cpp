#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef unsigned long long ull;
typedef unsigned short us;
typedef unsigned int ui;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
#define FOR(i, l, r) for (int i = l; i <= r; i++)
#define FOD(i, r, l) for (int i = r; i >= l; i--)
#define FORSM(i, l, r) for (int i = l; i < r; i++)
#define FODSM(i, r, l) for (int i = r; i > l; i--)
#define FORAM(i, l, r, amount) for (int i = l; i <= r; i += amount)
#define FODAM(i, r, l, amount) for (int i = r; i >= l; i -= amount)
const ll N = 1e5 + 5;

int n;

void ReadData() {
    
}

void Solve() {
    long n;
    cin >> n;
    cout << n << " ";
    while (n != 1) {
        if (n % 2 != 0) {
        	n = n * 3 + 1;
        	cout << n << " ";
        }
        else {
        	n = n / 2;
        	cout << n << " ";
        }
    }
}

int main() {
    faster
    
    ReadData();
    Solve();
    
    return 0;
}
