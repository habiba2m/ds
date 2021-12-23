#include "tree.h"
#include <stack>
#include<iostream>
using namespace std;

void print_attributes(node*);

string firstTag = "#text";
string textTag = '"' + firstTag + '"';

int FindFirstAngle(string s)
{
    for (int j = 0; j < s.length(); j++)
    {
        if (s[j] != ' ')
            return j;
    }
}


int Num_Of_Angle(string s)
{
    int count = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '<')
            count++;
    }
    return count;
}


vector<string> tokens(string s)
{
    vector<string> a;
    vector<int> spaces;
    int index = s.find('>');
    int count = 0;
    for (int i = 0; i < index + 1; i++)
    {
        if (s[i] == '"')
        {
            count++;
            if (count == 2)
                count = 0;
        }
        if (s[i] == ' ' && count == 0)
            spaces.push_back(i);
    }
    if (spaces.size() > 0)
    {
        a.push_back((s.substr(0, spaces[0])) + '>');
        for (int i = 0; i < spaces.size(); i++)
        {
            if (i < spaces.size() - 1)
                a.push_back(s.substr(spaces[i] + 1, spaces[i + 1] - spaces[i] - 1));
            else
                a.push_back(s.substr(spaces[i] + 1, index - spaces[i] - 1));
        }
    }
    else
        a.push_back(s.substr(0, index + 1));


    return a;
}
node::node(string t)
{
    name = t;
    JsonName = '"' + name.substr(1, name.length() - 2) + '"';
    JsonMark = false;
    level = 0;
    parent = NULL;
}

void node::set_attributes(vector<string> toks)
{
    for (int i = 1; i < toks.size(); i++)
    {
        attribute tr;
        int equal = toks[i].find('=');
        tr.name = '"' + toks[i].substr(0, equal) + '"';
        tr.value = toks[i].substr(equal + 1);
        attrs.push_back(tr);
    }
}
string tab_json(int n)
{
    string tab_json = "    ", st;
    for (int i = 0; i < n; i++)
    {
        st += tab_json;
    }
    return st;
}

vector<vector<node*>> Tree::similar(vector<node*> same)
{
    vector<vector<node*>> a;
    for (int i = 0; i < same.size(); i++)
    {
        vector<node*> temp;
        if (!same[i]->get_Mark())
        {
            temp.push_back(same[i]);
            same[i]->set_Mark(true);
        }
        for (int j = i + 1; j < same.size(); j++)
        {
            if ((same[i]->get_name() == same[j]->get_name()) && (!same[j]->get_Mark()))
            {
                temp.push_back(same[j]);
                same[j]->set_Mark(true);
            }
        }
        if (temp.size() > 0)
            a.push_back(temp);
    }
    for (int i = 0; i < same.size(); i++)
        same[i]->set_Mark(false);
    return a;
}

void Tree::insert(string FileLoc)
{
    ifstream in(FileLoc);
    stack<string> tags;
    stack<int> lvls;
    node* p = NULL;

    while (!in.eof())
    {
        string t;
        getline(in, t);
        int n = FindFirstAngle(t);

        t = t.substr(n);
        vector<string> toks;
        if (t[0] == '<')
            toks = tokens(t);

        if (Empty())
        {
            root = new node(toks[0]);
            p = root;
            root->set_tag(t);
            p->set_attributes(toks);
            tags.push(toks[0]);
            lvls.push(0);
            root->set_lvl(0); continue;
        }

        if (t[0] != '<')
        {
            node* ch = new node();
            ch->set_tag(t);
            ch->set_JsonName(t);
            p->set_child(ch);
            ch->set_lvl(ch->get_parent()->get_lvl() + 1);
        }
        else
        {
            if (t[1] == '/')
            {
                tags.pop(); lvls.pop();
                p = p->get_parent();
            }
            else
            {
                if (Num_Of_Angle(t) == 1)
                {
                    tags.push(toks[0]);
                    lvls.push(lvls.top() + 1);
                    node* ch = new node(toks[0]);
                    p->set_child(ch);
                    p = ch;
                    p->set_tag(t);
                    p->set_attributes(toks);
                    p->set_lvl(lvls.top());
                }
                else if (Num_Of_Angle(t) > 1)
                {
                    int index = t.find('>');
                    int index1 = t.rfind('<');
                    tags.push(toks[0]);
                    lvls.push(lvls.top() + 1);
                    node* ch = new node(toks[0]);
                    p->set_child(ch);
                    p = ch;
                    p->set_tag(t.substr(0, index + 1));
                    p->set_attributes(toks);
                    p->set_lvl(lvls.top());


                    node* text = new node();
                    text->set_tag(t.substr(index + 1, index1 - index - 1));
                    text->set_JsonName(text->get_tag());
                    p->set_child(text);
                    text->set_lvl(text->get_parent()->get_lvl() + 1);
                    tags.pop(); lvls.pop();
                    p = p->get_parent();
                }
            }
        }

    }
    in.close();
}

void Tree::print_attributes(node* n)
{
    for (int i = 0; i < n->get_attributes().size(); i++)
    {
        out << tab_json(n->get_attributes()[i].level + 1) << n->get_attributes()[i].name
            << ": " << n->get_attributes()[i].value << "," << endl;
    }
}




void Tree::print_Json(node* rootptr)
{
    vector<vector<node*>> simChildren;
    if (rootptr->get_tag()[0] == '<')
    {
        if (rootptr->getChildren()[0]->get_tag()[0] == '<')
            simChildren = similar(rootptr->getChildren());
    }

    if (rootptr->get_parent() == NULL)
    {
        out << "{" << endl;
        out << tab_json(rootptr->get_lvl() + 1) << rootptr->get_JsonName() << ":";
        if (rootptr->getChildren().size() > 0 || rootptr->get_attributes().size() > 0)
        {
            out << " {" << endl;
            print_attributes(rootptr);

            for (int i = 0; i < simChildren.size(); i++)
            {
                if (simChildren[i].size() > 1)
                {
                    for (int k = 0; k < simChildren[i].size(); k++)
                    {
                        simChildren[i][k]->set_Mark(true);
                    }
                    out << tab_json(simChildren[i][0]->get_lvl() + 1) << simChildren[i][0]->get_JsonName() << ": [\n";
                    for (int j = 0; j < simChildren[i].size(); j++)
                    {
                        if (simChildren[i][j]->getChildren()[0]->get_tag()[0] != '<' && simChildren[i][j]->get_attributes().size() == 0)
                        {
                            print_Json(simChildren[i][j]);
                        }
                        else if (simChildren[i][j]->getChildren()[0]->get_tag()[0] != '<' && simChildren[i][j]->get_attributes().size() > 0)
                        {
                            print_Json(simChildren[i][j]);
                        }
                        else
                        {
                            out << tab_json(simChildren[i][j]->get_lvl() + 2) << "{\n";
                            print_Json(simChildren[i][j]);
                        }
                        if (simChildren[i][j]->getChildren()[0]->get_tag()[0] != '<')
                        {
                            if (j == simChildren[i].size() - 1)
                                out << "\n";
                            else
                                out << ",\n";
                        }
                        else
                        {
                            if (j == simChildren[i].size() - 1)
                                out << tab_json(simChildren[i][j]->get_lvl() + 2) << "}\n";
                            else
                                out << tab_json(simChildren[i][j]->get_lvl() + 2) << "},\n";

                        }
                    }
                    if (simChildren[i][0]->getChildren()[0]->get_tag()[0] != '<' && simChildren[i][0]->get_attributes().size() == 0)
                        out << tab_json(simChildren[i][0]->get_lvl() + 1) << "]\n";
                    else
                        out << tab_json(simChildren[i][0]->get_lvl() + 1) << "]\n";
                }
                else
                {
                    print_Json(simChildren[i][0]);
                }
            }
            out << tab_json(rootptr->get_lvl() + 1) << "}\n";
        }
        out << "}";
    }

    else if (rootptr->get_tag()[0] != '<')
    {
        if (rootptr->get_parent()->get_attributes().size() > 0)
        {
            out << tab_json(rootptr->get_lvl() + 1) << textTag << ": " << rootptr->get_JsonName() << endl;
        }
        else if (rootptr->get_parent()->get_Mark() == true)
        {
            out << tab_json(rootptr->get_lvl() + 1) << rootptr->get_JsonName();
        }
        else
        {
            out << rootptr->get_JsonName() << ",\n";
        }

    }

    else if (rootptr->getChildren()[0]->get_tag()[0] != '<')
    {
        if (!rootptr->get_Mark())
        {
            out << tab_json(rootptr->get_lvl() + 1) << rootptr->get_JsonName() << ":";
        }
                if (rootptr->get_attributes().size() > 0)
        {
            if (!rootptr->get_Mark())
            {
                out << " {" << endl;
            }
            else
                out << tab_json(rootptr->get_lvl() + 2) << "{\n";

            print_attributes(rootptr);
            for (int i = 0; i < rootptr->getChildren().size(); i++)
            {
                print_Json(rootptr->getChildren()[i]);
            }
            if (!rootptr->get_Mark())
                out << tab_json(rootptr->get_lvl() + 2) << "},\n";
            else
                out << tab_json(rootptr->get_lvl() + 2) << "}";
        }
        else
        {
            out << " ";
            for (int i = 0; i < rootptr->getChildren().size(); i++)
            {
                print_Json(rootptr->getChildren()[i]);
            }
        }

    }

    else
    {
        if (!rootptr->get_Mark())
        {
            out << tab_json(rootptr->get_lvl() + 1) << rootptr->get_JsonName() << ":";
            if (rootptr->getChildren().size() > 0 || rootptr->get_attributes().size() > 0)
            {
                out << " {" << endl;
                print_attributes(rootptr);
            }
        }
        else
            print_attributes(rootptr);

        for (int i = 0; i < simChildren.size(); i++)
        {
            if (simChildren[i].size() > 1)
            {
                for (int k = 0; k < simChildren[i].size(); k++)
                {
                    simChildren[i][k]->set_Mark(true);
                }

                out << tab_json(simChildren[i][0]->get_lvl() + 1) << simChildren[i][0]->get_JsonName() << ": [\n";
                for (int j = 0; j < simChildren[i].size(); j++)
                {
                    if (simChildren[i][j]->getChildren()[0]->get_tag()[0] != '<' && simChildren[i][j]->get_attributes().size() == 0)
                    {
                        print_Json(simChildren[i][j]);
                    }
                    else if (simChildren[i][j]->getChildren()[0]->get_tag()[0] != '<' && simChildren[i][j]->get_attributes().size() > 0)
                    {
                        print_Json(simChildren[i][j]);
                    }
                    else
                    {
                        out << tab_json(simChildren[i][j]->get_lvl() + 2) << "{\n";
                        print_Json(simChildren[i][j]);
                    }
                    if (simChildren[i][j]->getChildren()[0]->get_tag()[0] != '<')
                    {
                        if (j == simChildren[i].size() - 1)
                            out << "\n";
                        else
                            out << ",\n";
                    }
                    else
                    {
                        if (j == simChildren[i].size() - 1)
                            out << tab_json(simChildren[i][j]->get_lvl() + 2) << "}\n";
                        else
                            out << tab_json(simChildren[i][j]->get_lvl() + 2) << "},\n";

                    }
                }

                if (simChildren[i][0]->getChildren()[0]->get_tag()[0] != '<' && simChildren[i][0]->get_attributes().size() == 0)
                    out << tab_json(simChildren[i][0]->get_lvl() + 1) << "]\n";
                else
                {
                    if (i == simChildren.size() - 1)
                    {
                        out << tab_json(simChildren[i][0]->get_lvl() + 1) << "]\n";
                    }
                    else
                        out << tab_json(simChildren[i][0]->get_lvl() + 1) << "],\n";
                }
            }
            else
            {
                print_Json(simChildren[i][0]);
            }
        }
        if (!rootptr->get_Mark())
            out << tab_json(rootptr->get_lvl() + 1) << "}\n";
    }
}
