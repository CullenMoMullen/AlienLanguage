// AlienLanguage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>

using namespace std;

typedef struct edge_ {
    char to;
    char from;
} edge_t;

string dict[] = { "baa", "abcd", "abca", "cab", "cad" };
int main()
{
    map<char,edge_t> verts;
    set<char> vertSet;
    int num_words = sizeof(dict) / sizeof(string);
    cout << "Num Words: " << num_words << endl;
    cout << "Alphabetical List of Alien Words:" << endl;
    cout << "--------------------------------" << endl;

    
    //Go through all of the letters in all of the words, adding each letter to a set
    //thus no repeats
    for (int i = 0; i < num_words; i++) {
        cout << i + 1 << ". " << dict[i] << endl;
        for (int j = 0; j < dict[i].size(); j++) {
            vertSet.insert(dict[i][j]);
        }
    }


    //Print out the letters in un-alphabetized order
    cout << "Letters: ";
    int i = 0;
    for (set<char>::iterator itr = vertSet.begin(); vertSet.end() != itr; ++itr, i++) {
        cout << *itr;
        if (i == vertSet.size() - 1) {
             cout << endl;
        }
        else {
            cout << ", ";
        }

        verts[*itr].from = 0;
        verts[*itr].to = 0;
    }

    //Compare adjacent words in dictionary letter for letter
    //When you find a mismatch then you know the the first word's
    //current letter comes prior to second word's current letter
    //make an edge, but if the destination already is pointed to by
    //an edge then take care to re-assign its from node's to edge to the first
    //word's current letter
    for (int i = 0; i < num_words - 1; i++) {
        string& str1 = dict[i];
        string& str2 = dict[i + 1];
        const char* c1 = str1.c_str();
        const char* c2 = str2.c_str();
        cout << endl << "Comparing:" << endl;
        cout << str1 << endl << str2 << endl;
        while (*c1 == *c2) {
            c1++; c2++;
        }
        //we need an edge from c1 to c2
        if (verts[*c2].from != 0) {
            verts[verts[*c2].from].to = *c1;
        }
        verts[*c1].to = *c2;
        verts[*c2].from = *c1;
    }

    //find the first letter in the alphabet (it will not have a from value)
    char firstLetter;
    for (auto itr = vertSet.begin(); itr != vertSet.end(); ++itr) {
        if (verts[*itr].from == 0) {
            firstLetter = *itr;
            break;
        }
    }
    cout << endl << "Alphabet: ";
    i = 0;
    while (firstLetter) {
        if (i++ == vertSet.size() - 1)
            cout << firstLetter << endl;
        else
            cout << firstLetter << ", ";
    
        firstLetter = verts[firstLetter].to;
    }
}
