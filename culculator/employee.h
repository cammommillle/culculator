#pragma once
#include <cassert>
#include "date.h"
#include <iostream>
#include <string>

class Employee {
 public:
  Employee() {}
  Employee(const std::string&, const std::string&, const Date&, const Date&);
  std::string GetFullName() const;
  std::string ToString() const;
  int GetAgeInYears(const Date&) const;
  int GetTenureInDays(const Date&) const;
 private:
  std::string first_name_;
  std::string last_name_;
  Date birth_date_;
  Date hiring_date_;
};
