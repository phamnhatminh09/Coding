#include <bits/stdc++.h>
using namespace std;

vector<int> transformFour(const vector<int>& a, int start) {
    vector<int> res = a;
    int a_val = res[start];
    int b_val = res[start + 1];
    int c_val = res[start + 2];
    int d_val = res[start + 3];
    res[start] = abs(a_val - b_val);
    res[start + 1] = abs(b_val - c_val);
    res[start + 2] = abs(c_val - d_val);
    res[start + 3] = abs(d_val - a_val);
    return res;
}

bool isAllZero(const vector<int>& a) {
    for (int num : a) {
        if (num != 0) return false;
    }
    return true;
}

struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        size_t seed = v.size();
        for (int num : v) {
            seed ^= num + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

int minTransformations(vector<int> a) {
    if (isAllZero(a)) return 0;

    queue<pair<vector<int>, int>> q;
    q.push({a, 0});
    unordered_set<vector<int>, VectorHash> visited;
    visited.insert(a);

    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        vector<int> currentVec = current.first;
        int steps = current.second;

        if (steps > 20) break; // Giới hạn số bước để tránh TLE

        for (int i = 0; i <= currentVec.size() - 4; ++i) {
            vector<int> nextVec = transformFour(currentVec, i);
            if (visited.find(nextVec) == visited.end()) {
                if (isAllZero(nextVec)) {
                    return steps + 1;
                }
                visited.insert(nextVec);
                q.push({nextVec, steps + 1});
            }
        }
    }

    return -1; // Trường hợp không thể biến đổi thành toàn số 0
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a;
    int num;
    while (cin >> num) {
        a.push_back(num);
    }

    cout << minTransformations(a) << endl;
    return 0;
}