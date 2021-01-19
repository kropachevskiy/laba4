// Copyright 2020 kropachevskiy <kropachev-95@mail.ru>

#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_

#include "Account.h"
#include "boost/filesystem.hpp"
#include "map"
#include "regex"
#include "set"
#include "string"

const std::regex Regular_Exp("^(balance_)\\d\\d\\d\\d\\d\\d\\d\\d_\\d\\d\\d\\d\\d\\d\\d\\d");

class Directory_Parser{
 private:
  std::vector<boost::filesystem::path> Files;
  std::set<std::string> Accounts_Strings;
  std::vector<Account> Accounts;

 public:
  explicit Directory_Parser(std::string);
  void Files_For_Acc();
  friend std::ostream & operator << (std::ostream & out, Directory_Parser& a);

};

#endif  // INCLUDE_PARSER_HPP_
