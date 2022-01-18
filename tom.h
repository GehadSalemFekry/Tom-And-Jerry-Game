#ifndef TOM_H
#define TOM_H
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QQueue>
#include <QDebug>

class Tom : public QGraphicsPixmapItem
{
private:
    int data[22][22];
    int dist[238];
    int visited[238];
    QVector<int> adj[238];
    int parent[238];
    int next[238][238];
    int row, column;

public:
    Tom(int BoardData[22][22]);

    bool home(int r, int c);
    void dijkstra(int source);
    void dijkstraPrep();

    void move(int r, int c);

    void set_row_col(int r, int c);
    void get_row_col(int &r, int &c);
    int get_row();
    int get_col();
};

#endif // TOM_H
