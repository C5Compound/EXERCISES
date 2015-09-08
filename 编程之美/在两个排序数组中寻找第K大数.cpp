/**
 *  两个排序数组寻找第K大数
 *  归并的方式寻找，时间复杂度为O(A+B)
 *  二分的方式找，时间复杂度为O(log(A+B))
 */
int findKth(int A[], int B[], int la, int lb, int k)
{
    if (la > lb) {
        findKth(B, A, lb, la, k);
    }
    if (la == 0) {
        return B[k - 1];
    }
    if (k == 1) {
        return min(A[0], B[0]);
    }
    int ak = min(k / 2, la), kb = k - ka;
    if (B[bk - 1] > A[ak - 1]) {
        return findKth(A + ak, B, la - ak, bk, k - ak);
    }
    if (B[bk - 1] < A[ak - 1]) {
        return findKth(A, B + bk, ak, lb - bk, k - bk);
    }
    return A[ak - 1];
}

