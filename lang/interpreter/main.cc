#include "includes.hh"

ganzZahl main(ganzZahl argc, char const* argv[])
{
      if (argc != 2) lang::panic("Pass a file as an argument");
      std::string file = lang::readFile(argv[1]);
      std::vector<std::string> lines = lang::splitLines(file);
      std::vector<std::unique_ptr<lang::numeral>> memory;
      std::vector<std::vector<std::unique_ptr<lang::numeral>>> listsMemory;

      // std::cout << lines[1] << std::endl;
      size_t lineCount = 0;
      while ("🎵🎵🎵🎵🎵im losing my sanity🎵🎵🎵🎵🎵") {
            /*
                  dl: declare list
                  di: declare var
                  prints (n at the end of command adds a newline):
                        p: ganzZahl
                        pl: list
                        pls: list as string
                  m: mov
                  ml: assign list
                  +: adds 1
                  -: adds -1

            */
            if (lineCount > lines.size() - 1) {
                  exit(0);
            }
            else if (lineCount < 0) {
                  lang::panic("Trying to GOTO failed: " + std::to_string(lineCount));
            }

            std::vector<std::string> tokens = lang::splitString(lines[lineCount], ' ');
            // lang::printVector(tokens);


            if (tokens[0][0] == 'd' && tokens[0][1] == 'i') {
                  memory.push_back(std::make_unique<lang::numeral>(0));
            }
            else if (tokens[0][0] == 'd' && tokens[0][1] == 'l') {
                  listsMemory.push_back(std::vector<std::unique_ptr<lang::numeral>>());
            }
            else if (tokens[0] == "m") {
                  memory[std::stoi(tokens[1])]->setInt(std::stoi(tokens[2]));
            }
            else if (tokens[0] == "ml") {
                  std::vector<std::unique_ptr<lang::numeral>>& myList = listsMemory[std::stoi(tokens[1])];
                  for (size_t i = 0; i < tokens.size() - 2; i++)
                        myList.push_back(std::make_unique<lang::numeral>(std::stoi(tokens[i + 2])));
            }
            else if (tokens[0] == "p") {
                  std::cout << memory[std::stoi(tokens[1])]->getInt();
            }
            else if (tokens[0] == "pn") {
                  std::cout << memory[std::stoi(tokens[1])]->getInt();
                  std::cout << std::endl;
            }
            else if (tokens[0] == "pl") {
                  // std::cout << memory[std::stoi(tokens[1])]->getInt();
                  std::vector<std::unique_ptr<lang::numeral>>& myList = listsMemory[std::stoi(tokens[1])];

                  if (myList.size() > 1) {
                        std::cout << "[";
                        std::cout << myList[0]->getInt();
                        for (size_t i = 1; i < myList.size(); i++) {
                              std::cout << ", " << myList[i]->getInt();
                        }std::cout << "]";
                  }
                  else {
                        std::cout << "[" << myList[0]->getInt() << "]";
                  }
            }
            else if (tokens[0] == "pln") {
                  std::vector<std::unique_ptr<lang::numeral>>& myList = listsMemory[std::stoi(tokens[1])];
                  if (myList.size() > 1) {
                        std::cout << "[";
                        std::cout << myList[0]->getInt();
                        for (size_t i = 1; i < myList.size(); i++) {
                              std::cout << ", " << myList[i]->getInt();
                        }
                        std::cout << "]";
                  }
                  else {
                        std::cout << "[" << myList[0]->getInt() << "]";
                  }
                  std::cout << std::endl;
            }
            else if (tokens[0] == "pls") {
                  std::vector<std::unique_ptr<lang::numeral>>& myList = listsMemory[std::stoi(tokens[1])];
                  for (size_t i = 0; i < myList.size(); i++) {
                        std::cout << static_cast<char>(myList[i]->getInt());
                  }
            }

            else if (tokens[0] == "plsn") {
                  std::vector<std::unique_ptr<lang::numeral>>& myList = listsMemory[std::stoi(tokens[1])];
                  for (size_t i = 0; i < myList.size(); i++) {
                        std::cout << static_cast<char>(myList[i]->getInt());
                  }
                  std::cout << std::endl;
            }


            else if (tokens[0][0] == '+') {
                  memory[std::stoi(tokens[1])]->inc();
            }
            else if (tokens[0][0] == '-') {
                  memory[std::stoi(tokens[1])]->dec();
            }
            else {
                  lang::panic("Unknown keyword \"" + tokens[0] + "\" at: line " + std::to_string(lineCount));
            }

            lineCount++;
      }

      return 0;
}
