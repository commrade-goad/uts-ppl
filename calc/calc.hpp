#ifndef CALC_HPP
#define CALC_HPP

#include <memory>
#include <sstream>

template <typename T>
struct CalcOperation {
public:
    char m_symbol = '?';

    virtual T execute(T a, T b)  = 0;

    CalcOperation(char sym) : m_symbol(sym) {}
    virtual ~CalcOperation() = default;
};

template<typename T>
struct AddOperator : public CalcOperation<T>{
    AddOperator() : CalcOperation<T>('+') {}
    T execute(T a, T b) override {
        return a + b;
    }
};

template<typename T>
struct MinOperator : public CalcOperation<T>{
    MinOperator() : CalcOperation<T>('-') {}
    T execute(T a, T b) override {
        return a - b;
    }
};

template<typename T>
struct DivOperator : public CalcOperation<T>{
    DivOperator() : CalcOperation<T>('/') {}
    T execute(T a, T b) override {
        return a / b;
    }
};

template<typename T>
struct MulOperator : public CalcOperation<T>{
    MulOperator() : CalcOperation<T>('*') {}
    T execute(T a, T b) override {
        return a * b;
    }
};

template <typename T>
struct Calculator {
private:
    T m_lhs, m_rhs , m_res;
    std::unique_ptr<CalcOperation<T>> m_mode;

public:
    Calculator() {};
    ~Calculator() {};

    T getResult() {
        m_res =  m_mode.get()->execute(m_lhs, m_rhs);
        return m_res;
    }
    std::string getStr() {
        std::stringstream ss;
        ss << m_lhs << " " << m_mode.get()->m_symbol << " " << m_rhs << " = " << m_res;
        return ss.str();
    }

    void setMode(std::unique_ptr<CalcOperation<T>> op) {
        m_mode = std::move(op);
    }

    void setOperands(T a, T b) {
        m_lhs = a;
        m_rhs = b;
    }
};

#endif // CALC_HPP
