#ifndef TODO_HPP_
#define TODO_HPP_

#include <string>
#include <cstdint>

struct Todo {
    uint16_t m_id;
    std::string m_body;
    bool m_checked;

    Todo(const char *body) {
        m_body = body;
    }

    Todo();
    ~Todo();

    void markAsDone() {
        m_checked = true;
    }

    void markAsUndone() {
        m_checked = false;
    }

    uint16_t getId() {
        return m_id;
    }

    std::string getBody() {
        return m_body;
    }

    bool getCheck() {
        return m_checked;
    }

    void setId(uint16_t id) {
        m_id = id;
    }
};

#endif // TODO_HPP_
