#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

vector<int> numeros;

void leerArchivo(string nombreArchivo);
void selectionSort();
void heapSort();
void countingSort();
void quickSort(int izquierda, int derecha);
bool estaOrdenado();
void mostrarMenu();