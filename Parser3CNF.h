#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#define MAX_GATE 32

using namespace std;

unsigned newId = 4;

template<int n> 
string orGate(const string output, const vector<string>& inputs, const string temp_out) {
    string result;
    if (n == 1) {
        result = output + " = OR("+ inputs[n-1] + "," + temp_out + ")";
    } else {
        string id = std::to_string(newId++);
        result = id + " = OR(" + inputs[n-1] + "," + inputs[n-2] + ")\n";
        result = orGate<n-1>(output, inputs, id);
    }
    return result;


}

int main() {
    vector<string> inputs;
    inputs.push_back("1");
    inputs.push_back("2");
    inputs.push_back("3");
    inputs.push_back("4");
    cout << orGate<1>("Blah", inputs, "");
    return 1;
}
