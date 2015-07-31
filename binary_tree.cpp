/**
 *  1.二叉树序列化和反序列化
 *  2.判断二叉树是否为二叉搜索树
 *  3.找出二叉树中的最大二叉搜索树
 */
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>
using namespace std;

struct node
{
    int val;
    node *left, *right;
    node(int x) : val(x), left(NULL), right(NULL) {};
};
/**
*  前序
*  二叉树的序列化
*/
void treeSerialize(node *root, FILE *fp)
{
    if (root == NULL) {
        fprintf(fp, "# ");
        return;
    }
    fprintf(fp, "%d ", root->val);
    treeSerialize(root->left, fp);
    treeSerialize(root->right, fp);
}

/**
*  树的反序列化
*  递归，前序
*/
node* treeDeserialize(FILE *fp)
{
    char val[10] = {0};
    // 如果是由treeSerialize生成的串
    // 最后不会读到文件尾就返回，所以feof不会为true
    if (feof(fp) || (fscanf(fp, "%s", val) && val[0] == '#')) {
        return NULL;
    }
    node *root = new node(atoi(val));
    root->left = treeDeserialize(fp);
    root->right = treeDeserialize(fp);
    return root;
}

/**
*  判断二叉树是否为二叉搜索树
*  递归
*/
bool isBSTree(node *root, int low = INT_MIN, int high = INT_MAX)
{
    if (root == NULL) {
        return true;
    }
    if (root->val > low && root->val < high) {
        return isBSTree(root->left, low, root->val) && isBSTree(root->right, root->val, high);
    }
    return false;
}

/**
*  返回出二叉树中的最大二叉搜索树
*  递归
*/
pair<int, bool> biggestBSTree(node *root, int low = INT_MIN, int high = INT_MAX)
{
    if (root == NULL) {
        return make_pair(0, true);
    }
    pair<int, bool> left = biggestBSTree(root->left, low, root->val);
    pair<int, bool> right = biggestBSTree(root->right, root->val, high);

    if (root->val < low || root->val > high || !left.second || !right.second) {
        return make_pair(max(left.first, right.first), false);
    }
    return make_pair(left.first + right.first + 1, true);
}

// codes below is for test
void freeTree(node *root)
{
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main()
{
    FILE *fp = fopen("fin.txt", "r+");
    FILE *wp = fopen("out.txt", "w");
    node *it = treeDeserialize(fp);
    printf("%s\n", isBSTree(it) ? "true" : "false");
    printf("%d\n", (biggestBSTree(it)).first);
    treeSerialize(it, wp);
    freeTree(it);
    fclose(fp);
    fclose(fp);
    return 0;
}