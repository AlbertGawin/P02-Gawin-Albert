#include <iostream>

using namespace std;

void spirala(int test[5][5], int M, int N) {

    // --- Inicjacja zmiennych ---
    int biegacz[2] = {0, 0};
    int meta[2] = {M-1, N-1};

    int gorny_rog[2] = {1,0};
    int dolny_rog[2] = {M-1, N-1};

    int licznik = M*N;

    // --- Wykonuj dopóki licznik jest wiêkszy od 0 ---
    while(licznik--) {
        // --- Wypisanie komórki ---
        cout << test[biegacz[0]][biegacz[1]] << " ";

        // --- Sprawdzenie czy biegacz dotar³ do mety, nastêpnie ustawienie nowej mety ---
        if (biegacz[0] == dolny_rog[0] && biegacz[1] == dolny_rog[1]) {
            meta[0] = gorny_rog[0];
            meta[1] = gorny_rog[1];

            dolny_rog[0]--;
            dolny_rog[1]--;
        } else if(biegacz[0] == gorny_rog[0] && biegacz[1] == gorny_rog[1]) {
            meta[0] = dolny_rog[0];
            meta[1] = dolny_rog[1];

            gorny_rog[0]++;
            gorny_rog[1]++;
        }

        // --- Skrypt biegu a¿ do mety ---
        if(biegacz[1] < meta[1]) {
            biegacz[1]++;
        } else if(biegacz[0] < meta[0]) {
            biegacz[0]++;
        } else if (biegacz[1] > meta[1]) {
            biegacz[1]--;
        } else if (biegacz[0] > meta[0]) {
            biegacz[0]--;
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
