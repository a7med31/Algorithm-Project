#include <iostream>
using namespace std;
#define N 8

// moves patterns of knight in chess

static int x_Moves[8] = {1, 1, 2, 2, -1, -1, -2, -2};
static int y_Moves[8] = {2, -2, 1, -1, 2, -2, 1, -1};

// checks whether a square is within the 8 x 8 chessboard  and empty or not
bool is_Empty(int a[], int x, int y)
{
    return ((x >= 0 && y >= 0) && (x < N && y < N)) && (a[y * N + x] < 0);
}

// returns the number of empty squares adjacent to x and y

int getDegree(int a[], int x, int y)
{
    int count = 0;
    for (int i = 0; i < 8; ++i)
        if (is_Empty(a, (x + x_Moves[i]), (y + y_Moves[i])))
            count++;

    return count;
}

// picks next point using minimum degree approach
// returns false if it is not possible to pick

bool nextMove(int sol[], int *x, int *y)
{
    int min_degree_index = -1, c, min_degree = (8 + 1), next_x, next_y;

    // from a random adjacent. Find the adjacent with minimum degree.

    int start = rand() % N;
    for (int count = 0; count < N; ++count)
    {
        int i = (start + count) % 8;
        next_x = *x + x_Moves[i];
        next_y = *y + y_Moves[i];
        if ((is_Empty(sol, next_x, next_y)) &&
            (c = getDegree(sol, next_x, next_y)) < min_degree)
        {
            min_degree_index = i;
            min_degree = c;
        }
    }

    // if we didn't find cells
    if (min_degree_index == -1)
        return false;

    // store coordinates of next point
    next_x = *x + x_Moves[min_degree_index];
    next_y = *y + y_Moves[min_degree_index];

    // mark next move
    sol[next_y * N + next_x] = sol[(*y) * N + (*x)] + 1;

    // update next point
    *x = next_x;
    *y = next_y;

    return true;
}

// printing the solution board with visited cells and its visit number
void print(int a[])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printf("%d\t", a[j * N + i]);
        printf("\n");
    }
}

// checks if the last cell visisted is 1 knight move away from starting cell
bool neighbour(int x, int y, int start_x, int start_y)
{
    for (int i = 0; i < 8; ++i)
        if (((x + x_Moves[i]) == start_x) && ((y + y_Moves[i]) == start_y))
            return true;

    return false;
}

bool findClosedKnightTour(int start_x, int start_y)
{
    // initialzing the chessboard with -1 as it marks the non visited cells
    int sol[N * N];
    for (int i = 0; i < N * N; ++i)
        sol[i] = -1;
    int x = start_x, y = start_y;
    sol[y * N + x] = 1; // Marking our starting point with 1 as its visited

    // keep picking next points using our greedy approach , which is picking next minimum degree cell to visit

    for (int i = 0; i < N * N - 1; ++i)
        if (nextMove(sol, &x, &y) == 0)
        {
            // print(sol);

            return false;
        }
    // checking if the knight tour is closed

    if (!neighbour(x, y, start_x, start_y))
        return false;

    print(sol);
    return true;
}

int main()
{
    int start_x;
    int start_y;
    cout << " Enter your start position x : " << '\n';
    cin >> start_x;
    cout << " Enter your start position y : " << '\n';
    cin >> start_y;

    while (!findClosedKnightTour(start_x, start_y))
    {
        // while no closed tour knight keep
        ;
    }

    return 0;
}
