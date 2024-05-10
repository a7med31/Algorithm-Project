#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For seeding srand()
using namespace std;

struct State
{
    bool found;
    int shots;
};

struct Shot
{
    int shooter_pos;
    int target_pos;
};

int hit_target(int n, int shooter_pos, int target_pos, vector<vector<State>> &dp, vector<vector<Shot>> &path)
{
    // Check if the shooter's position is within the valid range
    if (shooter_pos < 0 || shooter_pos >= n)
    {
        return INT_MAX; // Out of bounds, return worst-case scenario (infinite shots)
    }

    // Base case: If shooter reaches target
    if (shooter_pos == target_pos)
    {
        dp[shooter_pos][target_pos].shots = 1;
        dp[shooter_pos][target_pos].found = true;
        return 1;
    }

    // Base case: If n=2, 2 shots at the same spot will guarantee hitting the target
    if (n == 2)
    {
        dp[0][0].shots = 2;
        dp[0][0].found = true;
        return 2;
    }

    // Check memoization table before recursion
    if (dp[shooter_pos][target_pos].shots != INT_MAX)
    {
        return dp[shooter_pos][target_pos].shots;
    }

    // Simulate the target's movement randomly
    int new_target_pos = target_pos;
    if (rand() % 2 == 0)
    { // 50% chance of moving forward
        new_target_pos = min(n - 1, target_pos + 1);
    }
    else
    { // 50% chance of moving backward
        new_target_pos = max(0, target_pos - 1);
    }

    // Simulate the shooter's movement
    int new_shooter_pos;
    if (shooter_pos < n - 1 && shooter_pos >= 1)
    {
        new_shooter_pos = shooter_pos + 1; // Move one step forward
    }
    else
    {
        new_shooter_pos = 1; // Reset shooter position if out of bounds
    }

    // Recursive call to find minimum shots required
    dp[shooter_pos][target_pos].shots = min(dp[shooter_pos][target_pos].shots, 1 + hit_target(n, new_shooter_pos, new_target_pos, dp, path));

    // Store the shot's path
    if (dp[shooter_pos][target_pos].shots == 1 + dp[new_shooter_pos][new_target_pos].shots)
    {
        path[shooter_pos][target_pos] = {new_shooter_pos, new_target_pos};
    }

    return dp[shooter_pos][target_pos].shots;
}

int main()
{
    srand(time(0)); // Seed the random number generator

    int n; // Number of positions
    cout << "Enter the number of hiding spots: ";
    cin >> n;

    int target_pos; // Initial position of the target
    cout << "Enter the target position (0 to " << n - 1 << "): ";
    cin >> target_pos;

    // Validate the target position
    if (target_pos < 0 || target_pos >= n)
    {
        cout << "Invalid target position." << endl;
        return 1;
    }

    vector<vector<State>> dp(n, vector<State>(n, {false, INT_MAX}));
    vector<vector<Shot>> path(n, vector<Shot>(n));

    int shooter_pos = 1; // Initial position of the shooter

    // Call the function to calculate minimum shots required
    int min_shots = hit_target(n, shooter_pos, target_pos, dp, path);

    if (min_shots == INT_MAX)
    {
        cout << "Target cannot be hit." << endl;
    }
    else
    {
        cout << "Minimum shots required to hit the target: " << min_shots << endl;
        cout << "Shot Path:" << endl;
        int current_shooter = shooter_pos;
        int current_target = target_pos;
        while (current_shooter != current_target)
        {
            cout << "Shooter at position " << current_shooter << " shoots: The target position is " << current_target << endl;
            Shot next_shot = path[current_shooter][current_target];
            current_shooter = next_shot.shooter_pos;
            current_target = next_shot.target_pos;
        }
        cout << "Target hit at position " << current_target << endl;
    }

    return 0;
}
