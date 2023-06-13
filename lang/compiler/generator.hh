#include "parser.hh"

std::string generate(node& root)
{
      std::map<std::string, int> identifiers;
      std::map<std::string, int> list_identifiers;
      int identifierI = 0;
      int lIdentifierI = 0;

      std::string result = "";

      for (auto& subroot : root.children) {
            if (subroot.value.value == "var") {
                  std::cout << "declaring variable " << subroot.children[0].value.value << " of type " << subroot.children[2].value.type << "\n";
                  if (subroot.children[2].value.type == "NUMBER") {
                        std::string name = subroot.children[0].value.value;
                        identifiers[name] = identifierI;
                        identifierI++;
                        result += "di\n";
                        result += "m " + std::to_string(identifiers[name]) + " " + subroot.children[2].value.value + "\n";
                  }

            }
            // print ( numero )
            else if (subroot.value.value == "print") {
                  if (subroot.children[1].value.type == "IDENTIFIER") {
                        std::string name = subroot.children[1].value.value;
                        std::cout << name << "\n";
                        result += "p " + std::to_string(identifiers[name]) + "\n";
                  }
            }
            else if (subroot.value.value == "println") {
                  std::cout << "here" << std::endl;
                  if (subroot.children[1].value.type == "IDENTIFIER") {
                        std::string name = subroot.children[1].value.value;
                        std::cout << name << "\n";
                        result += "pn " + std::to_string(identifiers[name]) + "\n";
                  }
            }
      }
      // std::cout << result;
      return result;
}