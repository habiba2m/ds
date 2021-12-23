#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include <fstream>
#include <vector>
#include "Consistency.h"
using namespace std;

int countSpace(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ')
            return i;
    }

    return -1;
}


string space(int n)
{
    string space = "    ", st;
    for (int i = 0; i < n; i++)
    {
        st += space;
    }
    return st;
}



string space1(int n)
{
    string space = " ", st;
    for (int i = 0; i < n; i++)
    {
        st += space;
    }
    return st;
}

void putErrorArrows(queue<string>& error, int index, int lineLength) {
    string errorLength(index, ' ');
    string lineLengthArrows(lineLength, '^');
    string errorEqual(15, '=');
    error.push(errorLength + lineLengthArrows + errorEqual);
}


void consistency(string FileLocIn, string FileOutCorrect, string FileOutError, bool returnerror)
{
    stringstream in(FileLocIn);

    stack<string> s, tmp;
    stack<int> stackFirstCharIndex;

    queue<string> num, error;

    string line, sp;
    int u = 0;


    while (getline(in, line))
    {
        int firstCharIndex = countSpace(line);
        if (line == "")
            continue;
        if (firstCharIndex != 0 && u == 0)
            u = 1;
        if (s.empty())
        {
            num.push(line);
            error.push(line);
            stackFirstCharIndex.push(firstCharIndex);

            line = line.substr(line.find('<') + 1);
            s.push(line);
        }
        else
        {
            if(firstCharIndex!=-1)
            if (line[firstCharIndex] != '<')
            {
                num.push(line);
                error.push(line);
            }
            else
            {

                int closingTagIndex = line.find('>');
                if (closingTagIndex != line.length() - 1)
                {

                    if ((stackFirstCharIndex.top() == firstCharIndex && u == 1))
                    {
                        num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                        error.push(space1(stackFirstCharIndex.top()));
                        putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());

                        s.pop();
                        stackFirstCharIndex.pop();
                    }


                    if (u == 0 && num.back()[0] != '<')
                    {
                        num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                        error.push(space1(stackFirstCharIndex.top()));
                        putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());

                        s.pop();
                        stackFirstCharIndex.pop();
                    }

                    int ind = line.rfind('>');
                    if (ind == line.length() - 1)
                    {
                        string d, d1, r;
                        r = line.substr(0, firstCharIndex);
                        line = line.substr(firstCharIndex);
                        int tt = line.find(' ');
                        if (tt != -1 && tt < line.find('>'))
                        {
                            d = line.substr(line.find('<') + 1, line.find(' ') - line.find('<') - 1);
                            d1 = line.substr(line.rfind('<') + 2, line.length() - 3 - line.rfind('<'));
                        }
                        else
                        {
                            d = line.substr(line.find('<') + 1, line.find('>') - line.find('<') - 1);
                            d1 = line.substr(line.rfind('<') + 2, line.length() - 3 - line.rfind('<'));
                        }

                        if (d == d1)
                        {
                            num.push(r + line);
                            error.push(r + line);
                        }
                        else
                        {
                            error.push(r + line);
                            putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());

                            line = line.substr(line.find('<'), line.rfind('<') - line.find('<'));
                            num.push(r + line + "</" + d + ">");
                        }
                    }
                    else
                    {
                        string r = line.substr(0, firstCharIndex);
                        line = line.substr(firstCharIndex);
                        int tt = line.find(' ');
                        if (tt != -1 && tt < line.find('>'))
                            num.push(r + line + "</" + line.substr(line.find('<') + 1, (line.find(' ') - line.find('<') - 1)) + ">");
                        else
                            num.push(r + line + "</" + line.substr(line.find('<') + 1, (line.find('>') - line.find('<'))));
                        error.push(r + line);
                        putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());
                    }
                }
                else
                {
                    string co = s.top(), ff;
                    sp = line.substr(0, line.find('<'));
                    ff = line.substr(line.find('<') + 2);
                    if (co == ff)
                    {
                        ff = sp + "</" + ff;
                        num.push(ff);
                        error.push(ff);
                        s.pop();
                        stackFirstCharIndex.pop();

                    }
                    else
                    {
                        int y = 0, yy = 0;



                            if (u == 1 && num.back()[countSpace(num.back())] != '<')
                            {
                                string co = s.top(), ff;
                                sp = line.substr(0, line.find('<'));
                                ff = line.substr(line.find('<') + 2);
                                if (co == ff)
                                {
                                    ff = sp + "</" + ff;
                                    num.push(ff);
                                    error.push(ff);
                                    s.pop();
                                    stackFirstCharIndex.pop();
                                }
                                else
                                {
                                    num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                                    error.push(space1(stackFirstCharIndex.top()));
                                    putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());

                                    s.pop();
                                    stackFirstCharIndex.pop();
                                }
                            }

                        else
                        {
                            while (!s.empty() && line.find('/') != -1 && (line.find('/') - line.find('<') == 1))
                            {
                                string co = s.top(), ff1;
                                ff1 = line.substr(line.find('<') + 2);
                                if (co == ff1)
                                {
                                    y = 1;
                                    break;
                                }

                                y++;
                                tmp.push(s.top());
                                s.pop();

                            }

                            while (!tmp.empty())
                            {
                                s.push(tmp.top());
                                tmp.pop();
                            }

                            if ((stackFirstCharIndex.top() >= firstCharIndex && u == 1) && (line.find('/') == -1 || (line.find('/') - line.find('<') > 1)))
                                y = 1;
                            if (y > 1)
                            {
                                line = line.substr(firstCharIndex);
                                num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                                error.push(space1(stackFirstCharIndex.top()) + line);
                                putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());
                                s.pop();
                                stackFirstCharIndex.pop();
                            }

                            yy = 0;
                            if (((line.find('/') != -1 && (line.find('/') - line.find('<') == 1)) || (stackFirstCharIndex.top() >= firstCharIndex && u == 1)) && y == 1)
                            {
                                yy = 1;
                                if (line.find('/') != -1 && (line.find('/') - line.find('<') == 1))
                                {
                                    int c = 0;
                                    vector<string> vect;
                                    while (c == 0)
                                    {
                                        ff = line.substr(line.find('<') + 2);
                                        if (ff == s.top())
                                        {
                                            c = 1;
                                            num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                                            error.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                                            s.pop();
                                            stackFirstCharIndex.pop();

                                        }
                                        else
                                        {
                                            num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                                            error.push(space1(stackFirstCharIndex.top()));
                                            putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());

                                            s.pop();
                                            stackFirstCharIndex.pop();

                                        }
                                    }
                                }
                                else if (stackFirstCharIndex.top() >= firstCharIndex)
                                {
                                    if (stackFirstCharIndex.top() > firstCharIndex)
                                    {
                                        while (stackFirstCharIndex.top() != firstCharIndex)
                                        {
                                            num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                                            error.push(space1(stackFirstCharIndex.top()));
                                            putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());
                                            s.pop();
                                            stackFirstCharIndex.pop();

                                        }
                                    }

                                    if (stackFirstCharIndex.top() == firstCharIndex)
                                    {
                                        num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());
                                        error.push(space1(stackFirstCharIndex.top()));
                                        putErrorArrows(error, firstCharIndex, stackFirstCharIndex.top());
                                        s.pop();
                                        stackFirstCharIndex.pop();

                                    }

                                    num.push(line);
                                    error.push(line);
                                    stackFirstCharIndex.push(firstCharIndex);
                                    ff = line.substr(line.find('<') + 1);

                                    int index1 = ff.find(' ');
                                    if (index1 != -1)
                                        line = line.substr(line.find('<') + 1, index1) + '>';
                                    else
                                        line = line.substr(line.find('<') + 1);
                                    s.push(line);

                                }
                            }
                        }

                        if ((line.find('/') == -1 || (line.find('/') - line.find('<') > 1)) && yy == 0)
                        {
                            num.push(line);
                            error.push(line);
                            stackFirstCharIndex.push(firstCharIndex);
                            ff = line.substr(line.find('<') + 1);
                            int index1 = ff.find(' ');
                            if (index1 != -1)
                                line = ff.substr(0, index1) + '>';
                            else
                                line = line.substr(line.find('<') + 1);
                            s.push(line);
                        }
                    }
                }
            }
        }
    }

    if (!s.empty())
    {
        while (!s.empty())
        {
            num.push(space1(stackFirstCharIndex.top()) + "</" + s.top());

            error.push(space1(stackFirstCharIndex.top()));
            putErrorArrows(error, stackFirstCharIndex.top(), stackFirstCharIndex.top());
            s.pop();
            stackFirstCharIndex.pop();

        }
    }
    int size1 = num.size();
    int size2 = error.size();
    if (!returnerror)
    {
        ofstream out(FileOutCorrect);
              for (int i = 0; i < size1; i++)
        {
            out << num.front() << endl;
            num.pop();
        }

    }
    else {

        ofstream out2(FileOutError);
        for (int i = 0; i < size2; i++)
        {
            out2 << error.front() << endl;
            error.pop();
        }


    }


}
