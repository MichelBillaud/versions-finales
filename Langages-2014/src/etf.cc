// lecture d'expressions

#include <iostream>
#include <cstring>

using namespace std;

enum TokenType {
    ENDOFLINE,
    IDENTIFIER,
    NUMBER,
    PARENTHESIS,
    OPERATOR
};

class Lexer {
  string m_string;
  uint    m_index;   // next char
  uint    m_length;
  TokenType    m_type;
  string  m_content;
public:
  Lexer(string s) :
    m_string(s),
    m_index (0),
    m_length(m_string.length())
    {
      next();    
    }
  
  void next() {
    // skip spaces
    while (m_index < m_length 
          && isspace(m_string[m_index])) 
            m_index ++;
    if (m_index == m_length) {
      m_type = ENDOFLINE;
      m_content = "";
      return;
    }
    // first char
    m_content = m_string[m_index++];
    if (index("()", m_content[0]) >= 0) {
      m_type = PARENTHESIS;
      return; 
    }
    if (index("+-*/", m_content[0]) >= 0) {
      m_type = OPERATOR;
      return; 
    }
    
  }
 };

int main(int argc, char **argv)
{
	Lexer l("a+b*c");
	return 0;
}

