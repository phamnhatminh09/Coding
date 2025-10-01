#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const int N = 2e6 + 5;
const int oo = 1e9;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n; // Số đỉnh của đồ thị
int D[N], vis[N];
vector<pair<int, int>> g[N];  // first là đầu mút của cạnh, second là trọng số của cạnh
deque<int> dq;

void BFS_01(int s){
    for(int i = 1; i <= n; i++){
        D[i] = oo;              // Khởi tạo
        vis[i] = 0;
    }
    D[s] = 0;
    dq.push_front(s);
    while(!dq.empty()){
        int u = dq.front();
        dq.pop_front();
        if(vis[u])continue;
        vis[u] = 1;             // Đánh dấu
        for(auto v: g[u]){
            if(D[v.first] > D[u] + v.second){              //
                D[v.first] = D[u] + v.second;              // Duyệt và sử lý các cạnh của u
                if(v.second == 1)dq.push_back(v.first);    //
                else dq.push_front(v.first);
            }
        }
    }
}
void Solve() {
	
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}