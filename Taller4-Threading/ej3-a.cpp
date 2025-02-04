#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <cassert>

#define N 100
#define THREAD_COUNT 5

using namespace std;

void multiplicar_concurrente(vector<int>::iterator v1_begin, vector<int>::iterator v1_end,
                            vector<int>::iterator v2_begin, vector<int>::iterator v2_end,
                            vector<int>::iterator v3_begin, vector<int>::iterator v3_end) {
    for(auto v1_it = v1_begin, v2_it = v2_begin, v3_it = v3_begin; v1_it != v1_end; ++v1_it, ++v2_it, ++v3_it){

        *v3_it = *v1_it * *v2_it;  // Multiplicar los elementos
    }    
}


void verify(vector<int> v1, vector<int> v2, vector<int> v3) {
    cout << "v1 = [" << v1[0] << ", " << v1[1] << ", " << ", ..., " << v1[N - 2] << ", " << v1[N - 1] << "]" << endl;
    cout << "v2 = [" << v2[0] << ", " << v2[1] << ", " << ", ..., " << v2[N - 2] << ", " << v2[N - 1] << "]" << endl;
    cout << "v3 = [" << v3[0] << ", " << v3[1] << ", " << ", ..., " << v3[N - 2] << ", " << v3[N - 1] << "]" << endl;

    for (int i = 0; i < N; ++i) {
        assert(v3[i] == v1[i] * v2[i]);
    }
}

int main() {
    vector<int> v1(N);
    vector<int> v2(N);
    iota(v1.begin(), v1.end(), 1);
    iota(v2.begin(), v2.end(), N + 1);

    vector<int> v3(N);
    
    // TO-DO 
    vector<thread> threads;
    for (int i = 0; i < THREAD_COUNT; ++i) {
        int step = N/ THREAD_COUNT;
        int start = i * step;
        int end = step + start;
        threads.emplace_back(multiplicar_concurrente,
                            v1.begin() + start, v1.begin() + end,
                            v2.begin() + start, v2.begin() + end,
                            v3.begin() + start, v3.begin() + end);
    }
    
    for (auto& th : threads) {
        th.join();
    }

    verify(v1, v2, v3);

    return 0;
}