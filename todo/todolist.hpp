#ifndef TODOLIST_HPP_
#define TODOLIST_HPP_

#include "todo.hpp"
#include <vector>

enum CommandType {
    CMD_ADD,
    CMD_DELETE,
    CMD_MARK
};

struct TodoState {
    Todo m_todo;
};

struct Command {
    CommandType m_type;
    uint16_t m_id;
    TodoState m_before;
    TodoState m_after;

    Command();
    ~Command() = default;
};

struct TodoList {
    uint16_t m_counter;
    std::vector<Todo> m_data;
    std::vector<Command> m_undoStack;
    std::vector<Command> m_redoStack;

    TodoList() : m_counter(0) {
        static const int reserve_size = 20;
        m_data.reserve(reserve_size);
        m_undoStack.reserve(reserve_size);
        m_redoStack.reserve(reserve_size);
    }

    Todo* findTodo(uint16_t id, int* idx = nullptr) {
        for (int i = 0; i < m_data.size(); i++) {
            if (m_data[i].getId() == id) {
                if (idx) *idx = i;
                return &m_data[i];
            }
        }
        return nullptr;
    }

    void add_todo(Todo todo) {
        todo.setId(m_counter++);

        Command cmd = {};
        cmd.m_type = CMD_ADD;
        cmd.m_id = todo.getId();
        cmd.m_before = TodoState{};
        cmd.m_after = TodoState{todo};

        m_data.push_back(todo);
        m_undoStack.push_back(cmd);
        m_redoStack.clear();
    }

    void del_todo(uint16_t id) {
        int idx = -1;
        Todo* todo_ptr = findTodo(id, &idx);

        if (todo_ptr && idx >= 0) {
            Command cmd;
            cmd.m_type = CMD_DELETE;
            cmd.m_id = id;
            cmd.m_before = TodoState{*todo_ptr};
            cmd.m_after = TodoState{};

            m_data.erase(m_data.begin() + idx);
            m_undoStack.push_back(cmd);
            m_redoStack.clear();
        }
    }

    void mark(uint16_t id) {
        Todo* todo_ptr = findTodo(id);

        if (todo_ptr) {
            Todo oldState = *todo_ptr;

            todo_ptr->getCheck() ? todo_ptr->markAsUndone() : todo_ptr->markAsDone();

            Command cmd;
            cmd.m_type = CMD_MARK;
            cmd.m_id = id;
            cmd.m_before = TodoState{oldState};
            cmd.m_after = TodoState{*todo_ptr};

            m_undoStack.push_back(cmd);
            m_redoStack.clear();
        }
    }

    void execute_command(const Command& cmd) {
        switch (cmd.m_type) {
            case CMD_ADD: {
                Todo todo = cmd.m_after.m_todo;
                m_data.push_back(todo);
                break;
            }
            case CMD_DELETE: {
                int idx = -1;
                if (findTodo(cmd.m_id, &idx)) {
                    m_data.erase(m_data.begin() + idx);
                }
                break;
            }
            case CMD_MARK: {
                Todo* todo_ptr = findTodo(cmd.m_id);
                if (todo_ptr) {
                    *todo_ptr = cmd.m_after.m_todo;
                }
                break;
            }
        }
    }

    void execute_inverse_command(const Command& cmd) {
        switch (cmd.m_type) {
            case CMD_ADD: {
                int idx = -1;
                if (findTodo(cmd.m_id, &idx)) {
                    m_data.erase(m_data.begin() + idx);
                }
                break;
            }
            case CMD_DELETE: {
                m_data.push_back(cmd.m_before.m_todo);
                break;
            }
            case CMD_MARK: {
                Todo* todo_ptr = findTodo(cmd.m_id);
                if (todo_ptr) {
                    *todo_ptr = cmd.m_before.m_todo;
                }
                break;
            }
        }
    }

    void undo() {
        if (m_undoStack.empty()) return;

        Command cmd = m_undoStack.back();
        m_undoStack.pop_back();
        execute_inverse_command(cmd);
        m_redoStack.push_back(cmd);
    }

    void redo() {
        if (m_redoStack.empty()) return;

        Command cmd = m_redoStack.back();
        m_redoStack.pop_back();
        execute_command(cmd);
        m_undoStack.push_back(cmd);
    }
};

#endif // TODOLIST_HPP_
