#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<int>> memo; // Memoization vector
int count;

int hanoi(int n, int k, string from, string temp, string to) {
    if (n == 0) {
        return 0;

    }

    if (memo[n][k] != -1) {
        return memo[n][k];

    }

    int moves = 0;
    moves += hanoi(n - 1, k, from, to, temp);
    cout << "Move disc " << (n + k) << " from " << from << " to " << to << "\n";
    count++;
    moves++;
    moves += hanoi(n - 1, k, temp, from, to);
    memo[n][k] = moves; // Store result in memoization vector
    return moves;

}

void rev(int n, string from, string temp, string to, string temp2) {
    int k = (int)(n + 1 - round(sqrt(2 * n + 1)));
    if (k == 0) {
        cout << "Move disc " << 1 << " from " << from << " to " << to << "\n";
        count++;
        return;
    }
    rev(k, from, to, temp, temp2);
    hanoi(n - k, k, from, temp2, to);
    rev(k, temp, from, to, temp2);

}

int main() {
    int n = 8;
    // Initialize memoization vector with -1 values
    memo.assign(n + 1, vector<int>(n + 1, -1));
    rev(n, "A", "B", "D", "C");
    cout<<count;

}
