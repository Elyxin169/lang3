#include "utils.hh"

// Token structure to store token information
class token {
public:
      std::string type;
      std::string value;
      token(std::string& type, std::string& value)
      {
            this->type = type;
            this->value = value;
      }
      token(const std::string& type, const std::string& value)
      {
            this->type = type;
            this->value = value;
      }
      token(const std::string& value)
      {
            this->value = value;
      }
      token()
      {

      }
      void print(){
            std::cout << "type: " << this->type << " value: " << this->value << std::endl;
      }
};

bool isOperator(const std::string& value)
{
      bool result = false;
      const std::set<std::string> operators = { "=", "+", "-", "*", "/", ">", "<" };
      if (operators.count(value) > 0)
            result = true;
      return result;
}

bool isKeyword(const std::string& value)
{
      bool result = false;
      const std::set<std::string> keywords = { "print", "println", "var", "#", ":", "goto", "if" };
      if (keywords.count(value) > 0)
            result = true;
      return result;
}

std::vector<token> lex(const std::string& code)
{
      std::regex whitespaces(R"(\s+|\n+)");
      std::regex identifiers(R"([_a-zA-Z][a-zA-Z0-9_]*)");
      std::vector<std::string> tokens = utils::splitString(utils::replace(utils::replace(utils::replace(utils::replace(utils::replace(code, "(", " ( "), ")", " ) "), ";", " ; "), "\"", " \" "), "#", " # "), \
            whitespaces);
      std::vector<token> result;
      for (int i = 0; i < tokens.size(); i++) {
            std::string type = "UNKNOWN";
            std::string value = "";
            if (isOperator(tokens[i])) {
                  type = "OPERATOR";
                  value = tokens[i];
            }
            else if (isKeyword(tokens[i])) {
                  type = "KEYWORD";
                  value = tokens[i];
            }

            else if (tokens[i] == "\"") {
                  type = "STRING";
                  ++i;
                  for (;"i wanna die";++i) {
                        if (tokens[i] == "\"") {
                              break;
                        }
                        else value += " " + tokens[i];
                  }
                  value = value.substr(1);
            }
            else if (tokens[i] == "(") {
                  type = "L_PAREN";
                  value = tokens[i];
            }
            else if (tokens[i] == ")") {
                  type = "R_PAREN";
                  value = tokens[i];
            }
            else if (tokens[i] == "{") {
                  type = "L_CUR_PAREN";
                  value = tokens[i];
            }
            else if (tokens[i] == "}") {
                  type = "R_CUR_PAREN";
                  value = tokens[i];
            }
            else if (tokens[i] == ";") {
                  type = "END_STATEMENT";
                  value = tokens[i];
            }
            else if (utils::matchRegex(tokens[i], identifiers)) {
                  type = "IDENTIFIER";
                  value = tokens[i];
            }
            else if (utils::matchRegex(tokens[i], std::regex(R"([+-]?((\d+\.?\d*)|(\.\d+)))"))) {
                  type = "NUMBER";
                  value = tokens[i];
            }
            else value = tokens[i];

            result.push_back(token(type, value));
      }
      return result;
}

void printTokens(std::vector<token>& tokens)
{
      for (int i = 0; i < tokens.size(); i++) {
            std::cout << tokens[i].type << " " << tokens[i].value << std::endl;
      }
}