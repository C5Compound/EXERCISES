/**
 *  迷宫生成及迷宫寻路
 */
#include <cstdio>
#include <cstdlib>
using namespace std;

// ♦♥♠♣
int* gen_maze(int row, int col)
{
    int* maze = new int[row * col];
    // 初始化迷宫
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            maze[j + i * row] = 1 - (i % 2) * (j % 2);
        }
    }
    return maze;
}

void print_maze(int *maze, int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%s", (maze[j + i * row] == 0 ? "  " : "＋"));
        }
        printf("\n");
    }
}

int* solve_maze(int *maze, int row, int col)
{
    return NULL;
}

int main()
{
    int *maze = gen_maze(31, 31);
    print_maze(maze, 31, 31);
    delete[] maze;
    return 0;
}