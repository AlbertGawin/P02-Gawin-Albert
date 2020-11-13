#include <iostream>
#include <fstream>

using namespace std;

void spirala(int tab[], int M, int N) {

    int tablica[M][N];
    // --- Zmiana tablicy jednowymiarowej na dwuwymiarow¹ ---
    cout << "Dla tablicy [" << M << ", " << N << "]" << endl;

    for(int i=0; i<M; i++) {
        for(int j=0; j<N; j++) {
            tablica[i][j] = tab[i*N + j];
            cout << tablica[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // --- Inicjacja zmiennych ---
    int biegacz[2] = {0, 0};
    int meta[2] = {M-1, N-1};

    int gorny_rog[2] = {1,0};
    int dolny_rog[2] = {M-1, N-1};

    int licznik = M*N;

    // --- Wykonuj dopoki licznik jest wiekszy od 0 ---
    cout << "Wyszlo: ";

    while(licznik--) {
        // --- Wypisanie komorki ---
        cout << tablica[biegacz[0]][biegacz[1]] << " ";

        // --- Sprawdzenie czy biegacz dotarl do mety, nastepnie ustawienie nowej mety ---
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

        // --- Skrypt biegu az do mety ---
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

    cout << "\n\n\n";
}

int main() {

    std::fstream plik("tablice.txt");
    int M=0, N=0;
    int *tab;

    if(plik.good()) {
        while(plik >> M >> N) {
            tab = new int[M*N];

            for(int i=0; i<M*N; i++) {
                plik >> tab[i];
            }

            spirala(tab, M, N);

            delete[] tab;
        }
    }
    plik.close();

    return 0;
}
