#include "compress.h"
using namespace std;

vector<int> compress1(string input, string outfile) {
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
