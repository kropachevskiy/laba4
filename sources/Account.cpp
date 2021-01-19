// Copyright 2020 kropachevskiy <kropachev-95@mail.ru>

#include "Account.h"

void Account::Add_File(boost::filesystem::path path) { Files.push_back(path); }

void Account::Increment_Files_Sum() { ++Files_Sum; }

void Account::Set_Last_Date(int date) { Last_Date = date; }

void Account::Set_Brocker(std::string Brocker_Arg) { Brocker = Brocker_Arg; }

void Account::Set_Account_Number(std::string Acc_Num) { Account_Number = Acc_Num; }

std::string Account::Get_Brocker() { return Brocker; }

std::string Account::Get_Account_Number() { return Account_Number; }

std::size_t Account::Get_File_Sum() { return Files_Sum; }

int Account::Get_Last_Date() { return Last_Date; }
