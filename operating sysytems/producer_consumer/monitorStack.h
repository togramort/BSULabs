#ifndef LAB7_MONITORSTACK_H
#define LAB7_MONITORSTACK_H


#include <climits>

class MonitorStack {
private:
    short* elements;
    int top;
    int size;
public:
    MonitorStack(int size = INT_MAX);
    ~MonitorStack();
    void push(short symbol);
    short pop();
};


#endif