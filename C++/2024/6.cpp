#include <iostream>

using namespace std;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

void Solve() {
    const long long mod = 1e9 + 7;
    long n, q, x, y;
    cin >> n >> q;
    while (q--) {
        cin >> x >> y;
        
        long long sum = 0, firstr, firstl;
        
        if ((x % mod) == (y % mod)) sum += (((1 + (n % mod) * (n % mod)) * (n % mod) / 2) % mod);
        else {
            if ((x % mod) > (y % mod)) {
            	long x1 = x % mod, y1 = y % mod;
            	while (y1 != 1) {
            		y1--;
            		x1--;
            	}
            	firstr = ((((n % mod) * (x1 % mod)) - (((n % mod) - 1) * y1)) % mod);
                sum += ((((n % mod) - ((x1 % mod) - (y1 % mod))) * (((firstr % mod) * 2) + ((n % mod) - ((x1 % mod) - (y1 % mod)) - 1) * (n + 1)) / 2) % mod);
            }
            else {
                firstr = ((abs((x % mod) - (y % mod)) + 1) % mod);
                sum += ((((n % mod) - (abs((x % mod) - (y % mod)))) * (((firstr % mod) * 2) + ((n % mod) - abs((x % mod) - (y % mod)) - 1) * ((n % mod) + 1)) / 2) % mod);
            }
        }
        
        if ((x % mod) + (y % mod) == (n % mod) + 1) sum += (((n % mod) * (((n % mod) * 2) + ((n % mod) - 1) * ((n % mod) - 1)) / 2) % mod);
        else {
            if (((x % mod) + (y % mod) - 1) < (n % mod)) {
                firstl = (((x % mod) + (y % mod) - 1) % mod);
                sum += ((((x % mod) + (y % mod) - 1) * (((firstl % mod) * 2) + ((x % mod) + (y % mod) - 2) * ((n % mod) - 1)) / 2) % mod);
            }
            else if (((x % mod) + (y % mod) - 1) > (n % mod)) {
            	long x2 = x % mod, y2 = y % mod;
            	while (y2 != n) {
            		y2++;
            		x2--;
            	}
            	firstl = (((x2 % mod) * (y2 % mod)) % mod);
                sum += (((abs((x2 % mod) - (y2 % mod)) + 1) * (((firstl % mod) * 2) + abs((x2 % mod) - (y2 % mod)) * ((n % mod) - 1)) / 2) % mod);
            }
        }
    	
		sum -= (((((x % mod) - 1) * (n % mod)) + (y % mod)) % mod);
        
        cout << (long long) (sum % mod) << endl;
    }
}

int main() {
    faster
    
    Solve();
    
    return 0;
}
