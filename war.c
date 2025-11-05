#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
   Estrutura: Territorio
   ------------------------------------------------------------
   Representa um território no jogo, contendo:
   - nome: nome do território
   - cor: cor do exército que o domina
   - tropas: número de tropas alocadas
   ============================================================ */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ============================================================
   Função: atribuirMissao
   ------------------------------------------------------------
   Sorteia uma missão aleatoriamente e a copia para o destino.
   Parâmetros:
   - destino: ponteiro para armazenar a missão sorteada
   - missoes: vetor de strings com as missões disponíveis
   - totalMissoes: número total de missões no vetor
   ============================================================ */
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

/* ============================================================
   Função: exibirMissao
   ------------------------------------------------------------
   Exibe a missão do jogador (passagem por valor).
   ============================================================ */
void exibirMissao(char *missao) {
    printf("\nSua missão: %s\n", missao);
}

/* ============================================================
   Função: atacar
   ------------------------------------------------------------
   Simula um ataque entre territórios usando dados (1 a 6).
   - Se o atacante vencer: defensor muda de cor e perde tropas.
   - Se o atacante perder: ele perde uma tropa.
   ============================================================ */
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nVocê não pode atacar seu próprio território!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nAtaque: %s (%d) x %s (%d)\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Vitória! %s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Derrota! %s perdeu uma tropa.\n", atacante->nome);
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

/* ============================================================
   Função: verificarMissao
   ------------------------------------------------------------
   Verifica se o jogador cumpriu sua missão.
   (Lógica simplificada apenas para demonstração)
   ============================================================ */
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    if (strstr(missao, "3 territorios")) {
        // Verifica se há 3 territórios consecutivos da mesma cor
        int cont = 1;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0) {
                cont++;
                if (cont >= 3) return 1; // Missão cumprida
            } else {
                cont = 1;
            }
        }
    }

    if (strstr(missao, "vermelha")) {
        // Verifica se não há mais territórios vermelhos
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0)
                return 0;
        }
        return 1; // Missão cumprida
    }

    return 0; // Não cumpriu
}

/* ============================================================
   Função: exibirMapa
   ------------------------------------------------------------
   Exibe todos os territórios com seus dados.
   ============================================================ */
void exibirMapa(Territorio *mapa, int tamanho) {
    printf("\n=== Mapa Atual ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Território: %-12s | Cor: %-8s | Tropas: %d\n",
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/* ============================================================
   Função: liberarMemoria
   ------------------------------------------------------------
   Libera a memória alocada dinamicamente.
   ============================================================ */
void liberarMemoria(Territorio *mapa, char *missao1, char *missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
}

/* ============================================================
   Função principal
   ============================================================ */
int main() {
    srand(time(NULL));

    // 1. Criação do vetor de missões
    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Dominar todos os territorios azuis",
        "Controlar metade do mapa",
        "Manter 5 territorios com mais de 5 tropas"
    };
    int totalMissoes = 5;

    // 2. Alocação dinâmica do mapa (5 territórios)
    Territorio *mapa = (Territorio *) calloc(5, sizeof(Territorio));

    // 3. Cadastro simples dos territórios
    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "azul");
    mapa[0].tropas = 4;

    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "vermelha");
    mapa[1].tropas = 3;

    strcpy(mapa[2].nome, "Chile");
    strcpy(mapa[2].cor, "vermelha");
    mapa[2].tropas = 2;

    strcpy(mapa[3].nome, "Peru");
    strcpy(mapa[3].cor, "azul");
    mapa[3].tropas = 5;

    strcpy(mapa[4].nome, "Colombia");
    strcpy(mapa[4].cor, "verde");
    mapa[4].tropas = 3;

    // 4. Atribuição dinâmica das missões
    char *missaoJogador1 = (char *) malloc(100 * sizeof(char));
    char *missaoJogador2 = (char *) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("=== Início do Jogo ===\n");
    printf("\nJogador 1 ");
    exibirMissao(missaoJogador1);

    printf("\nJogador 2 ");
    exibirMissao(missaoJogador2);

    // 5. Exibir mapa inicial
    exibirMapa(mapa, 5);

    // 6. Simulação simples de turno
    printf("\n--- Turno de ataque ---\n");
    atacar(&mapa[0], &mapa[1]); // Jogador 1 ataca
    exibirMapa(mapa, 5);

    // 7. Verificar se alguém venceu
    if (verificarMissao(missaoJogador1, mapa, 5)) {
        printf("\n🎯 Jogador 1 cumpriu sua missão e venceu!\n");
    } else if (verificarMissao(missaoJogador2, mapa, 5)) {
        printf("\n🎯 Jogador 2 cumpriu sua missão e venceu!\n");
    } else {
        printf("\nNenhum jogador cumpriu a missão ainda.\n");
    }

    // 8. Liberação de memória
    liberarMemoria(mapa, missaoJogador1, missaoJogador2);

    return 0;
}
