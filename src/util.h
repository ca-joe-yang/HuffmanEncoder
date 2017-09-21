#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<fstream>

using namespace std;

string charToBit(const char& c);
char bitToChar(const string& str);

int myStrNCmp(const string& str1, const string& str2, size_t n);
size_t myStrGetTok(const string& str, string& tok, size_t pos = 0, const char del = ' ');

bool myStrToInt(const string& str, int& num);
bool myIntToStr(const int& num, string& str);

size_t fileSize(const string& fileName);

string getFileName(const string& str);
