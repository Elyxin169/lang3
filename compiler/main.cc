#include "generator.hh"
// Example usage
int main(int argc, char **argv)
{
      std::string filename = argv[1];
      std::string code = utils::readFile(filename);
      if (code.empty()) {
            return 1;
      }

      std::vector<token> tokens = lex(code);
      // printTokens(tokens);
      node tmp = parse(tokens);
      // printNode(tmp); <-------- root
      std::string output = generate(tmp);
      writeFile(getFileName(filename) + ".pss", output);

      return 0;
}