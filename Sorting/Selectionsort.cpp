#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm> 
#include <chrono>

using namespace std;
using namespace std::chrono;

// Funcion Selection sort
void selectionSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}

// Funcion para leer los datos del CSV
vector<int> readCSV(const string& filename)
{
    ifstream file(filename);
    vector<int> data;
    string line;
    
    while (getline(file, line))
    {
        stringstream ss(line);
        string value;
        while (getline(ss, value, ','))
        {
            data.push_back(stoi(value));
        }
    }
    
    return data;
}

// Funcion para escribir los datos ordenados
void writeCSV(const vector<int>& data, const string& filename)
{
    ofstream file(filename);
    for (size_t i = 0; i < data.size(); i++)
    {
        file << data[i];
        if (i < data.size() - 1)
            file << ",";
    }
    file << endl;
}

// Funcion para escribir los tiempos de ejecucion
void writeTimeToCSV(const string& filename, const string& algorithm, long long time)
{
    ofstream file(filename, ios::app);
    file << algorithm << "," << time << endl;
}

int main()
{
    // Nombres de los Archivos a ocupar
    string inputFilename = "partially_sorted_list.csv";
    string outputFilename = "resultado.csv";
    string timeFilename = "sorting_times.csv";

    // Se leen los datos desde el CSV
    vector<int> data = readCSV(inputFilename);

    auto start = high_resolution_clock::now(); // Inicio del temporizador

    // Se ejecuta el selection sort
    selectionSort(data);

    auto stop = high_resolution_clock::now();  // Fin del temporizador
    auto duration = duration_cast<milliseconds>(stop - start); // Duración en milisegundos

    // Se Escribe el tiempo de ejecución en un archivo CSV para algoritmos de sorting
    writeTimeToCSV(timeFilename, "Selection Sort partially_sorted_list", duration.count());

    // Se Muestra el tiempo de ejecución en la consola
    cout << "El tiempo de ejecución del Selection Sort fue de: " << duration.count() << " milisegundos" << endl;

    // Se escriben los datos ordenados en un CSV 
    writeCSV(data, outputFilename);

    cout << "Sorted data has been written to " << outputFilename << endl;

    return 0;
}