#include <set>
#include <string>
#include <vector>

using namespace std;

class Draw3CNFGates {
  public:

    static void countSig(const int& sig);
    static string andNCNF(const vector<int>& inputs, const int& out, unsigned& numGateInputs);
    static string orNCNF(const vector<int>& inputs, const int& out, unsigned& numGateInputs);
    static string xor3CNF(const int& in1, const int& in2, const int& out);
    static string inv(const int& in1, const int& out);
    static string buffer(const int& in1, const int& out);
    static string gnd(const int in1);

    static string drawAnd(const vector<int>& inputs, const unsigned& output, unsigned& numInputsMax);
    static string drawOr(const vector<int>& inputs, const unsigned& output, unsigned& numInputsMax);

    static int newId;
    static int numGates;
    static int numSig;
    static set<unsigned> sigMap;
};


