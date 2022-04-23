#include <iostream>
#include <sstream>
#include <vector>

template <typename T> int getline_as(std::istream &s, T &value) {
  std::string result;
  if (getline_as<std::string>(s, result)) {
    std::stringstream convert(result);
    convert >> value;
    return 1;
  } else {
    return 0;
  }
}

template <> int getline_as<std::string>(std::istream &s, std::string &str) {

  if (std::getline(s, str, ',')) {
    return 1;
  } else {
    return 0;
  }
}

template <typename T>
int getNextLineAndSplitAs(std::istream &str, std::vector<T> &result) {
  std::string line;
  if (!std::getline(str, line))
    return 0;

  std::stringstream lineStream(line);
  T cell;

  while (getline_as<T>(lineStream, cell)) {
    result.push_back(cell);
  }
  return 1;
}
