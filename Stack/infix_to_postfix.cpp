#include <iostream>
#include <stack>
#include <set>
#include <string>

using namespace std;

//  ch      #       (       */%     +-      )
//  isp     0       1       5       3       6
//  icp     0       6       4       2       1

set<char> operator_set = {'#', '(', '*', '/', '%', '+', '-', ')'};

int isp(char ch) {//transform operator into in stack priority
    switch (ch) {
        case '#': return 0;
        case '(': return 1;
        case '*': case '/': case '%': return 5;
        case '+': case '-': return 3;
        case ')': return 6;
    }
    return 0;
}

int icp(char op) {//transform operator into in coming priority
    switch (op) {
        case '#': return 0;
        case '(': return 6;
        case '*': case '/': case '%': return 4;
        case '+': case '-': return 2;
        case ')': return 1;
    }
    return 0;
}

bool isop(char ch) {
    if (operator_set.find(ch) != operator_set.end())
        return true;
    else
        return false;
}

void in_to_post(string infix) {
    int size = infix.length();
    stack<char> post_stack;
    post_stack.push('#');
    int index = 0;
    while (index < size && !post_stack.empty()) {
        char ch = infix[index];
        if (!isop(ch)) {//if ch is a number, then directly cout
            cout << ch - '0';
            index++;
        }
        else {
            char op = post_stack.top();
            if (icp(ch) > isp(op)) {//if the coming operator > stack operator, in stack
                post_stack.push(ch);
                index++;
                continue;
            }
            else if (icp(ch) < isp(op)) {//if the coming operator < stack operator, pop and cout
                cout << post_stack.top();
                post_stack.pop();
                continue;
            }
            else {//if the coming operator == stack operator, pop but not cout, if pop '(', continue
                char pop = post_stack.top();
                post_stack.pop();
                if (pop == '(')
                    index++;
            }
        }
    }
    /*for (int i = 0; i < size; i++) {
        char ch = infix[i];
        if (!isop(ch))//if ch is a number, then directly cout
            cout << infix[i] - '0';
        else {
            char op = post_stack.top();
            if (icp(ch) > isp(op)) {//if the coming operator > stack operator, in stack
                post_stack.push(ch);
                continue;
            }
            else if (icp(ch) < isp(op)) {//if the coming operator < stack operator, pop and cout
                cout << post_stack.top();
                post_stack.pop();
                continue;
            }
            else {//if the coming operator == stack operator, pop but not cout, if pop '(', continue
                char pop = post_stack.top();
                post_stack.pop();
                if (pop == '(')
                    continue;
            }
        }
    }*/
}

int main() {
    string infix;
    cin >> infix;
    in_to_post(infix);
    return 0;
}