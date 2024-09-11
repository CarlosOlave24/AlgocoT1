#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono> // Para medir el tiempo

using namespace std;
using namespace std::chrono; // Para acceder a las funciones de chrono

//Funcion auxiliar merge
void merge(vector<int>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Funcion Merge sort
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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
            data.push_back(stoi(value)); // Convert string to int and add to vector
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
    // Nombres de los archivos a ocupar
    string inputFilename = "partially_sorted_list.csv";
    string outputFilename = "resultado.csv";
    string timeFilename = "sorting_times.csv";

    // Se leen los datos del CSV
    vector<int> data = readCSV(inputFilename);

    auto start = high_resolution_clock::now(); // Inicio del temporizador

    // merge sort
    mergeSort(data, 0, data.size() - 1);

    auto stop = high_resolution_clock::now();  // Fin del temporizador
    auto duration = duration_cast<milliseconds>(stop - start); 

    // Se Escribe el tiempo de ejecución en un archivo CSV para algoritmos de sorting
    writeTimeToCSV(timeFilename, "Merge Sort partially_sorted_list", duration.count());

    // Se Muestra el tiempo de ejecución en la consola
    cout << "El tiempo de ejecución del Merge Sort fue de: " << duration.count() << " milisegundos" << endl;

    // Se escriben los datos ordenados en un CSV
    writeCSV(data, outputFilename);

    cout << "Sorted data has been written to " << outputFilename << endl;

    return 0;
}