#pragma once
#include <bits/stdc++.h>
using namespace std;


template<std::int64_t Modulus> class modint;
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
string myToStr(const multiset<T>& se);
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

template<std::int64_t Modulus>
string myToStr(const modint<Modulus>& modint) {
    return myToStr(modint.value);
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

template <class T>
string myToStr(const multiset<T>& se) {
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

template <std::int64_t Modulus> class modint {
    public:
    int64_t value;

    constexpr modint(const int64_t x = 0) noexcept : value(x % Modulus) {assert(x >= 0);}
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
        value += rhs.value;
        if (value >= Modulus) {
            value -= Modulus;
        }
        return *this;
    }
    constexpr modint &operator-=(const modint rhs) noexcept {
        if (value < rhs.value) {
            value += Modulus;
        }
        value -= rhs.value;
        return *this;
    }
    constexpr modint &operator*=(const modint rhs) noexcept {
        value = value * rhs.value % Modulus;
        return *this;
    }
    constexpr modint &operator/=(modint rhs) noexcept {
        if(value%rhs.value!=0) {
            cout<<"modint error!: cannnot divide value ("<<value<<") by ("<<rhs.value<<")"<<endl;
            exit(1);
        }
        value = value/rhs.value;
        return *this;
    }

    constexpr modint pow(int64_t t) noexcept {
        if(t==0) return 1;
        modint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }
    constexpr modint inv() noexcept {
        return pow(Modulus-2);
    }
    friend std::istream &operator>>(std::istream &is, modint &x) { int64_t t; is >> t; x = modint(t); return is; }
    friend std::ostream &operator<<(std::ostream &os, const modint &x) { os << x.value;  return os; }

    static modint calcPermutation(int64_t n, int64_t r){
        modint res = 1;
        for(int64_t i = 0; i < r; ++i){
            res *= (n - i);
        }
        return res;
    }

    static modint calcCombination(int64_t n, int64_t r) {
        assert(n<Modulus);
        static vector<modint> factorial, factorial_inv;
        if (factorial.size() == 0) {
            int maxsize = 2000000;
            factorial.resize(maxsize);
            factorial_inv.resize(maxsize);
            factorial[0] = 1;
            for(int i=1; i<=maxsize; ++i) factorial[i] = factorial[i-1] * i;
            factorial_inv[maxsize] = factorial[maxsize].inv();
            for(int i=maxsize; i>=1; --i) factorial_inv[i-1] = factorial_inv[i] * i;
        }
        return factorial[n]*factorial_inv[r]*factorial_inv[n-r];
    }
};
