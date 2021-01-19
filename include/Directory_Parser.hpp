// Copyright 2020 kropachevskiy <kropachev-95@mail.ru>

#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_

#include "Account.h"
#include "boost/filesystem.hpp"
#include "map"
#include "regex"
#include "set"
#include "string"
                                            /* b  a  l  a  n  c  e  _   0  0  0  0  1  2  3  4 */
const std::regex Regular_Exp("^(balance_)\\d\\d\\d\\d\\d\\d\\d\\d_\\d\\d\\d\\d\\d\\d\\d\\d");

class Directory_Parser{
 private:
  std::vector<boost::filesystem::path> Files;
  std::set<std::string> Accounts_Strings;
  std::vector<Account> Accounts;

 public:
  explicit Directory_Parser(std::string);
  void Files_For_Acc();
  std::string Print();

};

#endif  // INCLUDE_PARSER_HPP_
