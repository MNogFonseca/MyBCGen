
#include <cassert>
#include <fstream>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

#include "Parser.cpp"
#include "DrawGates.cpp"

#define FILTER_INV 0
using namespace std;

int main(int argc, char* argv[]) {
    string file = argv[1];
    Parser p(file);
    ofstream cnfFile;
    unsigned numGates = argc > 2 ? atoi(argv[2]) : 10000;
    unsigned maxLines = argc > 3 ? atoi(argv[3]) : 100000;

    if (argc > 2) {
        cnfFile.open(string(file + argv[2] + ".cnf").c_str());
    } else {
        cnfFile.open(string(file + ".cnf").c_str());
    }
    cnfFile << "temp                            " << endl;
 
    Draw3CNFGates::newId = p.getBiggerSignal()+1;
    while (!p.nextGate());
    do { 
        numGates = maxLines < p.getNumLine() ? 100000 : numGates;
        vector<int>& inputs = p.getInputs();
        int output = p.getOutput();
        GATE g = p.getGateType();
        switch(g) {
            case AND:
                cnfFile << Draw3CNFGates::drawAnd(inputs, output, numGates);
                break;
            case OR:
                cnfFile << Draw3CNFGates::drawOr(inputs, output, numGates);
                break;
            case XOR:
                cnfFile << Draw3CNFGates::xor3CNF(inputs[0], inputs[1], output);
                break;
            case INV:
                cnfFile << Draw3CNFGates::inv(inputs.back(), output);
                break;
            case BUF:
                cnfFile << Draw3CNFGates::buffer(inputs.back(), output);
                break;
            default:
                cout << p.getNumLine() << endl;
                assert(0);
        }
    } while (p.nextGate());
    cnfFile << p.getDesignOutput() << " 0" << endl;
    cnfFile.seekp(ios_base::beg);
    cnfFile << "p cnf " << Draw3CNFGates::numSig << " " << Draw3CNFGates::numGates+1;
    cnfFile.close();

    return 1;
}
