#include <iostream>
#include <algorithm>

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
//const ll N = 1e6 + 5;

using namespace std;

long no(long n) {
	string ns = to_string(n);
	return ns.size();
}

long first(long n) {
	string ns = to_string(n);
	reverse(ns.begin(), ns.end());
	n = stol(ns);
	return n % 10;
}

long sum (long n) {
	if (n / 10 == 0) return (N - 1) / 2;
	else if (int i = 2; i < no(n); ++i) return (4 * 5 * pow(10, no(n) - 2));
}

int main() {
    long N;
    cin >> N;
    
    long cnt;
    
    
    cout << cnt << endl;
    
    return 0;
}
