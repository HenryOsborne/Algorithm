#include <iostream>
using namespace std;
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <functional>
#include <numeric>
#include <string>
#include <cmath>
#include <queue>
#include <ctime>
#include <unordered_set>
#include <unordered_map>

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int val)
    {
        this->val = val;
        this->next = NULL;
    }
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *buildTreePreIn(vector<int> &preorder, vector<int> &inorder)
{
    if (preorder.empty())
        return nullptr;
    TreeNode *t = new TreeNode(preorder[0]);
    int i;
    vector<int> in1, in2, pre1, pre2;
    for (i = 0; i < inorder.size(); i++)
    {
        if (inorder[i] == preorder[0])
            break;
        in1.push_back(inorder[i]);
    }
    preorder.erase(preorder.begin());
    pre1.assign(preorder.begin(), preorder.begin() + i);
    pre2.assign(preorder.begin() + i, preorder.end());
    i++;
    for (; i < inorder.size(); i++)
    {
        in2.push_back(inorder[i]);
    }
    t->left = buildTreePreIn(pre1, in1);
    t->right = buildTreePreIn(pre2, in2);
    return t;
}

ListNode *CreateList(vector<int> v)
{
    if (v.empty())
        return NULL;
    ListNode *head = new ListNode(v[0]), *p = head;
    for (int i = 1; i < v.size(); i++)
    {
        ListNode *s = new ListNode(v[i]);
        p->next = s;
        p = s;
    }
    return head;
}

void PrintListNode(ListNode *head)
{
    ListNode *p = head;
    while (p != NULL)
    {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

TreeNode *Exchange(TreeNode *T)
{
    TreeNode *p;
    if (NULL == T || (NULL == T->left && NULL == T->right))
        return T;
    p = T->left;
    T->left = T->right;
    T->right = p;
    if (T->left)
    {
        T->left = Exchange(T->left);
    }
    if (T->right)
    {
        T->right = Exchange(T->right);
    }
    return T;
}

int main()
{
    cout << "hello" << endl;
    vector<int> pre = {1, 2, 3, 4, 5};
    vector<int> In = {3, 2, 1, 4, 5};
    TreeNode *tree, *tree2;
    tree = buildTreePreIn(pre, In);
    cout << "hello" << endl;
    tree2 = Exchange(tree);
    return 0;
}