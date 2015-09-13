/**
 *  二叉树节点的最大距离
 */
struct node
{
    int val;
    node *left, *right;
    node(int v) : val(v), left(NULL), right(NULL){};
};

pair<int, int> longestDistance(node *root) {
    if (root == NULL) {
        return make_pair(0, -1);
    }
    pair<int, int> l = longestDistance(root->left);
    pair<int, int> r = longestDistance(root->right);
    return make_pair(max(2 + l.second + r.second, max(r.first, l.first)), 1 + max(l.second, r.second));
}