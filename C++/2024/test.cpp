#include <iostream>

using namespace std;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const long long mod = 1e9 + 7;

long long nhan_mod (long long x,long long y) {
    if (y == 1) return x % mod;
    if (y % 2 == 0) return nhan_mod(x * 2 % mod, y / 2) % mod;
    else return ((nhan_mod(x * 2 % mod, y / 2)) % mod + x) % mod;
}

void Solve () {
    long n, q, x, y;
    cin >> n >> q;
    while (q--) {
        cin >> x >> y;
        
        long long sum = 0, firstr, firstl;
        
        if ((x % mod) == (y % mod))	{
        	sum += (nhan_mod((1 + nhan_mod(n, n)), n) / 2);
        }
        else {
            if ((x % mod) > (y % mod)) {
            	long x1 = x % mod, y1 = y % mod;
            	if (y1 != 1) {
            		y1 = 1;
            		x1 = y1 + (x - y);
            	}
            	firstr = ((nhan_mod(n, x1) - nhan_mod((n - 1), y1)) % mod);
            	sum += (nhan_mod((n - (x1 - y1)), ((nhan_mod(firstr, 2)) + (n - (x1 - y1) - 1) * (n + 1))) / 2);
            }
            else {
                firstr = abs(x - y) + 1;
                sum += (nhan_mod((n - (abs(x - y))), ((nhan_mod(firstr, 2)) + (n - abs(x - y) - 1) * (n + 1))) / 2);
            }
        }
        
        if ((x % mod) + (y % mod) == (n % mod) + 1) {
        	sum += (nhan_mod(n, ((nhan_mod(n, 2)) + nhan_mod((n - 1), (n - 1)))) / 2);
        }
        else {
            if (((x % mod) + (y % mod) - 1) < (n % mod)) {
                firstl = x + y - 1;
                sum += ((x + y - 1) * ((nhan_mod(firstl, 2)) + nhan_mod((x + y - 2), (n - 1))) / 2);
            }
            else if (((x % mod) + (y % mod) - 1) > (n % mod)) {
            	long x2 = x % mod, y2 = y % mod;
            	if (y2 != n) {
            		y2 = n;
            		x2 = (x + y) - y2;
            	}
            	firstl = (nhan_mod(x2, y2));
                sum += (nhan_mod((abs(x2 - y2) + 1), ((nhan_mod(firstl, 2)) + nhan_mod(abs(x2 - y2), (n - 1)))) / 2);
            }
        }
    	
		sum -= (nhan_mod((x - 1), n) + y);
        
        cout << (long long) ((sum % mod + mod) % mod) << endl;
    }
}

int main() {
    faster
    
    Solve();
    
    return 0;
}
