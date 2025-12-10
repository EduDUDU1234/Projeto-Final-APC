#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_QUESTOES 100
#define MAX_TAMANHO_QUESTAO 500
#define MAX_TAMANHO_RESPOSTA 10

typedef struct {
    int id;
    char questao[MAX_TAMANHO_QUESTAO];
    char gabarito[MAX_TAMANHO_RESPOSTA];  
} Questao;

typedef struct {
    int total_acertos;
    int total_erros;
} Estatisticas;

int num_questoes = 0;
Questao banco[MAX_QUESTOES];
Estatisticas stats = {0, 0};

void exibir_capa() {
    printf("\n");
    printf("====================================================================\n");
    printf("                                                                    \n");
    printf("               [OK] BANCO DE QUESTOES DE APC [OK]                  \n");
    printf("                                                                    \n");
   printf("           Teste seus conhecimentos de Algoritmos e                \n");
 printf("              Programacao em C de forma pratica                    \n");
printf("                                                                    \n");
    printf("====================================================================\n");
    printf("\n");
}

void exibir_menu() {
printf("\n");
  printf("===================================================================\n");
    printf("                      MENU PRINCIPAL                              \n");
    printf("===================================================================\n");
    printf("                                                                   \n");
    printf("  1. Inserir questao                                              \n");
    printf("  2. Remover questao                                              \n");
printf("  3. Realizar questoes                                            \n");
    printf("  4. Estatisticas                                                 \n");
    printf("  5. Limpar estatisticas                                          \n");
 printf("  0. Sair                                                         \n");
printf("                                                                   \n");
 printf("===================================================================\n");
    printf("\nEscolha uma opcao (0-5): ");
}

void inserir_questao() {
    if (num_questoes >= MAX_QUESTOES) {
        printf("\n[ERRO] Limite maximo de questoes (%d) atingido!\n", MAX_QUESTOES);
        return;
    }

    char resposta[MAX_TAMANHO_RESPOSTA];
    
    printf("\n-------------------------------------------------------------------\n");
    printf("                    INSERIR NOVA QUESTAO\n");
    printf("-------------------------------------------------------------------\n\n");

    printf("Digite a questao (maximo %d caracteres):\n", MAX_TAMANHO_QUESTAO - 1);
    fgets(banco[num_questoes].questao, MAX_TAMANHO_QUESTAO, stdin);
    
   
    size_t len = strlen(banco[num_questoes].questao);
    if (len > 0 && banco[num_questoes].questao[len - 1] == '\n') {
        banco[num_questoes].questao[len - 1] = '\0';
    }

    if (strlen(banco[num_questoes].questao) == 0) {
        printf("\n[ERRO] Questao nao pode estar vazia!\n");
        return;
    }

   
    printf("\nQual e a resposta correta?\n");
    printf("Digite (C) para Certo ou (E) para Errado: ");
    fgets(resposta, MAX_TAMANHO_RESPOSTA, stdin);
    
    resposta[strcspn(resposta, "\n")] = '\0';  
    
    char resposta_upper = toupper(resposta[0]);
    
    if (resposta_upper != 'C' && resposta_upper != 'E') {
        printf("\n[ERRO] Resposta invalida! Digite apenas C ou E.\n");
        return;
    }

    banco[num_questoes].gabarito[0] = resposta_upper;
    banco[num_questoes].gabarito[1] = '\0';
    banco[num_questoes].id = num_questoes + 1;

    num_questoes++;
    printf("\n[OK] Questao #%d inserida com sucesso!\n", num_questoes);
}

void remover_questao() {
    if (num_questoes == 0) {
        printf("\n[ERRO] Nao ha questoes para remover!\n");
        return;
    }

    printf("\n-------------------------------------------------------------------\n");
    printf("                    REMOVER QUESTAO\n");
    printf("-------------------------------------------------------------------\n\n");

    printf("Questoes disponiveis:\n");
    for (int i = 0; i < num_questoes; i++) {
        printf("\n[%d] %s\n", i + 1, banco[i].questao);
    }

    printf("\nDigite o numero da questao a remover (1-%d): ", num_questoes);
    int numero;
    
    if (scanf("%d", &numero) != 1) {
        printf("\n[ERRO] Entrada invalida!\n");
        while (getchar() != '\n');  
        return;
    }
    while (getchar() != '\n'); 

    if (numero < 1 || numero > num_questoes) {
        printf("\n[ERRO] Numero de questao invalido!\n");
        return;
    }

    numero--;  

    
    for (int i = numero; i < num_questoes - 1; i++) {
        banco[i] = banco[i + 1];
    }

    num_questoes--;
    printf("\n[OK] Questao removida com sucesso!\n");
}

void realizar_questoes() {
    if (num_questoes == 0) {
        printf("\n[ERRO] Nao ha questoes disponiveis! Insira questoes primeiro.\n");
        return;
    }

    printf("\n-------------------------------------------------------------------\n");
    printf("                   REALIZAR QUESTOES\n");
    printf("-------------------------------------------------------------------\n\n");

    printf("Total de questoes: %d\n\n", num_questoes);

    int acertos_sessao = 0;
    int erros_sessao = 0;

    for (int i = 0; i < num_questoes; i++) {
        printf("\n+-----------------------------------------------------------+\n");
        printf("| QUESTAO %d/%d\n", i + 1, num_questoes);
        printf("+-----------------------------------------------------------+\n\n");
        printf("%s\n\n", banco[i].questao);

        char resposta[MAX_TAMANHO_RESPOSTA];
        printf("Digite sua resposta (C para Certo / E para Errado): ");
        fgets(resposta, MAX_TAMANHO_RESPOSTA, stdin);
        
        char resposta_upper = toupper(resposta[0]);

        if (resposta_upper != 'C' && resposta_upper != 'E') {
            printf("[AVISO] Resposta invalida! Pulando questao...\n");
            continue;
        }

        
        if (resposta_upper == banco[i].gabarito[0]) {
            printf("\n[OK] Questao CERTA!\n");
            acertos_sessao++;
            stats.total_acertos++;
        } else {
            printf("\n[ERRO] Questao ERRADA!\n");
            printf("   Resposta correta: %s\n", 
                   banco[i].gabarito[0] == 'C' ? "Certo" : "Errado");
            erros_sessao++;
            stats.total_erros++;
        }

        if (i < num_questoes - 1) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    }

    printf("\n\n===================================================================\n");
    printf("                   FIM DO QUESTIONARIO                        \n");
    printf("===================================================================\n");
    printf("  Acertos nesta sessao: %d/%d                                      \n", acertos_sessao, num_questoes);
    printf("  Erros nesta sessao: %d/%d                                        \n", erros_sessao, num_questoes);
    
    float percentual = (num_questoes > 0) ? ((float)acertos_sessao / num_questoes) * 100 : 0;
    printf("  Percentual nesta sessao: %.2f%%                                  \n", percentual);
    printf("===================================================================\n");
}

void exibir_estatisticas() {
    printf("\n-------------------------------------------------------------------\n");
    printf("                    ESTATISTICAS GERAIS\n");
    printf("-------------------------------------------------------------------\n\n");

    int total = stats.total_acertos + stats.total_erros;

    if (total == 0) {
        printf("Nenhuma resposta registrada ainda.\n");
        return;
    }

    float percentual_acertos = ((float)stats.total_acertos / total) * 100;

    printf("===================================================================\n");
    printf("  Total de Acertos: %d                                             \n", stats.total_acertos);
    printf("  Total de Erros: %d                                               \n", stats.total_erros);
    printf("  Total de Respostas: %d                                           \n", total);
    printf("                                                                   \n");
    printf("  Percentual de Acertos: %.2f%%                                    \n", percentual_acertos);
    printf("===================================================================\n");
}

void limpar_estatisticas() {
    printf("\n-------------------------------------------------------------------\n");
    printf("               CONFIRMAR LIMPEZA DE ESTATISTICAS\n");
    printf("-------------------------------------------------------------------\n\n");

    printf("Tem certeza que deseja limpar todas as estatisticas? (S/N): ");
    char confirmacao;
    scanf("%c", &confirmacao);
    while (getchar() != '\n');  

    if (toupper(confirmacao) == 'S') {
        stats.total_acertos = 0;
        stats.total_erros = 0;
        printf("\n[OK] Estatisticas limpas com sucesso!\n");
    } else {
        printf("\n[AVISO] Operacao cancelada.\n");
    }
}

int main() {
    exibir_capa();

    int opcao;
    
    while (1) {
        exibir_menu();
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida! Digite um numero.\n");
            while (getchar() != '\n');  
            continue;
        }
        while (getchar() != '\n');  

        switch (opcao) {
            case 1:
                inserir_questao();
                break;
            case 2:
                remover_questao();
                break;
            case 3:
                realizar_questoes();
                break;
            case 4:
                exibir_estatisticas();
                break;
            case 5:
                limpar_estatisticas();
                break;
            case 0:
                printf("\n[OK] Ate logo! Obrigado por usar o Banco de Questoes de APC.\n\n");
                return 0;
            default:
                printf("\n[ERRO] Opcao invalida! Digite um numero de 0 a 5.\n");
        }
    }

    return 0;
}
