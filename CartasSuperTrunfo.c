#include <stdio.h>    // Para printf, scanf, fgets, getchar
#include <string.h>   // Para strcpy, strcmp, strcspn
#include <stdlib.h>   // Para exit (em caso de erro grave)

// Constantes para os índices dos atributos
#define ATTR_POPULACAO 1
#define ATTR_AREA 2
#define ATTR_PIB 3
#define ATTR_PONTOS_TURISTICOS 4
#define ATTR_DENSIDADE_POPULACIONAL 5
#define ATTR_PIB_PER_CAPITA 6

// Definição da estrutura para armazenar os dados do país (carta)
typedef struct {
    char nome[50];             // Nome do país (ex: Brasil)
    char codigo[10];           // Código da carta (ex: BR01)
    int populacao;             // Em milhões
    float area;                // Em km²
    float pib;                 // Em bilhões
    int pontosTuristicos;
    float densidadePopulacional; // Calculado
    float pibPerCapita;          // Calculado
} Pais;

// Função para inicializar uma carta com dados pré-definidos
// Para simplificar, não faremos o cadastro neste nível avançado
void inicializarCarta(Pais* pais, const char* nome, const char* codigo, int populacao, float area, float pib, int pontosTuristicos) {
    strcpy(pais->nome, nome);
    strcpy(pais->codigo, codigo);
    pais->populacao = populacao;
    pais->area = area;
    pais->pib = pib;
    pais->pontosTuristicos = pontosTuristicos;

    // Calcular Densidade Populacional e PIB per Capita
    // Em um cenário real, haveria tratamento para area == 0 ou populacao == 0
    // Mas para este desafio, assumimos valores válidos.
    if (pais->area > 0) {
        pais->densidadePopulacional = (float)pais->populacao / pais->area;
    } else {
        pais->densidadePopulacional = 0.0f; // Evita divisão por zero
    }

    if (pais->populacao > 0) {
        pais->pibPerCapita = pais->pib / (float)pais->populacao;
    } else {
        pais->pibPerCapita = 0.0f; // Evita divisão por zero
    }
}

// Função para exibir o menu de atributos e obter a escolha do usuário
int exibirMenuAtributos(int atributoJaEscolhido) {
    int escolha;
    int valido = 0; // Flag para validar a entrada

    do {
        printf("\nEscolha um atributo numerico para comparar:\n");
        if (atributoJaEscolhido != ATTR_POPULACAO) {
            printf("  %d - Populacao\n", ATTR_POPULACAO);
        }
        if (atributoJaEscolhido != ATTR_AREA) {
            printf("  %d - Area\n", ATTR_AREA);
        }
        if (atributoJaEscolhido != ATTR_PIB) {
            printf("  %d - PIB\n", ATTR_PIB);
        }
        if (atributoJaEscolhido != ATTR_PONTOS_TURISTICOS) {
            printf("  %d - Pontos Turisticos\n", ATTR_PONTOS_TURISTICOS);
        }
        if (atributoJaEscolhido != ATTR_DENSIDADE_POPULACIONAL) {
            printf("  %d - Densidade Populacional (Menor valor vence)\n", ATTR_DENSIDADE_POPULACIONAL);
        }
        if (atributoJaEscolhido != ATTR_PIB_PER_CAPITA) {
            printf("  %d - PIB per Capita\n", ATTR_PIB_PER_CAPITA);
        }
        printf("Sua escolha: ");
        
        // Limpa o buffer de entrada antes de scanf
        fflush(stdin); // Funciona em alguns compiladores/sistemas, mas não é padrao C.
                       // Alternativa portavel: while (getchar() != '\n' && getchar() != EOF);

        if (scanf("%d", &escolha) != 1) { // Verifica se a leitura foi bem-sucedida
            printf("Entrada invalida. Por favor, digite um numero.\n");
            // Limpa o buffer de entrada para evitar loop infinito em caso de entrada nao numerica
            while (getchar() != '\n' && getchar() != EOF);
            valido = 0;
            continue; // Tenta novamente
        }

        // Verifica se a escolha e valida e nao foi o atributo ja escolhido
        switch (escolha) {
            case ATTR_POPULACAO:
            case ATTR_AREA:
            case ATTR_PIB:
            case ATTR_PONTOS_TURISTICOS:
            case ATTR_DENSIDADE_POPULACIONAL:
            case ATTR_PIB_PER_CAPITA:
                if (escolha == atributoJaEscolhido) {
                    printf("Este atributo ja foi escolhido. Por favor, selecione outro.\n");
                    valido = 0;
                } else {
                    valido = 1;
                }
                break;
            default:
                printf("Opcao invalida. Por favor, escolha um numero da lista.\n");
                valido = 0;
                break;
        }
    } while (!valido);

    return escolha;
}

// Função para obter o valor de um atributo específico de uma carta
float getAtributoValor(const Pais* pais, int atributo) {
    switch (atributo) {
        case ATTR_POPULACAO:
            return (float)pais->populacao;
        case ATTR_AREA:
            return pais->area;
        case ATTR_PIB:
            return pais->pib;
        case ATTR_PONTOS_TURISTICOS:
            return (float)pais->pontosTuristicos;
        case ATTR_DENSIDADE_POPULACIONAL:
            return pais->densidadePopulacional;
        case ATTR_PIB_PER_CAPITA:
            return pais->pibPerCapita;
        default:
            return 0.0f; // Nunca deveria acontecer com a validacao de entrada
    }
}

// Função para obter o nome do atributo
const char* getAtributoNome(int atributo) {
    switch (atributo) {
        case ATTR_POPULACAO: return "Populacao";
        case ATTR_AREA: return "Area";
        case ATTR_PIB: return "PIB";
        case ATTR_PONTOS_TURISTICOS: return "Pontos Turisticos";
        case ATTR_DENSIDADE_POPULACIONAL: return "Densidade Populacional";
        case ATTR_PIB_PER_CAPITA: return "PIB per Capita";
        default: return "Desconhecido";
    }
}

int main() {
    Pais carta1, carta2;
    int escolha1, escolha2; // Para armazenar os atributos escolhidos
    float valor1_attr1, valor2_attr1;
    float valor1_attr2, valor2_attr2;
    float soma1, soma2;
    int vitorias_carta1 = 0;
    int vitorias_carta2 = 0;

    // --- Carga das cartas (pré-definidas conforme simplificação) ---
    // Carta 1
    inicializarCarta(&carta1, "Brasil", "BR01", 215, 8515767.0f, 2100.0f, 200); // Populacao em milhões, PIB em bilhões
    // Carta 2
    inicializarCarta(&carta2, "Canada", "CA01", 40, 9984670.0f, 2200.0f, 150);

    printf("--- Bem-vindo ao Super Trunfo de Paises! ---\n");

    // --- Escolha do Primeiro Atributo ---
    printf("\n--- Escolha do Primeiro Atributo ---\n");
    escolha1 = exibirMenuAtributos(0); // 0 indica que nenhum atributo foi escolhido ainda

    // --- Escolha do Segundo Atributo (dinâmico) ---
    printf("\n--- Escolha do Segundo Atributo ---\n");
    escolha2 = exibirMenuAtributos(escolha1); // Passa o primeiro atributo escolhido

    // --- Obter Valores dos Atributos ---
    valor1_attr1 = getAtributoValor(&carta1, escolha1);
    valor2_attr1 = getAtributoValor(&carta2, escolha1);
    valor1_attr2 = getAtributoValor(&carta1, escolha2);
    valor2_attr2 = getAtributoValor(&carta2, escolha2);

    // --- Comparação Individual dos Atributos ---
    printf("\n--- Resultados da Comparacao ---\n");
    printf("\nAtributo 1: %s\n", getAtributoNome(escolha1));
    printf("  %s (%s): %.2f\n", carta1.nome, carta1.codigo, valor1_attr1);
    printf("  %s (%s): %.2f\n", carta2.nome, carta2.codigo, valor2_attr1);

    // Operador ternário para determinar o vencedor do Atributo 1
    // Lógica para Densidade Populacional (menor vence)
    if (escolha1 == ATTR_DENSIDADE_POPULACIONAL) {
        printf("  Vencedor do %s: %s\n", getAtributoNome(escolha1), 
               (valor1_attr1 < valor2_attr1) ? carta1.nome : ((valor2_attr1 < valor1_attr1) ? carta2.nome : "Empate"));
        vitorias_carta1 += (valor1_attr1 < valor2_attr1);
        vitorias_carta2 += (valor2_attr1 < valor1_attr1);
    } else { // Outros atributos (maior vence)
        printf("  Vencedor do %s: %s\n", getAtributoNome(escolha1), 
               (valor1_attr1 > valor2_attr1) ? carta1.nome : ((valor2_attr1 > valor1_attr1) ? carta2.nome : "Empate"));
        vitorias_carta1 += (valor1_attr1 > valor2_attr1);
        vitorias_carta2 += (valor2_attr1 > valor1_attr1);
    }

    printf("\nAtributo 2: %s\n", getAtributoNome(escolha2));
    printf("  %s (%s): %.2f\n", carta1.nome, carta1.codigo, valor1_attr2);
    printf("  %s (%s): %.2f\n", carta2.nome, carta2.codigo, valor2_attr2);

    // Operador ternário para determinar o vencedor do Atributo 2
    if (escolha2 == ATTR_DENSIDADE_POPULACIONAL) {
        printf("  Vencedor do %s: %s\n", getAtributoNome(escolha2), 
               (valor1_attr2 < valor2_attr2) ? carta1.nome : ((valor2_attr2 < valor1_attr2) ? carta2.nome : "Empate"));
        vitorias_carta1 += (valor1_attr2 < valor2_attr2);
        vitorias_carta2 += (valor2_attr2 < valor1_attr2);
    } else {
        printf("  Vencedor do %s: %s\n", getAtributoNome(escolha2), 
               (valor1_attr2 > valor2_attr2) ? carta1.nome : ((valor2_attr2 > valor1_attr2) ? carta2.nome : "Empate"));
        vitorias_carta1 += (valor1_attr2 > valor2_attr2);
        vitorias_carta2 += (valor2_attr2 > valor1_attr2);
    }

    // --- Soma dos Atributos e Resultado Final ---
    soma1 = valor1_attr1 + valor1_attr2;
    soma2 = valor2_attr1 + valor2_attr2;

    printf("\n--- Resultado Final da Rodada ---\n");
    printf("%s (%s) Soma dos Atributos: %.2f\n", carta1.nome, carta1.codigo, soma1);
    printf("%s (%s) Soma dos Atributos: %.2f\n", carta2.nome, carta2.codigo, soma2);

    // Determina o vencedor da rodada pela soma
    if (soma1 > soma2) {
        printf("VENCEDOR DA RODADA: %s!\n", carta1.nome);
    } else if (soma2 > soma1) {
        printf("VENCEDOR DA RODADA: %s!\n", carta2.nome);
    } else {
        printf("Empate na soma dos atributos!\n");
    }
    
    printf("\n--- Placar Individual (para referencia) ---\n");
    printf("%s venceu %d atributo(s) individualmente.\n", carta1.nome, vitorias_carta1);
    printf("%s venceu %d atributo(s) individualmente.\n", carta2.nome, vitorias_carta2);
    printf("Este placar individual e apenas para demonstracao, o vencedor da rodada e pela SOMA.\n");


    return 0;
}