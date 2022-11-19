#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

int countk = 0;
int tree_h = 0;
queue<int> node;
vector<int> _data(30, -501);

void build_tree(vector<int> inorder, vector<int> postorder);

int find_index(vector<int> inorder, int val);

vector<int> cutarr(vector<int> a, int begin, int end);
int main(int argc, char *argv[])
{
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile;
    outfile.open(argv[2]);

    // TODO: Please code here
    int num_tree = 0;
    infile >> num_tree;
    while (num_tree--)
    {
        int number;
        infile >> number;
        vector<int> digit;
        for (int i = 0; i < number; i++)
        {
            int a;
            infile >> a;
            digit.push_back(a);
        }

        vector<int> digit_sorted(digit);

        sort(digit_sorted.begin(), digit_sorted.end());

        build_tree(digit_sorted, digit);
        for (int i = 0;; i++)
        {
            outfile << node.front() << " ";
            node.pop();
            if (node.empty())
                break;
        }
        outfile << endl;
        outfile << tree_h + 1;
        int record = 0;
        for (int i = 0; i < _data.size(); i++)
        {
            if (_data[i] == -501)
            {
                record = i;
                break;
            }
            cout<<endl;
            outfile << _data[i] ;
        }
        for (int i = 0; i < record; i++)
        {
            _data[i] = -501;
        }
        tree_h = 0;
    }

    infile.close();
    outfile.close();
    return 0;
}

int find_index(vector<int> inorder, int val)
{
    for (int i = 0; i < inorder.size(); i++)
    {
        if (val == inorder[i])
            return i;
    }
}
vector<int> cutarr(vector<int> a, int begin, int end)
{
    vector<int> result;
    for (int i = begin; i <= end; i++)
    {
        result.push_back(a[i]);
    }
    return result;
}
void build_tree(vector<int> inorder, vector<int> postorder)
{
    static int original_root = postorder.back();
    int root = postorder.back();
    if (countk > tree_h)tree_h = countk;
    if (_data[countk] < root) _data[countk] = root;
    node.push(root);
    int mid = find_index(inorder, root);
    postorder.pop_back();
    int pre = -1, suc = -1;
    if (postorder.empty()){
        return;
    }
    for (int i = 0; i < postorder.size(); i++){
        if (postorder[i] < inorder[mid])
            pre = i; // pre ==-1 只有右子數
        if (postorder[i] > inorder[mid])
            break;
    }
    suc = postorder.size() - pre - 1;
    if (pre != -1){//判斷有沒有左子樹
        countk++;
        build_tree(cutarr(inorder, 0, mid - 1), cutarr(postorder, 0, pre));
        countk--;
    }
    if (suc != 0){//判斷有沒有右子樹
        countk++;
        build_tree(cutarr(inorder, mid + 1, inorder.size() - 1), cutarr(postorder, pre + 1, postorder.size() - 1)); //右
        countk--;
    }
}