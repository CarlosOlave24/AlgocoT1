#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono> // Para medir el tiempo

using namespace std;
using namespace std::chrono;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Función para leer datos de un archivo CSV
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

// Función para escribir datos en un archivo CSV
void writeCSV(const vector<int>& data, const string& filename) {
    ofstream file(filename);
    for (size_t i = 0; i < data.size(); i++) {
        file << data[i];
        if (i < data.size() - 1) 
            file << ",";
    }
    file << endl;
}

// Función para agregar el tiempo de ejecución a un archivo CSV
void writeTimeToCSV(const string& filename, const string& algorithm, long long time) {
    ofstream file(filename, ios::app); 
    file << algorithm << "," << time << endl; 
}

int main() {
    // Nombres de archivos a utilizar
    string inputFilename = "partially_sorted_list.csv";
    string outputFilename = "resultado.csv";
    string timeFilename = "sorting_times.csv"; 

    // Leer datos del archivo CSV
    vector<int> arr = readCSV(inputFilename);
    int n = arr.size();

    auto start = high_resolution_clock::now(); // Inicio del temporizador

    // Ordenar los datos usando QuickSort
    quickSort(arr, 0, n - 1);

    auto stop = high_resolution_clock::now(); // Fin del temporizador
    auto duration = duration_cast<milliseconds>(stop - start);

    // Escribir el tiempo de ejecución en un archivo CSV
    writeTimeToCSV(timeFilename, "QuickSort partially_sorted_list", duration.count());

    // Mostrar el tiempo de ejecución en la consola
    cout << "El tiempo de ejecución de QuickSort fue de: " << duration.count() << " milisegundos" << endl;

    // Escribir los datos ordenados en un archivo CSV
    writeCSV(arr, outputFilename);

    cout << "Los datos ordenados han sido escritos en " << outputFilename << endl;

    return 0;
}