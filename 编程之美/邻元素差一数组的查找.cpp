/**
 *  数组A中任意两个相邻元素大小相差1，现给定这样的数组A和目标整数t，找出t在数组A中的所有位置。
 *  如数组：[1,2,3,4,3,4,5,6,5]，找到4在数组中的位置。
 *  这道题目最差时间复杂度也是O（N），所以重点在于能不能找到一种尽可能减少比较次数的方法。
 */
vector<int> find(vector<int> arr, int t)
{
    vector<int> pos;
    for (int i = 0; i < arr.size();) {
        if (arr[i] == t) {
            pos.push_back(i);
            i += 2;
        }
        i += abs(arr[i] - t);
    }
    return pos;
}
