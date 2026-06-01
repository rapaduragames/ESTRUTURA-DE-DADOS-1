#include <iostream>
using namespace std;

struct No {
    int senha;
    No *prox;
};

struct Fila {
    No *inicio;
    No *fim;
    int quantidade;
};

void inicializar(Fila &f) {
    f.inicio = nullptr;
    f.fim = nullptr;
    f.quantidade = 0;
}

bool vazia(Fila &f) {
    return f.inicio == nullptr;
}

void enfileirar(Fila &f, int valor) {
    No *novo = new No;
    novo->senha = valor;
    novo->prox = nullptr;

    if (vazia(f)) {
        f.inicio = novo;
        f.fim = novo;
    } else {
        f.fim->prox = novo;
        f.fim = novo;
    }

    f.quantidade++;
}

int desenfileirar(Fila &f) {
    if (vazia(f))
        return -1;

    No *aux = f.inicio;
    int valor = aux->senha;

    f.inicio = f.inicio->prox;

    if (f.inicio == nullptr)
        f.fim = nullptr;

    delete aux;
    f.quantidade--;

    return valor;
}

int main() {
    Fila senhasGeradas;
    Fila senhasAtendidas;

    inicializar(senhasGeradas);
    inicializar(senhasAtendidas);

    int opcao;
    int contadorSenha = 0;

    do {
        cout << "\n=== SISTEMA DE ATENDIMENTO ===\n";
        cout << "Senhas aguardando: " << senhasGeradas.quantidade << "\n";
        cout << "0 - Sair\n";
        cout << "1 - Gerar senha\n";
        cout << "2 - Realizar atendimento\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                contadorSenha++;
                enfileirar(senhasGeradas, contadorSenha);
                cout << "Senha gerada: " << contadorSenha << endl;
                break;

            case 2:
                if (vazia(senhasGeradas)) {
                    cout << "Nao ha senhas para atendimento.\n";
                } else {
                    int senha = desenfileirar(senhasGeradas);
                    cout << "Atendendo senha: " << senha << endl;
                    enfileirar(senhasAtendidas, senha);
                }
                break;

            case 0:
                if (!vazia(senhasGeradas)) {
                    cout << "Ainda existem senhas aguardando atendimento!\n";
                }
                break;

            default:
                cout << "Opcao invalida!\n";
        }

    } while (opcao != 0 || !vazia(senhasGeradas));

    cout << "\nPrograma encerrado.\n";
    cout << "Quantidade de senhas atendidas: "
         << senhasAtendidas.quantidade << endl;

    return 0;
}
