#include "Parser.h"
#include <stdlib.h>
#include <iostream>

string
Parser::nextLine() {
    if (m_file.is_open()) {
        string line;
        while (getline(m_file, line)) {
            m_line++;
            if (line[0] != ' ' 
                && line[0] != '#'
                && !line.empty()
                && line[0] != 'I') {
                return line;
            }
        }
    }
    return "EOF";
}

bool
Parser::nextGate() {
    string gateInfo = nextLine();
    if (gateInfo == "EOF") {
        return false;
    }
        
    if (gateInfo[0] == 'O') {
        int posI = gateInfo.find('(');
        int posF = gateInfo.find(')');
        m_designOutput = atoi(gateInfo.substr(posI+1, posF-posI-1).c_str());
        clearDesignInfo();
        return false;
    } else {

        int pos = gateInfo.find(' ');
        m_output = atoi(gateInfo.substr(0,pos).c_str());
        assert(m_output);

        int posEnd = gateInfo.find('(');
        m_gate = toGate(gateInfo.substr(pos+3,posEnd-pos-3));
  
        pos = gateInfo.find(')');
        std::istringstream iss(gateInfo.substr(posEnd+1, pos-posEnd-1));
        string token; 
        m_inputs.clear();
        while (getline(iss, token, ',')) {
            unsigned i = atoi(token.c_str());
            assert(i);
            m_inputs.push_back(i);
        }
    }   
    return true;
}

unsigned
Parser::getBiggerSignal() {
    unsigned bigger = 0;

    while(!nextGate());
    do {
        if (m_output > bigger) {
            bigger = m_output;
        }
        for (vector<int>::const_iterator it = m_inputs.begin(); it != m_inputs.end(); ++it) {
            if (*it > bigger) {
                bigger = *it;
            }
        }
    } while(nextGate());
    m_file.clear();
    m_file.seekg(0,ios_base::beg);
    m_designOutput = 0;
    m_gate = ERROR;
    m_line = 0;
    return bigger;
}
 
