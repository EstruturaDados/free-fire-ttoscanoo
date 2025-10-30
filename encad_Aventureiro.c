#include <stdio.h>
#include <string.h>
#include <stdlib.h> // (NOVO: Essencial para malloc e free)

// Código da Ilha – Edição Free Fire
// Nível: AVENTUREIRO (Versão 2: Mochila com LISTA ENCADEADA)

// --- Definições Globais de Estruturas ---

// (Requisito 1: struct Item)
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// (Requisito 1: struct No)
struct No {
    struct Item dados;     
    struct No* proximo;  
};


// --- Definições Globais ---

// Em vez de um vetor, temos apenas um ponteiro para o início (cabeça) da lista
struct No* listaHead = NULL; 

int numItensLista = 0; // Contador de itens
int g_comparacoes = 0; // Contador para a busca


// --- Protótipos das Funções ---

void limparTela();
void limparBufferEntrada();
void exibirMenu();
void pausarTela();

// (Funções equivalentes para lista)
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();
void liberarLista(); // (NOVO: Importante para evitar vazamento de memória)


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
                inserirItemLista();
                break;
            case 2:
                removerItemLista();
                break;
            case 3:
                listarItensLista();
                break;
            case 4:
                buscarSequencialLista();
                break;
            case 0:
                limparTela();
                liberarLista(); // (NOVO: Limpa a memória antes de sair)
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
    printf("  (Versao: LISTA ENCADEADA)\n");
    printf("  Itens na Mochila: %d\n", numItensLista); // (Não há máximo)
    printf("==================================================\n");
    printf("1. Adicionar Item (inserirItemLista)\n");
    printf("2. Remover Item (removerItemLista)\n");
    printf("3. Listar Itens (listarItensLista)\n");
    printf("4. Buscar Item (buscarSequencialLista)\n");
    printf("0. Sair\n");
    printf("--------------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// --- Implementação das Funções Principais (Lista) ---

// (Requisito 3: Inserir)
void inserirItemLista() {
    limparTela();
    printf("--- (Lista) Adicionar Novo Item ---\n");

    // 1. Alocar espaço na memória para um novo 'No'
    struct No* novoNo = (struct No*) malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("Erro! Falta de memoria para adicionar o item.\n");
        pausarTela();
        return;
    }

    // 2. Preencher os dados do item dentro do 'No'
    printf("Nome do item: ");
    scanf(" %s", novoNo->dados.nome);
    printf("Tipo: ");
    scanf(" %s", novoNo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &(novoNo->dados.quantidade)); 
    limparBufferEntrada();
    
    // 3. "Engatar" o novo 'No' na lista
    novoNo->proximo = listaHead; 
    listaHead = novoNo;        
    
    numItensLista++;
    printf("\nItem '%s' adicionado com sucesso!\n", novoNo->dados.nome);
    pausarTela();
}

// (Requisito 3: Remover)
void removerItemLista() {
    limparTela();
    printf("--- (Lista) Remover Item da Mochila ---\n");
    
    if (listaHead == NULL) { 
        printf("Mochila (Lista) ja esta vazia.\n");
        pausarTela();
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    scanf(" %s", nomeBusca);
    limparBufferEntrada();

    struct No* atual = listaHead;
    struct No* anterior = NULL; // Ponteiro "rastreador"

    // 1. Percorrer a lista para encontrar o item
    while (atual != NULL && strcmp(atual->dados.nome, nomeBusca) != 0) {
        anterior = atual;        
        atual = atual->proximo; 
    }

    // 2. Verificar se encontrou
    if (atual == NULL) {
        printf("Item '%s' nao foi encontrado na mochila.\n", nomeBusca);
    } else {
        
        if (anterior == NULL) {
            listaHead = atual->proximo; 
        } else {
            anterior->proximo = atual->proximo; 
        }

        // 3. Liberar a memória que 'atual' estava usando
        free(atual); // (Este é o "delete" da lista encadeada)
        numItensLista--;
        printf("Item '%s' removido com sucesso!\n", nomeBusca);
    }
    
    pausarTela();
}

// (Requisito 3: Listar)
void listarItensLista() {
    limparTela();
    printf("==================================================\n");
    printf("           --- ITENS NA MOCHILA (%d) ---\n", numItensLista);
    printf("==================================================\n");
    
    if (listaHead == NULL) {
        printf("A mochila esta vazia.\n");
    } else {
        printf("%-30s | %-20s | %s\n", "NOME", "TIPO", "QUANTIDADE");
        printf("--------------------------------------------------\n");
        
        struct No* atual = listaHead; 
        
        // Loop 'while' para percorrer a lista
        while (atual != NULL) {
            // Imprime os dados do 'No' atual
            printf("%-30s | %-20s | %d\n", 
                atual->dados.nome, 
                atual->dados.tipo, 
                atual->dados.quantidade);
                
            atual = atual->proximo; 
        }
    }
    printf("==================================================\n");
    pausarTela(); 
}

// (Requisito 3 e 6: Busca Sequencial com contador)
void buscarSequencialLista() {
    limparTela();
    printf("--- (Lista) Buscar Item (Busca Sequencial) ---\n");

    if (listaHead == NULL) {
        printf("Mochila vazia.\n");
        pausarTela(); return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf(" %s", nomeBusca);
    limparBufferEntrada();

    g_comparacoes = 0;
    struct No* atual = listaHead;
    struct No* itemEncontrado = NULL;

    // Loop 'while' para percorrer a lista
    while (atual != NULL) {
        g_comparacoes++; // Conta a comparação
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            itemEncontrado = atual; // Guarda o ponteiro do item
            break; // Encontrou, para o loop
        }
        atual = atual->proximo; // Avança
    }

    // Exibe o resultado
    if (itemEncontrado == NULL) {
        printf("\nItem '%s' nao encontrado.\n", nomeBusca);
    } else {
        printf("\nItem encontrado!\n");
        printf("--------------------------------------------------\n");
        printf("%-30s | %-20s | %s\n", "NOME", "TIPO", "QTD.");
        printf("--------------------------------------------------\n");
        printf("%-30s | %-20s | %d\n", 
            itemEncontrado->dados.nome, 
            itemEncontrado->dados.tipo, 
            itemEncontrado->dados.quantidade);
    }
    
    printf("\nNumero de comparacoes realizadas: %d\n", g_comparacoes);
    pausarTela();
}


// (Função de "limpeza" para evitar vazamento de memória)
void liberarLista() {
    struct No* atual = listaHead;
    struct No* proximoNo;
    
    while (atual != NULL) {
        proximoNo = atual->proximo; // Guarda a referência para o próximo
        free(atual);                // Libera o 'No' atual
        atual = proximoNo;          // Avança para o próximo
    }
    listaHead = NULL; // Marca a lista como vazia
    printf("Memoria da lista liberada.\n");
}