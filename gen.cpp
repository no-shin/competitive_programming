#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: gen testcase_id\n";
    return 1;
  }

  int id = stoi(argv[1]);

  // idを使えばケースごとに内容を変えられる
  uniform_int_distribution<int> dist(1, 100);

  cout << dist(rng) << '\n';
}
