#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int evaluate(const string &expr) {
    if (all_of(expr.begin(), expr.end(), ::isdigit)) return stoi(expr);
    
    size_t ob = expr.find('(');
    string func = expr.substr(0, ob);
    
    string temp = expr.substr(ob + 1, expr.size() - ob - 2);
    size_t comma = 0;
    int x = 0;
    for (size_t i = 0; i < temp.size(); ++i) {
        if (temp[i] == '(') x++;
        else if (temp[i] == ')') x--;
        else if (temp[i] == ',' && x == 0) {
            comma = i;
            break;
        }
    }
    string A_str = temp.substr(0, comma);
    string B_str = temp.substr(comma + 1);
    
    int A = evaluate(A_str), B = evaluate(B_str);
    
    if (func == "SUM") return A + B;
    if (func == "DIF") return A - B;
    if (func == "MAX") return max(A, B);
    if (func == "MIN") return min(A, B);
    if (func == "GCD") return gcd(abs(A), abs(B));
    
    return 0;
}

void Solve() {
	string expr;
    getline(cin, expr);

    cout << evaluate(expr) << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}