#include <iostream>
#include <vector>
#include <windows.h>

#include "MonitorStack.h"

struct ArgsConsumer {
    MonitorStack* st;
    CRITICAL_SECTION cs;
    HANDLE hSemaphoreStackFull;
    HANDLE hSemaphoreStackEmpty;
    int numberOfProductsConsume;
};

struct ArgsProducer {
    MonitorStack* st;
    CRITICAL_SECTION cs;
    HANDLE hSemaphoreStackFull;
    HANDLE hSemaphoreStackEmpty;
    int numberOfProductsProduce;
    short newProduct;
};

DWORD WINAPI consumer(LPVOID lpParam) {
    ArgsConsumer* args = static_cast<ArgsConsumer*>(lpParam);
    for (int i = 0; i < args->numberOfProductsConsume; ++i) {
        WaitForSingleObject(args->hSemaphoreStackFull, INFINITE);
        EnterCriticalSection(&args->cs);
        short top = args->st->pop();
        std::cout << "Consumed " << top << '\n';
        LeaveCriticalSection(&args->cs);
        ReleaseSemaphore(args->hSemaphoreStackEmpty, 1, NULL);
    }
    return 0;
}

DWORD WINAPI producer(LPVOID lpParam) {
    ArgsProducer* args = static_cast<ArgsProducer*>(lpParam);
    for (int i = 0; i < args->numberOfProductsProduce; ++i) {
        WaitForSingleObject(args->hSemaphoreStackEmpty, INFINITE);
        EnterCriticalSection(&args->cs);
        args->st->push(args->newProduct);
        std::cout << "Produced " << args->newProduct << '\n';
        LeaveCriticalSection(&args->cs);
        ReleaseSemaphore(args->hSemaphoreStackFull, 1, NULL);
    }
    return 0;
}

int main() {
    int sizeStack;
    std::cout << "Enter the size of stack\n";
    std::cin >> sizeStack;
    MonitorStack* st = new MonitorStack(sizeStack);

    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);
    HANDLE hSemaphoreStackFull = CreateSemaphoreW(NULL, 0, sizeStack, NULL);
    HANDLE hSemaphoreStackEmpty = CreateSemaphoreW(NULL, sizeStack, sizeStack, NULL);

    int numberConsumers, numberProducers;
    std::cout << "Enter the number of consumers\n";
    std::cin >> numberConsumers;
    std::cout << "Enter the number of producers\n";
    std::cin >> numberProducers;

    HANDLE* hConsumers = new HANDLE[numberConsumers];
    HANDLE* hProducers = new HANDLE[numberProducers];
    ArgsConsumer* argsConsumer = new ArgsConsumer[numberConsumers];
    ArgsProducer* argsProducer = new ArgsProducer[numberProducers];
    for (int i = 0; i < numberConsumers; ++i) {
        argsConsumer[i].st = st;
        argsConsumer[i].hSemaphoreStackEmpty = hSemaphoreStackEmpty;
        argsConsumer[i].hSemaphoreStackFull = hSemaphoreStackFull;
        argsConsumer[i].cs = cs;
        std::cout << "Enter the number of products to consume for " << i + 1 << " consumer\n";
        std::cin >> argsConsumer[i].numberOfProductsConsume;
    }

    for (int i = 0; i < numberProducers; ++i) {
        argsProducer[i].st = st;
        argsProducer[i].hSemaphoreStackEmpty = hSemaphoreStackEmpty;
        argsProducer[i].hSemaphoreStackFull = hSemaphoreStackFull;
        argsProducer[i].cs = cs;
        std::cout << "Enter the number of products to produce for " << i + 1 << " producer\n";
        std::cin >> argsProducer[i].numberOfProductsProduce;
        std::cout << "Enter the product (short number)\n";
        std::cin >> argsProducer[i].newProduct;
    }

    HANDLE* hThreads = new HANDLE[numberConsumers + numberProducers];
    for (int i = 0; i < numberProducers; ++i) {
        hProducers[i] = CreateThread(NULL, 0, producer, static_cast<LPVOID>(&argsProducer[i]), 0, NULL);
        if (hProducers[i] == NULL) {
            std::cout << "Failed to create thread producer " << i + 1 << '\n';
            return GetLastError();
        }
        hThreads[i] = hProducers[i];
    }

    for (int i = 0; i < numberConsumers; ++i) {
        hConsumers[i] = CreateThread(NULL, 0, consumer, static_cast<LPVOID>(&argsConsumer[i]), 0, NULL);
        if (hConsumers[i] == NULL) {
            std::cout << "Failed to create thread producer " << i + 1 << '\n';
            return GetLastError();
        }
        hThreads[i + numberProducers] = hConsumers[i];
    }

    WaitForMultipleObjects(numberProducers + numberConsumers, hThreads, TRUE, INFINITE);
    for (int i = 0; i < numberProducers + numberConsumers; ++i)
        CloseHandle(hThreads[i]);
    CloseHandle(hSemaphoreStackEmpty);
    CloseHandle(hSemaphoreStackFull);
    DeleteCriticalSection(&cs);
    delete[] hConsumers;
    delete[] hProducers;
    delete[] argsProducer;
    delete[] argsConsumer;
    return 0;
} 