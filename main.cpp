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
    int runner[2] = {0, 0};
    int finish[2] = {M-1, N-1};

    int up_corner[2] = {1,0};
    int down_corner[2] = {M-1, N-1};

    int i = 0;

    // Wykonuj dopoki [i] jest mniejszy od M*N
    while(i < M*N) {

        // Zapisanie wyniku do [result]
        result[i] = matrix[runner[0]][runner[1]];

        /* Sprawdzenie czy [runner] dotarl do [finish],
            nastepnie ustawienie nowej mety */
        if (runner[0] == down_corner[0] && runner[1] == down_corner[1]) {
            finish[0] = up_corner[0];
            finish[1] = up_corner[1];

            down_corner[0]--;
            down_corner[1]--;
        } else if(runner[0] == up_corner[0] && runner[1] == up_corner[1]) {
            finish[0] = down_corner[0];
            finish[1] = down_corner[1];

            up_corner[0]++;
            up_corner[1]++;
        }

        // Skrypt biegu az do [finish]
        if(runner[1] < finish[1]) {
            runner[1]++;
        } else if(runner[0] < finish[0]) {
            runner[0]++;
        } else if (runner[1] > finish[1]) {
            runner[1]--;
        } else if (runner[0] > finish[0]) {
            runner[0]--;
        }

        i++;
    }

    return result;
}

void saveMatrixToFile(int* tab, int M, int N, int k) {

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
        PROSZE O ZMIANE ZMIENNEJ [numberOfFiles] JESLI DODANO PLIKI */
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
        saveMatrixToFile(result, M, N, i);
    }

    return 0;
}
