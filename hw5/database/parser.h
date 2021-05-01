#include <string>
#include <vector>

#ifndef PARSER_H
#define PARSER_H

namespace parser {
// Function splits given string by delimeter and returns resulting vector with
// entries
std::vector<std::string> parse_string(std::string input, char delimeter) {
  std::vector<std::string> tokens;
  if (input.size() == 0) return tokens;
  std::string token = "";
  for (auto input_c : input) {
    // we have ended token
    if (input_c == delimeter) {
      tokens.push_back(token);
      token = "";
    } else {
      token += input_c;
    }
  }
  tokens.push_back(token);
  return tokens;
}
}  // namespace parser

#endif