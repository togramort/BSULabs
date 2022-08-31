#include <exception>

#include "MonitorStack.h"

MonitorStack::MonitorStack(int size) {
    this->size = size;
    this->top = 0;
    this->elements = new short[size];
}

MonitorStack::~MonitorStack() {
    delete[] elements;
}

void MonitorStack::push(short symbol) {
    if (this->top + 1 >= size)
        throw std::exception("Stack overflow");

    ++this->top;
    this->elements[top] = symbol;
}

short MonitorStack::pop() {
    short symbol = this->elements[top];
    --top;
    return symbol;
}