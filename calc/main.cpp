#include <iostream>
#include "calc.hpp"

int main() {
    Calculator<double> calc;
    calc.setOperands(12.0, 4.0);

    calc.setMode(std::make_unique<MulOperator<double>>());
    calc.getResult();
    std::cout << calc.getStr() << "\n";

    calc.setMode(std::make_unique<DivOperator<double>>());
    calc.getResult();
    std::cout << calc.getStr() << "\n";

    return 0;
}
