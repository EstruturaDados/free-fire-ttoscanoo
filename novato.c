#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Código da Ilha – Edição Free Fire
// Nível: NOVATO 

// --- Definições Globais ---

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

#define MAX_ITENS 10
struct Item mochila[MAX_ITENS];
int numItens = 0;

// --- Protótipos das Funções ---

void limparTela();
void limparBufferEntrada(); 
void exibirMenu();
void pausarTela(); 

void inserirItem();
void removerItem();
void listarItens();
void buscarItem();


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
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                pausarTela();
                break;
            case 4:
                buscarItem();
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

// --- Implementação das Funções ---

void limparTela() {
    system("clear");
}


void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void pausarTela() {
    printf("\n[Pressione Enter para continuar...]");
    getchar(); 
}

void exibirMenu() {
    limparTela(); 
    printf("===========================================\n");
    printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("  Itens na Mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("===========================================\n");
    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("4. Buscar Item por Nome\n");
    printf("0. Sair\n");
    printf("-------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

void inserirItem() {
    limparTela(); 
    printf("--- Adicionar Novo Item ---\n");

    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
    } else {
        
        printf("Nome do item: ");
        scanf(" %s", mochila[numItens].nome); 

        printf("Tipo (arma, municao, cura, etc.): ");
        scanf(" %s", mochila[numItens].tipo);

        printf("Quantidade: ");
        scanf("%d", &mochila[numItens].quantidade);
        limparBufferEntrada(); 

        printf("\nItem '%s' adicionado com sucesso!\n", mochila[numItens].nome);
        
        numItens++;
    }
    
    printf("\n...Atualizando lista de itens...\n");
    
    pausarTela(); 
    
    listarItens(); 
    pausarTela();  
}

void removerItem() {
    limparTela();
    listarItens();
    printf("--- Remover Item da Mochila ---\n");

    if (numItens == 0) {
        printf("Mochila ja esta vazia. Nada para remover.\n");
        pausarTela();
        return;
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
        printf("Item '%s' nao foi encontrado na mochila.\n", nomeBusca);
    } else {
        for (int i = indiceEncontrado; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("Item '%s' removido com sucesso!\n", nomeBusca);
    }
    
    printf("\n...Atualizando lista de itens...\n");
    pausarTela();
    listarItens();
    pausarTela();
}


void listarItens() {
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

void buscarItem() {
    limparTela(); 
    printf("--- Buscar Item por Nome ---\n");

    if (numItens == 0) {
        printf("Mochila vazia. Nada para buscar.\n");
        pausarTela();
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
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
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
    } else {
        printf("\nItem encontrado!\n");
        printf("--------------------------------------------------\n");
        printf("%-30s | %-20s | %s\n", "NOME", "TIPO", "QTD.");
        printf("--------------------------------------------------\n");
        printf("%-30s | %-20s | %d\n", 
            mochila[indiceEncontrado].nome, 
            mochila[indiceEncontrado].tipo, 
            mochila[indiceEncontrado].quantidade);
    }
    
    pausarTela();
}