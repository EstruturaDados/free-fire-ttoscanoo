#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> // (Necessário para clock())

// Código da Ilha – Edição Free Fire
// Nível: Mestre

// --- DEFINIÇÕES DE TIPOS (MOVIMOS PARA CIMA) ---

// (Struct 'Componente': Conforme Imagens, com todos os campos)
struct Componente {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
};

// (Enum CriterioOrdenacao: Conforme Readme)
enum CriterioOrdenacao {
    NOME,
    TIPO,
    PRIORIDADE
};

// --- DEFINIÇÕES GLOBAIS (APENAS UM LUGAR) ---

#define MAX_ITENS 10
struct Componente mochila[MAX_ITENS];

// (Variáveis de controle)
int numItens = 0;
long long g_comparacoes = 0; 
bool ordenadaPorNome = false;

// --- PROTÓTIPOS FUNÇÕES AUXILIARES ---
void limparTela();
void limparBufferEntrada();
void pausarTela();
void lerStringSegura(char* destino, int tamanho); 

// --- PROTÓTIPOS FUNÇÕES PRINCIPAIS ---
void exibirMenu();
void inserirComponente();
void removerComponente();
void listarComponentes();
void menuDeOrdenacao();
void insertionSort(enum CriterioOrdenacao criterio);
void buscaBinariaPorNome();
void medirTempo(void (*algoritmo)(enum CriterioOrdenacao), enum CriterioOrdenacao criterio);

// --- FUNÇÃO PRINCIPAL ---

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
        limparBufferEntrada(); // (Limpa o \n do scanf)

        switch (opcao) {
            case 1: inserirComponente(); break;
            case 2: removerComponente(); break;
            case 3: 
                limparTela();
                listarComponentes(); 
                pausarTela(); 
                break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0:
                limparTela();
                printf("ATIVANDO TORRE DE FUGA (Sair)...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                pausarTela();
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO FUNÇÕES AUXILIARES ---

void limparTela() { 
    system("clear"); 
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausarTela() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

void lerStringSegura(char* destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    // Remove o '\n' (Enter) que o fgets captura
    size_t len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') {
        destino[len - 1] = '\0';
    }
}

// (Requisito do Enunciado: medirTempo)
void medirTempo(void (*algoritmo)(enum CriterioOrdenacao), enum CriterioOrdenacao criterio) {
    clock_t start, end;
    double cpu_time_used;

    start = clock(); 
    algoritmo(criterio); 
    end = clock(); 
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Analise de Desempenho: Foram necessarias %lld comparacoes.\n", g_comparacoes);
    printf("Tempo de execucao: %f segundos.\n", cpu_time_used);
}


// --- IMPLEMENTAÇÃO FUNÇÕES PRINCIPAIS ---

void exibirMenu() {
    limparTela();
    printf("==================================================\n");
    printf("  PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("==================================================\n");
    printf("Itens na Mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("Status da Ordenacao por Nome: %s\n", ordenadaPorNome ? "ORDENADO" : "NAO ORDENADO");
    printf("--------------------------------------------------\n");
    printf("1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar Mochila (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave (por nome)\n");
    printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("==================================================\n");
    printf("Escolha uma opcao: ");
}

void inserirComponente() {
    limparTela();
    printf("--- Coletando Novo Componente ---\n");
    if (numItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
    } else {
        printf("Nome: ");
        lerStringSegura(mochila[numItens].nome, 30);

        printf("Tipo (Estrutural, Eletronico, Energia): ");
        lerStringSegura(mochila[numItens].tipo, 20);

        printf("Quantidade: ");
        scanf("%d", &mochila[numItens].quantidade);
        
        printf("Prioridade de Montagem (1-5): ");
        scanf("%d", &mochila[numItens].prioridade);
        limparBufferEntrada(); // (Limpa o \n do último scanf)
        
        printf("\nComponente '%s' adicionado com sucesso!\n", mochila[numItens].nome);
        numItens++;
        ordenadaPorNome = false;
    }
    pausarTela();
}

void removerComponente() {
    limparTela();
    printf("--- Descartar Componente ---\n");
    if (numItens == 0) {
        printf("Mochila ja esta vazia.\n");
        pausarTela(); return;
    }
    char nomeBusca[30];
    printf("Digite o nome do componente a descartar: ");
    lerStringSegura(nomeBusca, 30);

    int indiceEncontrado = -1;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("Componente '%s' nao foi encontrado.\n", nomeBusca);
    } else {
        for (int i = indiceEncontrado; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("Componente '%s' descartado com sucesso!\n", nomeBusca);
        ordenadaPorNome = false; 
    }
    pausarTela();
}

void listarComponentes() {
    printf("=================================================================\n");
    printf("               --- INVENTARIO ATUAL (%d/%d) ---\n", numItens, MAX_ITENS);
    printf("=================================================================\n");
    
    if (numItens == 0) {
        printf("O inventario esta vazio.\n");
    } else {
        printf("%-15s | %-12s | %10s | %10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
        printf("-----------------------------------------------------------------\n");
        for (int i = 0; i < numItens; i++) {
            printf("%-15s | %-12s | %10d | %10d\n", 
                mochila[i].nome, 
                mochila[i].tipo, 
                mochila[i].quantidade,
                mochila[i].prioridade);
        }
    }
    printf("=================================================================\n");
}

void menuDeOrdenacao() {
    limparTela();
    printf("--- Organizar Mochila (Ordenar Componentes) ---\n");
    printf("Escolha o criterio para ordenar:\n");
    printf("1. Por Nome (A-Z)\n");
    printf("2. Por Tipo (A-Z)\n");
    printf("3. Por Prioridade (5-1, da mais alta para a mais baixa)\n");
    printf("0. Cancelar\n");
    printf("Escolha uma opcao: ");

    int opcao;
    if (scanf("%d", &opcao) != 1) {
        printf("Entrada invalida!\n");
        limparBufferEntrada();
        pausarTela(); return;
    }
    limparBufferEntrada(); 

    if (opcao == 0) return;

    g_comparacoes = 0;
    const char* criterioNome = "";
    enum CriterioOrdenacao criterioEscolhido;

    switch(opcao) {
        case 1:
            criterioNome = "NOME";
            criterioEscolhido = NOME;
            break;
        case 2:
            criterioNome = "TIPO";
            criterioEscolhido = TIPO;
            break;
        case 3:
            criterioNome = "PRIORIDADE";
            criterioEscolhido = PRIORIDADE;
            break;
        default:
            printf("Opcao invalida.\n");
            pausarTela(); return;
    }

    printf("\nOrdenando por %s. Aguarde...\n", criterioNome);
    medirTempo(insertionSort, criterioEscolhido);     
    
    listarComponentes(); 
    pausarTela();
}

void insertionSort(enum CriterioOrdenacao criterio) {
    ordenadaPorNome = false;
    for (int i = 1; i < numItens; i++) {
        struct Componente chave = mochila[i];
        int j = i - 1;
        bool precisaMover = false;
        
        while (j >= 0) {
            g_comparacoes++;
            if (criterio == NOME) {
                precisaMover = strcmp(mochila[j].nome, chave.nome) > 0;
            } else if (criterio == TIPO) {
                precisaMover = strcmp(mochila[j].tipo, chave.tipo) > 0;
            } else {
                precisaMover = mochila[j].prioridade < chave.prioridade;
            }
            
            if (precisaMover) {
                mochila[j + 1] = mochila[j];
                j = j - 1;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
    if (criterio == NOME) {
        ordenadaPorNome = true;
    }
}

void buscaBinariaPorNome() {
    limparTela();
    printf("--- Busca Binaria por Componente-Chave (por nome) ---\n");

    if (ordenadaPorNome == false) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a Opcao 4 para organizar a mochila primeiro.\n");
        pausarTela();
        return;
    }
    if (numItens == 0) {
        printf("Mochila vazia.\n");
        pausarTela(); return;
    }

    char nomeBusca[30];
    printf("Digite o nome do componente-chave a buscar: ");
    lerStringSegura(nomeBusca, 30);

    g_comparacoes = 0;
    int indiceEncontrado = -1;
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
        printf("\nComponente '%s' nao encontrado.\n", nomeBusca);
    } else {
        printf("\nComponente-Chave encontrado!\n");
        printf("%-15s | %-12s | %10d | %10d\n", 
            mochila[indiceEncontrado].nome, 
            mochila[indiceEncontrado].tipo, 
            mochila[indiceEncontrado].quantidade,
            mochila[indiceEncontrado].prioridade);
    }
    printf("\nNumero de comparacoes realizadas: %lld\n", g_comparacoes);
    pausarTela();
}