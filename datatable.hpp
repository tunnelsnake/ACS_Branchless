#ifndef DATA_TABLE_HPP
#define DATA_TABLE_HPP

#include "csv.hpp"
#include <fstream>
#include <vector>

template <typename T> class DataTable {
public:
  DataTable() {
    _table = new std::vector<std::vector<T>>();
    _width = 0;
    _height = 0;
  }
  ~DataTable() {}

  void clear() {
    _table->clear();
    _width = 0;
    _height = 0;
  }

  void fromCSV(const std::string &path) {
    std::cout << "Loading from CSV " << path << std::endl;
    std::ifstream f(path);
    std::vector<T> s;

    unsigned long rowIndex = 0;
    while (getNextLineAndSplitAs<T>(f, s)) {
      _table->push_back(s);
      _width = s.size();
      _height += 1;
      s.clear();
    }
    std::cout << "rows: " << _height << " columns: " << _width << std::endl;
  }

  void print() {
    // If the type is of type string or type char, then we need to surround
    // each element with quotes to indicate its type to the user.
    std::string strTypeDummy;
    char charTypeDummy;
    bool isStringType;
    if (typeid(T).name() == typeid(strTypeDummy).name() ||
        typeid(T).name() == typeid(charTypeDummy).name()) {
      isStringType = true;
    }
    // Print out some additional information
    std::cout << "DataTable of Type " << typeid(T).name() << " Size: " << _width
              << " x " << _height << std::endl;

    // Iterate over the table and print its constituents (conditionally surround
    // with quotes if string or char)
    for (auto row : *_table) {
      for (auto col : row) {
        std::cout << (isStringType ? "\"" : "") << col
                  << (isStringType ? "\"" : "") << ", ";
      }
      std::cout << "\n";
    }
  }

  // The function that allows us to run a function against every element of the
  // data table. It takes a single function pointer to a fn that returns bool
  // and is passed <T>.
  void map(bool (*func)(T *)) {
    for (auto row : *_table) {
      for (auto col : row) {
        func(&col);
        // std::cout << func(col) << std::endl;
      }
    }
  }

  // This function allows us to run a function against every element of the data
  // table. It takes a function pointer ... uses OpenMP to split up the
  // workload.
  void map_parallel(bool (*func)(T *)) {
#pragma omp parallel
    {
#pragma omp for collapse(2)
      for (int row = 0; row < _height; row++) {
        for (int col = 0; col < _width; col++) {
          func(&(_table->at(row).at(col)));
          // std::cout << func(_table->at(row).at(col)) << std::endl;
        }
      }
    }
  }

  // This function will let us map over every row of the data table and
  // run a function on them.
  void mapRows(std::vector<bool> (*func)(std::vector<T> &)) {
    for (int row = 0; row < _height; row++) {
      func(_table->at(row));
    }
  }

  // This function will let us map over every row of the data table and
  // run a function on them.
  void mapRowsParallel(std::vector<bool> (*func)(std::vector<T> &)) {
#pragma omp parallel
    {
#pragma omp for
      for (int row = 0; row < _height; row++) {
        func(_table->at(row));
      }
    }
  }

private:
  std::vector<std::vector<T>> *_table;
  unsigned long _width;
  unsigned long _height;
};

#endif // DATA_TABLE_HPP