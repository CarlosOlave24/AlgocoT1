#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono> // Para medir el tiempo

using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo CSV
vector<vector<int>> leerMatrizDesdeCSV(const string& nombreArchivo) {
    vector<vector<int>> matriz;
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        vector<int> fila;
        stringstream ss(linea);
        string valor;

        while (getline(ss, valor, ',')) {
            fila.push_back(stoi(valor));
        }
        matriz.push_back(fila);
    }

    return matriz;
}

// Función para guardar una matriz en un archivo CSV
void guardarMatrizEnCSV(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    for (const auto& fila : matriz) {
        for (size_t i = 0; i < fila.size(); ++i) {
            archivo << fila[i];
            if (i < fila.size() - 1) {
                archivo << ",";
            }
        }
        archivo << "\n";
    }
}

// Función para transponer una matriz
vector<vector<int>> transponerMatriz(const vector<vector<int>>& B) {
    int m = B.size();
    int p = B[0].size(); 
    vector<vector<int>> B_T(p, vector<int>(m)); 

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            B_T[j][i] = B[i][j];
        }
    }

    return B_T;
}

// Función para multiplicar matrices con la segunda matriz transpuesta
vector<vector<int>> multiplicarMatricesOptimizado(const vector<vector<int>>& A, const vector<vector<int>>& B_T) {
    int n = A.size();
    int m = A[0].size(); 
    int p = B_T.size();  

    vector<vector<int>> C(n, vector<int>(p, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < m; ++k) {
                C[i][j] += A[i][k] * B_T[j][k]; 
            }
        }
    }

    return C;
}

// Función para escribir el tiempo de ejecución en un archivo CSV
void escribirTiempoEnCSV(const string& nombreArchivo, const string& algoritmo, long long tiempo) {
    ofstream archivo(nombreArchivo, ios::app);
    archivo << algoritmo << "," << tiempo << endl; 
}

int main() {
    // Nombre de los archivos a utilizar
    string archivoA = "square_matrix1.csv";
    string archivoB = "rectangular_matrix.csv";
    string archivoC = "resultado.csv";
    string archivoTiempo = "matrix_multiplication_times.csv";

    // Leer matrices desde archivos CSV
    vector<vector<int>> A = leerMatrizDesdeCSV(archivoA);
    vector<vector<int>> B = leerMatrizDesdeCSV(archivoB);

    // Transponer la matriz B
    vector<vector<int>> B_T = transponerMatriz(B);

    auto start = high_resolution_clock::now(); // Inicio del temporizador

    // Multiplicar matrices A y B_T
    vector<vector<int>> C = multiplicarMatricesOptimizado(A, B_T);

    auto stop = high_resolution_clock::now();  // Fin del temporizador
    auto duration = duration_cast<milliseconds>(stop - start);

    // Guardar la matriz resultante en un archivo CSV
    guardarMatrizEnCSV(C, archivoC);

    // Escribir el tiempo de ejecución en el archivo CSV
    escribirTiempoEnCSV(archivoTiempo, "Iterativo Cubico Optimizado square/rectangular", duration.count());

    cout << "Multiplicación de matrices completada y guardada en: " << archivoC << endl;
    cout << "El tiempo de ejecución de la multiplicación optimizada fue de: " << duration.count() << " milisegundos" << endl;

    return 0;
}