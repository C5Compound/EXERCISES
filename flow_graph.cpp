// 有向图用邻接矩阵存储

class FlowGraph
{
public:
    FlowGraph(){};
private:
    void printGraph();
    float printChance(int);
};

void printGraph()
{
    //0表示转态在A，1表示在B，2表示在C, 3表示end
    int next_state = 0;
    while (1) {
        //返回0-1之间的数字
        float r = (int)(rand() % 100) / 100;
        switch(next_state) {
            case 0:
                cout << "A";
                next_state = r < a1 ? 0 : (r < a1 + a2 ? 2 : (r < a1 + a2 + a3) ? 3 : 1);
                break;
            case 1:
                cout << "B";

                break;
            case 2:
                cout << "C";
                
                break;
            default:
                assert(FALSE);
                break;
        }
        if (next_state == 3) break;
    }
    cout << endl;
    cout << "the end" << endl;
}

float printChance(int n)
{
    float matrix[3][N] = {0.0};
    
}