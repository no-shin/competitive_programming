#include <bits/stdc++.h>
using namespace std;

int main() {
  int limit;
  cin >> limit;

  int l = 1, r = 100;

  while (limit--) {
    int mid = (l + r) / 2;

    cout << mid << endl;
    cout.flush();

    string res;
    cin >> res;

    if (res == "CORRECT") {
      return 0;
    } else if (res == "HIGHER") {
      l = mid + 1;
    } else if (res == "LOWER") {
      r = mid - 1;
    } else {
      return 0;
    }
  }
}
