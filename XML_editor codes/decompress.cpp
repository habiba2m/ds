#include "decompress.h"
#include<ostream>
#include <fstream>
#include <iostream>
using namespace std;
vector<int> compress(string input,string outfile) {
    unordered_map <string, int> mapp;
    for (int i = 0; i < 256; i++) {
        string charac = "";
        charac += char(i);
        mapp[charac] = i;
    }

    string p = "", c = "";
    p += input[0];
    int code = 256;
    vector<int> out;
    for (int i = 0; i < input.length(); i++) {
        if (i != input.length() - 1) {
            c += input[i + 1];
        }
        if (mapp.find(p + c) != mapp.end()) {
            p += c;
        }
        else {
            out.push_back(mapp[p]);
            mapp[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    out.push_back(mapp[p]);
    ofstream out1(outfile);
    int size = out.size();
    for (int i = 0; i < size; i++) {
        out1 << out[i];
    }
    return out;
}


string decompress(vector<int> input,string filepath)
{
    string out = "";
    unordered_map<int, string> mapp;
    for (int i = 0; i <= 255; i++) {
        string charac = "";
        charac += char(i);
        mapp[i] = charac;
    }
    int old = input[0], n;
    string s = mapp[old];
    string c = "";
    c += s[0];
    out += s;
    int count = 256;
    for (int i = 0; i < input.size() - 1; i++) {
        n = input[i + 1];
        if (mapp.find(n) == mapp.end()) {
            s = mapp[old];
            s = s + c;
        }
        else {
            s = mapp[n];
        }
        out += s;
        c = "";
        c += s[0];
        mapp[count] = mapp[old] + c;
        count++;
        old = n;
    }
    ofstream out2(filepath);
    out2 << out;
    return out;

}
