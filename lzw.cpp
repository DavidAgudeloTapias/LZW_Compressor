#include <bits/stdc++.h>
#include <fstream>
using namespace std;

vector<int> encoding(const string& s1) {
    cout << "Encoding\n";
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    cout << "String\tOutput_Code\tAddition\n";
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        } else {
            cout << p << "\t" << table[p] << "\t\t" << p + c << "\t" << code << endl;
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    cout << p << "\t" << table[p] << endl;
    output_code.push_back(table[p]);
    return output_code;
}

void decoding(const vector<int>& op, ostream& os) {
    cout << "\nDecoding\n";
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    os << s;
    int count = 256;
    for (int i = 0; i < op.size() - 1; i++) {
        n = op[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        } else {
            s = table[n];
        }
        os << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("compressed_output.txt"), decodedFile("decoded_output.txt");

    string s((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    vector<int> output_code = encoding(s);

    outputFile << "Output Codes are: ";
    for (int code : output_code) {
        outputFile << code << " ";
    }
    outputFile << endl;

    decoding(output_code, decodedFile);

    inputFile.close();
    outputFile.close();
    decodedFile.close();

    return 0;
}
