#include <stdio.h>

typedef struct {
    char estado[2];
    int cidade;
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} Cidade;

int main() {
    Cidade carta1, carta2;

    // Cadastro da primeira carta
    printf("Cadastro da primeira carta:\n");
    printf("Estado (A-H): ");
    scanf("%s", carta1.estado);
    printf("Cidade (1-4): ");
    scanf("%d", &carta1.cidade);
    printf("População: ");
    scanf("%d", &carta1.populacao);
    printf("Área (km²): ");
    scanf("%f", &carta1.area);
    printf("PIB (em milhões): ");
    scanf("%f", &carta1.pib);
    printf("Número de pontos turísticos: ");
    scanf("%d", &carta1.pontosTuristicos);

    // Cadastro da segunda carta
    printf("\nCadastro da segunda carta:\n");
    printf("Estado (A-H): ");
    scanf("%s", carta2.estado);
    printf("Cidade (1-4): ");
    scanf("%d", &carta2.cidade);
    printf("População: ");
    scanf("%d", &carta2.populacao);
    printf("Área (km²): ");
    scanf("%f", &carta2.area);
    printf("PIB (em milhões): ");
    scanf("%f", &carta2.pib);
    printf("Número de pontos turísticos: ");
    scanf("%d", &carta2.pontosTuristicos);



    
return 0;

}
