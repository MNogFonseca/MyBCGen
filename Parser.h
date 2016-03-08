#include <cassert>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

enum GATE {
    AND,
    OR,
    BUF,
    INV,
    XOR,
    ERROR
};

GATE toGate(string gateName) {
    if (gateName == "AND") {
        return AND;
    } else if (gateName == "OR") {
        return OR;
    } else if (gateName == "BUFF") {
        return BUF;
    } else if (gateName == "NOT") {
        return INV;
    } else if (gateName == "XOR") {
        return XOR;
    } else {
        assert(0);
        return ERROR;
    }
}

class Parser {
  public:
    Parser (string file) 
        : m_file(file.c_str())
        , m_line(0)
        , m_output()
        , m_inputs()
        , m_gate()
        , m_numSignals(0)
        , delimiters(" ,()")
        {}
    ~Parser() { m_file.close(); }

    string nextLine();
    bool nextGate();
    
    vector<int>& getInputs() { return m_inputs; }
    unsigned&    getOutput() { return m_output; }
    unsigned&    getNumSignals() { return m_numSignals; }
    GATE         getGateType() { return m_gate; }

  private:
    ifstream m_file;
    unsigned m_line;
    unsigned m_output;
    unsigned m_numSignals;
    vector<int> m_inputs;
    GATE m_gate;
    string delimiters;
};

