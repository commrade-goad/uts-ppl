#ifndef SUHU_HPP_
#define SUHU_HPP_

#include <memory>
#include <string>
#include <vector>
#include <iostream>

struct Observer {
public:
    Observer() {};
    virtual ~Observer() = default;

    virtual void update(float temp) = 0;
    virtual void print_status()     = 0;
    virtual void print_statistic()  = 0;
};

struct Display: public Observer {
public:
    std::string m_name;
    std::vector<float> m_temp;
    float m_max;
    float m_min;

    Display(const char *name): Observer() {
        m_name = name;
    };
    virtual void update(float temp) override {
        m_temp.push_back(temp);
    }
    virtual void print_status() override {
        std::cout << "INFO: " << m_name << " Current temp -> " << m_temp.back() << std::endl;
    }
    virtual void print_statistic() override {
        float sum = 0.0f;
        m_min = m_temp[0];
        m_max = m_temp[0];
        for (const auto &t: m_temp) {
            if (m_min > t) m_min = t;
            if (m_max < t) m_max = t;
            sum += t;
        }
        float avg = sum / m_temp.size();

        std::cout << "INFO: Avg -> " << avg << ", Min -> " << m_min << ", Max -> " << m_max << std::endl;
    }
    virtual ~Display() {};
};

struct TempStation {
public:
    std::vector<std::pair<size_t, std::shared_ptr<Observer>>> m_stations;
    size_t m_counter;

    TempStation() {
        m_counter = 0;
        m_stations.reserve(20);
    };

    ~TempStation() = default;

    void set_temperature(float temp, size_t id) {
        for (int i = 0; i < m_stations.size(); i++) {
            if (m_stations[i].first == id) {
                auto &selected = m_stations[i].second;
                selected->update(temp);
                selected->print_status();
                selected->print_statistic();
                return;
            }
        }
    }

    size_t register_observer(std::shared_ptr<Observer> observer) {
        size_t old_counter = m_counter;
        m_stations.push_back(std::make_pair(m_counter, observer));
        m_counter++;
        return old_counter;
    }

    void remove_observer(size_t id) {
        for (int i = 0; i < m_stations.size(); i++) {
            if (m_stations[i].first == id) {
                m_stations.erase(m_stations.begin() + i);
                return;
            }
        }
    }
};

#endif // SUHU_HPP_
