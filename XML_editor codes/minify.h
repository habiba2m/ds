#ifndef MINIFY_H
#define MINIFY_H
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <algorithm>
#include<sstream>
using namespace std;
void minify(string file_path, string outFile);
//void minify(string file_path);
//string xml = "<users>\n    <user>\n        <id>1\n        <name>Ahmed Ali</name>\n        <posts>\n            <post>\n                <body>\n                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n                </body>\n                <topics>\n                    <topic>\n                        economy\n                    </topic>\n                    <topic>\n                        finance\n                    </topic>\n                </topics>\n            </post>\n            <post>\n                <body>\n                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n                </body>\n                <topics>\n                    <topic>\n                        solar_energy\n                    </topic>\n                </topics>\n            </post>\n        </posts>\n        <followers>\n            <follower>\n                <id>2</id>\n            </follower>\n            <follower>\n                <id>3</id>\n            </follower>\n        </followers>\n    </user>\n    <user>\n        <id>2</id>\n        <name>Yasser Ahmed</name>\n        <posts>\n            <post>\n                <body>\n                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n                </body>\n                <topics>\n                    <topic>\n                        education\n                    </topic>\n                </topics>\n            </post>\n        </posts>\n        <followers>\n            <follower>\n                <id>1</id>\n            </follower>\n        </followers>\n    </user>\n    <user>\n        <id>3</id>\n        <name>Mohamed Sherif</name>\n        <posts>\n            <post>\n                <body>\n                    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n                </body>\n                <topics>\n                    <topic>\n                        sports\n                    </topic>\n                </topics>\n            </post>\n        </posts>\n        <followers>\n            <follower>\n                <id>1</id>\n            </follower>\n        </followers>\n    </user>\n</users>";

#endif // MINIFY_H
