#include "parser.hh"

std::string generate(node& root)
{
      std::map<std::string, int> identifiers;
      std::map<std::string, int> list_identifiers;
      std::map<std::string, int> labels;
      int identifierI = 0;
      int lIdentifierI = 0;
      int labelI = 0;

      std::string result = "";
      // std::cout << "here\n";

      node* newRoot = new node();
      root.traverse(newRoot);
      newRoot->children.push_back(node("FILE_END", ""));
      // std::cout << "here\n";
      // newRoot->children.pop_back();
      // newRoot->children.pop_back();
      // newRoot->traverse();
      // std::cout << "here: " << newRoot->children.size() << std::endl;


      for (size_t i = 1; i < newRoot->children.size(); i++) {
            token currNode = newRoot->children[i].value;
            std::cout << "now reading: " << currNode.type << std::endl;
            // std::cout << "size: " << newRoot->children.size() << std::endl;
            // std::cout << "i = " << i << std::endl;

            if (currNode.type == "EXPR") {
                  // std::cout << "here\n";
                  std::vector<token> tokens;
                  ++i;
                  while (newRoot->children[i].value.type != "EXPR") {
                        if (newRoot->children[i].value.type == "FILE_END")
                              goto to_for;
                        tokens.push_back(newRoot->children[i].value);
                        ++i;
                        // std::cout << "increased i in theory\n";
                  }
                  --i;
            to_for:


                  for (token tokn : tokens)
                        tokn.print();

                        

                  if (newRoot->children[i].value.type == "FILE_END")
                        goto out_here;
            } else if (currNode.type == "NODE" || currNode.type == "ROOT" || currNode.type == "") {
                  continue;
            } else {
                  std::cout << "something went terribly wrong\n";
                  printNode(currNode);
                  newRoot->traverse();
                  exit(-69);
            }
      }

out_here:

      /*
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
                        // std::cout << name << "\n";
                        result += "p " + std::to_string(identifiers[name]) + "\n";
                  }
            }
            else if (subroot.value.value == "println") {
                  if (subroot.children[1].value.type == "IDENTIFIER") {
                        std::string name = subroot.children[1].value.value;
                        // std::cout << name << "\n";
                        result += "pn " + std::to_string(identifiers[name]) + "\n";
                  }
            }
            else if (subroot.value.value == ":") {
                  if (subroot.children[0].value.type == "IDENTIFIER"){
                        std::string name = subroot.children[0].value.value;
                        labels[name] = labelI;
                        labelI++;
                        result += "lbl " + std::to_string(labels[name]) + "\n";
                  }
            }
            else if (subroot.value.value == "goto"){
                  if (subroot.children[0].value.type == "IDENTIFIER"){
                        std::string name = subroot.children[0].value.value;
                        result += "goto " + std::to_string(labels[name]) + "\n";
                  }
            }
      }
      */
      return result;
}