#include<iostream>
#include<string>
using namespace std;
class Solution {
 public:
  int convert(string str) {
    if (str.size() == 0) {
      return 0;
    }
    int i = 0;
    while (i < str.length() && str[i] == ' ') {
      i++;
    }
    if (i >= str.length()
        || (str[i] != '-'
            && str[i] != '+' && !((str[i] >= '0') && (str[i] <= '9')))) {
      return 0;
    }
    int sign = 1;
    if (i < str.length() && (str[i] == '-' || i < str.length() && str[i] == '+')) {
      sign = str[i] == '-' ? -1 : 1;
      i++;
    }
    // 需要无符号数，否则 -2147483648会溢出
    unsigned int sum = 0;
    for (; i < str.length(); i++) {
      if (str[i] >= '0' && str[i] <= '9') {
        if (sign == 1) {
          if (sum > INT_MAX / 10 || sum == INT_MAX / 10 && (str[i] - '0') > 7) {
            return INT_MAX;
          }
        } else {
          if (sum > (INT_MAX) / 10 || sum == (INT_MAX) / 10 && (str[i] - '0') > 8) {
            return INT_MIN;
          }
        }
        sum = sum * 10 + (str[i] - '0');
      } else {
        return sum * sign;
      }
    }
    return sum * sign;
  }
};
int main() {
  Solution solution;
  cout << solution.convert(" 32") << endl;
  cout << solution.convert("+32") << endl;
  cout << solution.convert(" -32") << endl;
  cout << solution.convert("32 abc") << endl;
  cout << solution.convert("8917239179619698") << endl;
  return 0;
}