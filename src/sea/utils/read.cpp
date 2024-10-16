#include <iostream>
#include <fstream>
#include <sstream>
#include "read.h"
using namespace std;

string readShaderFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Failed to open shader file: " << filePath << endl;
        return "";
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
