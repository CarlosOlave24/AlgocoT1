#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono> // Para medir el tiempo

using namespace std;
using namespace std::chrono; // Para acceder a las funciones de chrono

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
    archivo.close();
    return matriz;
}

// Función para escribir una matriz en un archivo CSV
void escribirMatrizEnCSV(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    for (const auto& fila : matriz) {
        for (size_t i = 0; i < fila.size(); ++i) {
            archivo << fila[i];
            if (i < fila.size() - 1) archivo << ",";
        }
        archivo << endl;
    }
    archivo.close();
}

// Función para multiplicar dos matrices
vector<vector<int>> multiplicarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();  
    int m = A[0].size(); 
    int p = B[0].size(); 
    
    vector<vector<int>> C(n, vector<int>(p, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < m; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Función para agregar el tiempo de ejecución a un archivo CSV
void escribirTiempoEnCSV(const string& nombreArchivo, const string& algoritmo, long long tiempo) {
    ofstream archivo(nombreArchivo, ios::app); 
    archivo << algoritmo << "," << tiempo << endl;
}

int main() {
    // Nombres de archivos a utilizar
    string archivoTiempo = "matrix_multiplication_times.csv";
    vector<vector<int>> A = leerMatrizDesdeCSV("square_matrix1.csv");
    vector<vector<int>> B = leerMatrizDesdeCSV("rectangular_matrix.csv");

    auto start = high_resolution_clock::now(); // Inicio del temporizador

    // Multiplicar matrices A y B
    vector<vector<int>> C = multiplicarMatrices(A, B);

    auto stop = high_resolution_clock::now();  // Fin del temporizador
    auto duracion = duration_cast<milliseconds>(stop - start);

    // Escribir el tiempo de ejecución en un archivo CSV
    escribirTiempoEnCSV(archivoTiempo, "Iterativo Cubico Tradicional square/rectangular", duracion.count());

    // Mostrar el tiempo de ejecución en la consola
    cout << "El tiempo de ejecución de la multiplicación iterativa cúbica tradicional fue de: " << duracion.count() << " milisegundos" << endl;

    // Escribir la matriz resultante en un archivo CSV
    escribirMatrizEnCSV(C, "resultado.csv");

    cout << "La multiplicación de matrices se ha completado y el resultado se ha guardado en 'resultado.csv'." << endl;

    return 0;
}