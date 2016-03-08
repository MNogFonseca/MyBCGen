
#include <cassert>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Parser.cpp"
#include "DrawGates.cpp"

using namespace std;


int main(int argc, char* argv[]) {
    string file = argv[1];
    Parser p(file);
    ofstream cnfFile;
    cnfFile.open(string(file + ".cnf").c_str());
    cnfFile << "temp                            " << endl;

    p.nextGate();
    while(p.nextGate()) {
        vector<int>& inputs = p.getInputs();
        unsigned output = p.getOutput();
        GATE g = p.getGateType();
        switch(g) {
            case AND:
                cnfFile << Draw3CNFGates::drawAnd(inputs, output);
                break;
            case OR:
                cnfFile << Draw3CNFGates::drawOr(inputs, output);
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
                assert(0);
        }
        
    }
    cnfFile << p.getNumSignals() << " 0" << endl;
    cnfFile.seekp(ios_base::beg);
    cnfFile << "p cnf " << Draw3CNFGates::numSig << " " << Draw3CNFGates::numGates+1;
    cnfFile.close();
    return 1;
}
