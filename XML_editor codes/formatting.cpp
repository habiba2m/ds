#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include <sstream>
#include "Formatting.h"
using namespace std;


int countSpaces(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ')
            return i;
    }

    return -1;
}


string tab(int n)
{
    string tab1 = "    ", st;
    for (int i = 0; i < n; i++)
    {
        st += tab1;
    }
    return st;
}


void format(string FileLocIn, string FileLocOut) {
    ofstream out(FileLocOut);
    stringstream in(FileLocIn);
    stack<string>c;
    queue<string>formatted;
    string line;
    int x = 0;
    while (getline(in, line))
    {

        int opentag = line.find('<') + 1;
        if (c.empty())
        {
            line = line.substr(countSpaces(line));
            formatted.push(line);
            int pos1 = line.find(' ');
            if (pos1 != -1)
                line = line.substr(1, pos1 - 1) + '>';
            else
                line = line.substr(1, line.length() - 1);
            c.push(line);
        }
        else
        {
                 if(countSpaces(line)!=-1)
                if (line[countSpaces(line)] != '<')
                {

                    line = line.substr(countSpaces(line));
                    formatted.push(tab(x + 1) + line);
                }
                else {
                    int index = line.find('>');
                    if (index != line.length() - 1) {
                        line = line.substr(countSpaces(line));
                        formatted.push(tab(x + 1) + line);
                    }
                    else {
                        string y = c.top(), str;
                        str = line.substr(opentag + 1);


                        if (y == str && line.find('/') != -1)
                        {

                            str = tab(x) + "</" + str;
                            formatted.push(str);
                            c.pop();
                            x--;
                        }
                        else {
                            x++;
                            line = line.substr(countSpaces(line));
                            formatted.push(tab(x) + line);
                            int index = line.find(' ');
                            if (index == -1)
                                line = line.substr(1);
                            else
                                line = line.substr(1, index - 1) + '>';
                            c.push(line);
                        }
                    }
                }

            }



    }
    int formatted_size = formatted.size();
    for (int i = 0; i < formatted_size; i++)
    {
        out << formatted.front() << endl;
        formatted.pop();
    }


}
