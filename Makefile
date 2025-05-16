all: calculator todo suhu

calculator: calc/main.cpp calc/calc.hpp
	g++ calc/main.cpp -O2 -o calculator

todo: todo/todo.c
	g++ todo/todo.cpp -O2 -o todo

suhu: suhu/suhu.c
	g++ suhu/suhu.cpp -O2 -o suhu
