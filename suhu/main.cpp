#include "suhu.hpp"

int main(void) {
    TempStation ts = TempStation();
    size_t dapur = ts.registerObserver(std::make_shared<Display>("dapur"));
    size_t km    = ts.registerObserver(std::make_shared<Display>("kamar mandi"));

    ts.setTemperature(20, dapur);
    ts.setTemperature(25, km);

    ts.removeObserver(km);

    ts.setTemperature(25, dapur);
    return 0;
}
