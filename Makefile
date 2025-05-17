all: calculator-exec todo-exec

calculator: calc/main.cpp calc/calc.hpp
	g++ calc/main.cpp -ggdb -o calculator-exec

todo-exec: todo/main.cpp todo/todo.hpp todo/todolist.hpp
	g++ todo/main.cpp -ggdb -o todo-exec

suhu-exec: suhu/main.cpp suhu/suhu.hpp
	g++ suhu/main.cpp -ggdb -o suhu-exec
