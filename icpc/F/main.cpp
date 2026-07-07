#include <bits/stdc++.h>
using namespace std;
#pragma region templates
struct Init {
  Init() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(13);
  }
} init;

using ll = long long;
using lint = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using i128 = __int128_t;
template <typename T> using minpq = priority_queue<T, vector<T>, greater<T>>;

#define uniqv(v) v.erase(unique(all(v)), v.end())
#define OVERLOAD_REP(_1, _2, _3, name, ...) name
#define REP1(i, n) for (auto i = std::decay_t<decltype(n)>{}; (i) < (n); ++(i))
#define REP2(i, l, r) for (auto i = (l); (i) < (r); ++(i))
#define rep(...) OVERLOAD_REP(__VA_ARGS__, REP2, REP1)(__VA_ARGS__)
#define REP(i, x, limit) for (int i = (x); i <= (limit); ++i)
#define all(x) std::begin(x), std::end(x)
#define rall(x) std::rbegin(x), std::rend(x)
#define el '\n'
#define spa ' '
#define Yes cout << "Yes" << el
#define No cout << "No" << el
#define YES cout << "YES" << el
#define NO cout << "NO" << el
#define END(x) cout << (x) << el, exit(0)
#define debug(x) cerr << #x << " = " << x << el

[[maybe_unused]] const int inf = 1073741823;
[[maybe_unused]] const ll infl = 1LL << 60;

std::string i128_to_str(const __int128_t &target) {
  std::string res_str;
  __uint128_t target_tmp = target < 0 ? -target : target;
  do {
    res_str += target_tmp % 10 + '0';
    target_tmp /= 10;
  } while (target_tmp != 0);
  if (target < 0)
    res_str += '-';
  std::reverse(std::begin(res_str), std::end(res_str));
  return res_str;
}

// is_pair
template <typename T> constexpr bool is_pair_v = false;
template <typename T, typename U>
constexpr bool is_pair_v<std::pair<T, U>> = true;

// istreamable
#if __cplusplus >= 202002L
template <typename T>
concept istreamable_v = requires(T a) { std::cin >> a; };
#else // earlier C++20
template <typename T, typename = void> constexpr bool istreamable_v = false;
template <typename T>
constexpr bool
    istreamable_v<T, std::void_t<decltype(std::cin >> std::declval<T &>())>> =
        true;
#endif

// ostreamable
#if __cplusplus >= 202002L
template <typename T>
concept ostreamable_v = requires(T a) { std::cout << a; };
#else // earlier C++20
template <typename T, typename = void> constexpr bool ostreamable_v = false;
template <typename T>
constexpr bool
    ostreamable_v<T, std::void_t<decltype(std::cout << std::declval<T &>())>> =
        true;
#endif

// iterable
#if __cplusplus >= 202002L
#if __has_include(<ranges>)
template <typename T>
concept iterable_v = std::ranges::range<T>;
#else // C++20, not has <ranges>
template <typename T>
concept iterable_v = requires(T a) {
  std::begin(a);
  std::end(a);
};
#endif
#else // earlier C++20
template <typename T>
constexpr bool iterable_v =
    std::is_same_v<decltype(std::begin(std::declval<T>())),
                   decltype(std::end(std::declval<T>()))>;
#endif

// concepts for debug use only:
#if __cplusplus >= 202002L
// stack_like_v (std::stack, std::priority_queue)
template <typename T>
concept stack_like_v = requires(T t) {
  requires(std::same_as<decltype(t.top()), typename T::reference> ||
           std::same_as<decltype(t.top()), typename T::const_reference>);
  { t.pop() };
  { t.empty() } -> std::same_as<bool>;
};

// queue_like_v (std::queue)
template <typename T>
concept queue_like_v = requires(T t) {
  { t.front() } -> std::same_as<typename T::reference &>;
  { t.pop() };
  { t.empty() } -> std::same_as<bool>;
};
#endif

void input() { return; }
template <typename T, typename... Rest> void input(T &target, Rest &...rest) {
  if constexpr (istreamable_v<T>)
    cin >> target;
  else if constexpr (iterable_v<T>)
    for (auto &e : target)
      input(e);
  else if constexpr (is_pair_v<T>) {
    input(target.first);
    input(target.second);
  } else if constexpr (std::is_convertible_v<long long, T>) {
    long long val;
    input(val);
    target = val;
  } else {
    cerr << "Invalid Input: Unreadable variable detected" << std::endl;
    assert(false);
  }
  input(rest...);
}

// output for debugging
template <typename T> void write_value(const T &target) {
  using V = std::decay_t<T>;
  if constexpr (ostreamable_v<V>) {
    std::cout << target;
  } else if constexpr (is_pair_v<V>) {
    std::cout << '{';
    write_value(target.first);
    std::cout << ',';
    write_value(target.second);
    std::cout << '}';
  } else if constexpr (iterable_v<V>) {
    std::cout << '[';
    bool first = true;
    for (const auto &e : target) {
      if (!first)
        std::cout << ", ";
      write_value(e);
      first = false;
    }
    std::cout << ']';
  } else if constexpr (std::is_convertible<V, __int128_t>::value) {
    write_value(i128_to_str(target));
  } else if constexpr (std::is_convertible_v<V, long long>) {
    write_value(static_cast<long long>(target));
  } else if constexpr (stack_like_v<V>) {
    auto tmp = target;
    std::cout << '[';
    bool first = true;
    while (!tmp.empty()) {
      if (!first)
        std::cout << ", ";
      write_value(tmp.top());
      tmp.pop();
      first = false;
    }
    std::cout << ']';
  } else if constexpr (queue_like_v<V>) {
    auto tmp = target;
    std::cout << '[';
    bool first = true;
    while (!tmp.empty()) {
      if (!first)
        std::cout << ", ";
      write_value(tmp.front());
      tmp.pop();
      first = false;
    }
    std::cout << ']';
  } else {
    std::cerr << "Invalid Output: Unwritable variable detected" << std::endl;
    assert(false);
  }
}

void output() { std::cout << '\n'; }
template <typename T, typename... Rest>
void output(const T &target, const Rest &...rest) {
  write_value(target);
  if constexpr (sizeof...(rest) > 0) {
    std::cout << ' ';
    output(rest...);
  } else {
    std::cout << '\n';
  }
}

template <typename T1, typename T2> bool chmin(T1 &a, T2 b) {
  return a > b ? a = b, true : false;
}
template <typename T1, typename T2> bool chmax(T1 &a, T2 b) {
  return a < b ? a = b, true : false;
}

// a^bを返す オーバーフローに注意
ll Pow(ll a, ll b) {
  assert(b >= 0);
  if (a == 0 and b == 0)
    return 1;
  if (a == 1)
    return 1;
  if (a == -1)
    return (b & 1) ? -1 : 1;
  ll res = 1;
  while (b) {
    if (b & 1)
      res *= a;
    b >>= 1;
    if (b)
      a *= a;
  }
  return res;
}

// 二分探索による、浮動小数点型を介さないsqrt
// 制約：0 <= x <= LLONG_MAX
ll ll_sqrt(ll x) {
  assert(0 <= x);
  ll ok = 0, ng = x / 2 + 2;
  while (abs(ok - ng) > 1) {
    ll mid = (ok + ng) / 2;
    if (x / mid < mid)
      ng = mid;
    else
      ok = mid;
  }
  return ok;
}

// 浮動小数点型を介さず、aを底とした対数関数 log_a(x)以上の最小の整数を返す
// 制約: 0 < x <= LLONG_MAX, 1 < a <= LLONG_MAX
ll ll_log(ll x, ll a = 2) {
  assert(x > 0 && a > 1);
  ll res = 0;
  while (x > 1) {
    x = (x + a - 1) / a;
    res++;
  }
  return res;
}

// Pythonのenumerateみたいなやつ　[index,value]を範囲for文に提供
template <typename T> vector<pair<int, T>> enumerate(const vector<T> &v) {
  vector<pair<int, T>> res(ssize(v));
  for (int i = 0; i < ssize(v); i++)
    res[i] = {i, v[i]};
  return res;
}
vector<pair<int, char>> enumerate(const string &s) {
  vector<pair<int, char>> res(s.size());
  for (int i = 0; i < s.size(); i++)
    res[i] = {i, s[i]};
  return res;
}

// 第二引数を第一引数の比較関数でソートして、その順番で第三引数以降もソート
template <typename Compare, typename... Vectors>
vector<size_t> multipleSort(Compare comp = Compare(), Vectors &...vectors) {
  const size_t size = std::get<0>(std::tie(vectors...)).size();
  ((void)std::initializer_list<int>{
      (vectors.size() == size ? 0
                              : throw std::invalid_argument(
                                    "Vectors must have the same size"))...});

  std::vector<size_t> indices(size);
  std::iota(indices.begin(), indices.end(), 0);

  std::sort(indices.begin(), indices.end(), [&](size_t i, size_t j) {
    return comp(std::get<0>(std::tie(vectors...))[i],
                std::get<0>(std::tie(vectors...))[j]);
  });

  auto reorder = [&](auto &vec) {
    auto temp = vec;
    for (size_t i = 0; i < size; ++i) {
      vec[i] = temp[indices[i]];
    }
  };
  (reorder(vectors), ...);
  return indices;
}

template <typename T> T floor(T x, T y) {
  return x / y - (x % y && (x ^ y) < 0);
}
template <typename T> T ceil(T x, T y) { return floor(x + y - 1, y); }
template <typename T> T bmod(T x, T y) { return x - y * floor(x, y); }
template <typename T> pair<T, T> divmod(T x, T y) {
  T q = floor(x, y);
  return {q, x - y * q};
}

#pragma endregion

int main() {
  lint n, u, v;
  while (1) {
    input(n, u, v);

    if (n == 0)
      break;
    lint m;
    input(m);
    vector<pair<lint, lint>> cor;
    vector<lint> a(m), b(m), c(m), d(m);

    for (int i = 0; i < m; i++)
      cin >> a[i] >> b[i] >> c[i] >> d[i];

    vector<ll> x = {u}, y = {v};
    rep(i, 0, m) {
      if (a[i] - 1 > 0)
        x.emplace_back(a[i] - 1);
      // x.emplace_back(a[i]);
      // x.emplace_back(b[i]);
      if (b[i] + 1 <= n)
        x.emplace_back(b[i] + 1);
      if (c[i] - 1 > 0)
        y.emplace_back(c[i] - 1);
      // y.emplace_back(c[i]);
      // y.emplace_back(d[i]);
      if (d[i] + 1 <= n)
        y.emplace_back(d[i] + 1);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    uniqv(x);
    uniqv(y);

    const int xn = x.size();
    const int yn = y.size();
    map<pair<int, int>, int> mp;
    int idx{};
    rep(i, 0, xn) rep(j, 0, yn) { mp[{x[i], y[j]}] = idx++; }
    // output(mp);
    const int N = mp.size();
    vector<pii> invmp;
    for (auto [p, _] : mp) {
      invmp.emplace_back(p);
    }
    vector G(N, vector<pll>());
    auto check = [&](int aa, int bb) {
      if (aa < 0 or N <= aa or bb < 0 or N <= bb)
        return false;
      auto [xa, ya] = invmp[aa];
      auto [xb, yb] = invmp[bb];
      if (xa != xb and ya != yb)
        return false;
      if (xa == xb) {
        rep(i, 0, m) {
          bool isok = false;
          if (a[i] > xa or xa > b[i])
            isok = true;
          if (min(ya, yb) > d[i] or max(ya, yb) < c[i])
            isok = true;
          if (!isok)
            return false;
        }
        return true;
      } else {
        rep(i, 0, m) {
          bool isok = false;
          if (min(xa, xb) > b[i] or max(xa, xb) < a[i])
            isok = true;
          if (c[i] > ya or ya > d[i])
            isok = true;
          if (!isok)
            return false;
        }
        return true;
      }
    };
    rep(i, 0, N) {
      auto [xi, yi] = invmp[i];
      if (check(i, i + 1)) {
        auto [xi1, yi1] = invmp[i + 1];
        G[i].emplace_back(i + 1, (yi1 - yi));
      }
      if (check(i, i - 1)) {
        auto [xi1, yi1] = invmp[i - 1];
        G[i].emplace_back(i - 1, (yi - yi1));
      }
      if (check(i, i + yn)) {
        auto [xi1, yi1] = invmp[i + yn];
        G[i].emplace_back(i + yn, (xi1 - xi));
      }
      if (check(i, i - yn)) {
        auto [xi1, yi1] = invmp[i - yn];
        G[i].emplace_back(i - yn, (xi - xi1));
      }
    }

    // output(G);
    // 始点
    auto kinbou = [&](pii p) {
      auto [px, py] = p;
      vector<pii> res;
      vector<int> X, Y;
      if (lower_bound(x.begin(), x.end(), px) != x.end() and
          *lower_bound(x.begin(), x.end(), px) == px) {
        X.emplace_back(px);
      } else {
        auto ue = lower_bound(x.begin(), x.end(), px);
        if (ue != x.end())
          X.emplace_back(*ue);
        if (ue != x.begin()) {
          ue--;
          X.emplace_back(*ue);
        }
      }
      if (lower_bound(y.begin(), y.end(), py) != y.end() and
          *lower_bound(y.begin(), y.end(), py) == py) {
        Y.emplace_back(py);
      } else {
        auto migi = lower_bound(y.begin(), y.end(), py);
        if (migi != y.end())
          Y.emplace_back(*migi);
        if (migi != y.begin()) {
          migi--;
          Y.emplace_back(*migi);
        }
      }
      for (auto ex : X)
        for (auto ey : Y)
          res.emplace_back(ex, ey);
      return res;
    };

    vector<pll> kinbousitenn = {{u, v}};
    vector<ll> dist(N, infl);
    minpq<pair<ll, pii>> que;
    for (auto p : kinbousitenn) {
      ll mand = abs(p.first - u) + abs(p.second - v);
      que.push({mand, p});
    }
    int cnt{};
    while (que.size()) {
      auto [d, p_] = que.top();
      que.pop();
      int p = mp[p_];
      if (dist[p] != infl)
        continue;
      dist[p] = d;
      for (auto q : G[p]) {
        que.push({d + q.second, invmp[q.first]});
      }
      cnt++;
      // if(cnt>=1e5){
      //     output(que);
      //     output(dist);
      //     break;
      // }
    }

    // output(dist);

    int Q;
    cin >> Q;
    while (Q--) {
      int a, b;
      cin >> a >> b;
      auto v_ = kinbou({a, b});
      ll ans = infl;

      for (auto [ex, ey] : v_) {
        chmin(ans, abs(ex - a) + abs(ey - b) + dist[mp[{ex, ey}]]);
      }
      if (ans == infl)
        output("no");
      else
        output(ans);
    }
    // output(x);
    // output(y);
    // output();
  }
}
