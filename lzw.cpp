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

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " [mode] [file]" << endl;
        cout << "Modes:" << endl;
        cout << "  compress   Compress the file." << endl;
        cout << "  decompress Decompress the file." << endl;
        return 1;
    }

    string mode = argv[1];
    string filename = argv[2];
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    if (mode == "compress") {
        ofstream outputFile("./compressed_files/compressed_output.txt");
        string s((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
        vector<int> output_code = encoding(s);

        for (int code : output_code) {
            outputFile << code << " ";
        }
        outputFile.close();
        cout << "Compression completed. Output written to compressed_output.txt" << endl;
    } else if (mode == "decompress") {
        ofstream decodedFile("decoded_output.txt");
        vector<int> codes;
        int temp;
        while (inputFile >> temp) {
            codes.push_back(temp);
        }
        decoding(codes, decodedFile);
        decodedFile.close();
        cout << "Decompression completed. Output written to decoded_output.txt" << endl;
    } else {
        cerr << "Invalid mode. Use 'compress' or 'decompress'." << endl;
        return 1;
    }

    inputFile.close();
    return 0;
}
