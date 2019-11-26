#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

#include "core.hpp"
#include "strlib.hpp"

using namespace lt;

// Splits string into a vector
std::vector<std::string> strlib::split(std::string str, std::string delimiter) {
  std::vector<std::string> result;
  auto string_size = str.size(); auto delimiter_size = delimiter.size();
  int last_found = -delimiter_size;
  bool done = false;
  while (!done) {
    unsigned int found = str.find(delimiter, last_found + delimiter_size);
    if (found == std::string::npos) {
      done = true;
      found = string_size;
    };
    if (found - (last_found + delimiter_size) > 0) {
      result.push_back(str.substr(last_found + delimiter_size, found - (last_found + delimiter_size)));
    };
    last_found = found;
  };
  return result;
};

// Removes excess characters from beginning and end of string
std::string strlib::strip(std::string str, char to_strip) {
  auto string_size = str.size();
  unsigned int left = 0, right = string_size - 1;
  for (unsigned int i = left; i < string_size; ++i) {
    if (str[i] != to_strip) {
      left = i;
      break;
    };
  };
  for (unsigned int i = right; i >= 0; --i) {
    if (str[i] != to_strip) {
      right = i;
      break;
    };
  };
  return str.substr(left, right - left);
};

std::wstring strlib::string_to_wstring(std::string str) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(str);
}

#define MIN_OF_THREE(a, b, c) (a < (b < c ? b : c) ? a : (b < c ? b : c))
#define MAX_OF_TWO(a, b) (a > b ? a : b)
#define CLAMP(a, min, max) (a < min ? min : (a > max ? max : a))

template <class string_type>
unsigned int T_edit_distance(string_type a, string_type b) {
  unsigned int msize = MAX_OF_TWO(a.size(), b.size()); 
  unsigned int matrix[msize + 1][msize + 1];
  matrix[0][0] = 0;
  for (unsigned int x = 1; x < msize + 1; ++x) {matrix[x][0] = CLAMP(x, 0, a.size());};
  for (unsigned int y = 1; y < msize + 1; ++y) {matrix[0][y] = CLAMP(y, 0, b.size());};

  for (unsigned int x = 1; x < msize + 1; ++x) {
    for (unsigned int y = 1; y < msize + 1; ++y) {
      matrix[x][y] = MIN_OF_THREE(matrix[x - 1][y], matrix[x - 1][y - 1], matrix[x][y - 1]);
      if (a[x - 1] != b[y - 1]) {++matrix[x][y];};
    }
  }

  // Logs matrix
  //for (int y = 0; y < msize + 1; ++y) {for (int x = 0; x < msize + 1; ++x) {std::cout << matrix[x][y] << " ";}; std::cout << "\n";};

  return matrix[msize][msize];
};

unsigned int strlib::edit_distance(std::string a, std::string b) {
  return T_edit_distance<std::string>(a, b);
};

unsigned int strlib::edit_distance(std::wstring a, std::wstring b) {
  return T_edit_distance<std::wstring>(a, b);
};

template <class string_type>
float T_percentual_similiarity(string_type a, string_type b) {
  return ((float)MAX_OF_TWO(a.size(), b.size()) - (float)T_edit_distance<string_type>(a, b)) / (float)MAX_OF_TWO(a.size(), b.size());
};

float strlib::percentual_similiarity(std::string a, std::string b) {
  return T_percentual_similiarity<std::string>(a, b);
};

float strlib::percentual_similiarity(std::wstring a, std::wstring b) {
  return T_percentual_similiarity<std::wstring>(a, b);
};