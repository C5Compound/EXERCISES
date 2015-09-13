/**
 *  二叉树最大距离节点
 */
 
pair<int, int> longestPath(node *root) 
{
    if (root == NULL) {
        return make_pair(0, -1);
    }
    auto left = longestPath(root->left);
    auto right = longestPath(root->right);
    return make_pair(max(2 + left.second + right.second, max(left.first, right.first)), 1 + max(left.second, right.second));
}