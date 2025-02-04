#include <thread>
#include <iostream>
#include <unistd.h>
#include <vector>

#define CANT_THREADS 10

using namespace std;

void f (int i, string msj) {
    this_thread::sleep_for(1000ms*i);
    printf("%s%i\n", msj.c_str(), i);
    // otra opcion
    //out << "Hola!" << "Soy el thread: " << i << endl;
}


int main() {
    vector<thread> threads;
    string msj = "Hola! Soy el thread: ";
    for (int i = 0; i < CANT_THREADS; i++) {
        threads.emplace_back(f, i, msj);
    }
    for (auto &t: threads) {
        // Opcion 1
        t.join();
        // Opcion 2
        //t.detach();
    }
    
    return 0;
}