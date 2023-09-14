#include "lexer.hh"

class node {
public:
      std::vector<node> children;
      token value;
      node(std::string& type, std::string& value)
      {
            // this->type = type;
            this->value = token(type, value);
      }
      node(const std::string& type, const std::string& value)
      {
            // this->type = type;
            this->value = token(type, value);
      }
      node(const std::string& value)
      {
            this->value = token(value);
      }
      node(const token& token)
      {
            this->value = token;
      }
      node()
      {
            this->value = token("ROOT", "root");
      }
      void traverse()
      {
            // Print the value of the current node
            this->value.print();

            // Recursively traverse the children
            for (node& child : this->children) {
                  child.traverse();
            }
      }
      void traverse(node* newRoot)
      {
            // Print the value of the current node
            // this->value.print();
            node* tmp = new node(this->value);
            newRoot->children.push_back(*tmp);

            // Recursively traverse the children
            for (node& child : this->children) {
                  child.traverse(newRoot);
            }
      }
};

void printNode(const node& rootNode, const std::string& indentation = "")
{
      std::cout << indentation << "Type: " << rootNode.value.type << ", Value: " << rootNode.value.value << std::endl;

      for (const auto& child : rootNode.children) {
            printNode(child, indentation + "  ");
      }
}
node parse(std::vector<token>& tokenStream)
{
      node root = node(token("ROOT", "69"));

      std::vector<token> tokens = tokenStream;
      size_t index = 0;

      std::function<node()> constructTree = [&]() -> node {
            node currentNode("NODE", "");

            while (index < tokens.size()) {
                  std::vector<token> statement;
                  while (index < tokens.size() && tokens[index].value != "{" && tokens[index].value != "}" && (tokens[index].type != "END_STATEMENT" || tokens[index].value != ";")) {
                        if (tokens[index].value != "(" && tokens[index].value != ")") { // Skip parentheses
                              statement.push_back(tokens[index]);
                        }
                        index++;
                  }

                  if (!statement.empty()) {
                        node exprNode("EXPR", ""); // Create an EXPR node for every statement

                        if (statement[0].value == "if") {
                              node ifNode("KEYWORD", "if");
                              size_t i = 1;

                              while (i < statement.size() && statement[i].value != "{") {
                                    exprNode.children.push_back(node(statement[i]));
                                    i++;
                              }

                              index++; // Skip over the '{' token

                              ifNode.children.push_back(exprNode);
                              ifNode.children.push_back(constructTree());
                              currentNode.children.push_back(node("IF_BODY", ""));
                              currentNode.children.push_back(ifNode);
                        } else {
                              node subroot(statement[0].type, statement[0].value);
                              for (size_t i = 1; i < statement.size(); i++) {
                                    subroot.children.push_back(node(statement[i]));
                              }
                              exprNode.children.push_back(subroot); // Add the subroot to the EXPR node
                        }

                        currentNode.children.push_back(exprNode); // Add the EXPR node to the current node
                  }

                  if (tokens[index].value == "}") {
                        index++; // Skip the closing brace
                        break;
                  } else {
                        index++; // Skip the end of statement
                  }
            }

            return currentNode;
            };

      while (index < tokens.size()) {
            root.children.push_back(constructTree());
      }
      return root;
}