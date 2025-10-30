#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: AVENTUREIRO (Versao 1: Mochila com VETOR)
// (Nomenclatura alinhada com o Enunciado)

// --- Definições Globais ---

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

#define MAX_ITENS 10
struct Item mochila[MAX_ITENS];
int numItens = 0;

bool isVetorOrdenado = false; 
int g_comparacoes = 0;

// --- Protótipos das Funções ---

void limparTela();
void limparBufferEntrada();
void exibirMenu();
void pausarTela();

// (Nomes de acordo com o Enunciado)
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor(); // (Função auxiliar de listagem)
void buscarSequencialVetor();
void ordenarVetor();
void buscarBinariaVetor(); 


// --- Função Principal ---

int main() {
    int opcao;

    do {
        exibirMenu();
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            limparBufferEntrada();
            opcao = -1;
            pausarTela();
            continue;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirItemVetor(); 
                break;
            case 2:
                removerItemVetor(); 
                break;
            case 3:
                listarItensVetor(); 
                pausarTela();
                break;
            case 4:
                buscarSequencialVetor(); 
                break;
            case 5:
                ordenarVetor(); 
                break;
            case 6:
                buscarBinariaVetor(); 
                break;
            case 0:
                limparTela();
                printf("Saindo do gerenciador de mochila... Ate logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                pausarTela();
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções Auxiliares ---

void limparTela() { system("clear"); }

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausarTela() {
    printf("\n[Pressione Enter para continuar...]");
    getchar();
}

void exibirMenu() {
    limparTela();
    printf("==================================================\n");
    printf("  MOCHILA DE SOBREVIVENCIA (Nivel Aventureiro)\n");
    printf("  (Versao: VETOR)\n");
    printf("  Itens na Mochila: %d/%d | Ordenado: %s\n", numItens, MAX_ITENS, isVetorOrdenado ? "Sim" : "Nao");
    printf("==================================================\n");
    printf("1. Adicionar Item (inserirItemVetor)\n");
    printf("2. Remover Item (removerItemVetor)\n");
    printf("3. Listar Itens (listarItensVetor)\n");
    printf("4. Buscar Item (buscarSequencialVetor)\n");
    printf("5. Ordenar Itens (ordenarVetor)\n");
    printf("6. Buscar Item (buscarBinariaVetor)\n");
    printf("0. Sair\n");
    printf("--------------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// --- Implementação das Funções Principais ---


void inserirItemVetor() {
    limparTela();
    printf("--- (Vetor) Adicionar Novo Item ---\n");

    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
    } else {
        printf("Nome do item: ");
        scanf(" %s", mochila[numItens].nome);
        printf("Tipo: ");
        scanf(" %s", mochila[numItens].tipo);
        printf("Quantidade: ");
        scanf("%d", &mochila[numItens].quantidade);
        limparBufferEntrada();
        printf("\nItem '%s' adicionado com sucesso!\n", mochila[numItens].nome);
        numItens++;
        isVetorOrdenado = false; // "Quebra" a ordenação
    }
    
    printf("\n...Atualizando lista de itens...\n");
    pausarTela();
    listarItensVetor();
    pausarTela();  
}


void removerItemVetor() {
    limparTela();
    printf("--- (Vetor) Remover Item da Mochila ---\n");
    if (numItens == 0) {
        printf("Mochila ja esta vazia.\n");
        pausarTela(); return;
    }
    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    scanf(" %s", nomeBusca);
    limparBufferEntrada();

    int indiceEncontrado = -1;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("Item '%s' nao foi encontrado.\n", nomeBusca);
    } else {
        for (int i = indiceEncontrado; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("Item '%s' removido com sucesso!\n", nomeBusca);
        isVetorOrdenado = false; // "Quebra" a ordenação
    }
    
    printf("\n...Atualizando lista de itens...\n");
    pausarTela();
    listarItensVetor();
    pausarTela();
}


void listarItensVetor() {
    limparTela();
    printf("==================================================\n");
    printf("           --- ITENS NA MOCHILA (%d/%d) ---\n", numItens, MAX_ITENS);
    printf("==================================================\n");
    if (numItens == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        printf("%-30s | %-20s | %s\n", "NOME", "TIPO", "QUANTIDADE");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < numItens; i++) {
            printf("%-30s | %-20s | %d\n", 
                mochila[i].nome, 
                mochila[i].tipo, 
                mochila[i].quantidade);
        }
    }
    printf("==================================================\n");
}


// (Requisito 4: Ordenação no vetor - Bubble Sort)
void ordenarVetor() {
    limparTela();
    printf("--- (Vetor) Ordenando Itens por Nome (Bubble Sort) ---\n");

    if (numItens < 2) {
        printf("Nao ha itens suficientes para ordenar.\n");
        isVetorOrdenado = true;
        pausarTela();
        return;
    }

    // Lógica do Bubble Sort
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                // Troca os itens de lugar
                struct Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    isVetorOrdenado = true;
    printf("Mochila ordenada com sucesso!\n");
    
    listarItensVetor();
    pausarTela();
}


// (Requisito 6: Contador de operações)
void buscarSequencialVetor() {
    limparTela();
    printf("--- (Vetor) Buscar Item (Busca Sequencial) ---\n");

    if (numItens == 0) {
        printf("Mochila vazia.\n");
        pausarTela(); return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf(" %s", nomeBusca);
    limparBufferEntrada();

    g_comparacoes = 0;
    int indiceEncontrado = -1;

    for (int i = 0; i < numItens; i++) {
        g_comparacoes++;
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\nItem '%s' nao encontrado.\n", nomeBusca);
    } else {
        printf("\nItem encontrado!\n");
        printf("%-30s | %-20s | %d\n", 
            mochila[indiceEncontrado].nome, 
            mochila[indiceEncontrado].tipo, 
            mochila[indiceEncontrado].quantidade);
    }
    
    printf("\nNumero de comparacoes realizadas: %d\n", g_comparacoes);
    pausarTela();
}


// (Requisito 5: Busca Binária)
void buscarBinariaVetor() {
    limparTela();
    printf("--- (Vetor) Buscar Item (Busca Binaria) ---\n");

 
    if (isVetorOrdenado == false) {
        printf("ERRO: O vetor nao esta ordenado!\n");
        printf("Use a opcao 5 (ordenarVetor) primeiro.\n");
        pausarTela();
        return; // Não executa a busca
    }

    if (numItens == 0) {
        printf("Mochila vazia.\n");
        pausarTela(); return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf(" %s", nomeBusca);
    limparBufferEntrada();

    g_comparacoes = 0;
    int indiceEncontrado = -1;

    // Lógica da Busca Binária
    int esquerda = 0;
    int direita = numItens - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        g_comparacoes++;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            indiceEncontrado = meio;
            break;
        } 
        else if (cmp < 0) {
            esquerda = meio + 1;
        } 
        else {
            direita = meio - 1;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\nItem '%s' nao encontrado.\n", nomeBusca);
    } else {
        printf("\nItem encontrado!\n");
        printf("%-30s | %-20s | %d\n", 
            mochila[indiceEncontrado].nome, 
            mochila[indiceEncontrado].tipo, 
            mochila[indiceEncontrado].quantidade);
    }

    printf("\nNumero de comparacoes realizadas: %d\n", g_comparacoes);
    pausarTela();
}