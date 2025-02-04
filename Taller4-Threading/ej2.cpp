#include <thread>
#include <iostream>
#include <semaphore>

using namespace std;

binary_semaphore sem1(0);
binary_semaphore sem2(0);


#define MSG_COUNT 5


void f1_a() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F1 (A)\n";
        this_thread::sleep_for(100ms);
    }
}

void f1_b() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F1 (B)\n";
        this_thread::sleep_for(200ms);
    }
}

void f2_a() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F2 (A)\n";
        this_thread::sleep_for(500ms);
    }
}

void f2_b() {
    for (int i = 0; i < MSG_COUNT; ++i) {
        cout << "Ejecutando F2 (B)\n";
        this_thread::sleep_for(10ms);
    }
}

void f1() {
    f1_a();
    sem1.release();
    sem2.acquire();
    f1_b();
}

void f2() {
    f2_a();
    sem2.release();
    sem1.acquire();
    f2_b();
}

int main() {
    // Crear los threads para f1 y f2
    thread t1(f1);
    thread t2(f2);

    // Esperamos a que ambos threads terminen
    t1.join();
    t2.join();

    return 0;
}

//faltan muchisimas cosas
