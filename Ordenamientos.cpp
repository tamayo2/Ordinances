#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

vector<int> numeros;

void leerArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    int num;
    numeros.clear();

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    while (archivo >> num) {
        numeros.push_back(num);
    }

    archivo.close();
}

void mostrarNumerosOrdenados() {
    cout << "Numeros ordenados:" << endl;
    for (int i = 0; i < numeros.size(); i++) {
        cout << numeros[i] << " ";

        if ((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void selectionSort() {
    int n = numeros.size();
    if (n <= 1) {
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (numeros[j] < numeros[min_idx]) {
                min_idx = j;
            }
        }
        int temp = numeros[i];
        numeros[i] = numeros[min_idx];
        numeros[min_idx] = temp;
    }
}

void heapify(int n, int i) {
    int mayor = i; 
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < n && numeros[izquierda] > numeros[mayor]) {
        mayor = izquierda;
    }

    if (derecha < n && numeros[derecha] > numeros[mayor]) {
        mayor = derecha;
    }

    if (mayor != i) {
        int temp = numeros[i];
        numeros[i] = numeros[mayor];
        numeros[mayor] = temp;
        heapify(n, mayor);
    }
}

void heapSort() {
    int n = numeros.size();

    if (n <= 1) {
        return;
    }

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        int temp = numeros[0];
        numeros[0] = numeros[i];
        numeros[i] = temp;

        heapify(i, 0);
    }
}

void countingSort() {
    int n = numeros.size();

    if (n <= 1) {
        return;
    }

    int maxVal = numeros[0];
    for (int i = 1; i < n; i++) {
        if (numeros[i] > maxVal) {
            maxVal = numeros[i];
        }
    }

    int minVal = numeros[0];
    for (int i = 1; i < n; i++) {
        if (numeros[i] < minVal) {
            minVal = numeros[i];
        }
    }
    if (minVal < 0) {
        cout << "Error: Counting Sort no puede manejar numeros negativos." << endl;
        return;
    }

    vector<int> conteo(maxVal + 1, 0);
    for (int i = 0; i < n; i++) {
        conteo[numeros[i]]++;
    }

    int idx = 0;
    for (int i = 0; i <= maxVal; i++) {
        while (conteo[i] > 0) {
            numeros[idx] = i;
            idx++;
            conteo[i]--;
        }
    }
}

int particion(int izquierda, int derecha) {
    int pivote = numeros[derecha];
    int i = izquierda - 1;

    for (int j = izquierda; j < derecha; j++) {
        if (numeros[j] <= pivote) {
            i++;
            int temp = numeros[i];
            numeros[i] = numeros[j];
            numeros[j] = temp;
        }
    }

    int temp = numeros[i + 1];
    numeros[i + 1] = numeros[derecha];
    numeros[derecha] = temp;

    return i + 1;
}

void quickSort(int izquierda, int derecha) {
    if (izquierda < derecha) {
        int pivote = particion(izquierda, derecha);
        quickSort(izquierda, pivote - 1);
        quickSort(pivote + 1, derecha);
    }
}

bool estaOrdenado() {
    for (int i = 1; i < numeros.size(); i++) {
        if (numeros[i] < numeros[i - 1]) {
            return false;
        }
    }
    return true;
}

void mostrarMenu() {
    int opcion;
    cout << "=== Menu de Ordenamiento ===" << endl;
    cout << "1. Selection Sort" << endl;
    cout << "2. Heap Sort" << endl;
    cout << "3. Counting Sort" << endl;
    cout << "4. Quick Sort" << endl;
    cout << "5. Salir" << endl;
    cout << "Elige un metodo de ordenamiento (1-5): ";
    cin >> opcion;

    vector<int> numerosCopia = numeros;

    clock_t inicio = clock();

    if (opcion == 1) {
        cout << "Ordenando con Selection Sort..." << endl;
        selectionSort();
    }
    else if (opcion == 2) {
        cout << "Ordenando con Heap Sort..." << endl;
        heapSort();
    }
    else if (opcion == 3) {
        cout << "Ordenando con Counting Sort..." << endl;
        countingSort();
    }
    else if (opcion == 4) {
        cout << "Ordenando con Quick Sort..." << endl;
        quickSort(0, numeros.size() - 1);
    }
    else if (opcion == 5) {
        cout << "Saliendo del programa..." << endl;
        exit(0);
    }
    else {
        cout << "Opcion invalida." << endl;
        return;
    }

    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC * 1000;

    if (estaOrdenado()) {
        cout << "Los numeros estan correctamente ordenados." << endl;
    }
    else {
        cout << "Error: Los numeros NO estan correctamente ordenados." << endl;
    }

    mostrarNumerosOrdenados();

    cout << "Tiempo de ejecucion: " << tiempo << " milisegundos." << endl;

    numeros = numerosCopia;
}

int main() {
    string archivos[5] = {"numeros1.txt", "numeros2.txt", "numeros3.txt", "numeros4.txt", "numeros5.txt"};
    
    while (true) {
        int archivoElegido;
        cout << "=== Seleccion de Archivo ===" << endl;
        cout << "1. numeros1.txt" << endl;
        cout << "2. numeros2.txt" << endl;
        cout << "3. numeros3.txt" << endl;
        cout << "4. numeros4.txt" << endl;
        cout << "5. numeros5.txt" << endl;
        cout << "Elige un archivo (1-5): ";
        cin >> archivoElegido;

        if (archivoElegido < 1 || archivoElegido > 5) {
            cout << "Opcion invalida, intenta de nuevo." << endl;
            continue;
        }

        leerArchivo(archivos[archivoElegido - 1]);
        cout << "Se leyeron " << numeros.size() << " numeros del archivo." << endl;

        mostrarMenu();
    }

    return 0;
}