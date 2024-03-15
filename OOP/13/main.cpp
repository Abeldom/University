// Domokos Abel
// 411

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool cmp(pair<string, int>& a,
    pair<string, int>& b)
{
    return a.second < b.second;
}

int main()
{
    ifstream in("Dickens.txt");
    map<string, int> szavak;

    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            for (int itr = 0; itr < word.size(); itr++) {
                word[itr] = tolower(word[itr]);
                if (word[itr] < 97 || word[itr] > 122) {
                    word.erase(itr);
                    itr--;
                }
            }
            // cout << "belep:" << word << ":" << endl;
            if (szavak.find(word) == szavak.end()) {
                szavak.insert(pair<string, int>(word, 1));
            } else {
                szavak[word]++;
            }
        }
    }

    map<string, int>::iterator itr;
    for (itr = szavak.begin(); itr != szavak.end(); itr++) {
        cout << itr->first << " " << itr->second << endl;
    }

    vector<pair<string, int>> myvector(szavak.begin(), szavak.end());
    sort(myvector.begin(), myvector.end(), cmp);

    for (auto itr = myvector.begin(); itr != myvector.end(); itr++) {
        cout << itr->first << " " << itr->second << endl;
    }

    return 0;
}