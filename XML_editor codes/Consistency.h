#ifndef CONSISTENCY_H
#define CONSISTENCY_H

#include <string>
using namespace std;
#include <stack>
#include <string>
#include <queue>
#include <fstream>
#include <vector>
#include <sstream>

int countSpace(string s);
void consistency(string FileLocIn, string FileOutCorrect, string FileOutError, bool returnerror);
string tab(int);
string space1(int);
void putErrorArrows(queue<string>&, int, int);

#endif // CONSISTENCY_H
