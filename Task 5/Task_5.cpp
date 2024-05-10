#include <iostream>
#include <vector>

using namespace std;

// Function to form pairs of coins starting from the rightmost coin
void Right(vector<vector<int>> &row, int &jumps, int &moves)
{
    int n = row.size();
    // Iterate over the coins from right to left
    for (int i = n - 1; i > 0; i--)
    {
        // Check if the required number of pairs has been formed
        if (jumps > (n / 4) - 1)
            break;

        // If the coin is already paired, skip it
        if (row[i][0] == -1)
            continue;

        int index = i - 1;
        int currentJumps = 0;

        // Keep jumping until the required number of coins to jump over is reached
        while (currentJumps != jumps)
        {
            if (row[index].size() == 1 && row[index][0] != -1)
                currentJumps++;

            if (row[index].size() == 2)
                currentJumps += 2;

            index--;
        }

        // Find the next available coin to make a pair with after the required number of jumps is reached
        while (row[index][0] == -1)
        {
            index--;
        }

        // Make the coin pair and update the coins row to indicate the new empty position
        row[i].push_back(row[index][0]);
        row[index][0] = -1;

        jumps++;
        moves++;
    }
}

// Function to form pairs of coins starting from the leftmost coin
void Left(vector<vector<int>> &row, int &jumps, int &moves)
{
    int n = row.size();
    // Iterate over the coins from left to right
    for (int i = 0; i < n; i++)
    {
        // If it is a pair or empty space, skip it
        if (row[i][0] == -1 || row[i].size() == 2)
            continue;

        int index = i + 1;
        int currentJumps = 0;

        // Keep jumping until the required number of coins to jump over is reached
        while (currentJumps != jumps)
        {
            if (row[index].size() == 1 && row[index][0] != -1)
                currentJumps++;

            if (row[index].size() == 2)
                currentJumps += 2;

            index++;
        }

        // Find the next available coin to make a pair with after the required number of jumps is reached
        while (row[index][0] == -1)
        {
            index++;
        }

        // Make the coin pair and update the coins row to indicate the new empty position
        row[index].push_back(row[i][0]);
        row[i][0] = -1;

        jumps++;
        moves++;
    }
}

// Function to generate a row of coins
vector<vector<int>> toRow(int n)
{
    vector<vector<int>> row;

    // Make a row of coins numbered from 1 to n
    for (int i = 1; i < n + 1; i++)
    {
        row.push_back({i});
    }

    return row;
}

// Function to display the result
void displayResult(vector<vector<int>> &row, int &moves)
{
    cout << "Minimum number of moves: " << moves << endl;

    for (int i = 0; i < row.size(); i++)
    {
        if (row[i][0] == -1)
            continue;

        cout << "( ";
        for (int j = 0; j < row[i].size(); j++)
        {
            cout << row[i][j] << " ";
        }
        cout << ") ";
    }
}

// Function to orchestrate the process of forming pairs of coins
void Pairs(int n)
{
    // Check if the number of coins allows for a solution
    if (n % 4 != 0)
    {
        cout << "There is no solution for this number of coins " << endl;
        return;
    }

    int moves = 0, jumps = 1;
    // Generate the row of coins
    vector<vector<int>> row = toRow(n);

    // Start forming pairs from the rightmost coin until no more pairs can be formed
    Right(row, jumps, moves);

    // Continue forming pairs from the leftmost coin until no more pairs can be formed
    Left(row, jumps, moves);

    // Display the result
    displayResult(row, moves);
}

int main()
{
    // Call the function to form pairs with 20 coins
    Pairs(20);
    return 0;
}
