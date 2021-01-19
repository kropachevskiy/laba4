// Copyright 2020 kropachevskiy <kropachev-95@mail.ru>

#include "Directory_Parser.hpp"

#include "boost/filesystem.hpp"
#include "iostream"

Directory_Parser::Directory_Parser(std::string path_For_Parser) {
  const boost::filesystem::path path_Obj{path_For_Parser};
  if (boost::filesystem::exists(path_Obj)) {
    for (auto itEntry = boost::filesystem::recursive_directory_iterator(path_Obj);
         itEntry != boost::filesystem::recursive_directory_iterator(); ++itEntry)
    {
      if (boost::filesystem::is_regular_file(itEntry->path())) {
        /* balance_00001234_20181001.old.txt */
        if ((itEntry->path().stem().extension() == "")) {
          /* balance_00001234_20181001.txt */
          if (itEntry->path().extension() == ".txt") {
            /*balance_00001234                                   , balance_\\d\\d\\d\\d\\d\\d\\d\\d*/
            if (std::regex_search(itEntry->path().stem().string(), Regular_Exp)) {
              Files.push_back(itEntry->path());
              /* /home/.../bcs/balance_00001234_20181001.txt */
              Accounts_Strings.insert(itEntry->path().stem().string().substr(8, 8));
            }
          }
        }
      }

      if (boost::filesystem::is_symlink(itEntry->path())) {
        for (auto itEntrySymLink = boost::filesystem::recursive_directory_iterator(itEntry->path());
             itEntrySymLink != boost::filesystem::recursive_directory_iterator(); ++itEntrySymLink) {
          if (boost::filesystem::is_regular_file(itEntry->path())) {
            /* balance_00001234_20181001.old.txt */
            if ((itEntry->path().stem().extension() == "")) {
              /* balance_00001234_20181001.txt */
              if (itEntry->path().extension() == ".txt") {
                /*balance_00001234                                   , balance_\\d\\d\\d\\d\\d\\d\\d\\d*/
                if (std::regex_search(itEntry->path().stem().string(),Regular_Exp)) {
                  Files.push_back(itEntry->path());
                  /* /home/.../bcs/balance_00001234_20181001.txt */
                  Accounts_Strings.insert(itEntry->path().stem().string().substr(8, 8));
                }
              }
            }
          }
        }
      }
    }
  }
}

void Directory_Parser::Files_For_Acc() {
  for (auto acc : Accounts_Strings) {
    Account tempAcc;
    tempAcc.Set_Account_Number(acc);
    int lastDate = 0;
    for (auto file : Files) {
      /* balance_00001234_20181001.txt */
      if (file.filename().string().substr(8, 8) == acc) {
        tempAcc.Increment_Files_Sum();
        tempAcc.Add_File(file);
        tempAcc.Set_Brocker(
            file.parent_path().filename().string()); /* ib, bcs, otkritie */
        /* balance_00001234_20181001.txt */
        if (std::stoi(file.filename().stem().string().substr(17, 8)) > lastDate) {
          lastDate = std::stoi(file.filename().stem().string().substr(17, 8));
        }
      }
    }
    tempAcc.Set_Last_Date(lastDate);
    Accounts.push_back(tempAcc);
  }
}

std::string Directory_Parser::Print() {
  std::stringstream ss;
  for (auto file : Files) {
    ss << file.parent_path().filename().string() << "\t" << file.filename().string() << "\n";
          /* bcs                                            balance_00122223_20181010.txt */
  }
  for (auto acc : Accounts) {
    ss << "broker:" << acc.Get_Brocker() << "\t" << "account:" << acc.Get_Account_Number() << "\t"
       /*  broker:     ib                            account:     00100001              */
       << "files:" << acc.Get_File_Sum() << "\t" << "lastdate:" << acc.Get_Last_Date() << "\n";
       /*  files:     48                             lastdate:     20181018            */
  }
  return ss.str();
}