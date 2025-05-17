#include "suhu.hpp"

int main(void) {
    TempStation ts = TempStation();
    size_t dapur = ts.register_observer(std::make_shared<Display>("dapur"));
    size_t km    = ts.register_observer(std::make_shared<Display>("kamar mandi"));

    ts.set_temperature(20, dapur);
    ts.set_temperature(25, km);

    ts.remove_observer(km);

    ts.set_temperature(25, dapur);
    return 0;
}
