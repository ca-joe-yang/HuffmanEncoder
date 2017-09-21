#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cassert>
#include "util.h"

using namespace std;

string charToBit(const char& c) 
{
   int sign = 1;
   char ch = c;
   string str = "";
   if (ch == -128)
      return "10000000";
   if (ch < 0) { ch = -ch; sign = -1;}
   else str[1] = 0;
   while (ch > 0) {
      if (ch % 2 == 0)
         str = "0" + str;
      else
         str = "1" + str;
      ch /= 2;
   }
   for (; str.size() < 7;) {
      str = "0" + str;
   }
   if (sign == -1) str = "1" + str;
   else str = "0" + str;
   return str;
}

char bitToChar(const string& str) 
{
   int sign = 1;
   char c = 0;
   if (str[0] == '1') sign = -1; 
   for (size_t i = 1; i < 8; ++i) {
      char strCh = str[i] - '0';
      c = c * 2 + strCh;
   }
   if (sign == -1 && c == 0) return -128;
   c *= sign;
   return c;
}

// compare s1 to s2
int myStrNCmp(const string& str1, const string& str2, size_t n)
{
   assert(n > 0);
   size_t n2 = str2.size();
   if (n2 == 0) return -1;
   size_t n1 = str1.size();
   assert(n1 >= n);
   for (size_t i = 0; i < n1; ++i) {
      if (i == n2) return (i < n) ? 1 : 0;
      char ch1 = (isupper(str1[i])) ? tolower(str1[i]) : str1[i];
      char ch2 = (isupper(str2[i])) ? tolower(str2[i]) : str2[i];
      if (ch1 != ch2)
         return (ch1 - ch2);
   }
   return (n1 - n2);
}

size_t myStrGetTok(const string& str, string& tok, size_t pos, const char del) 
{
   size_t begin = str.find_first_not_of(del, pos);
   if (begin == string::npos) {
      tok = "";
      return begin;
   }
   size_t end = str.find_first_of(del, begin);
   tok = str.substr(begin, end - begin);
   return end;
}

bool myStrToInt(const string& str, int& num) 
{
   num = 0;
   size_t i = 0;
   int sign = 1;
   if (str[0] == '-') { sign = -1; i = 1; }
   bool valid = false;
   for (; i < str.size(); ++i) {
      if (isdigit(str[i] == 0)) return false;
      num *= 10;
      num += int(str[i] - '0');
      valid = true;
   }
   num *= sign;
   return valid;
}

bool myIntToStr(const int& num, string& str) {
   int n = num;
   if (n == 0) str = "0";
   while (n > 0) {
      str = char(char(n % 10) + '0') + str;
      n /= 10;
   }
   return true;
}

size_t fileSize(const string& fileName) {
   fstream file;
   file.open(fileName.c_str());
   file.seekg(0, file.end);
   size_t s = file.tellg();
   file.close();
   return s;
}

string getFileName(const string& str)
{
   string name = str;
   size_t i = name.length();
   for (; i > 0; i --) {
        if (name[i - 1] == '/') break;
   }
   if (i != 0) name = name.substr(i, name.length() - 1);
   return name;
}

