#include <iostream>

using namespace std;

void imprimirVetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int particiona(int v[], int inicio, int fim) {
    int pivo = v[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (v[j] <= pivo) {
            i++;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[fim]);
    return i + 1;
}

void quickSort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int p = particiona(v, inicio, fim);

        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}

int main() {
    int v[] = {49, 38, 58, 87, 34, 93, 26, 13};
    int n = sizeof(v) / sizeof(v[0]);

    cout << "Vetor antes da ordenacao:" << endl;
    imprimirVetor(v, n);

    quickSort(v, 0, n - 1);

    cout << "\nVetor apos a ordenacao:" << endl;
    imprimirVetor(v, n);

    return 0;
}
