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
        , m_designOutput(0)
        , delimiters(" ,()")
        {}
    ~Parser() { m_file.close(); }

    string nextLine();
    bool nextGate();
    unsigned getBiggerSignal();
    
    vector<int>& getInputs() { return m_inputs; }
    unsigned&    getOutput() { return m_output; }
    unsigned&    getNumLine()   { return m_line; }
    unsigned&    getDesignOutput() { return m_designOutput; }
    GATE         getGateType() { return m_gate; }

    void clearDesignInfo() {
        m_inputs.clear();
        m_output = 0;
        m_gate = ERROR;
    }
    void rewind() {
        m_file.clear();
        m_file.seekg(0,ios_base::beg);
        m_designOutput = 0;
    }

  private:
    ifstream m_file;
    unsigned m_line;
    unsigned m_output;
    unsigned m_designOutput;
    vector<int> m_inputs;
    GATE m_gate;
    string delimiters;
};

