/**
 *  排序的旋转数组的查找
 *  TODO
 */
int find(int A[], int n, int k)
{
    if (n == 1) return A[0] == k ? 0 : -1;
    int ret;
    if (A[n / 2] > k) {
        if (A[0] > k) {
            if ((ret = find(A + n / 2, n - n / 2, k)) != -1) {
                return ret + n / 2;
            } else return -1;
        } else {
            if ((ret = find(A, n / 2, k)) != -1) {
                return ret;
            } else return -1;
        }
    }
    else {
        if (A[0] > k) {
            if ((ret = find(A + n / 2, n - n / 2, k)) != -1) {
                return ret + n / 2;
            } else return -1;
        } else {
            if ((ret = find(A, n / 2, k)) != -1) {
                return ret;
            } else return -1;
        }
    }
}