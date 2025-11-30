#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct para representar um cômodo (Nó da Árvore)
// Contém o nome da sala e ponteiros para os caminhos Esquerda e Direita. 
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda; // Caminho para o filho à esquerda
    struct Sala* direita;  // Caminho para o filho à direita
} Sala;

// --- 1. FUNÇÕES OBRIGATÓRIAS ---

/*
 * criarSala() - Cria dinamicamente um novo nó (cômodo) na memória. [cite: 1782, 1792]
 * Recebe o nome e inicializa os ponteiros dos filhos como NULL.
 */
Sala* criarSala(const char* nome) {
    // Aloca memória para a nova sala
    Sala* nova_sala = (Sala*)malloc(sizeof(Sala));

    if (nova_sala == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    
    // Copia o nome da sala para o campo 'nome'
    strncpy(nova_sala->nome, nome, 49);
    nova_sala->nome[49] = '\0'; 
    
    // Inicializa os ponteiros dos filhos como NULL
    nova_sala->esquerda = NULL;
    nova_sala->direita = NULL;

    return nova_sala;
}

/*
 * explorarSalas() - Permite a navegação interativa do jogador pela árvore do mapa. [cite: 1783, 1773]
 * A navegação continua até o jogador digitar 's' ou chegar a um nó-folha. [cite: 1775, 1787]
 */
void explorarSalas(Sala* atual) {
    char escolha;

    // Loop de exploração: continua enquanto a sala atual não for uma folha
    while (atual != NULL) {
        printf("\nVocê está em: **%s**\n", atual->nome);

        // Verifica se é um nó-folha (não tem caminhos para esquerda nem direita)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou a um beco sem saída! Fim da exploração neste caminho.\n");
            break; // Sai do loop ao atingir um nó-folha 
        }
        
        // Exibe as opções de navegação
        printf("Escolha o próximo caminho:\n");
        if (atual->esquerda != NULL) {
            printf("  [e] Esquerda -> %s\n", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("  [d] Direita -> %s\n", atual->direita->nome);
        }
        printf("  [s] Sair da exploração\n");
        printf("Sua escolha (e/d/s): ");

        if (scanf(" %c", &escolha) != 1) { // Nota: o espaço antes de %c consome newlines/whitespaces
            // Lógica de limpeza do buffer em caso de entrada inválida
            while (getchar() != '\n'); 
            escolha = 'i'; // Opção inválida
        }

        // --- Lógica de Decisão (Condicionais) --- [cite: 1793]
        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Caminho esquerdo não existe! Tente outra direção.\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Caminho direito não existe! Tente outra direção.\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("Encerrando a exploração.\n");
            break; 
        } else {
            printf("Escolha inválida. Use 'e', 'd' ou 's'.\n");
        }
    }
}

/*
 * liberarMemoria() - Libera a memória alocada dinamicamente para os nós da árvore.
 * Usa o percurso Pós-ordem (visita filhos, depois o nó atual) para liberar com segurança.
 */
void liberarMemoria(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarMemoria(raiz->esquerda);
    liberarMemoria(raiz->direita);
    free(raiz);
}

/*
 * main() - Monta a estrutura da árvore e inicia a exploração. [cite: 1784]
 */
int main() {
    printf("=== DETECTIVE QUEST: EXPLORAÇÃO DA MANSÃO (Nível Novato) ===\n");
    printf("O mapa da mansão foi montado automaticamente (Árvore Binária).\n");

    // --- 2. MONTAGEM DA ÁRVORE (Estrutura da Mansão) --- [cite: 1774, 1788]
    
    // Nível 0: Raiz
    Sala* hall = criarSala("Hall de Entrada");

    // Nível 1
    Sala* sala_estar = criarSala("Sala de Estar");
    Sala* biblioteca = criarSala("Biblioteca");
    hall->esquerda = sala_estar;
    hall->direita = biblioteca;
    
    // Nível 2
    Sala* quarto = criarSala("Quarto Principal");
    Sala* cozinha = criarSala("Cozinha");
    sala_estar->esquerda = quarto;
    sala_estar->direita = cozinha; // Novo caminho adicionado aqui
    
    // Nível 3 (Folhas)
    Sala* jardim = criarSala("Jardim");
    quarto->esquerda = jardim; // Quarto->Direita = NULL (folha)

    biblioteca->esquerda = criarSala("Sala de Jantar");
    // biblioteca->direita = NULL (folha)
    // Cozinha->Esquerda = NULL; Cozinha->Direita = NULL (folha)


    // --- 3. INÍCIO DA EXPLORAÇÃO ---
    printf("\nIniciando a exploração a partir do **%s**...\n", hall->nome);
    explorarSalas(hall);

    // Libera toda a memória alocada ao final da execução [cite: 1695]
    liberarMemoria(hall); 

    printf("\nPrograma finalizado. Lógica da Árvore Binária dominada.\n");

    return 0;
}