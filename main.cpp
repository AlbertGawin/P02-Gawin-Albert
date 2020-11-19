#include <iostream>
#include <fstream>

using namespace std;

int** getMatrixFromFile(string path, int& M, int& N) {

    fstream file(path, ios::in);
    bool isEmpty = file.peek() == std::ifstream::traits_type::eof();

    int** matrix;

    // Sprawdz czy plik poprawnie otwarty oraz czy nie jest pusty
    if(file.good() && !isEmpty) {
        file >> M >> N;
        matrix = new int*[M];

        for(int i=0; i<M; i++) {
            matrix[i] = new int[N];
            for(int j=0; j<N; j++) {
                file >> matrix[i][j];
            }
        }
    } else {
        file.close();
        return 0;
    }
    file.close();

    return matrix;
}

int* getResultOfSpiral(int** matrix, int M, int N) {

    int* result = new int[M*N];

    // Inicjacja zmiennych
    int biegacz[2] = {0, 0};
    int meta[2] = {M-1, N-1};

    int gorny_rog[2] = {1,0};
    int dolny_rog[2] = {M-1, N-1};

    int i = 0;

    // Wykonuj dopoki [i] jest mniejszy od M*N
    while(i < M*N) {

        // Zapisanie wyniku do [result]
        result[i] = matrix[biegacz[0]][biegacz[1]];

        /* Sprawdzenie czy [biegacz] dotarl do [meta],
            nastepnie ustawienie nowej mety */
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

        // Skrypt biegu az do [meta]
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

    /* Przy pierwszej iteracji stworz nowy plik,
        przy nastepnych iteracjach dopisuj */
    fstream file;
    if (k == 1) {
        file.open("wynik.txt", ios::out);
    } else {
        file.open("wynik.txt", ios::out | ios::app);
    }

    file << "WYNIK [" << k << ".txt]: ";
    for(int i=0; i<M*N; i++) {
        file << tab[i] << " ";
    }
    file << "\n\n";

    file.close();
}

int main() {

    /* PRZYKLADOWA NAZWA PLIKU Z MACIERZA: [cyfra].txt,
        GDZIE [cyfra] NALEZY DO ZBIORU LICZB CALKOWITYCH */

    /* SKRYPT NIE OBSLUGUJE DYNAMICZNEGO ODCZYTYWANIA ILOSCI PLIKOW,
        PROSZE O ZMIANE ZMIENNEJ [numberOfFiles] JESLI DODANO/USUNIETO PLIKI */
    int numberOfFiles = 10;

    int** matrix;
    int* result;
    int M=0, N=0;

    // Petla odczytuje pliki od 1 do podanej ilosci
    for(int i=1; i<=numberOfFiles; i++) {

        // Zwraca macierz z pliku i zapisuje do zmiennej [matrix]
        matrix = getMatrixFromFile("macierze/"+ to_string(i) +".txt", M, N);
        if (matrix == 0) continue; // --- Jesli zwrocono blad, pomin nastepne kroki

        // Zwraca resultat spirali na macierzy i zapisuje do zmiennej [result]
        result = getResultOfSpiral(matrix, M, N);

        // Zapisuje [result] do pliku "wynik.txt"
        saveToFile(result, M, N, i);
    }

    return 0;
}
