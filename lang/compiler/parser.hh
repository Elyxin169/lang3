#include "lexer.hh"

class node {
public:
      std::vector<node> children;
      token value;
      node(std::string& type, std::string& value)
      {
            this->value = token(type, value);
      }
      node(const std::string& type, const std::string& value)
      {
            this->value = token(type, value);
      }
      node(const std::string& value)
      {
            this->value = token(value);
      }
      node(const token& token){
            this->value = token;
      }
      node()
      {
            this->value = token("root");
      }
};

std::vector<std::vector<token>> splitList(const std::vector<token>& tokens)
{
      std::vector<std::vector<token>> list;
      std::vector<token> tmp;
      for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i].type != "END_STATEMENT") {
                  // std::cout << tokens[i].type << ": " << tokens[i].value << std::endl;
                  tmp.push_back(token(tokens[i].type, tokens[i].value));
            }
            else {
                  list.push_back(tmp);
                  tmp.clear();
            }
      }

      return list;
}

void printNode(const node& rootNode, const std::string& indentation = "")
{
      std::cout << indentation << "Type: " << rootNode.value.type << ", Value: " << rootNode.value.value << std::endl;

      for (const auto& child : rootNode.children) {
            printNode(child, indentation + "  ");
      }
}

node parse(const std::vector<token>& tokenStream)
{
      node root = node(token("ROOT", "69"));

      std::vector<std::vector<token>> list = splitList(tokenStream);
      // std::cout << list[1][0].type << "\n";
      // for (const auto& subList : list) {
      //       for (const auto& token : subList) {
      //             std::cout << "Type: " << token.type << ", Value: " << token.value << "\n";
      //       }
      //       std::cout << std::endl;
      // }

      for (const auto& statement : list) {
            node subroot(statement[0].type, statement[0].value); // Set the type of the subroot node
            if (subroot.value.value == "#") continue;
            // std::cout << subroot.value << std::endl;
            // for now...
            for (size_t i = 1; i < statement.size(); i++) {
                  subroot.children.push_back(node(statement[i]));
            }
            root.children.push_back(subroot);
      }

      // std::cout << root.children[1].value.type << std::endl;
      // root.children.push_back(node(std::string("testtype"), std::string("test")));
      return root;
}