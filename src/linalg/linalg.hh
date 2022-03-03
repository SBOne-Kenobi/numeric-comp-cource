#ifndef LINALG_LINALG_HH
#define LINALG_LINALG_HH

#include <ostream>
#include <vector>
#include <optional>

class Expression {};
template <class T>
class Array;

template <class E>
Array<typename E::value_type> evaluate(const E& expr) {
    using value_type = typename E::value_type;
    const auto n = expr.size();
    Array<value_type> result(n);
    for (int i=0; i<n; ++i) {
        result(i) = expr.evaluate(i);
    }
    return result;
}

template<class E1, class E2>
typename std::enable_if<std::is_base_of<Expression, E1>::value &&
                        std::is_base_of<Expression, E2>::value, bool>::type
operator ==(const E1& a, const E2& b) {
    const auto n = a.size();
    const auto m = b.size();
    if (n != m) return false;
    for (int i=0; i<n; ++i) {
        if (a.evaluate(i) != b.evaluate(i))
            return false;
    }
    return true;
}

template <class T>
class Array: public Expression {

public:
    using value_type = T;

private:
    std::vector<T> _data;

public:

    Array(std::initializer_list<T> rhs): _data(rhs) {}
    explicit Array(int n): _data(n) {}
    template <class E>
    Array(const E& expr,
           typename std::enable_if<std::is_base_of<Expression,E>::value,E>::type* dummy=nullptr):
    Array(::evaluate(expr)) {}

    Array() = default;
    ~Array() = default;
    Array(Array&& rhs) = default;
    Array(const Array& rhs) = default;
    Array& operator=(Array&& rhs) = default;
    Array& operator=(const Array& rhs) = default;

    T& operator()(int i) { return this->_data[i]; }
    const T& operator()(int i) const { return this->_data[i]; }
    T evaluate(int i) { return this->_data[i]; }
    T evaluate(int i) const { return this->_data[i]; }
    int size() const { return this->_data.size(); }
    void display(std::ostream& out) const {
        out << "Array(";
        const auto n = size();
        if (n != 0) { out << this->_data.front(); }
        for (int i=1; i<n; ++i) { out << ',' << this->_data[i]; }
        out << ')';
    }

};

template <class E>
typename std::enable_if<std::is_base_of<Expression,E>::value,std::ostream&>::type
operator<<(std::ostream& out, const E& expr) {
    expr.display(out); return out;
}

template <class E1, class E2>
class Plus: public Expression {

public:
    using value_type =
        typename std::common_type<typename E1::value_type,typename E2::value_type>::type;

private:
    const E1& _a;
    const E2& _b;

public:
    explicit Plus(const E1& a, const E2& b): _a(a), _b(b) {}
    value_type evaluate(int i) { return this->_a.evaluate(i) + this->_b.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i) + this->_b.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "Plus(" << this->_a << ", " << this->_b << ')';
    }

};

template <class E1, class E2>
typename std::enable_if<std::is_base_of<Expression,E1>::value &&
                        std::is_base_of<Expression,E2>::value,Plus<E1,E2>>::type
operator+(const E1& a, const E2& b) {
    return Plus<E1,E2>(a,b);
}

template<class E1, class E2>
class Less: public Expression {
public:
    using value_type = char; // because vector<bool> bad with bool&

private:
    const E1& _a;
    const E2& _b;

public:
    explicit Less(const E1& a, const E2& b): _a(a), _b(b) {}
    value_type evaluate(int i) { return this->_a.evaluate(i) < this->_b.evaluate(i); }
    value_type evaluate(int i) const { return this->_a.evaluate(i) < this->_b.evaluate(i); }
    int size() const { return this->_a.size(); }
    void display(std::ostream& out) const {
        out << "Less(" << this->_a << ", " << this->_b << ')';
    }
};

template<class E1, class E2>
typename std::enable_if<std::is_base_of<Expression,E1>::value &&
                        std::is_base_of<Expression,E2>::value,Less<E1,E2>>::type
operator <(const E1& a, const E2& b) {
    return Less<E1,E2>(a,b);
}

template<class E>
class All : public Expression {
public:
    using value_type = bool;

private:
    const E& _a;
    mutable std::optional<value_type> _res;

public:
    explicit All(const E& a): _a(a), _res(std::nullopt) {}

    value_type evaluate() const {
        if (!_res.has_value()) {
            const auto n = _a.size();
            _res = true;
            for (int i=0; i<n; ++i) {
                if (!_a.evaluate(i)) {
                    _res = false;
                    break;
                }
            }
        }
        return _res.value();
    }
    void display(std::ostream& out) const {
        out << "All(" << this->_a << ')';
    }
};

template<class E>
bool evaluate(const All<E>& expr) {
    return expr.evaluate();
}

template<class E>
typename std::enable_if<std::is_base_of<Expression, E>::value, All<E>>::type
all(const E& a) {
    return All<E>(a);
}

template<class E>
class Any : public Expression {
public:
    using value_type = bool;

private:
    const E& _a;
    mutable std::optional<value_type> _res;

public:
    explicit Any(const E& a): _a(a), _res(std::nullopt) {}

    value_type evaluate() const {
        if (!_res.has_value()) {
            const auto n = _a.size();
            _res = false;
            for (int i=0; i<n; ++i) {
                if (_a.evaluate(i)) {
                    _res = true;
                    break;
                }
            }
        }
        return _res.value();
    }

    void display(std::ostream& out) const {
        out << "Any(" << this->_a << ')';
    }
};

template<class E>
bool evaluate(const Any<E>& expr) {
    return expr.evaluate();
}

template<class E>
typename std::enable_if<std::is_base_of<Expression, E>::value, Any<E>>::type
any(const E& a) {
    return Any<E>(a);
}

template<class E1, class E2, class E3>
class Where : public Expression {
public:
    using value_type =
        typename std::common_type<typename E2::value_type,typename E3::value_type>::type;

private:
    const E1& _p;
    mutable std::optional<bool> _p_res;
    const E2& _a;
    const E3& _b;

    bool get_res() const {
        if (!_p_res.has_value()) {
            _p_res = _p.evaluate();
        }
        return _p_res.value();
    }

public:
    explicit Where(const E1 &p, const E2 &a, const E3 &b) : _p(p), _p_res(std::nullopt), _a(a), _b(b) {}

    value_type evaluate(int i) { return get_res() ? this->_a.evaluate(i) : this->_b.evaluate(i); }
    value_type evaluate(int i) const { return get_res() ? this->_a.evaluate(i) : this->_b.evaluate(i); }
    int size() const { return get_res() ? this->_a.size() : this->_b.size(); }

    void display(std::ostream& out) const {
        out << "Where(" << this->_p << ", " << this->_a << ", " << this->_b << ')';
    }
};

template<class E1, class E2, class E3>
typename std::enable_if<std::is_base_of<Expression, E1>::value &&
                        std::is_base_of<Expression, E2>::value &&
                        std::is_base_of<Expression, E2>::value, Where<E1, E2, E3>>::type
where(const E1& p, const E2& a, const E3& b) {
    return Where<E1, E2, E3>(p, a, b);
}

#endif // vim:filetype=cpp
