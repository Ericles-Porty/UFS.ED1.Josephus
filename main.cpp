/*
            ALUNOS
    ERICLES DOS SANTOS CUNHA
    MARIA MILENA DE OLIVEIRA SOUZA
    THIAGO SANTOS SANTANA
*/

#include <iostream>
#include <cstring>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

int parametro;
typedef struct no
{
    char nome[30];
    struct no* proxNo;

} tipoNo;

typedef struct listaGerenciada
{
    tipoNo* fim;
    int quant;
} tipoLista;

int gerador()
{
    srand(time(0));
    return rand() % parametro;
}

void criaLista(tipoLista* listaCirc)
{
    listaCirc->fim = NULL;
    listaCirc->quant = 0;
}

int insereNoFimDaLista(tipoLista* listaCirc, char* nome)
{
    tipoNo* novoNo;
    novoNo = (tipoNo*)malloc(sizeof(tipoNo));
    if (listaCirc->fim == NULL)
    {
        tipoNo* novoNo;
        novoNo = (tipoNo*)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
            return 0;
        strcpy(novoNo->nome, nome);
        novoNo->proxNo = novoNo;
        listaCirc->fim = novoNo;
        listaCirc->quant++;
        parametro = listaCirc->quant;
        return 1;
    }
    else
    {
        strcpy(novoNo->nome, nome);
        novoNo->proxNo = listaCirc->fim->proxNo;
        listaCirc->fim->proxNo = novoNo;
        listaCirc->fim = novoNo;
        listaCirc->quant++;
        parametro = listaCirc->quant;
        return 0;
    }
}

void printaLista(tipoLista* listaCirc)
{
    if (listaCirc->quant == 0)
    {
        cout << "Nao existe participantes." << endl;
        return;
    }

    tipoNo* atual;
    atual = listaCirc->fim->proxNo;
    cout << atual->nome;
    while (atual != listaCirc->fim)
    {
        atual = atual->proxNo;
        cout << " - " << atual->nome;
    }
    cout << endl;
}

void Josephus(tipoLista* listaCirc)
{
    tipoNo* atual, * antigo;
    int contador = 0;
    int numRandom = gerador();
    if (listaCirc->quant > 1)
    {
        while (numRandom == 0)
            numRandom = gerador();
        cout << "Numero sorteado: " << numRandom << endl;
        do
        {
            if (contador < numRandom)
                antigo = atual;
            if (numRandom == 1)
                antigo = listaCirc->fim;

            atual = listaCirc->fim->proxNo;
            listaCirc->fim = atual;
            contador++;
            cout << "Lista " << contador << ": " << listaCirc->fim->nome << endl;
        } while (contador < numRandom);
        cout << "O participante " << listaCirc->fim->nome << " foi eliminado." << endl;
        if (numRandom == 1)
        {
            antigo->proxNo = atual->proxNo;
            listaCirc->fim = antigo;
        }
        else
        {
            antigo->proxNo = atual->proxNo;
            listaCirc->fim = antigo;
        }
        listaCirc->quant--;
        if (listaCirc->quant == 1)
        {
            cout << "\nO GANHADOR FOI: " << listaCirc->fim->nome << endl
                << endl;
            criaLista(listaCirc);
        }
    }
    else
        cout << "Sem participantes." << endl;
}

void JosephusResultadoFinal(tipoLista* listaCirc)
{
    tipoNo* atual, * antigo;
    do
    {
        int contador = 0;
        int numRandom = gerador();
        if (listaCirc->quant > 1)
        {
            while (numRandom == 0)
                numRandom = gerador();
            do
            {
                if (contador < numRandom)
                    antigo = atual;
                if (numRandom == 1)
                    antigo = listaCirc->fim;

                atual = listaCirc->fim->proxNo;
                listaCirc->fim = atual;
                contador++;
            } while (contador < numRandom);
            if (numRandom == 1)
            {
                antigo->proxNo = atual->proxNo;
                listaCirc->fim = antigo;
            }
            else
            {
                antigo->proxNo = atual->proxNo;
                listaCirc->fim = antigo;
            }
            listaCirc->quant--;
        }
        else
            cout << "Sem participantes." << endl;
    } while (listaCirc->quant > 1);
    if (listaCirc->quant == 1) {
        cout << "\nO GANHADOR FOI: " << listaCirc->fim->nome << endl;
        criaLista(listaCirc);
    }
}

int main()
{
    tipoLista lista;
    criaLista(&lista);
    int numero, dec, op;
    char nome[30];
    system("cls");
    do
    {
        cout << "0 - Encerrar programa " << endl;
        cout << "1 - Insere participante " << endl;
        cout << "2 - Sortear por partes " << endl;
        cout << "3 - Sortear com resultado final " << endl;
        cout << "4 - Mostra participantes restantes " << endl;
        cout << "Selecione uma opcao: ";
        cin >> op;
        system("cls");
        switch (op)
        {
        case 1:
            cout << "Nome do participante: ";
            getchar();
            cin.getline(nome, 30);

            dec = insereNoFimDaLista(&lista, nome);
            if (dec == 1)
            {
                cout << "O primeiro participante foi cadastrado" << endl;
            }
            else
            {
                cout << "Participante cadastrado" << endl;
            }
            break;
        case 2:
            Josephus(&lista);
            break;
        case 3:
            JosephusResultadoFinal(&lista);
            break;
        default:
            break;

        case 4:
            printaLista(&lista);
            break;
        }

    } while (op != 0);
    return 0;
}