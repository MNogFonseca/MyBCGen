#include "DrawGates.h"
#include <sstream>

int Draw3CNFGates::newId    = 1416;
int Draw3CNFGates::numGates = 0;
int Draw3CNFGates::numSig = 0;
set<unsigned> Draw3CNFGates::sigMap;

void
Draw3CNFGates::countSig(const int& sig) {
     unsigned int usig = (sig < 0) ? sig*-1 : sig;
     if (sigMap.find(usig) == sigMap.end()) {
         sigMap.insert(usig);
         numSig++;
     }
}

string
Draw3CNFGates::and3CNF(const int& in1, const int& in2, const int& out) {
    countSig(in1);
    countSig(in2);
    countSig(out);
    stringstream result;
    result << in1 << " " << out*-1 << " 0\n";
    result << in2 << " " << out*-1 << " 0\n";
    result << in1*-1 << " " << in2*-1 << " " << out << " 0\n";
    numGates += 3;
    return result.str();
}

string
Draw3CNFGates::or3CNF(const int& in1, const int& in2, const int& out) {
    countSig(in1);
    countSig(in2);
    countSig(out);

    stringstream result;
    result << in1*-1 << " " << out << " 0\n";
    result << in2*-1 << " " << out << " 0\n";
    result << in1 << " " << in2 << " " << out*-1 << " 0\n";
    numGates += 3;
    return result.str();
}

string
Draw3CNFGates::xor3CNF(const int& in1, const int& in2, const int& out) {
    stringstream result;
    countSig(in1);
    countSig(in2);
    countSig(out);
    result << in1 << " " << in2 << " " << out*-1 << " 0\n";
    result << in1 << " " << in2*-1 << " " << out << " 0\n";
    result << in1*-1 << " " << in2 << " " << out << " 0\n";
    result << in1*-1 << " " << in2*-1 << " " << out*-1 << " 0\n";
    numGates += 4;
    return result.str();
}

string
Draw3CNFGates::inv(const int& in1, const int& out) {
    countSig(in1);
    countSig(out);
    stringstream result;
    result << in1*-1 << " " << out*-1 << " 0\n";
    result << in1 << " " << out << " 0\n";
    numGates += 2;
    return result.str();
}

string
Draw3CNFGates::buffer(const int& in1, const int& out) {
    countSig(in1);
    countSig(out);
    stringstream result;
    result << in1*-1 << " " << out << " 0\n";
    result << in1 << " " << out*-1 << " 0\n";
    numGates += 2;
    return result.str();
}

string
Draw3CNFGates::drawAnd(const vector<int>& inputs, const unsigned& output) {
    string result;
    unsigned out = output;
    if (inputs.size() == 2) {
        result = and3CNF(inputs[0], inputs[1], output);
    } else {
        out = newId++;
        result += and3CNF(inputs[0], inputs[1], out);
        for (int i = 2; i < inputs.size()-1; ++i) {
            unsigned prevOut = out;
            out = newId++;
            result += and3CNF(inputs[i], prevOut, out);
        }
        result += and3CNF(inputs.back(), out, output);
    }
    return result;
}

string
Draw3CNFGates::drawOr(const vector<int>& inputs, const unsigned& output) {
    string result;
    unsigned out = output;
    if (inputs.size() == 2) {
        result = or3CNF(inputs[0], inputs[1], output);
    } else {
        out = newId++;
        result += or3CNF(inputs[0], inputs[1], out);
        for (int i = 2; i < inputs.size()-1; ++i) {
            unsigned prevOut = out;
            out = newId++;
            result += or3CNF(inputs[i], prevOut, out);
        }
        result += or3CNF(inputs.back(), out, output);
    }
    return result;
}
