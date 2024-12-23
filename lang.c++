#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

// Tokenizer
vector<string> lexer(const string& inputdata) {
    string word;
    vector<string> tokens;
    for (char c : inputdata) {
        if (c == ' ' || c == '\n') {
            if (!word.empty()) {
                tokens.push_back(word);
                word = "";
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) tokens.push_back(word);
    return tokens;
}

// Parser and Interpreter
void parser(const vector<string>& tokens) {
    unordered_map<string, int> variables;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "yele") {
            if (i + 3 >= tokens.size() || tokens[i + 2] != "=") {
                cout << "Syntax Error: Invalid variable declaration." << endl;
                return;
            }
            string varName = tokens[i + 1];
            int value = stoi(tokens[i + 3]);
            variables[varName] = value;
            i += 3;
        } else if (tokens[i] == "yekar") {
            if (i + 5 >= tokens.size() || tokens[i + 4] != "+" && tokens[i + 4] != "-" &&
                tokens[i + 4] != "*" && tokens[i + 4] != "/") {
                cout << "Syntax Error: Invalid arithmetic operation." << endl;
                return;
            }
            string varName = tokens[i + 1];
            string var1 = tokens[i + 3];
            string var2 = tokens[i + 5];
            string operation = tokens[i + 4];

            if (variables.find(var1) == variables.end() || variables.find(var2) == variables.end()) {
                cout << "Error: Undefined variable in calculation." << endl;
                return;
            }

            if (operation == "+") {
                variables[varName] = variables[var1] + variables[var2];
            } else if (operation == "-") {
                variables[varName] = variables[var1] - variables[var2];
            } else if (operation == "*") {
                variables[varName] = variables[var1] * variables[var2];
            } else if (operation == "/") {
                if (variables[var2] == 0) {
                    cout << "Error: Division by zero." << endl;
                    return;
                }
                variables[varName] = variables[var1] / variables[var2];
            }
            i += 5;
        } else if (tokens[i] == "printkr") {
            if (i + 1 >= tokens.size()) {
                cout << "Syntax Error: Missing variable name in printkr." << endl;
                return;
            }
            string varName = tokens[i + 1];
            if (variables.find(varName) != variables.end()) {
                cout << variables[varName] << endl;
            } else {
                cout << "Error: Variable " << varName << " not found!" << endl;
            }
            i += 1;
        } else {
            cout << "Error: Unknown keyword or syntax error near " << tokens[i] << endl;
            return;
        }
    }
}

int main() {
    string input = R"(
        yele x = 5
        yele y = 20
        yekar z = x + y
        printkr z
    )";
    std::cout<<"The Input Code is:"<<input<<std::endl;
    vector<string> tokens = lexer(input);

    parser(tokens);

    return 0;
}
