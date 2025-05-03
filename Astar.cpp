#include<bits/stdc++.h>
using namespace std;

const int N = 3;

struct PuzzleState
{
    int puzzle[N][N];
    int zeroRow, zeroCol;
    int g; // cost from start
    int h; // heuristic (Manhattan)

    // Used by priority_queue to prioritize lower f = g + h
    bool operator<(const PuzzleState &other) const
    {
        return (g + h) > (other.g + other.h); // min-heap
    }
};

// Function to print a puzzle
void printPuzzle(const PuzzleState &state)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << state.puzzle[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----\n";
}

// Check if two puzzles are the same
bool isEqual(const PuzzleState &state1, const PuzzleState &state2)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (state1.puzzle[i][j] != state2.puzzle[i][j])
                return false;
        }
    }
    return true;
}

// Manhattan Distance as heuristic
int calculateManhattanDistance(const PuzzleState &current, const PuzzleState &goal)
{
    int distance = 0;
    unordered_map<int, pair<int, int>> goalPosition;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int val = goal.puzzle[i][j];
            goalPosition[val] = {i, j};
        }

    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int value = current.puzzle[i][j];
            if (value != 0)
            {
                int goalRow = goalPosition[value].first;
                int goalCol = goalPosition[value].second;
                distance += abs(i - goalRow) + abs(j - goalCol);
            }
        }
    }

    return distance;
}

// Check if a coordinate is within bounds
bool isValid(int row, int col)
{
    return (row >= 0 && row < N && col >= 0 && col < N);
}

// Generate all valid next states
vector<PuzzleState> generateNextStates(const PuzzleState &currentState, const PuzzleState &goal)
{
    vector<PuzzleState> nextStates;
    const int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // Left, Right, Up, Down

    for (int k = 0; k < 4; k++)
    {
        int nextZeroRow = currentState.zeroRow + moves[k][0];
        int nextZeroCol = currentState.zeroCol + moves[k][1];

        if (isValid(nextZeroRow, nextZeroCol))
        {
            PuzzleState nextState = currentState;
            swap(nextState.puzzle[currentState.zeroRow][currentState.zeroCol],
                 nextState.puzzle[nextZeroRow][nextZeroCol]);
            nextState.zeroRow = nextZeroRow;
            nextState.zeroCol = nextZeroCol;
            nextState.g = currentState.g + 1;
            nextState.h = calculateManhattanDistance(nextState, goal);
            nextStates.push_back(nextState);
        }
    }

    return nextStates;
}

// A* Search algorithm
void aStarSearch(const PuzzleState &initialState, const PuzzleState &finalState)
{
priority_queue<PuzzleState> pq;
unordered_set<string> visited;

pq.push(initialState);

while (!pq.empty())
{
    PuzzleState current = pq.top();
    pq.pop();

    cout << "Current State:\n";
    printPuzzle(current);
    cout << "Number of moves: " << current.g << endl;
    cout << "Heuristic cost: " << current.h << endl;
    cout << "-------------------\n";
    cout << "Log: Expanding node with g=" << current.g << " and h=" << current.h << endl;

    if (isEqual(current, finalState))
    {
        cout << "Goal State Reached!\n";
        cout << "Total moves: " << current.g << endl;
        cout << "Log: Goal state found after " << current.g << " moves" << endl;
        break;
    }

    vector<PuzzleState> nextStates = generateNextStates(current, finalState);

    for (const PuzzleState &nextState : nextStates)
    {
        string hash = "";
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                hash += to_string(nextState.puzzle[i][j]);

        if (visited.find(hash) == visited.end())
        {
            pq.push(nextState);
            visited.insert(hash);
            cout << "Log: Adding node to queue with g=" << nextState.g << " and h=" << nextState.h << endl;
        }
        else
        {
            cout << "Log: Skipping duplicate node with g=" << nextState.g << " and h=" << nextState.h << endl;
        }
    }
}
       
}

// Function to get puzzle input from user
PuzzleState getPuzzleState(const string &prompt)
{
    PuzzleState state;

    cout << prompt << " (0 = empty tile):\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << "Enter value at (" << i << ", " << j << "): ";
            cin >> state.puzzle[i][j];

            if (state.puzzle[i][j] == 0)
            {
                state.zeroRow = i; 
                state.zeroCol = j;
            }
        }
    }

    return state;
}

int main()
{
    PuzzleState initial = getPuzzleState("Enter the initial state");
    PuzzleState goal = getPuzzleState("Enter the goal state");

    initial.g = 0;
    initial.h = calculateManhattanDistance(initial, goal);

    printPuzzle(initial);

    aStarSearch(initial, goal);

    return 0;
}
