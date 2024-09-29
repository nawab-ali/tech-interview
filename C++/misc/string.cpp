#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

using namespace std;

void string_tests(void) {
    string s1 = string("This is a test.");
    cout << s1 << endl;
    cout << s1.length() << endl;
    s1.erase(s1.begin(), s1.begin() + 5);
    cout << s1 << endl;
    s1.append(" Another test.");
    cout << s1 << endl;
    cout << s1.find("test") << endl;
    cout << s1.substr(10);
}

vector <string> tokenize_string(const string &str, const char sep) {
    vector <string> tokens;

    boost::split(tokens, str, [&sep](const char c) { return (c == sep); });

    for (auto &token : tokens) {
        boost::trim(token);
        boost::to_lower(token);
    }

    return (tokens);
}

long num_words(const string &text, const char sep) {
    vector <string> tokens;

    tokens = tokenize_string(text, sep);

    return (tokens.size());
}

long num_chars(const string &text) {
    return (text.length());
}

void wc(string filename) {
    ifstream file(filename);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    } else {
        throw runtime_error("Unable to open file");
    }
}

void word_freq(const vector <string> &words) {
    unordered_map<string, int> umap;

    for (const auto &word : words) {
        if (umap.find(word) == umap.end()) {
            umap[word] = 1;
        } else {
            umap[word] += 1;
        }
    }

    for (const auto &pair : umap) {
        cout << pair.first << ":" << pair.second << endl;
    }
}

int main(int argc, char **argv) {
    const char sep = ' ';
    vector <string> tokens;
    string text = "Let me split this into words Let me split";
    string filename = "C:\\wpm_log.txt";

    //string_tests();
    tokens = tokenize_string(text, sep);
    for (const auto &token : tokens) {
        cout << token << endl;
    }

    cout << num_words(text, sep) << ", " << num_chars(text) << endl;

    try {
        wc(filename);
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    word_freq(tokens);

    return 0;
}