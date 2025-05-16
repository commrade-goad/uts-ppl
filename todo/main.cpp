#include "todolist.hpp"

int main(void) {
    TodoList tl{};

    uint16_t milk = tl.addTodo(Todo{"Buy Milk"});
    uint16_t rice = tl.addTodo(Todo{"Rice my archlinux again"});

    tl.markTodo(rice);

    tl.delTodo(milk);

    tl.undo();

    return 0;
}
