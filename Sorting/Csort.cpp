#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <chrono> // Para medir el tiempo

using namespace std;
using namespace std::chrono;

// Función para leer un archivo CSV y devolver un vector de enteros
vector<int> readCSV(const string& filename) {
    ifstream file(filename);
    vector<int> data;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string value;

        while (getline(ss, value, ',')) {
            data.push_back(stoi(value));
        }
    }
    return data;
}

// Función para escribir un vector de enteros en un archivo CSV
void writeCSV(const vector<int>& data, const string& filename) {
    ofstream file(filename);

    for (size_t i = 0; i < data.size(); i++) {
        file << data[i];
        if (i < data.size() - 1) {
            file << ",";
        }
    }
    file << endl;
}

// Función para agregar el tiempo de ejecución a un archivo CSV
void writeTimeToCSV(const string& filename, const string& algorithm, long long time) {
    ofstream file(filename, ios::app);
    file << algorithm << "," << time << endl;
}

int main() {
    // Nombre de los archivos a utilizar
    string inputFilename = "partially_sorted_list.csv";
    string outputFilename = "resultado.csv";
    string timeFilename = "sorting_times.csv"; 

    // Leer datos desde el archivo CSV de entrada
    vector<int> vec = readCSV(inputFilename);

    auto start = high_resolution_clock::now(); // Inicio del temporizador

    // Llamar a la función sort para ordenar el vector
    sort(vec.begin(), vec.end());

    auto stop = high_resolution_clock::now();  // Fin del temporizador
    auto duration = duration_cast<milliseconds>(stop - start);

    // Escribir el tiempo de ejecución en un archivo CSV
    writeTimeToCSV(timeFilename, "C++ Sort partially_sorted_list", duration.count());

    // Mostrar el tiempo de ejecución en la consola
    cout << "El tiempo de ejecución de C++ Sort fue de: " << duration.count() << " milisegundos" << endl;

    // Escribir el vector ordenado en el archivo CSV de salida
    writeCSV(vec, outputFilename);

    cout << "Los datos ordenados se han escrito en " << outputFilename << endl;

    return 0;
}


