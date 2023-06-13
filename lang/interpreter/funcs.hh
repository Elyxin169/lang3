#pragma once
#ifndef FUNCS_H
#define FUNCS_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "types.hh"

namespace lang {

      std::string readFile(const std::string& filename)
      {
            std::ifstream file(filename);
            std::string content;

            if (file.is_open()) {
                  std::string line;
                  while (std::getline(file, line)) {
                        content += line;
                        if (!file.eof()) {
                              content += "\n";
                        }
                  }
                  file.close();
            }
            else {
                  std::cout << "Failed to open the file: " << filename << std::endl;
            }

            return content;
      }

      std::vector<std::string> splitLines(const std::string& content)
      {
            std::vector<std::string> lines;
            std::string line;
            std::istringstream iss(content);

            while (std::getline(iss, line)) {
                  lines.push_back(line);
            }

            return lines;
      }


      std::vector<std::string> splitString(const std::string& input, char delimiter)
      {
            std::vector<std::string> substrings;
            std::string substring;
            std::istringstream iss(input);

            while (std::getline(iss, substring, delimiter)) {
                  substrings.push_back(substring);
            }

            return substrings;
      }

      void printVector(const std::vector<std::string>& vec)
      {
            for (const auto& element : vec) {
                  std::cout << element << ' ';
            }
            std::cout << std::endl;
      }

      void panic(const std::string& message)
      {
            std::cout << "ERROR: " << message << std::endl;
            exit(-69);
      }

      void writeFile(const std::string& filename, const std::string& content)
      {
            std::ofstream file(filename);
            if (file.is_open()) {
                  file << content;
                  file.close();
                  std::cout << "Content successfully written to the file." << std::endl;
            }
            else {
                  std::cerr << "Unable to open the file." << std::endl;
            }
      }
}

#endif // FUNCS_H