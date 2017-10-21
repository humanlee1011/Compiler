#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct DS10{
  int number;
  string str[10];
  DS10(int num, string* s = NULL) {
    number = num;
    for (int i = 0; i < num; i++) {
      str[i] = s[i];
    }
  }
  bool insert(string& s) {
    if (number < 9) {
      str[number++] = s;
      return true;
    }
    else
      return false;
  }
};

struct DS100 {
  int number;
  string str[100];
  DS100(int num, string* s = NULL) {
    number = num;
    for (int i = 0; i < num; i++) {
      str[i] = s[i];
    }
  }
  bool insert(string& s) {
    if (number < 99) {
      str[number++] = s;
      return true;
    }
    else
      return false;
  }
};

bool isLetters(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool isDigits(char ch) {
  return ch <= '9' && ch >= '0';
}

int isDS(DS10& ds, char ch) {
  for (int i = 0; i < ds.number; i++) {
    if (ch == ds.str[i][0]) {
      return i + 1;
    }
  }
  return 0;
}

void analyze(string str) {
  string k1[3] = {"int","main","return"};
  string k2[5] = {"+","*","=","+=","*="};
  string k3[6] = {"(",")","{","}",",",";"};
  DS10 keywords(3, k1);
  DS10 operators(5, k2);
  DS10 boundaries(6, k3);
  DS100 identifieres(0);
  DS100 Unsigned_integer(0);
  char ch = str[0];
  int pos = 0;
  while (pos < str.length()) {
    string letters, digits;
    int k = 0;
    if (ch == ' ' || ch == '\n') {
      ch = str[++pos];
      continue;
    }
    else if (isLetters(ch)) {
      while (isLetters(ch) || isDigits(ch)) {
        letters.insert(letters.end(), ch);
        ch = str[++pos];
      }
      bool isKeyWord = false, isIden = false;
      for (int i = 0; i < keywords.number; i++) {
        if (keywords.str[i] == letters) {
          isKeyWord = true;
          cout << "<1," << i << ">";
          break;
        }
      }
      for (int i = 0; i < identifieres.number; i++) {
        if (identifieres.str[i] == letters) {
          isIden = true;
          cout << "<4," << i << ">";
          break;
        }
      }
      if (!isKeyWord && !isIden) {
        cout << "<4," << identifieres.number << ">";
        identifieres.insert(letters);
      }
    }
    else if (isDigits(ch)) {
      while (isDigits(ch)) {
        digits.insert(digits.end(), ch);
        ch = str[++pos];
      }
      bool isUint = false;
      for (int i = 0; i < Unsigned_integer.number; i++) {
        if (Unsigned_integer.str[i] == digits) {
          isUint = true;
          cout << "<5," << i << ">";
        }
      }
      if (!isUint) {
        cout << "<5," << Unsigned_integer.number << ">";
        Unsigned_integer.insert(digits);
      }
    }
    else if (isDS(operators, ch)) {
      cout << "<2," << isDS(operators, ch) - 1 << ">";
      ch = str[++pos];
    }
    else if (isDS(boundaries, ch)) {
      cout << "<3," << isDS(boundaries, ch) - 1 << ">";
      ch = str[++pos];
    }
  }
  cout << "\nidentifieres:";
  for (int i = 0; i < identifieres.number; i++) {
    cout << identifieres.str[i] << ' ';
  }
  cout << "\nUnsigned_interger:";
  for (int i = 0; i < Unsigned_integer.number; i++) {
    cout << Unsigned_integer.str[i] << ' ';
  }
  cout << endl;

}

int main() {
  string program;
  char ch;
  while ((cin.get(ch)) && ch != '#')
    program.insert(program.end(), ch);
  analyze(program);
}

