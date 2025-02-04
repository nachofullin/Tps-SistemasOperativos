#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <mutex>

#define CANT_THREADS 10

using namespace std;

mutex mtx;

void f (int i) {
    lock_guard<mutex> lock(mtx);
    //printf("%s%i\n", msj.c_str(), i);
    // otra opcion
    cout << "Hola! Soy el thread: " << i << endl;
        this_thread::sleep_for(100ms*i);
    cout << "Chau! Saludos desde: " << i << endl;
} //cuando termino se destruyte el lock y se hace unlock


int main() {
    vector<thread> threads;

    for (int i = 0; i < CANT_THREADS; i++) {
        threads.emplace_back(f, i);
    }
    for (auto &t: threads) {
        // Opcion 1
        t.join();
        // Opcion 2
        //t.detach();
    }
    
    return 0;
}



