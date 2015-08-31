// 在有序的二维矩阵中查找
// 矩阵元素沿行列增的方向增大
// 复杂度为O(M+N)
pair<int, int> findInMatrix(vector<vector<int>> &matrix, int k)
{
    if (matrix.empty()) {
        return make_pair(-1, -1);
    }
    int row = 0, col = matrix[0].size() - 1;
    while (row < matrix.size() && col >= 0) {
        if (matrix[row][col] == k) {
            return make_pair(row, col);
        } else if (matrix[row][col] > k) {
            --col;
        } else {
            ++row;
        }
    }
    return make_pair(-1, -1);
}