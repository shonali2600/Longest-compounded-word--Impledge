#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int MAX = 32;

class TrieNode {
public:
        bool word_ends;
        vector<TrieNode *> children;
        TrieNode(int arity);
        ~TrieNode();
};

TrieNode :: TrieNode(int arity) {
        word_ends = false;
        for (int i = 0; i < arity; i++) {
                children.push_back(NULL);
        }
}

TrieNode :: ~TrieNode() {
        vector<TrieNode *> :: iterator i = children.begin();
        for (; i != children.end(); ++i)
                if (*i != NULL)
                        delete(*i);
}


class Trie {
        TrieNode *root;
        int arity;
public:
        Trie(int value);
        ~Trie();
        void stripWord(string &word);
        void insertWord(string word);
        bool isCompoundWord(string word, int);
};

Trie :: Trie(int value) {
        arity = value;
        root = new TrieNode(arity);
}

Trie :: ~Trie() {
        delete(root);
}

inline void Trie :: stripWord(string &word) {
        if (*word.rbegin() == '\r') {
                word.erase(word.length() - 1);
        }
}

/* Function to insert a word in the Trie tree */
void Trie :: insertWord(string word) {
        TrieNode *r = root;

        for (string :: iterator i = word.begin(); i != word.end(); ++i) {
                char chr = *i;
                int index = chr - 'a';

                if (r -> children[index] == NULL) {
                        r -> children[index] = new TrieNode(arity);
                }
                r = (TrieNode *)r -> children[index];
        }
        if (!r -> word_ends)
                r -> word_ends = true;
}

/* A recursive function to check whether a given word is compound word */
bool Trie :: isCompoundWord(string word, int word_length) {
        TrieNode *r = root;
        int cnt = 0;
        if (word.empty())
                return true;

        string :: iterator i = word.begin();
        while (i != word.end()) {
                char chr = *i;
                int index = chr - 'a';
                r = r -> children[index];
                if (r != NULL) {
                        if (r -> word_ends) {
                                string suffix = string(word, cnt + 1);
                                if (isCompoundWord(suffix, word_length)) {
                                        if (word.length() != word_length) {
                                                return true;
                                        } else if (suffix.length() == 0) {
                                                return false;
                                        } else {
                                                return true;
                                        }
                                }
                        }
                }
                else {
                        return false;
                }
                i++;
                cnt++;
        }
        if (!(r -> word_ends)) {
                return false;
        }
}

/* Function to get the file to be parsed from the user */
void getFile(char filename[]) {
        ifstream file;
        cout << "Enter filename: ";
        cin >> filename;
        file.open(filename);
        while(!file) {
                cout << "Enter filename: ";
                cin >> filename;
                file.open(filename);
        }
        file.close();
}

/* Function to load all the words from the given file in the Trie tree */
void loadData(Trie &T, char *filename) {
        ifstream file;
        file.open(filename);
        for (string word; getline(file, word);) {
                T.stripWord(word);
                T.insertWord(word);
        }
        file.close();
}

/*  Function to read through the file and check for all the compound words.
    It displays the first and second longest compound word.
 */
void findCompoundedWords(Trie &T, char *filename) {
        string word, longest_word, second_longest_word;
        int c = 0, max_length = 0, second_max_length = 0;

        ifstream file;
        file.open(filename);

        for (string word; getline(file, word);) {
                T.stripWord(word);
                if (T.isCompoundWord(word, word.length())) {
                        c++;
                        if (max_length < word.length()) {
                                second_max_length = max_length;
                                second_longest_word = longest_word;

                                max_length = word.length();
                                longest_word = word;
                        }
                        else {
                                if (second_max_length <= word.length()) {
                                        second_max_length = word.length();
                                        second_longest_word = word;
                                }
                        }
                }
        }
        file.close();
        cout << "First Longest compounded word: " << setw(30) << longest_word << " Length: " << max_length << endl;
        cout << "Second Longest compounded word: " << setw(30) << second_longest_word << " Length: " << second_max_length << endl;
}

int main(int argc, char *argv[]) {
        Trie T(26);
        char filename[MAX];
        auto start = high_resolution_clock::now();
        getFile(filename);
        loadData(T, filename);
        findCompoundedWords(T, filename);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
         cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
        return 0;
}
