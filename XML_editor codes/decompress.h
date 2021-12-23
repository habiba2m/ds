#ifndef DECOMPRESS_H
#define DECOMPRESS_H
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include<string>
using namespace std;


vector<int> compress(string input, string outfile);
string decompress(vector<int> input, string filepath);

#endif // DECOMPRESS_H
