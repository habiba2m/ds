#include"minify.h"
using namespace std;



void minify(string file_path,string outFile)
{
    stringstream file(file_path);

    ofstream MyFile(outFile);
    string line, min_output;
    while (getline(file, line)) {
        if (line != "") {

            int pos = line.find("<");
            if (pos != -1)
                line = line.substr(pos);

            pos = line.find_first_not_of(' ');
            if (pos != -1)
                line = line.substr(pos);
            min_output += line;
        }
    }

    for (int i = 0; i < min_output.length(); i++) {

            if (min_output[i] == '>' && min_output[i + 1] == ' ') {
                int clos_tag_pos = i + 1, first_letter_pos;
                while (min_output[i + 1] == ' ' && i != min_output.size() - 1)
                    i++;
                first_letter_pos = i;
                string line0, line1;
                line0 = min_output.substr(0, clos_tag_pos);
                line1 = min_output.substr(first_letter_pos + 1);
                min_output = line0 + line1;
                i = i - (first_letter_pos - clos_tag_pos);
            }

    }
    for (int i = min_output.size(); i > 0; i--) {
        if (min_output[i] == '<' && min_output[i - 1] == ' ') {
            int opening_tag_pos = i - 1, first_letter_pos;
            while (min_output[i - 1] == ' ')
                i--;
            first_letter_pos = i;
            string line0, line1;
            line0 = min_output.substr(0, first_letter_pos);
            line1 = min_output.substr(opening_tag_pos + 1);
            min_output = line0 + line1;
            i = i + (first_letter_pos - opening_tag_pos);
        }
    }


    MyFile << min_output;

    MyFile.close();
}
