#include <iostream>

using namespace std;

class PilhaVetor {
private:
    int dados[30];
    int topo;

public:
    PilhaVetor() {
        topo = -1;
    }

    void push(int valor) {
        topo++;
        dados[topo] = valor;
    }

    int pop() {
        int valor = dados[topo];
        topo--;
        return valor;
    }

    bool isEmpty() {
        return topo == -1;
    }
};

int main() {

    PilhaVetor pares;
    PilhaVetor impares;

    int numero;
    int anterior = -999999;

    cout << "Digite 30 numeros em ordem crescente:\n";

    for (int i = 0; i < 30; i++) {

        do {
            cout << "Numero " << i + 1 << ": ";
            cin >> numero;

            if (numero <= anterior) {
                cout << "ERRO! O numero deve ser maior que o anterior.\n";
            }

        } while (numero <= anterior);

        anterior = numero;

        if (numero % 2 == 0) {
            pares.push(numero);
        }
        else {
            impares.push(numero);
        }
    }

    cout << "\nPares em ordem decrescente:\n";

    while (!pares.isEmpty()) {
        cout << pares.pop() << endl;
    }

    cout << "\nImpares em ordem decrescente:\n";

    while (!impares.isEmpty()) {
        cout << impares.pop() << endl;
    }

    return 0;
}
