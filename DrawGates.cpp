#include "DrawGates.h"
#include <sstream>
#include <iostream>

int Draw3CNFGates::newId = 0;
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
Draw3CNFGates::andNCNF(const vector<int>& inputs, const int& out, unsigned& numGateInputs) {
    stringstream result;
    result << out;
    unsigned max = inputs.size() < numGateInputs ? inputs.size() : numGateInputs;
    for (int i = 0; i < max; ++i) {
        countSig(inputs[i]);
        result << " " << inputs[i]*-1;
    }
    result << " 0\n";

    for (int i = 0; i < max; ++i) {
        result << out*-1 << " " << inputs[i]<< " 0\n";
    }
    numGates += 1 + max;
    return result.str();
}

string
Draw3CNFGates::orNCNF(const vector<int>& inputs, const int& out, unsigned& numGateInputs) {
    stringstream result;
    result << out*-1;
    unsigned max = inputs.size() < numGateInputs ? inputs.size() : numGateInputs;
    for (int i = 0; i < max; ++i) {
        countSig(inputs[i]);
        result << " " << inputs[i];
    }
    result << " 0\n";

    for (int i = 0; i < max; ++i) {
        result << out << " " << inputs[i]*-1<< " 0\n";
    }
    numGates += 1 + max;
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
Draw3CNFGates::drawAnd(const vector<int>& inputs, const unsigned& output, unsigned& numInputsMax) {
    string result;
    if (inputs.size() <= numInputsMax) {
        result = andNCNF(inputs, output, numInputsMax);
    } else {
        unsigned out = newId++;
        result = andNCNF(inputs, out, numInputsMax);
        unsigned inputsDone = numInputsMax;
        while (inputsDone < inputs.size()) {
            unsigned prevOut = out, tamNextGate;
            if ((((float) inputs.size()) - inputsDone)/(numInputsMax-1.0f) > 1) {
                tamNextGate = numInputsMax;
                out = newId++;
            } else {
                tamNextGate = inputs.size() - inputsDone+1;
                out = output;
            }
            vector<int>::const_iterator first = inputs.begin() + inputsDone;
            vector<int>::const_iterator last = inputs.begin() + inputsDone + tamNextGate - 1;
            vector<int> tmp(first, last);
            tmp.push_back(prevOut);
            result += andNCNF(tmp, out, tamNextGate);

            inputsDone += tamNextGate-1;
        }
    }
    return result;
}

string
Draw3CNFGates::drawOr(const vector<int>& inputs, const unsigned& output, unsigned& numInputsMax) {
    string result;
    if (inputs.size() <= numInputsMax) {
        result = orNCNF(inputs, output, numInputsMax);
    } else {
        unsigned out = newId++;
        result = orNCNF(inputs, out, numInputsMax);
        unsigned inputsDone = numInputsMax;
        while (inputsDone < inputs.size()) {
            unsigned prevOut = out, tamNextGate;
            if ((((float) inputs.size()) - inputsDone)/(numInputsMax-1.0f) > 1) {
                tamNextGate = numInputsMax;
                out = newId++;
            } else {
                tamNextGate = inputs.size() - inputsDone+1;
                out = output;
            }
            vector<int>::const_iterator first = inputs.begin() + inputsDone;
            vector<int>::const_iterator last = inputs.begin() + inputsDone + tamNextGate - 1;
            vector<int> tmp(first, last);
            tmp.push_back(prevOut);
            result += orNCNF(tmp, out, tamNextGate);

            inputsDone += tamNextGate-1;
        }
    }
    return result;
}
