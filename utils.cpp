#pragma once
#include <bits/stdc++.h>
using namespace std;

/*========== output utilities ===========*/

template <class T>
string myToStr(const T& misc);
string myToStr(const char* c);
string myToStr(const string& s);
template <class T>
string myToStr(const pair<T, T>& p);
template <class T>
string myToStr(const set<T>& se);
template <class T>
string myToStr(const vector<T>& vec);
template <class T, class U>
string myToStr(const map<T, U>& mp);
template <class T>
string myToStr(const vector<vector<T>>& vec);

template <class T>
string myToStr(const T& misc) {
    return to_string(misc);
}

string myToStr(const char* c) {
    string s = c;
    return s;
}

string myToStr(const string& s) {
    return s;
}

template <class T>
string myToStr(const pair<T, T>& p) {
    string ret = "(" + myToStr(p.first) + ", " + myToStr(p.second) + ")";
    return ret;
}

template <class T>
string myToStr(const vector<T>& vec) {
    string ret = "[";
    for (int i=0; i<vec.size(); ++i) {
        ret += myToStr(vec[i]);
        if (i < vec.size() -1 ) ret += ", ";
    }
    ret+="]";
    return ret;
}

template <class T>
string myToStr(const set<T>& se) {
    string ret = "{";
    int cnt=0; //もっと良い書き方はあるはず
    for(auto e: se) {
        ret += myToStr(e);
        if(++cnt < se.size()) ret += ", ";
    }
    ret += "}";
    return ret;
}

template <class T, class U>
string myToStr(const map<T, U>& mp) {
    string ret = "{";
    int cnt=0; //もっと良い書き方はあるはず
    for(auto p: mp) {
        ret += myToStr(p.first) + ": " + myToStr(p.second);
        if(++cnt < mp.size()) ret += ", ";
    }
    ret += "}";
    return ret;
}

template <class T>
string myToStr(const vector<vector<T>>& vec) {
    string ret = "[";
    for (int i=0; i<vec.size(); ++i) {
        if (i != 0) ret += " ";
        ret += myToStr(vec[i]);
        if (i < vec.size() -1 ) ret += "\n";
    }
    ret+="]";
    return ret;
}


// パラメータパックが空になったら終了
void print() {cout<<endl;}

// ひとつ以上のパラメータを受け取るようにし、
// 可変引数を先頭とそれ以外に分割する
template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail)
{
    std::cout << myToStr(head);
    constexpr std::size_t tail_size = sizeof...(Tail);
    if(tail_size) cout<<" ";

    // パラメータパックtailをさらにheadとtailに分割する
    print(std::forward<Tail>(tail)...);
}

/*======================================*/


vector<vector<bool>> getSubgraph(const vector<vector<bool>>& base, const vector<int>& nodes) {
    auto M = nodes.size();
    vector<vector<bool>> subgraph(M, vector<bool>(M, false));
    for(int i=0; i<M; ++i) {
        for(int j=0; j<M; ++j) {
            subgraph[i][j] = base[nodes[i]][nodes[j]];
        }
    }
    return subgraph;
}

vector<int> getPositiveBits(int64_t bit) {
    vector<int> indices;
    for(int i=0; 1<<i <= bit; ++i) {
        if(bit & 1<<i) indices.push_back(i);
    }
    return indices;
}

vector<int> getNegativeBits(int64_t bit) {
    vector<int> indices;
    for(int i=0; 1<<i <= bit; ++i) {
        if(! (bit & 1<<i)) indices.push_back(i);
    }
    return indices;
}



int64_t calcPermutation(int64_t n, int64_t r){
    int64_t res = 1;
    for(int64_t i = 0; i < r; ++i){
        res *= (n - i);
    }
    return res;
}

int64_t calcCombination(int64_t n, int64_t r){
    return calcPermutation(n, r) / calcPermutation(r, r);
}


class range {
    private:
    struct I{
        int x;
        int operator*(){return x;}
        bool operator!=(I& lhs){return x != lhs.x;}
        void operator++(){++x;}
    };
    I i,n;
    
    public:
    range(int n):i({0}),n({n}){}
    range(int i,int n):i({i}),n({n}){}
    I& begin(){return i;}
    I& end(){return n;}
};

template <std::uint_fast64_t Modulus> class modint {
  using u64 = std::uint_fast64_t;

public:
  u64 a;

  constexpr modint(const u64 x = 0) noexcept : a(x % Modulus) {}
  constexpr u64 &value() noexcept { return a; }
  constexpr const u64 &value() const noexcept { return a; }
  constexpr modint operator+(const modint rhs) const noexcept {
    return modint(*this) += rhs;
  }
  constexpr modint operator-(const modint rhs) const noexcept {
    return modint(*this) -= rhs;
  }
  constexpr modint operator*(const modint rhs) const noexcept {
    return modint(*this) *= rhs;
  }
  constexpr modint operator/(const modint rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint rhs) noexcept {
    a += rhs.a;
    if (a >= Modulus) {
      a -= Modulus;
    }
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (a < rhs.a) {
      a += Modulus;
    }
    a -= rhs.a;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    a = a * rhs.a % Modulus;
    return *this;
  }
  constexpr modint &operator/=(modint rhs) noexcept {
    u64 exp = Modulus - 2;
    while (exp) {
      if (exp % 2) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }
};
