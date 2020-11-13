#include <iostream>
#include <fstream>

using namespace std;

int** getMatrixFromFile(string path, int& M, int& N) {

    fstream file(path, ios::in);
    int** matrix;

    if(file.good()) {
        file >> M >> N;
        matrix = new int*[M];

        for(int i=0; i<M; i++) {
            matrix[i] = new int[N];
            for(int j=0; j<N; j++) {
                file >> matrix[i][j];
            }
        }
    }
    file.close();

    return matrix;
}

int* getResultOfSpiral(int** matrix, int M, int N) {

    int* result = new int[M*N];

    // --- Inicjacja zmiennych ---
    int biegacz[2] = {0, 0};
    int meta[2] = {M-1, N-1};

    int gorny_rog[2] = {1,0};
    int dolny_rog[2] = {M-1, N-1};

    int licznik = M*N;
    int i=0;

    // --- Wykonuj dopoki licznik jest wiekszy od 0 ---
    while(licznik--) {

        // --- Zapisanie wyniku do tab ---
        result[i] = matrix[biegacz[0]][biegacz[1]];

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

        i++;
    }

    return result;
}

void saveToFile(int* tab, int M, int N, int k) {

    fstream result("wynik.txt", ios::out | ios::app);

    result << "WYNIK [" << k << "]: ";
    for(int i=0; i<M*N; i++) {
        result << tab[i] << " ";
    }
    result << "\n\n";

    result.close();
}

int main() {

    int** matrix;
    int* result;
    int matrixN = 10, M=0, N=0;

    for(int i=1; i<=matrixN; i++) {
        matrix = getMatrixFromFile("macierze/"+ to_string(i) +".txt", M, N);
        result = getResultOfSpiral(matrix, M, N);
        saveToFile(result, M, N, i);
    }

    return 0;
}
