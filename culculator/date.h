#pragma once
#include <string>
#include <fstream>
#include <vector>

struct Date {
  int day;
  int month;
  int year;
  Date() {}
  Date(int day, int month, int year) : day(day), month(month), year(year) {}
};

std::string DateToString(const Date&);
std::string PrevDate(const Date&);
std::string NextDate(const Date&);
bool IsLess(const Date&, const Date&);
bool IsLipYear(const int);
void ProcessDates(const std::string&, const std::string&);
int DateToDays(const Date&);
