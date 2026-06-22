#include <iostream>

using namespace std;

// ---------------- FILA ----------------

struct NoFila {
    int senha;
    NoFila* prox;
};

struct Fila {
    NoFila* inicio;
    NoFila* fim;
};

void inicializarFila(Fila* f) {
    f->inicio = nullptr;
    f->fim = nullptr;
}

bool filaVazia(Fila* f) {
    return f->inicio == nullptr;
}

void enfileirar(Fila* f, int valor) {
    NoFila* novo = new NoFila;
    novo->senha = valor;
    novo->prox = nullptr;

    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

bool desenfileirar(Fila* f, int& valor) {
    if (filaVazia(f))
        return false;

    NoFila* aux = f->inicio;
    valor = aux->senha;

    f->inicio = aux->prox;

    if (f->inicio == nullptr)
        f->fim = nullptr;

    delete aux;
    return true;
}

int contarFila(Fila* f) {
    int cont = 0;
    NoFila* aux = f->inicio;

    while (aux != nullptr) {
        cont++;
        aux = aux->prox;
    }

    return cont;
}

void listarFila(Fila* f) {
    NoFila* aux = f->inicio;

    if (aux == nullptr) {
        cout << "Nenhuma senha atendida.\n";
        return;
    }

    while (aux != nullptr) {
        cout << aux->senha << " ";
        aux = aux->prox;
    }

    cout << endl;
}

// ---------------- LISTA DE GUICHÊS ----------------

struct Guiche {
    int id;
    Fila senhasAtendidas;
    Guiche* prox;
};

void adicionarGuiche(Guiche*& lista, int id) {
    Guiche* novo = new Guiche;

    novo->id = id;
    inicializarFila(&novo->senhasAtendidas);
    novo->prox = nullptr;

    if (lista == nullptr) {
        lista = novo;
        return;
    }

    Guiche* aux = lista;

    while (aux->prox != nullptr)
        aux = aux->prox;

    aux->prox = novo;
}

Guiche* buscarGuiche(Guiche* lista, int id) {
    Guiche* aux = lista;

    while (aux != nullptr) {
        if (aux->id == id)
            return aux;

        aux = aux->prox;
    }

    return nullptr;
}

int contarGuiches(Guiche* lista) {
    int cont = 0;

    while (lista != nullptr) {
        cont++;
        lista = lista->prox;
    }

    return cont;
}

// ---------------- PROGRAMA ----------------

int main() {

    Fila senhasGeradas;
    inicializarFila(&senhasGeradas);

    Guiche* listaGuiches = nullptr;

    int opcao;
    int proximaSenha = 1;
    int totalAtendidas = 0;

    do {

        cout << "\n==================================\n";
        cout << "Senhas aguardando: "
             << contarFila(&senhasGeradas) << endl;

        cout << "Guiches abertos: "
             << contarGuiches(listaGuiches) << endl;

        cout << "==================================\n";
        cout << "0 - Sair\n";
        cout << "1 - Gerar senha\n";
        cout << "2 - Abrir guiche\n";
        cout << "3 - Realizar atendimento\n";
        cout << "4 - Listar senhas atendidas\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {

        case 1: {
            enfileirar(&senhasGeradas, proximaSenha);

            cout << "Senha gerada: "
                 << proximaSenha << endl;

            proximaSenha++;
            break;
        }

        case 2: {
            int id;

            cout << "ID do guiche: ";
            cin >> id;

            if (buscarGuiche(listaGuiches, id) != nullptr) {
                cout << "Guiche ja existe.\n";
            } else {
                adicionarGuiche(listaGuiches, id);
                cout << "Guiche aberto com sucesso.\n";
            }

            break;
        }

        case 3: {

            if (filaVazia(&senhasGeradas)) {
                cout << "Nao ha senhas aguardando.\n";
                break;
            }

            int id;

            cout << "ID do guiche: ";
            cin >> id;

            Guiche* g = buscarGuiche(listaGuiches, id);

            if (g == nullptr) {
                cout << "Guiche nao encontrado.\n";
                break;
            }

            int senha;

            desenfileirar(&senhasGeradas, senha);

            enfileirar(&g->senhasAtendidas, senha);

            totalAtendidas++;

            cout << "Guiche " << id
                 << " atendeu a senha "
                 << senha << endl;

            break;
        }

        case 4: {

            int id;

            cout << "ID do guiche: ";
            cin >> id;

            Guiche* g = buscarGuiche(listaGuiches, id);

            if (g == nullptr) {
                cout << "Guiche nao encontrado.\n";
            } else {
                cout << "Senhas atendidas pelo guiche "
                     << id << ": ";

                listarFila(&g->senhasAtendidas);
            }

            break;
        }

        case 0: {

            if (!filaVazia(&senhasGeradas)) {
                cout << "\nNao e possivel encerrar.\n";
                cout << "Ainda existem senhas aguardando atendimento.\n";
                opcao = -1;
            }

            break;
        }

        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    cout << "\nPrograma encerrado.\n";
    cout << "Quantidade total de senhas atendidas: "
         << totalAtendidas << endl;

    return 0;
}
