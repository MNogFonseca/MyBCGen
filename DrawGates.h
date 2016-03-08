#include <set>
#include <string>
#include <vector>

using namespace std;

class Draw3CNFGates {
  public:

    static void countSig(const int& sig);
    static string and3CNF(const int& in1, const int& in2, const int& out);
    static string or3CNF(const int& in1, const int& in2, const int& out);
    static string xor3CNF(const int& in1, const int& in2, const int& out);
    static string inv(const int& in1, const int& out);
    static string buffer(const int& in1, const int& out);

    static string drawAnd(const vector<int>& inputs, const unsigned& output);
    static string drawOr(const vector<int>& inputs, const unsigned& output);

    static int newId;
    static int numGates;
    static int numSig;
    static set<unsigned> sigMap;
};


