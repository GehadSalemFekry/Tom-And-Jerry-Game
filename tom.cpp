#include "tom.h"

Tom::Tom(int BoardData[22][22])
{
    // Reading the image
    QPixmap image("Tom.svg");
    // Setting dimensions of the image
    image = image.scaledToWidth(30);
    image = image.scaledToHeight(30);

    // Setting Tom image
    setPixmap(image);

    // Setting Tom position
    row = 20;
    column = 10;
    setPos(70 + (30 * column), 70 + (30 * row));

    // Reading Board
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 22; j++) {
            data[i][j] = BoardData[i][j];

            // Marking open cells in Jerry's home as closed
            if (data[i][j] == 85 || data[i][j] == 86 || data[i][j] == 113 || data[i][j] == 127 ||
                data[i][j] == 149 || data[i][j] == 148 || data[i][j] == 122)
                data[i][j] = -1;
        }

    // Precomputing shortest path from all nodes to all nodes
    dijkstraPrep();
}

bool Tom::home(int r, int c) // Checking if Tom is at home to not enter inside
{
    for (int i = 8; i <= 13; i++)
        for (int j = 8; j <= 13; j++)
            if ((r == i) && (c == j))
                return true;
    return false;
}
void Tom::set_row_col(int r, int c)
{
    row = r;
    column = c;
    setPos(70 + (30 * column), 70 + (30 * row));
}
void Tom::get_row_col(int &r, int &c)
{
    r = row;
    c = column;
}

void Tom::move(int r, int c)
{
    // new row and column are initially the current position
    int new_row = row, new_col = column;

    // Getting current node number of Tom and Jerry
    int tomCur = data[row][column]; //row and column are Tom position
    int jerryCur = data[r][c]; //r and c are Jerry position

    // next is the next node after being computed by Dijkstra
    int nxt = next[tomCur][jerryCur];

    if (row - 1 >= 0 && data[row - 1][column] == nxt)
        new_row = row - 1;
    else if (column - 1 >= 0 && data[row][column - 1] == nxt)
        new_col = column - 1;
    else if (row + 1 < 22 && data[row + 1][column] == nxt)
        new_row = row + 1;
    else if (column + 1 < 22 && data[row][column + 1] == nxt)
        new_col = column + 1;

    // Tom can't enter Jerry's home
    if (!home(new_row, new_col))
        set_row_col(new_row, new_col);
}
void Tom::dijkstraPrep()
{
    // Precomputing dijkstra for all nodes, so that the next node is always pre-calculated

    // Preparing the adjacency list with nodes and edges
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 22; j++)
        {
            if (data[i][j] >= 0) // Adjacency list is an array of vectors (for each node there is a vector)
            {
                if (i - 1 >= 0 && data[i - 1][j] >= 0)
                    adj[data[i][j]].push_back(data[i - 1][j]);
                if (i + 1 < 22 && data[i + 1][j] >= 0)
                    adj[data[i][j]].push_back(data[i + 1][j]);
                if (j - 1 >= 0 && data[i][j - 1] >= 0)
                    adj[data[i][j]].push_back(data[i][j - 1]);
                if (j + 1 < 22 && data[i][j + 1] >= 0)
                    adj[data[i][j]].push_back(data[i][j + 1]);
            }
        }
    }

    for (int i = 0; i < 238; i++)
    {
        // Initializing the arrays with default values for each iteration
        for (int j = 0; j < 238; j++)
        {//for each node, it has a distance, visited and a parent
            dist[j] = 1e5; //initially to infinity
            visited[j] = false; //initially node is not visited
            parent[j] = i;
        }

        // Calculating shorted path from node i to all other nodes
        dijkstra(i);

        // Retrieving the first next node to all nodes from the calculated path
        for (int j = 0; j < 238; j++)
        {
            int prev = j;
            while (prev != i) {
                next[i][j] = prev;
                prev = parent[prev];
            }
        }
    }
}
void Tom::dijkstra(int source)
{
    // Normal BFS travesal
    QQueue<int> q;

    q.enqueue(source);
    dist[source] = 0; // f : cost, s : cur
    parent[source] = source;

    while (!q.empty()) {
        int cur = q.head();
        q.dequeue();

        if (visited[cur])
            continue;

        for (int nxt : adj[cur]) {//looping on the adjacent nodes (max 4)
            if (!visited[nxt] && dist[cur] + 1 < dist[nxt]) {
                dist[nxt] = dist[cur] + 1;
                parent[nxt] = cur;
                q.enqueue(nxt);
            }
        }
        visited[cur] = true;
    }
}
