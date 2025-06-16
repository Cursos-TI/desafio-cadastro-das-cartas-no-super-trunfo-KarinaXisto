#include <stdio.h>   // Para printf, scanf
#include <string.h>  // Para strcpy, para copiar strings de forma segura (embora não usada aqui diretamente, é boa prática para char arrays)

// Definição da estrutura para armazenar os dados da cidade
typedef struct {
    char estado[3];       // Aumentado para 3 para "SP" + '\0' (null terminator)
    char codigo[4];       // Aumentado para 4 para "A01" + '\0'
    char nomeCidade[50];  // Tamanho razoável para o nome da cidade
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional; // Novo campo para densidade
    float pibPerCapita;          // Novo campo para PIB per capita
} Cidade;

// Função para obter dados da cidade do usuário
void obterDadosCidade(Cidade* cidade, int numeroCarta) {
    printf("\n--- Cadastro da Carta %d ---\n", numeroCarta);
    printf("Estado (ex: SP): ");
    scanf("%2s", cidade->estado); // Limita a leitura a 2 caracteres para evitar overflow
    printf("Código (ex: A01): ");
    scanf("%3s", cidade->codigo); // Limita a leitura a 3 caracteres
    printf("Nome da Cidade: ");
    // Limpa o buffer antes de ler a linha (necessário após scanf %s, %d, %f)
    while (getchar() != '\n'); 
    fgets(cidade->nomeCidade, sizeof(cidade->nomeCidade), stdin);
    // Remove o '\n' que fgets pode adicionar no final
    cidade->nomeCidade[strcspn(cidade->nomeCidade, "\n")] = 0;

    printf("Populacao: ");
    scanf("%d", &cidade->populacao);
    printf("Area (km²): ");
    scanf("%f", &cidade->area);
    printf("PIB (em milhoes): ");
    scanf("%f", &cidade->pib);
    printf("Numero de pontos turisticos: ");
    scanf("%d", &cidade->pontosTuristicos);
}

// Função para calcular as métricas derivadas da cidade
void calcularMetricasCidade(Cidade* cidade) {
    // Calcular Densidade Populacional
    // Assumimos que area > 0 para evitar divisão por zero, já que não podemos usar if/else
    cidade->densidadePopulacional = (float)cidade->populacao / cidade->area;

    // Calcular PIB per Capita
    // Assumimos que populacao > 0 para evitar divisão por zero, já que não podemos usar if/else
    cidade->pibPerCapita = cidade->pib / (float)cidade->populacao;
}

// Função para exibir os detalhes da cidade
void exibirDetalhesCidade(const Cidade* cidade, int numeroCarta) {
    printf("\n--- Carta %d ---\n", numeroCarta);
    printf("Estado: %s\n", cidade->estado);
    printf("Codigo: %s\n", cidade->codigo);
    printf("Nome da Cidade: %s\n", cidade->nomeCidade);
    printf("Populacao: %d\n", cidade->populacao);
    // Formata a área com duas casas decimais
    printf("Area: %.2f km^2\n", cidade->area);
    // Formata o PIB com duas casas decimais
    printf("PIB: %.2f bilhoes de reais\n", cidade->pib);
    printf("Numero de Pontos Turisticos: %d\n", cidade->pontosTuristicos);
    // Formata a densidade populacional e PIB per capita com duas casas decimais
    printf("Densidade Populacional: %.2f hab/km^2\n", cidade->densidadePopulacional);
    printf("PIB per Capita: %.2f reais\n", cidade->pibPerCapita);
    printf("------------------------------------\n");
}

int main() {
    Cidade carta1, carta2;

    // Obter dados, calcular e exibir para a primeira carta
    obterDadosCidade(&carta1, 1);
    calcularMetricasCidade(&carta1);
    exibirDetalhesCidade(&carta1, 1);

    // Obter dados, calcular e exibir para a segunda carta
    obterDadosCidade(&carta2, 2);
    calcularMetricasCidade(&carta2);
    exibirDetalhesCidade(&carta2, 2);

    return 0;
}