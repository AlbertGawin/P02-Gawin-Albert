#include <iostream>
#include <vector>

using namespace std;

void spirala(int test[5][5], int M, int N) {

    int p[2] = {0, 0};
    int q[2] = {M-1, N-1};
    int licznik = M*N;

    int _start[2] = {1,0};
    int _stop[2] = {M-1, N-1};

    while(licznik--) {
        cout << test[p[0]][p[1]] << " ";

        if (p[0] == _stop[0] && p[1] == _stop[1]) {
            q[0] = _start[0];
            q[1] = _start[1];

            _stop[0]--;
            _stop[1]--;
        } else if(p[0] == _start[0] && p[1] == _start[1]) {
            q[0] = _stop[0];
            q[1] = _stop[1];

            _start[0]++;
            _start[1]++;
        }

        if(p[1] < q[1]) {
            p[1]++;
        } else if(p[0] < q[0]) {
            p[0]++;
        } else if (p[1] > q[1]) {
            p[1]--;
        } else if (p[0] > q[0]) {
            p[0]--;
        }
    }
}

int main() {

    int test[5][5] = {
        {1,2,3,4,5},
        {16,17,18,19,6},
        {15,24,25,20,7},
        {14,23,22,21,8},
        {13,12,11,10,9},
    };

    int M = sizeof(test)/sizeof(test[0]);
    int N = sizeof(test)/sizeof(test[0][0]) / M;

    spirala(test, M, N);

    return 0;
}
