///**
//*  迷宫生成及迷宫寻路
//*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
using namespace std;

class Maze
{
private:
    vector<vector<int>> maze;
    vector<vector<bool>> visit;
    const int row;
    const int col;
    Maze(const Maze&);
public:
    Maze(int, int);
    ~Maze();
    void genMaze();
    void mazeDfs(int, int);
    void printMaze();
    void Solve();
    bool solve(int, int);
};

Maze::Maze(int _row, int _col) : row(2 *_row + 1), col(2 * _col + 1)
{
    srand(time(0));
    maze.assign(row, vector<int>(col, 0));
    visit.assign(row, vector<bool>(col, false));
}

Maze::~Maze()
{
}

void Maze::genMaze()
{
    // 初始化迷宫
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
            maze[j][i] = 1 - (i % 2) * (j % 2);
        }
    }
    // 除了左下角的点，其他的墙不让打破
    visit[1][1] = true;
    visit[row - 1][col - 1] = true;
    mazeDfs(1, 1);
    // 入口
    maze[1][0] = 0;
    // 出口
    maze[row - 2][col - 1] = 0;
    for (int j = 1; j < row - 1; ++j) {
        for (int i = 1; i < col - 1; ++i) {
            if (visit[j][i]) {
                maze[j][i] = 0;
            }
        }
    }
}

// DFS
void Maze::mazeDfs(int x, int y)
{
    const static int direc[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    // 初始方向随机
    for (int i = rand() % 4, j = 0; j < 4; ++j, i = (i + j) % 4) {

        int nx = x + 2 * direc[i][0];
        int ny = y + 2 * direc[i][1];

        if (nx > 0 && nx < col - 1 && 
            ny > 0 && ny < row - 1 && 
            !visit[ny][nx]) {
            // 拆墙
            visit[(ny + y) / 2][(nx + x) / 2] = true;
            visit[ny][nx] = true;
            mazeDfs(nx, ny);
        }
    }
}

void Maze::printMaze()
{
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
            printf("%s", (maze[j][i] == 0 ? "  " : (maze[j][i] == 1 ? "＋" : "->")));
        }
        printf("\n");
    }
}

// 回溯
bool Maze::solve(int x, int y)
{
    if (x == col - 1 && y == row - 1) {
        return true;
    }
    const static int direc[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    // 初始方向随机
    for (int i = 0; i < 4; ++i) {

        int nx = x + 2 * direc[i][0];
        int ny = y + 2 * direc[i][1];

        if (nx > 0 && nx < col - 1 && 
            ny > 0 && ny < row - 1 && 
            !visit[ny][nx]) {
            // 中间没有墙
            if (maze[(ny + y) / 2][(nx + x) / 2] == 0) {
                visit[ny][nx] = true;
                if (solve(nx, ny)) {
                    return true;
                }
                visit[ny][nx] = false;
            }
        }
    }
    return false;
}

void Maze::Solve() 
{
    // 清除标志
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
            visit[j][i] = false;
        }
    }
    visit[1][1] = true;
    solve(1, 1);
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
            if(visit[j][i] == true) {
                maze[j][i] = 2;
            }
        }
    }
    printMaze();
}

int main()
{
    Maze maze(15, 15);
    maze.genMaze();
    maze.printMaze();
    maze.Solve();
    return 0;
}