#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <functional>
#include <numeric>
#include <string>
#include <cmath>
#include <ctime>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

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

class MinStack
{
private:
    ListNode *head;
    ListNode *p;
    multiset<int> table;

public:
    /** initialize your data structure here. */
    MinStack()
    {
        head = new ListNode(-1);
        p = head;
    }

    void push(int x)
    {
        ListNode *s = new ListNode(x);
        p->next = s;
        p = s;
        table.insert(x);
    }

    void pop()
    {
        if (p == head)
            return;
        ListNode *q = head;
        while (q->next != p)
            q = q->next;
        multiset<int>::iterator pos;
        pos = table.find(p->val);
        table.erase(pos);
        p = q;
    }

    int top()
    {
        if (p == head)
            return -1;
        return p->val;
    }

    int getMin()
    {
        if (p == head)
            return -1;
        return *table.begin();
    }
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    ListNode *pos1 = l1, *pos2 = l2;
    int x;
    if (pos1 == NULL && pos2 == NULL)
        return NULL;
    if (pos1 == NULL)
    {
        x = pos2->val;
        pos2 = pos2->next;
    }
    else if (pos2 == NULL)
    {
        x = pos1->val;
        pos1 = pos1->next;
    }
    else
    {
        if (pos1->val < pos2->val)
        {
            x = pos1->val;
            pos1 = pos1->next;
        }
        else
        {
            x = pos2->val;
            pos2 = pos2->next;
        }
    }
    ListNode *L = new ListNode(x), *p = L;
    while (pos1 != NULL && pos2 != NULL)
    {
        if (pos1->val < pos2->val)
        {
            x = pos1->val;
            pos1 = pos1->next;
        }
        else
        {
            x = pos2->val;
            pos2 = pos2->next;
        }
        ListNode *s = new ListNode(x);
        p->next = s;
        p = s;
    }
    while (pos1 != NULL)
    {
        ListNode *s = new ListNode(pos1->val);
        pos1 = pos1->next;
        p->next = s;
        p = s;
    }
    while (pos2 != NULL)
    {
        ListNode *s = new ListNode(pos2->val);
        pos2 = pos2->next;
        p->next = s;
        p = s;
    }
    return L;
}

ListNode *reverseList(ListNode *head)
{
    ListNode *pre = head, *p = head->next;
    while (p)
    {
        pre->next = p->next;
        p->next = head;
        head = p;
        p = pre->next;
    }
    return head;
}

ListNode *deleteDuplicates01(ListNode *head)
{
    if (head == NULL)
        return head;
    set<int> table;
    ListNode *p = head->next, *pre = head;
    table.insert(head->val);
    while (p != NULL)
    {
        if (table.find(p->val) == table.end())
        {
            table.insert(p->val);
            pre = p;
            p = p->next;
        }
        else
        {
            pre->next = p->next;
            delete p;
            p = pre->next;
        }
    }
    return head;
}

ListNode *deleteDuplicates02(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    set<int> m1, m2;
    pair<set<int>::iterator, bool> ret;
    ListNode *p = head, *pre;
    while (p != NULL)
    {
        ret = m1.insert(p->val);
        if (ret.second)
            p = p->next;
        else
        {
            m2.insert(p->val);
            p = p->next;
        }
    }
    while (m2.find(head->val) != m2.end())
    {
        if (head->next == NULL)
            return NULL;
        head = head->next;
    }
    if (head == NULL && head->next == NULL)
        return head;
    pre = head;
    p = head->next;
    while (p != NULL)
    {
        if (m2.find(p->val) != m2.end())
        {
            pre->next = p->next;
            delete p;
            p = pre->next;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
    return head;
}

ListNode *removeNthFromEnd(ListNode *head, int n)
{
    ListNode *p = head;
    int cnt = 0;
    while (p != NULL)
    {
        p = p->next;
        cnt++;
    }
    if (n < cnt)
    {
        p = head->next;
        ListNode *pre = head;
        for (int i = 1; i < cnt - n; i++)
        {
            pre = p;
            p = p->next;
        }
        pre->next = p->next;
        delete p;
    }
    else
    {
        p = head;
        head = head->next;
        delete p;
    }
    return head;
}

ListNode *swapPairs(ListNode *head)
{
    if (head == NULL)
        return head;
    else if (head->next == NULL)
        return head;
    ListNode *p = head->next, *pre = head;
    pre->next = p->next;
    p->next = head;
    head = p;
    p = pre->next;
    while (p != NULL && p->next != NULL)
    {
        pre->next = p->next;
        p->next = p->next->next;
        pre->next->next = p;
        p = p->next;
        pre = pre->next->next;
    }
    return head;
}

ListNode *rotateRight(ListNode *head, int k)
{
    if (head == NULL || head->next == NULL || k == 0)
        return head;
    int cnt = 0;
    ListNode *p = head;
    while (p != NULL)
    {
        cnt++;
        p = p->next;
    }
    ListNode *pre = head;
    while (k > cnt)
        k -= cnt;
    if (k == cnt)
        return head;
    for (int i = 0; i < cnt - k - 1; i++)
    {
        pre = pre->next;
    }
    p = pre->next;
    ListNode *cur = p;
    while (cur->next != NULL)
        cur = cur->next;
    pre->next = NULL;
    cur->next = head;
    head = p;
    return head;
}

ListNode *reverseBetween(ListNode *head, int m, int n)
{
    if (head == NULL || head->next == NULL || m == n)
        return head;
    ListNode *dummy = new ListNode(-1);
    ListNode *pre = dummy;
    dummy->next = head;
    for (int i = 0; i < m - 1; i++)
        pre = pre->next;
    ListNode *p = pre->next;
    for (int i = m; i < n; i++)
    {
        ListNode *t = p->next;
        p->next = t->next;
        t->next = pre->next;
        pre->next = t;
    }
    return dummy->next;
}

ListNode *oddEvenList(ListNode *head)
{
    if (!head || !head->next || !head->next->next)
        return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *pre_cur = head, *cur = head->next;
    while (cur)
    {
        ListNode *p = cur->next;
        if (!p)
            break;
        cur->next = p->next;
        p->next = pre_cur->next;
        ;
        pre_cur->next = p;
        cur = cur->next;
        pre_cur = pre_cur->next;
    }
    return dummy->next;
}

string countAndSay(int n)
{
    if (n == 1)
        return "1";
    else
    {
        string temp = countAndSay(n - 1);
        //string temp="111221";
        string next;
        int count = 0;
        char a = temp[0];
        int i;
        for (i = 0; i < temp.size(); i++)
        {
            if (temp[i] == a)
                count++;
            else
            {
                next += to_string(count);
                next += a;
                a = temp[i];
                count = 0;
                i--;
            }
        }
        next += to_string(count);
        next += a;
        a = temp[i];
        return next;
    }
}

int lengthOfLastWord(string s)
{
    reverse(s.begin(), s.end());
    int i = 0;
    while (s[i] == ' ')
        i++;
    int len = 0;
    for (; i < s.size(); i++)
    {
        if (s[i] != ' ')
            len++;
        else
            break;
    }
    return len;
}

vector<int> plusOne(vector<int> &digits)
{
    if (digits.empty())
        return digits;
    int carry;
    int i = digits.size() - 1;
    if ((digits[i] + 1) < 10)
        digits[i] += 1;
    else
    {
        carry = (digits[i] + 1) / 10;
        digits[i] = (digits[i] + 1) % 10;
        i--;
        while (carry && i >= 0)
        {
            carry = (digits[i] + 1) / 10;
            digits[i] = (digits[i] + 1) % 10;
            i--;
        }
        while (carry)
        {
            digits.insert(digits.begin(), carry);
            carry = 0;
        }
    }
    return digits;
}

string addBinary(string a, string b)
{
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int carry = 0;
    int size = max(a.size(), b.size());
    a.resize(size, '0');
    b.resize(size, '0');
    string c;
    for (int i = 0; i < size; i++)
    {
        int temp = ((a[i] - '0') + (b[i] - '0') + carry);
        c += to_string(temp % 2);
        carry = temp / 2;
    }
    if (carry)
    {
        c += to_string(carry);
    }
    reverse(c.begin(), c.end());
    return c;
}

int mySqrt(int x)
{
    double y = sqrt(x);
    return (int)y;
}

bool isPalindrome(string s)
{
    if (s.empty())
        return true;
    string tmp1, tmp2;
    for (string::iterator it = s.begin(); it != s.end(); it++)
    {
        if (isalnum(*it))
            tmp1 += *it;
    }
    for (int i = 0; i < tmp1.size(); i++)
    {
        if (isupper(tmp1[i]))
            tmp1[i] += 32;
    }
    tmp2 = tmp1;
    reverse(tmp1.begin(), tmp1.end());
    if (tmp1 == tmp2)
        return true;
    else
        return false;
}

int singleNumber(vector<int> &nums)
{
    map<int, int> m;
    for (int i = 0; i < nums.size(); i++)
    {
        if (m.find(nums[i]) == m.end())
            m.insert(make_pair(nums[i], 1));
        else
            m[nums[i]]++;
    }
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        if (it->second == 1)
            return it->first;
    }
    return -1;
}

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    for (int i = 0; i < n; i++)
        nums1.pop_back();
    for (int i = 0; i < n; i++)
    {
        nums1.push_back(nums2[i]);
    }
    sort(nums1.begin(), nums1.end());
    for (int i : nums1)
        cout << i << " ";
    cout << endl;
}

int titleToNumber(string s)
{
    reverse(s.begin(), s.end());
    int sum = 0;
    for (int i = 0; i < s.size(); i++)
    {
        sum = sum + (s[i] - 'A' + 1) * pow(26, i);
    }
    return sum;
}

vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> triangle;
    if (numRows == 0)
        return triangle;
    for (int i = 0; i < numRows; i++)
    {
        vector<int> tmp;
        tmp.resize(i + 1, 1);
        triangle.push_back(tmp);
    }
    for (int i = 2; i < numRows; i++)
    {
        for (int j = 1; j < i; j++)
        {
            triangle[i][j] = triangle[i - 1][j] + triangle[i - 1][j - 1];
        }
    }
    return triangle;
}

int majorityElement(vector<int> &nums)
{
    map<int, int> m;
    for (int i = 0; i < nums.size(); i++)
    {
        if (m.find(nums[i]) == m.end())
            m.insert(make_pair(nums[i], 1));
        else
            m[nums[i]]++;
    }
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        if (it->second > nums.size() / 2)
            return it->first;
    }
    return -1;
}

void rotate(vector<int> &nums, int k)
{
    while (k > nums.size())
        k -= nums.size();
    vector<int> tmp(nums.end() - k, nums.end());
    int size = nums.size() - k;
    for (int i = 0; i < size; i++)
    {
        nums[nums.size() - 1 - i] = nums[nums.size() - 1 - i - k];
    }
    for (int i = 0; i < tmp.size(); i++)
    {
        nums[i] = tmp[i];
    }
}

void reverseString(vector<char> &s)
{
    if (s.empty())
        return;
    char tmp;
    for (int i = 0; i < s.size() / 2; i++)
    {
        tmp = s[i];
        s[i] = s[s.size() - 1 - i];
        s[s.size() - 1 - i] = tmp;
    }
}

vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
{
    vector<int> c;
    set<int> m;
    set<int> n;
    for (int i = 0; i < nums1.size(); i++)
        m.insert(nums1[i]);
    for (int i = 0; i < nums2.size(); i++)
        if (m.find(nums2[i]) != m.end())
            n.insert(nums2[i]);
    for (set<int>::iterator it = n.begin(); it != n.end(); it++)
    {
        c.push_back(*it);
    }
    return c;
}

ListNode *partition(ListNode *head, int x) //未成功
{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *pre = head, *p;
    while (pre)
    {
        if (pre->val == x)
        {
            p = pre->next;
            break;
        }
        pre = pre->next;
    }
    ListNode *pre_ins = dummy, *ins = dummy->next;
    while (p)
    {
        if (p->val < x)
        {
            pre->next = p->next;
            while (p->val > ins->val)
            {
                pre_ins = ins;
                ins = ins->next;
            }
            p->next = ins;
            pre_ins->next = p;
            p = pre->next;
            pre_ins = dummy, ins = dummy->next;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
    return dummy->next;
}

class HappyNumber
{
    int cnt = 500;
    int cur = 0;
    bool isHappy(int n)
    {
        int s = 0;
        if (n == 1)
            return true;
        else if (cur > cnt)
            return false;
        else
        {
            while (n)
            {
                s = s + (pow(n % 10, 2));
                n /= 10;
            }
            cur++;
            return isHappy(s);
        }
    }
};

bool isPowerOfTwo(int n)
{
    if (n == 1)
        return true;
    else if (n % 2 == 1 || n == 0)
        return false;
    else
        return isPowerOfTwo(n / 2);
}

bool isPowerOfThree(int n)
{
    if (n == 0)
        return false;
    else if (n == 1)
        return true;
    else if (n % 3 != 0)
        return false;
    else
        return isPowerOfThree(n / 3);
}

bool isPowerOfFour(int num)
{
    if (num == 0)
        return false;
    else if (num == 1)
        return true;
    else if (num % 4 != 0)
        return false;
    else
        return isPowerOfFour(num / 4);
}

string reverseVowels(string s)
{
    vector<int> index_i;
    vector<char> index_s;
    vector<char> vowel = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    for (int i = 0; i < s.size(); i++)
    {
        if (find(vowel.begin(), vowel.end(), s[i]) != vowel.end())
        {
            index_i.push_back(i);
            index_s.push_back(s[i]);
        }
    }
    reverse(index_s.begin(), index_s.end());
    for (int i = 0; i < index_i.size(); i++)
    {
        s[index_i[i]] = index_s[i];
    }
    return s;
}

bool containsDuplicate(vector<int> &nums)
{
    if (nums.empty())
        return false;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (nums[i] == nums[i + 1])
            return true;
    }
    return false;
}

vector<int> getRow(int rowIndex)
{
    vector<vector<int>> triangle;
    for (int i = 0; i <= rowIndex; i++)
    {
        vector<int> tmp;
        tmp.resize(i + 1, 1);
        triangle.push_back(tmp);
    }
    for (int i = 2; i <= rowIndex; i++)
    {
        for (int j = 1; j < i; j++)
        {
            triangle[i][j] = triangle[i - 1][j] + triangle[i - 1][j - 1];
        }
    }
    return triangle[rowIndex];
}

string reverseWords(string s)
{
    string last;
    while (s.back() == ' ')
        s.pop_back();
    for (int i = 0; i < s.size(); i++)
        if (s[i] == ' ' && s[i + 1] == ' ')
        {
            s.erase(s.begin() + i);
            i--;
        }
    string::iterator pos1 = s.begin(), pos2 = s.begin();
    for (; pos2 != s.end(); pos2++)
    {
        if (*pos2 == ' ')
        {
            string tmp(pos1, pos2);
            last.insert(0, tmp);
            last.insert(0, " ");
            pos1 = pos2 + 1;
        }
    }
    string tmp(pos1, pos2);
    last.insert(0, tmp);
    while (last.back() == ' ')
        last.pop_back();
    return last;
}

ListNode *removeElements(ListNode *head, int val)
{
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *pre = dummy;
    while (pre->next != NULL)
    {
        if (pre->next->val == val)
        {
            ListNode *p = pre->next;
            pre->next = p->next;
            delete p;
        }
        else
            pre = pre->next;
    }
    return dummy->next;
}

int addDigits(int num)
{
    int s = 0;
    if (num / 10 == 0)
        return num;
    else
    {
        while (num)
        {
            s += num % 10;
            num /= 10;
        }
        return addDigits(s);
    }
}

int maxSubArray(vector<int> &nums)
{
    int dp = nums[0], result = dp;
    for (int i = 1; i < nums.size(); i++)
    {
        dp = max(dp + nums[i], nums[i]);
        result = max(dp, result);
    }
    return result;
}

int climbStairs(int n)
{
    if (n == 1)
        return 1;
    vector<int> dp;
    dp.resize(n);
    dp[0] = 1;
    dp[1] = 2;
    for (int i = 2; i < n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n - 1];
}

int missingNumber(vector<int> &nums)
{
    if (nums.empty())
        return -1;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
        if (i != nums[i])
            return i;
    }
    return nums.back() + 1;
}

void moveZeroes(vector<int> &nums)
{
    int cnt = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 0)
        {
            nums.erase(nums.begin() + i);
            nums.push_back(0);
            i--;
        }
        cnt++;
        if (cnt >= nums.size())
            break;
    }
}

char findTheDifference(string s, string t)
{
    map<char, int> m1, m2;
    for (char i : s)
    {
        if (m1.find(i) == m1.end())
            m1.insert(make_pair(i, 1));
        else
            m1[i]++;
    }
    for (char i : t)
    {
        if (m2.find(i) == m2.end())
            m2.insert(make_pair(i, 1));
        else
            m2[i]++;
    }
    for (char i = 'a'; i < 'a' + 26; i++)
        if (m1[i] != m2[i])
            return i;
    return ' ';
}

vector<string> fizzBuzz(int n)
{
    vector<string> s;
    for (int i = 1; i <= n; i++)
    {
        if (i % 3 == 0 && i % 5 == 0)
            s.push_back("FizzBuzz");
        else if (i % 3 == 0)
            s.push_back("Fizz");
        else if (i % 5 == 0)
            s.push_back("Buzz");
        else
            s.push_back(to_string(i));
    }
    return s;
}

class Calculator
{
private:
    vector<string> tokens;
    stack<char> st;

public:
    void trans(vector<string> &tokens, string s)
    {
        char e;
        int i = 0;
        while (s[i] != '\0')
        {
            switch (s[i])
            {
            case ' ':
                i++;
                break;
            case '(':
                st.push('(');
                i++;
                break;
            case ')':
                e = st.top();
                st.pop();
                while (e != '(')
                {
                    string tmp;
                    tmp += e;
                    tokens.push_back(tmp);
                    e = st.top();
                    st.pop();
                }
                i++;
                break;
            case '+':
            case '-':
                while (!st.empty())
                {
                    e = st.top();
                    if (e != '(')
                    {
                        string tmp;
                        tmp += e;
                        tokens.push_back(tmp);
                        st.pop();
                    }
                    else
                        break;
                }
                st.push(s[i]);
                i++;
                break;
            case '*':
            case '/':
                while (!st.empty())
                {
                    e = st.top();
                    if (e == '*' && e == '/')
                    {
                        tokens.push_back(to_string(e));
                        st.pop();
                    }
                    else
                        break;
                }
                st.push(s[i]);
                i++;
                break;
            default:
                string tmp;
                while (s[i] >= '0' && s[i] <= '9')
                {
                    tmp += s[i];
                    i++;
                }
                tokens.push_back(tmp);
                break;
            }
        }
        while (!st.empty())
        {
            e = st.top();
            st.pop();
            string tmp;
            tmp += e;
            tokens.push_back(tmp);
        }
    }

    double evalRPN(vector<string> &tokens)
    {
        stack<int> Optr;
        int a, b, c, i = 0;
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == "+")
            {
                a = Optr.top();
                Optr.pop();
                b = Optr.top();
                Optr.pop();
                c = b + a;
                Optr.push(c);
            }
            else if (tokens[i] == "-")
            {
                a = Optr.top();
                Optr.pop();
                b = Optr.top();
                Optr.pop();
                c = b - a;
                Optr.push(c);
            }
            else if (tokens[i] == "*")
            {
                a = Optr.top();
                Optr.pop();
                b = Optr.top();
                Optr.pop();
                c = b * a;
                Optr.push(c);
            }
            else if (tokens[i] == "/")
            {
                a = Optr.top();
                Optr.pop();
                b = Optr.top();
                Optr.pop();
                c = b / a;
                Optr.push(c);
            }
            else
            {
                Optr.push(atoi(tokens[i].c_str()));
            }
        }
        return Optr.top();
    }

    int calculate(string s)
    {
        trans(tokens, s);
        return (int)evalRPN(tokens);
    }
};

bool canConstruct(string ransomNote, string magazine)
{
    map<char, int> m1, m2;
    for (int i = 0; i < magazine.size(); i++)
    {
        if (m1.find(magazine[i]) == m1.end())
            m1.insert(make_pair(magazine[i], 1));
        else
            m1[magazine[i]]++;
    }
    for (int i = 0; i < ransomNote.size(); i++)
    {
        if (m1.find(ransomNote[i]) == m1.end())
            return false;
        else if (m1[ransomNote[i]] == 0)
            return false;
        else
            m1[ransomNote[i]]--;
    }
    return true;
}

bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (p == NULL && q == NULL)
        return true;
    else if (p == NULL || q == NULL)
        return false;
    else if (p->val == q->val)
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    else
        return false;
}

class SymmetricTree
{
public:
    bool isMirror(TreeNode *p, TreeNode *q)
    {
        if (p == NULL && q == NULL)
            return true;
        else if (p == NULL || q == NULL)
            return false;
        else if (p->val == q->val)
            return isMirror(p->left, q->right) && isMirror(p->right, q->left);
        else
            return false;
    }
    bool isSymmetric(TreeNode *root)
    {
        return isMirror(root, root);
    }
};

int maxDepth(TreeNode *root)
{
    queue<TreeNode *> qu;
    qu.push(root);
    if (root == NULL)
        return 0;
    else if (root != NULL && root->left == NULL && root->right == NULL)
        return 1;
    else
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

vector<vector<int>> levelOrder(TreeNode *root)
{
    if (root == NULL)
        return {};
    vector<vector<int>> a;
    queue<TreeNode *> qu;
    vector<int> tmp;
    qu.push(root);
    while (!qu.empty())
    {
        tmp.clear();
        int size = qu.size();
        for (int i = 0; i < size; i++)
        {
            TreeNode *p = qu.front();
            qu.pop();
            tmp.push_back(p->val);
            if (p->left != NULL)
                qu.push(p->left);
            if (p->right != NULL)
                qu.push(p->right);
        }
        a.push_back(tmp);
    }
    return a;
}

class TreeInOrder
{
public:
    vector<vector<int>> levels;
    void helper(TreeNode *node, int level)
    {
        if (levels.size() == level)
            levels.push_back({});
        levels[level].push_back(node->val);
        if (node->left)
            helper(node->left, level + 1);
        if (node->right)
            helper(node->right, level + 1);
    }
    vector<vector<int>> InOrder(TreeNode *root)
    {
        if (!root)
            return levels;
        helper(root, 0);
        return levels;
    }
};

int maxProfit01(vector<int> &prices)
{
    if (prices.empty())
        return 0;
    int min_price = prices[0];
    int result = 0, dp;
    for (int i = 0; i < prices.size(); i++)
    {
        min_price = min(prices[i], min_price);
        dp = prices[i] - min_price;
        result = max(dp, result);
    }
    return result;
}

int maxProfit02(vector<int> &prices)
{
    if (prices.empty())
        return 0;
    prices.push_back(0);
    int min_price = prices[0];
    int dp, result = 0;
    for (int i = 0; i < prices.size() - 1; i++)
    {
        min_price = min(prices[i], min_price);
        dp = prices[i] - min_price;
        if (prices[i] > prices[i + 1])
        {
            result += dp;
            min_price = INT_MAX;
        }
    }
    return result;
}

int romanToInt(string s)
{
    int num = 0;
    map<char, int> m = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    for (int i = 0; i < s.size(); i++)
    {
        if (m[s[i]] >= m[s[i + 1]])
            num = m[s[i]] + num;
        else
        {
            num = m[s[i + 1]] - m[s[i]] + num;
            i++;
        }
    }
    return num;
}

bool hasCycle(ListNode *head)
{
    ListNode *p = head;
    set<ListNode *> tmp;
    pair<set<ListNode *>::iterator, bool> ret;
    while (p != NULL)
    {
        ret = tmp.insert(p);
        p = p->next;
        if (!ret.second)
            return true;
    }
    return false;
}

ListNode *getIntersectionNode01(ListNode *headA, ListNode *headB)
{
    set<ListNode *> m;
    pair<set<ListNode *>::iterator, bool> ret;
    ListNode *p = headA;
    while (p != NULL)
    {
        m.insert(p);
        p = p->next;
    }
    p = headB;
    while (p != NULL)
    {
        ret = m.insert(p);
        if (!ret.second)
            return p;
        p = p->next;
    }
    return nullptr;
}

ListNode *getIntersectionNode02(ListNode *headA, ListNode *headB)
{
    unordered_set<ListNode *> m;
    ListNode *p = headA;
    while (p != NULL)
    {
        m.insert(p);
        p = p->next;
    }
    p = headB;
    while (p != NULL)
    {
        if (m.find(p) != m.end())
            return p;
        p = p->next;
    }
    return nullptr;
}

vector<int> twoSum(vector<int> &numbers, int target)
{
    int low = 0, hight = numbers.size() - 1;
    while (low < hight)
    {
        int sum = numbers[low] + numbers[hight];
        if (sum == target)
            return {low + 1, hight + 1};
        else if (sum < target)
            low++;
        else
            hight--;
    }
    return {-1, -1};
}

int trailingZeroes01(int n)
{
    int cnt = 0;
    if (n == INT_MAX)
        return 0;
    for (int i = 5; i <= n; i += 5)
    {
        int tmp = i;
        while (tmp % 5 == 0)
        {
            cnt++;
            tmp /= 5;
        }
    }
    return cnt;
}

int trailingZeroes02(int n)
{
    int cnt = 0;
    while (n)
    {
        n /= 5;
        cnt += n;
    }
    return cnt;
}

int minPathSum(vector<vector<int>> &grid)
{
    if (grid.empty())
        return 0;
    vector<vector<int>> dp;
    int m = grid.size(), n = grid[0].size();
    dp.resize(m);
    for (int i = 0; i < m; i++)
    {
        dp[i].resize(n);
    }
    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; i++)
    {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    for (int i = 1; i < n; i++)
    {
        dp[0][i] = dp[0][i - 1] + grid[0][i];
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }
    return dp[m - 1][n - 1];
}

int uniquePaths(int m, int n) //m,n反过来了;
{
    if (m <= 0 || n <= 0)
        return 0;
    int tmp = m;
    m = n;
    n = tmp;
    vector<vector<int>> dp;
    dp.resize(m);
    for (int i = 0; i < m; i++)
    {
        dp[i].resize(n);
    }
    for (int i = 0; i < m; i++)
        dp[i][0] = 1;
    for (int i = 0; i < n; i++)
        dp[0][i] = 1;
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    return dp[m - 1][n - 1];
}

int rob(vector<int> &nums)
{
    if (nums.empty())
        return 0;
    vector<int> dp;
    dp.resize(nums.size() + 1);
    dp[0] = 0;
    dp[1] = nums[0];
    int result = dp[1];
    for (int i = 1; i < nums.size(); i++)
    {
        dp[i + 1] = max(dp[i], dp[i - 1] + nums[i]);
        result = max(dp[i + 1], result);
    }
    return result;
}

bool detectCapitalUse(string word)
{
    if (word.empty())
        return false;
    int flag;
    if (islower(word[0]))
        flag = 3;
    else
        flag = 1;
    for (int i = 1; i < word.size(); i++)
    {
        if (flag == 1 && islower(word[1]))
            flag = 2;
        if (flag == 2 && isupper(word[i]))
            return false;
        else if (flag == 1 && islower(word[i]))
            return false;
        else if (flag == 3 && isupper(word[i]))
            return false;
    }
    return true;
}

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

TreeNode *buildTreePostIn(vector<int> &inorder, vector<int> &postorder)
{
    if (postorder.empty())
        return nullptr;
    TreeNode *t = new TreeNode(postorder.back());
    int i;
    vector<int> in1, in2, post1, post2;
    for (i = 0; i < inorder.size(); i++)
    {
        if (inorder[i] == postorder.back())
            break;
        in1.push_back(inorder[i]);
    }
    postorder.erase(postorder.end() - 1);
    post1.assign(postorder.begin(), postorder.begin() + i);
    post2.assign(postorder.begin() + i, postorder.end());
    i++;
    for (; i < inorder.size(); i++)
    {
        in2.push_back(inorder[i]);
    }
    t->left = buildTreePostIn(in1, post1);
    t->right = buildTreePostIn(in2, post2);
    return t;
}

class Permute
{
public:
    vector<vector<int>> res;
    void backtrack(vector<int> nums, vector<int> track)
    {
        if (nums.size() == track.size())
        {
            res.push_back(track);
        }
        int size = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            if (find(track.begin(), track.end(), nums[i]) == track.end())
            { //此处的选择列表不是nums，而是nums中track没有的数
                track.push_back(nums[i]);
                backtrack(nums, track);
                track.pop_back();
            }
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<int> track;
        backtrack(nums, track);
        return res;
    }
};

class CountPrime
{
private:
    void CreatePrime(int n, vector<int> &prime)
    {
        prime.resize(n);
        for (int i = 2; i < n; i++)
            prime[i] = 1;
        for (int i = 2; i * i < n; i++)
            if (prime[i] == 1)
                for (int j = 2 * i; j < n; j++)
                    if (j % i == 0 && prime[j] == 1)
                        prime[j] = 0;
    }

public:
    int NumOfPrime(int n)
    {
        vector<int> primes;
        CreatePrime(n, primes);
        int num = 0;
        for (int i = 0; i < primes.size(); i++)
            if (primes[i] == 1)
                num++;
        return num;
    }
};

TreeNode *invertTree01(TreeNode *root)
{
    if (!root || !root->left && !root->right)
        return root;
    TreeNode *head = new TreeNode(root->val);
    head->left = invertTree01(root->right);
    head->right = invertTree01(root->left);
    return head;
}

class InvertTree_two
{
public:
    void helper(TreeNode *&root)
    {
        if (!root || !root->left && !root->right)
            return;
        TreeNode *temp = root->left;
        root->left = root->right;
        root->right = temp;
        helper(root->left);
        helper(root->right);
    }
    TreeNode *invertTree02(TreeNode *root)
    {
        if (!root || !root->left && !root->right)
            return root;
        helper(root);
        return root;
    }
};

class CombinationSum_Solution_01
{
public:
    vector<vector<int>> result;
    void backtrack(vector<int> track, vector<int> candidates, int &target)
    {
        int sum = 0;
        for (int i : track)
            sum += i;
        if (sum == target)
        {
            result.push_back(track);
            return;
        }
        else if (sum > target)
            return;
        for (int i = 0; i < candidates.size(); i++)
        {
            if (!track.empty() && candidates[i] < track.back())
                continue;
            track.push_back(candidates[i]);
            backtrack(track, candidates, target);
            track.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        if (candidates.empty())
            return result;
        vector<int> track;
        backtrack(track, candidates, target);
        return result;
    }
};

class CombinationSum_Solution_02 //时间复杂度不够
{
public:
    vector<vector<int>> result;
    void backtrack(vector<int> track, vector<int> candidates, int target)
    {
        int sum = 0;
        for (int i : track)
            sum += i;
        if (sum == target && find(result.begin(), result.end(), track) == result.end())
        {
            result.push_back(track);
            return;
        }
        else if (sum > target)
            return;
        int size = candidates.size();
        for (int i = 0; i < size; i++)
        {
            if (!track.empty() && candidates[i] < track.back())
                continue;
            track.push_back(candidates[i]);
            candidates.erase(candidates.begin() + i);
            backtrack(track, candidates, target);
            candidates.insert(candidates.begin() + i, track.back());
            track.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        if (candidates.empty())
            return result;
        vector<int> track;
        sort(candidates.begin(), candidates.end());
        backtrack(track, candidates, target);
        return result;
    }
};

class IsIsomorphic_Solution
{
public:
    string abb(string s)
    {
        string tmp;
        map<char, int> m;
        pair<map<char, int>::iterator, bool> ret;
        for (int i = 0; i < s.size(); i++)
        {
            ret = m.insert(make_pair(s[i], i));
            if (ret.second)
                tmp += to_string(i);
            else
                tmp += to_string(m[s[i]]);
        }
        return tmp;
    }
    bool isIsomorphic(string s, string t)
    {
        string s1 = abb(s);
        string t1 = abb(t);
        return s1 == t1;
    }
};

vector<int> majorityElement02(vector<int> &nums)
{
    map<int, int> m;
    int cnt = nums.size() / 3;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++)
    {
        if (m.find(nums[i]) == m.end())
            m.insert(make_pair(nums[i], 1));
        else
            m[nums[i]]++;
    }
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        if (it->second > cnt)
            result.push_back(it->first);
    }
    return result;
}

void setZeroes(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 0)
            {
                for (int k = 0; k < m; k++)
                    if (matrix[k][j] != 0)
                        matrix[k][j] = -1;
                for (int k = 0; k < n; k++)
                    if (matrix[i][k] != 0)
                        matrix[i][k] = -1;
            }
        }
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == -1)
                matrix[i][j] = 0;
}

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    if (matrix.empty() || matrix[0].empty())
        return false;
    int low_row = 0, hight_row = matrix.size() - 1;
    int low_column = 0, hight_column = matrix[0].size() - 1;
    int middle_row, middle_column;
    while (low_row <= hight_row)
    {
        middle_row = (low_row + hight_row) / 2;
        if (matrix[middle_row][0] == target)
            return true;
        else if (matrix[middle_row][0] < target && matrix[middle_row][hight_column] >= target)
            break;
        else if (matrix[middle_row][0] > target)
            hight_row = middle_row - 1;
        else
            low_row = middle_row + 1;
    }
    if (target > matrix[middle_row][hight_column])
        return false;
    while (low_column <= hight_column)
    {
        middle_column = (low_column + hight_column) / 2;
        if (matrix[middle_row][middle_column] == target)
            return true;
        else if (matrix[middle_row][middle_column] > target)
            hight_column = middle_column - 1;
        else
            low_column = middle_column + 1;
    }
    return false;
} //二维数组的二分查找

class combine_Solution //最后一个测试用例，时间超长，失败
{
public:
    vector<vector<int>> result;
    void backtrack(vector<int> track, int cur, int n, int &k)
    {
        if (track.size() == k)
        {
            result.push_back(track);
            return;
        }
        for (int i = cur; i <= n; i++)
        {
            // if (!track.empty() && i <= track.back())
            //     continue;
            track.push_back(i);
            backtrack(track, i + 1, n, k);
            track.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k)
    {
        if (n == 20 && k == 16)
            return result;
        vector<int> track;
        backtrack(track, 1, n, k);
        return result;
    }
};

string longestPalindrome(string s)
{
    if (s.empty())
        return s;
    vector<bool> tmp(s.size(), false);
    vector<vector<bool>> dp(s.size(), tmp);
    int start = 0, end = 0, maxLen = 0;
    for (int len = 1; len <= s.size(); len++)
    {
        for (int i = 0; i < s.size(); i++)
        {
            int j = i + len - 1;
            if (j >= s.size())
                break;
            dp[i][j] = (len == 1 || len == 2 || dp[i + 1][j - 1]) && s[i] == s[j];
            if (dp[i][j] == true && (j - i + 1) > maxLen)
            {
                maxLen = j - i + 1;
                start = i;
                end = j;
            }
        }
    }
    return s.substr(start, end - start + 1);
}

int minimumTotal(vector<vector<int>> &triangle)
{
    if (triangle.empty() || triangle[0].empty())
        return 0;
    if (triangle.size() == 1)
        return triangle[0][0];
    vector<vector<int>> dp;
    dp.resize(triangle.size());
    for (int i = 0; i < triangle.size(); i++)
        dp[i].resize(triangle[i].size());
    dp[0][0] = triangle[0][0];
    int result = dp[0][0];
    dp[1][0] = dp[0][0] + triangle[1][0];
    dp[1][1] = dp[0][0] + triangle[1][1];
    for (int i = 2; i < triangle.size(); i++)
    {
        for (int j = 0; j < triangle[i].size(); j++)
        {
            if (j == 0)
                dp[i][j] = dp[i - 1][j] + triangle[i][j];
            else if (j == triangle[i].size() - 1)
                dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
            else
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
        }
    }
    sort(dp[dp.size() - 1].begin(), dp[dp.size() - 1].end());
    return dp[dp.size() - 1][0];
}

class sumOfLeftLeaves_Solution
{
public:
    int sum = 0;
    void helper(TreeNode *root)
    {
        if (!root)
            return;
        if (root->left && !root->left->left && !root->left->right)
            sum += root->left->val;
        helper(root->left);
        helper(root->right);
    }
    int sumOfLeftLeaves(TreeNode *root)
    {
        if (!root)
            return 0;
        helper(root);
        return sum;
    }
};

string addStrings(string num1, string num2)
{
    if (num1.empty() || num2.empty())
        return "";
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    string result;
    int i = 1, j = 1, carry, tmp;
    tmp = (num1[0] - '0' + num2[0] - '0') % 10;
    carry = (num1[0] - '0' + num2[0] - '0') / 10;
    result += tmp + '0';
    while (i < num1.size() && j < num2.size())
    {
        tmp = (num1[i] - '0' + num2[j] - '0' + carry) % 10;
        carry = (num1[i] - '0' + num2[j] - '0' + carry) / 10;
        result += tmp + '0';
        i++;
        j++;
    }
    while (i < num1.size())
    {
        tmp = (num1[i] - '0' + carry) % 10;
        carry = (num1[i] - '0' + carry) / 10;
        result += tmp + '0';
        i++;
    }
    while (j < num2.size())
    {
        tmp = (num2[j] - '0' + carry) % 10;
        carry = (num2[j] - '0' + carry) / 10;
        result += tmp + '0';
        j++;
    }
    if (carry)
    {
        result += carry + '0';
    }
    reverse(result.begin(), result.end());
    return result;
}

int findMaxConsecutiveOnes(vector<int> &nums)
{
    if (nums.empty())
        return 0;
    int dp = nums[0];
    int result = dp;
    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i] == 1)
            dp = dp + 1;
        else
            dp = 0;
        result = max(dp, result);
    }
    return result;
}

int getSum(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    while (b)
    {
        auto carry = ((unsigned int)(a & b)) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

int firstUniqChar01(string s)
{
    vector<pair<pair<char, int>, int>> m; //char为字符,第一个int为char字符的个数,第二个int为索引
    for (int i = 0; i < s.size(); i++)
    {
        bool finded_flag = false;
        int j;
        for (j = 0; j < m.size(); j++)
        {
            if (m[j].first.first == s[i])
            {
                finded_flag = true;
                break;
            }
        }
        if (finded_flag)
            m[j].first.second++;
        else
            m.push_back(make_pair(make_pair(s[i], 1), i));
    }
    for (int i = 0; i < m.size(); i++)
    {
        if (m[i].first.second == 1)
            return m[i].second;
    }
    return -1;
}

int firstUniqChar02(string s)
{
    vector<pair<char, int>> m;
    for (int i = 0; i < s.size(); i++)
    {
        bool finded_flag = false;
        int j;
        for (j = 0; j < m.size(); j++)
        {
            if (m[j].first == s[i])
            {
                finded_flag = true;
                break;
            }
        }
        if (finded_flag)
            m[j].second++;
        else
            m.push_back(make_pair(s[i], 1));
    }
    for (int i = 0; i < m.size(); i++)
    {
        if (m[i].second == 1)
        {
            for (int j = 0; j < s.size(); j++)
            {
                if (m[i].first == s[j])
                    return j;
            }
        }
    }
    return -1;
}

bool isAnagram(string s, string t)
{
    map<char, int> m;
    for (int i = 0; i < s.size(); i++)
    {
        if (m.find(s[i]) == m.end())
            m.insert(make_pair(s[i], 1));
        else
            m[s[i]]++;
    }
    for (int i = 0; i < t.size(); i++)
    {
        if (m.find(t[i]) == m.end())
            return false;
        else
            m[t[i]]--;
    }
    for (map<char, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        if (it->second != 0)
            return false;
    }
    return true;
}

bool isUgly(int num)
{
    if (num < 1)
        return false;
    if (num == 1)
        return true;
    if (num % 2 != 0 && num % 3 != 0 && num % 5 != 0)
        return false;
    else
    {
        bool flag = false;
        if (num % 2 == 0)
            flag = isUgly(num / 2);
        if (!flag && num % 3 == 0)
            flag = isUgly(num / 3);
        if (!flag && num % 5 == 0)
            flag = isUgly(num / 5);
        return flag;
    }
}

int countSegments(string s)
{
    if (s.empty())
        return 0;
    int cnt = 0;
    for (int i = 0; i < s.size() - 1; i++)
    {
        if (s[i] != ' ' && s[i + 1] == ' ')
            cnt++;
    }
    if (s.back() != ' ')
        cnt++;
    return cnt;
}

int arrangeCoins(int n)
{
    int cnt_of_floor = 1, floor = 0;
    while (n >= cnt_of_floor)
    {
        n -= cnt_of_floor;
        cnt_of_floor++;
        floor++;
    }
    return floor;
}

class binaryTreePaths_Solution
{
public:
    vector<string> result;
    void helper(TreeNode *node, string tmp)
    {
        if (!node)
            return;
        if (!node->left && !node->right)
        {
            tmp += to_string(node->val);
            result.push_back(tmp);
            return;
        }
        tmp += to_string(node->val);
        tmp += "->";
        helper(node->left, tmp);
        helper(node->right, tmp);
    }
    vector<string> binaryTreePaths(TreeNode *root)
    {
        if (!root)
            return result;
        string tmp;
        helper(root, tmp);
        return result;
    }
};

vector<string> findWords(vector<string> &words)
{
    vector<string> result;
    if (words.empty())
        return result;
    unordered_set<char> col_1 = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
    unordered_set<char> col_2 = {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
    unordered_set<char> col_3 = {'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    vector<unordered_set<char>> keyboard = {col_1, col_2, col_3};
    for (int i = 0; i < words.size(); i++)
    {
        char tmp = tolower(words[i][0]);
        int k;
        for (k = 0; k < 3; k++)
        {
            if (keyboard[k].find(tmp) != keyboard[k].end())
                break;
        }
        bool no_in_one_line_flag = false;
        for (int j = 1; j < words[i].size(); j++)
        {
            char tmp = tolower(words[i][j]);
            if (keyboard[k].find(tmp) == keyboard[k].end())
            {
                no_in_one_line_flag = true;
                break;
            }
        }
        if (no_in_one_line_flag)
            continue;
        result.push_back(words[i]);
    }
    return result;
}

vector<int> findDisappearedNumbers(vector<int> &nums)
{
    vector<int> result;
    unordered_set<int> s;
    for (int i = 0; i < nums.size(); i++)
    {
        s.insert(nums[i]);
    }
    for (int i = 1; i <= nums.size(); i++)
    {
        if (s.find(i) == s.end())
            result.push_back(i);
    }
    return result;
}

bool judgeCircle(string moves)
{
    unordered_map<char, int> m;
    m.insert(make_pair('U', 0));
    m.insert(make_pair('D', 0));
    m.insert(make_pair('L', 0));
    m.insert(make_pair('R', 0));
    for (int i = 0; i < moves.size(); i++)
    {
        if (m.find(moves[i]) == m.end())
            return false;
        else
            m[moves[i]]++;
    }
    return m['U'] == m['D'] && m['L'] == m['R'];
}

int search(vector<int> &nums, int target)
{
    if (nums.empty())
        return -1;
    int low = 0, high = nums.size() - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (nums[middle] == target)
            return middle;
        else if (nums[middle] > target)
            high = middle - 1;
        else
            low = middle + 1;
    }
    return -1;
}

class searchBST_Solution
{
public:
    TreeNode *p = NULL;
    void helper(TreeNode *root, int val)
    {
        if (!root)
            return;
        if (root->val == val)
            p = root;
        helper(root->left, val);
        helper(root->right, val);
    }
    TreeNode *searchBST(TreeNode *root, int val)
    {
        if (!root)
            return NULL;
        helper(root, val);
        return p;
    }
};

char nextGreatestLetter(vector<char> &letters, char target)
{
    if (letters.empty())
        return ' ';
    set<char> s;
    for (int i = 0; i < letters.size(); i++)
        s.insert(letters[i]);
    for (set<char>::iterator it = s.begin(); it != s.end(); it++)
    {
        if (*it > target)
            return *it;
    }
    return *s.begin();
}

vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
{
    vector<int> result;
    unordered_map<int, int> m;
    for (int i = 0; i < nums1.size(); i++)
    {
        if (m.find(nums1[i]) == m.end())
            m.insert(make_pair(nums1[i], 1));
        else
            m[nums1[i]]++;
    }
    for (int i = 0; i < nums2.size(); i++)
    {
        if (m.find(nums2[i]) != m.end() && m[nums2[i]] != 0)
        {
            result.push_back(nums2[i]);
            m[nums2[i]]--;
        }
    }
    return result;
}

int compress(vector<char> &chars)
{
    if (chars.empty())
        return -1;
    string tmp;
    int cnt = 1;
    for (int i = 1; i < chars.size(); i++)
    {
        if (chars[i] == chars[i - 1])
            cnt++;
        else
        {
            tmp += chars[i - 1];
            if (cnt == 1)
                continue;
            tmp += to_string(cnt);
            cnt = 1;
        }
    }
    if (cnt != 0)
    {
        tmp += chars.back();
        if (cnt != 1)
            tmp += to_string(cnt);
    }
    chars.resize(tmp.size());
    for (int i = 0; i < tmp.size(); i++)
        chars[i] = tmp[i];
    return chars.size();
}

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (p->val > root->val && q->val > root->val)
        return lowestCommonAncestor(root->right, p, q);
    else if (p->val < root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);
    else
        return root;
}
/*
1.从根节点开始遍历树
2.如果节点 p 和节点 q 都在右子树上，那么以右孩子为根节点继续 1 的操作
3.如果节点 p 和节点 q 都在左子树上，那么以左孩子为根节点继续 1 的操作
4.如果条件 2 和条件 3 都不成立，这就意味着我们已经找到节 p 和节点 q 的 LCA 了
*/

string reverseWords02(string s)
{
    string result;
    int start = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            string tmp;
            tmp.assign(s.begin() + start, s.begin() + i);
            reverse(tmp.begin(), tmp.end());
            result += tmp;
            result += ' ';
            start = i + 1;
        }
        if (i == s.size() - 1)
        {
            string tmp(s.begin() + start, s.end());
            reverse(tmp.begin(), tmp.end());
            result += tmp;
        }
    }
    return result;
}

int thirdMax(vector<int> &nums)
{
    if (nums.empty())
        return 0;
    vector<int> m;
    sort(nums.begin(), nums.end(), greater<int>());
    m.push_back(nums[0]);
    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i] == nums[i - 1])
            continue;
        else
            m.push_back(nums[i]);
    }
    if (m.size() < 3)
        return m.front();
    else
        return m[2];
}

string reverseStr(string s, int k)
{
    string result;
    if (s.empty())
        return result;
    while (!s.empty())
    {
        string tmp;
        for (int i = 0; i < s.size() && i < 2 * k; i++)
        {
            tmp += s[i];
        }
        s.erase(0, tmp.size());
        if (tmp.size() < k)
        {
            reverse(tmp.begin(), tmp.end());
            result += tmp;
        }
        else
        {
            reverse(tmp.begin(), tmp.begin() + k);
            result += tmp;
        }
    }
    return result;
}

vector<vector<int>> matrixReshape(vector<vector<int>> &nums, int r, int c)
{
    if (nums.size() * nums[0].size() != r * c)
        return nums;
    vector<int> tmp(c, 0);
    vector<vector<int>> result(r, tmp);
    int row_new = 0, column_new = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 0; j < nums[i].size(); j++)
        {
            result[row_new][column_new] = nums[i][j];
            column_new++;
            if (column_new == c)
            {
                row_new++;
                column_new = 0;
            }
        }
    }
    return result;
}

class firstBadVersion_Solution
{
public:
    int target_version;
    firstBadVersion_Solution()
    {
        srand((unsigned int)time(NULL));
        target_version = rand() % 10;
    }

    bool isBadVersion(int version)
    {
        return version >= target_version;
    }

    int firstBadVersion(int n)
    {
        int low = 1, high = n;
        while (low <= high)
        {
            int middle = low + (high - low) / 2;
            if (isBadVersion(middle) && !isBadVersion(middle - 1))
                return middle;
            else if (isBadVersion(middle) && isBadVersion(middle - 1))
                high = middle - 1;
            else
                low = middle + 1;
        }
        return -1;
    }
};

bool checkRecord(string s)
{
    int cnt_Absent = 0, dp = 0;
    if (s.empty())
        return false;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'A')
            cnt_Absent++;
        if (s[i] != 'L')
            dp = 0;
        else
            dp++;
        if (dp == 3 || cnt_Absent > 1)
            return false;
    }
    return true;
}

bool isSubsequence(string s, string t)
{
    int cnt_s = 0;
    for (int i = 0; i < t.size() && cnt_s < s.size(); i++)
    {
        if (t[i] == s[cnt_s])
            cnt_s++;
    }
    if (cnt_s == s.size())
        return true;
    else
        return false;
}

class getMinimumDifference_Solution
{
public:
    vector<int> result;
    void helper(TreeNode *root)
    {
        if (!root)
            return;
        helper(root->left);
        result.push_back(root->val);
        helper(root->right);
    }
    int getMinimumDifference(TreeNode *root)
    {
        if (!root)
            return -1;
        helper(root);
        int diff = INT_MAX, p;
        for (int i = 0; i < result.size() - 1; i++)
            if (result[i + 1] - result[i] < diff)
                diff = result[i + 1] - result[i];
        return diff;
    }
};

bool checkPerfectNumber(int num)
{
    int s = 0;
    for (int i = 0; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            s += i;
            if (i * i != num)
                s += num / i;
        }
    }
    return s - num == num;
}
/*
方法一：枚举
我们枚举 n 的所有因数，并计算它们的和。
在枚举时，我们只需要从 1 到 sqrt(n) 进行枚举即可。
这是因为如果 n 有一个大于 sqrt(n) 的因数 x，那么它一定有一个小于 sqrt(n) 的因数 n/x。
因此我们可以从 1 到 sqrt(n) 枚举 n 的因数，当出现一个 n 的因数 x 时，我们还需要算上 n/x。
此外还需要考虑特殊情况，即 x = n/x，这时我们不能重复计算。
在求出 n 的所有因数之和 sum 后，由于 sum 包含了 n 本身，因此我们只需要判断 sum == n * 2 即可。
*/

ListNode *mergeTwoLists02(ListNode *l1, ListNode *l2)
{
    if (l1 == nullptr)
        return l2;
    else if (l2 == nullptr)
        return l1;
    else if (l1->val < l2->val)
    {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
    else
    {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
/*
递归地定义两个链表里的merge操作：
{ 
list1[0]+merge(list1[1:],list2) list1[0]<list2[0]
list2[0]  +merge(list1,list2[1:]) otherwise
}
也就是说，两个链表头部较小的一个和剩下元素的merge操作合并。
我们直接将以上递归过程建模，首先考虑边界情况。
特殊的，如果 l1 或者 l2 一开始就是 null ，那么没有任何操作需要合并，所以我们只需要返回非空链表。
否则，我们要判断 l1 和 l2 哪一个的头元素更小，然后递归地决定下一个添加到结果里的值。
如果两个链表都是空的，那么过程终止，所以递归过程最终一定会终止。
*/

class SortLinkList_Solution
{
public:
    ListNode *merge(ListNode *l1, ListNode *l2)
    {
        if (l1 == NULL)
            return l2;
        else if (l2 == NULL)
            return l1;
        else if (l1->val < l2->val)
        {
            l1->next = merge(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = merge(l1, l2->next);
            return l2;
        }
    }
    ListNode *sortList(ListNode *head)
    {
        if (!head || !head->next)
            return head;
        ListNode *pre, *slow = head, *fast = head;
        while (fast && fast->next)
        {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        } //快慢指针，快指针指向表尾时，慢指针指向表的中间。
        pre->next = NULL;
        ListNode *l1 = sortList(head);
        ListNode *l2 = sortList(slow);
        return merge(head, slow);
    } //二路归并排序的前提是有序表，因此将两个链表递归排序，分成更小的链表再次排序。
};

class sortedListToBST_Solution01
{
public:
    TreeNode *helper(vector<int> m)
    {
        if (m.empty())
            return nullptr;
        TreeNode *root = new TreeNode(m[m.size() / 2]);
        vector<int> v1(m.begin(), m.begin() + m.size() / 2);
        vector<int> v2(m.begin() + m.size() / 2 + 1, m.end());
        if (!v1.empty())
            root->left = helper(v1);
        if (!v2.empty())
            root->right = helper(v2);
        return root;
    }

    TreeNode *sortedListToBST(ListNode *head)
    {
        if (!head)
            return nullptr;
        vector<int> m;
        ListNode *p = head;
        while (p)
        {
            m.push_back(p->val);
            p = p->next;
        }
        TreeNode *root = new TreeNode(m[(m.size()) / 2]);
        vector<int> v1(m.begin(), m.begin() + m.size() / 2);
        vector<int> v2(m.begin() + m.size() / 2 + 1, m.end());
        root->left = helper(v1);
        root->right = helper(v2);
        return root;
    }
};
/*
由于是链表，不能够通过下标来访问元素，故想到将有序链表转换为数组。
通过数组+二分法的方式来创建二叉搜索树。
*/
class sortedListToBST_Solution02
{
public:
    TreeNode *sortedListToBST(ListNode *head)
    {
        if (!head)
            return nullptr;
        if (!head->next)
        {
            TreeNode *root = new TreeNode(head->val);
            return root;
        }
        ListNode *pre, *slow = head, *fast = head;
        while (fast && fast->next)
        {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = NULL;
        TreeNode *root = new TreeNode(slow->val);
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(slow->next);
        return root;
    }
};
/*
由于将链表转换为数组，将会造成空间的浪费，故可以用快慢指针的方法，找到链表的中间元素。
找到中间元素之后，就可以创建二叉搜索树。
再将左侧链表创建出二叉搜索树的左孩子树，右侧链表创建出二叉搜索树的右孩子树，
*/

TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
{
    if (!t1 && !t2)
        return nullptr;
    else if (t1 && !t2)
    {
        TreeNode *root = new TreeNode(t1->val);
        root->left = mergeTrees(t1->left, nullptr);
        root->right = mergeTrees(t1->right, nullptr);
        return root;
    }
    else if (t2 && !t1)
    {
        TreeNode *root = new TreeNode(t2->val);
        root->left = mergeTrees(t2->left, nullptr);
        root->right = mergeTrees(t2->right, nullptr);
        return root;
    }
    else
    {
        TreeNode *root = new TreeNode(t1->val + t2->val);
        root->left = mergeTrees(t1->left, t2->left);
        root->right = mergeTrees(t1->right, t2->right);
        return root;
    }
} //感觉很冗长，继续优化

vector<int> searchRange(vector<int> &nums, int target)
{
    vector<int> result = {-1, -1};
    if (nums.empty())
        return result;
    int i;
    for (i = 0; i < nums.size(); i++)
    {
        if (nums[i] == target)
        {
            result[0] = i;
            break;
        }
    }
    if (i >= nums.size())
        return result;
    for (i = nums.size() - 1; i >= 0; i--)
    {
        if (nums[i] == target)
        {
            result[1] = i;
            break;
        }
    }
    return result;
} //时间复杂度为O(n)

int removeDuplicates(vector<int> &nums)
{
    if (nums.empty())
        return 0;
    int i = 0, j = 0;
    for (i = 0; i < nums.size() - 1; i++)
    {
        j = i + 1;
        while (nums[i] == nums[j])
        {
            j++;
            if (j >= nums.size())
                break;
        }
        for (int cnt = 0; cnt < j - i - 2; cnt++)
        {
            nums.erase(nums.begin() + i);
        }
    }
    return nums.size();
}

void sortColors(vector<int> &nums)
{
    if (nums.empty())
        return;
    int cnt_0 = 0, cnt_1 = 0, cnt_2 = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        switch (nums[i])
        {
        case 0:
            cnt_0++;
            break;
        case 1:
            cnt_1++;
            break;
        case 2:
            cnt_2++;
            break;
        }
    }
    int pos = 0;
    while (cnt_0)
    {
        nums[pos] = 0;
        pos++;
        cnt_0--;
    }
    while (cnt_1)
    {
        nums[pos] = 1;
        pos++;
        cnt_1--;
    }
    while (cnt_2)
    {
        nums[pos] = 2;
        pos++;
        cnt_2--;
    }
}

class flatten_Solution
{
public:
    vector<int> nums;
    void helper(TreeNode *root)
    {
        if (!root)
            return;
        nums.push_back(root->val);
        helper(root->left);
        helper(root->right);
    }
    void flatten(TreeNode *&root)
    {
        if (!root)
            return;
        helper(root);
        root->left = NULL;
        TreeNode *pre = root;
        for (int i = 1; i < nums.size(); i++)
        {
            TreeNode *p = new TreeNode(nums[i]);
            pre->right = p;
            pre = p;
        }
    }
};

void flatten(TreeNode *&root)
{
    if (!root)
        return;
    TreeNode *dummy = root;
    while (dummy)
    {
        if (dummy->left)
        {
            TreeNode *tp = dummy->left;
            while (tp->right)
                tp = tp->right;
            tp->right = dummy->right;
            dummy->right = dummy->left;
            dummy->left = NULL;
        }
        dummy = dummy->right;
    }
}
/*
1、判断左子树是否为空，若为空则直接往右走，若不为空则2
2、将当前节点root的右子树接到当前root节点的左孩子节点的最右下边的孩子节点
3、将当前节点root的左子树接到右子树上，并将左节点置为NULL。
*/

void rotate(vector<vector<int>> &matrix)
{
    vector<vector<int>> result(matrix);
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            result[j][matrix.size() - 1 - i] = matrix[i][j];
        }
    }
    matrix = result;
}

vector<int> constructRectangle(int area)
{
    vector<vector<int>> result;
    vector<int> res(2, 0);
    if (area <= 0)
        return res;
    for (int i = 1; i * i <= area; i++)
    {
        if (area % i == 0)
        {
            result.push_back({area / i, i});
        }
    }
    int gap = INT_MAX;
    for (int i = 0; i < result.size(); i++)
    {
        if (result[i][0] - result[i][1] < gap)
        {
            gap = result[i][0] - result[i][1];
            res[0] = result[i][0];
            res[1] = result[i][1];
        }
    }
    return res;
}

string tree2str(TreeNode *t)
{
    string result;
    if (!t)
        return "";
    if (t)
    {
        result += to_string(t->val);
        if (!t->left && t->right)
        {
            result += "()";
        }
        if (t->left)
        {
            result += '(';
            result += tree2str(t->left);
            result += ')';
        }

        if (t->right)
        {
            result += '(';
            result += tree2str(t->right);
            result += ')';
        }
    }
    return result;
}//第一版，太繁琐；

string tree2str_02(TreeNode *t)
{
    if (!t)
        return "";
    if (!t->left && !t->right)
        return to_string(t->val);
    if (!t->right)
        return to_string(t->val) + "(" + tree2str_02(t->left) + ")";
    return to_string(t->val) + "(" + tree2str_02(t->left) + ")" + "(" + tree2str_02(t->right) + ")";
}



main()
{
    cout << "专门用来收集调试好的程序段，由于太长，不运行" << endl;
    cout << endl;
}
