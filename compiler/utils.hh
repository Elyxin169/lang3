#pragma once
#ifndef utils
#define utils
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <set>

namespace utils {
      std::string readFile(const std::string& filename)
      {
            std::ifstream file(filename);
            if (!file) {
                  std::cerr << "Error opening file: " << filename << std::endl;
                  return "";
            }

            std::string content;
            std::string line;
            while (std::getline(file, line)) {
                  content += line + "\n";
            }

            file.close();
            return content;
      }

      std::string getFileName(const std::string& filepath)
      {
            std::regex regexPattern(R"(([^/\\]+?)(\.[^.]*$|$))");
            std::smatch matches;

            if (std::regex_search(filepath, matches, regexPattern)) {
                  return matches[1].str();
            }
            return "";
      }

      void writeFile(const std::string& filename, const std::string& content)
      {
            std::ofstream file(filename); // Open the file for writing

            if (file.is_open()) { // Check if the file is successfully opened
                  file << content; // Write the content to the file
                  file.close(); // Close the file
                  std::cout << "File written successfully." << std::endl;
            }
            else {
                  std::cerr << "Failed to open the file." << std::endl;
            }
      }

      std::vector<std::string> splitString(const std::string& str, const std::regex& regexPattern)
      {
            std::vector<std::string> tokens;

            std::sregex_token_iterator iter(str.begin(), str.end(), regexPattern, -1);
            std::sregex_token_iterator end;

            while (iter != end) {
                  std::string token = *iter++;
                  tokens.push_back(token);
            }

            return tokens;
      }
      std::string replace(const std::string& str, const std::string& from, const std::string& to)
      {
            std::string result = str;
            size_t startPos = 0;
            while ((startPos = result.find(from, startPos)) != std::string::npos) {
                  result.replace(startPos, from.length(), to);
                  startPos += to.length();
            }
            return result;
      }
      bool matchRegex(const std::string& inputString, const std::regex& pattern)
      {
            return std::regex_match(inputString, pattern);
      }

}

#endif