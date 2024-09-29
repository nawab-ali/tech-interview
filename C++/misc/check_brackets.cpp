//Check if brackets '({[]})' are balanced in src code

#include<stack>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

//Check if brackets '({[]})' are balanced in string expression
bool is_balanced(string expression) {
    stack<char> s;

    for (char c : expression) {
        switch (c) {
            case '[':
            case '(':
            case '{':
                s.push(c);
                break;
            case ']':
                if (s.empty() || s.top() != '[') {
                    return false;
                } else {
                    s.pop();
                }
                break;
            case ')':
                if (s.empty() || s.top() != '(') {
                    return false;
                } else {
                    s.pop();
                }
                break;
            case '}':
                if (s.empty() || s.top() != '{') {
                    return false;
                } else {
                    s.pop();
                }
                break;
            default:
                break;
        }
    }

    //Unbalanced brackets if stack not empty
    return (s.empty());
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <file>" << endl;
        return (1);
    }

    string line;
    ifstream testcases(argv[1]);

    if (testcases.is_open()) {
        while (getline(testcases, line)) {
            cout << line << ": " << is_balanced(line) << endl;
        }
        testcases.close();
    } else {
        cout << "ERROR: Unable to open file " << argv[1] << endl;
        return (1);
    }

    return (0);
}
