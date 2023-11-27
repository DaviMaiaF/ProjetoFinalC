#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Gasto {
    char descricao[100];
    float valor;
    char data[11];
};

void inserirGasto(struct Gasto *gastos, int *numGastos) {
    if (*numGastos >= 100) {
        printf("Limite de gastos atingido.\n");
        return;
    }

    printf("Digite a descrição do gasto: ");
    scanf("%s", gastos[*numGastos].descricao);

    printf("Digite o valor do gasto: ");
    scanf("%f", &gastos[*numGastos].valor);

    printf("Digite a data do gasto (dd/mm/yyyy): ");
    scanf("%s", gastos[*numGastos].data);

    (*numGastos)++;

    printf("Gasto adicionado com sucesso!\n");
}

void exibirGastos(struct Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("Nenhum gasto cadastrado.\n");
        return;
    }

    printf("Lista de gastos:\n");
    for (int i = 0; i < numGastos; i++) {
        printf("[%d] Descrição: %s\n", i, gastos[i].descricao);
        printf("    Valor: %.2f\n", gastos[i].valor);
        printf("    Data: %s\n", gastos[i].data);
        printf("\n");
    }
}

void buscarGasto(struct Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("Nenhum gasto cadastrado.\n");
        return;
    }

    int indice;
    printf("Digite o índice do gasto: ");
    scanf("%d", &indice);

    if (indice < 0 || indice >= numGastos) {
        printf("Índice inválido.\n");
        return;
    }

    getchar();
  
    printf("Gasto encontrado:\n");
    printf("Descrição: %s\n", gastos[indice].descricao);
    printf("Valor: %.2f\n", gastos[indice].valor);
    printf("Data: %s\n", gastos[indice].data);

    return;
}

void editarGasto(struct Gasto *gastos, int numGastos) {
  int indice;
  
  if (numGastos == 0) {
    printf("Nenhum gasto cadastrado.\n");
    return;
  }
  
  printf("Digite o índice do gasto a ser editado: ");
  scanf("%d", &indice);

  if (indice < 0 || indice >= numGastos) {
    printf("Índice inválido.\n");
    return;
  }

  getchar();

  printf("Insira a nova descrição: ");
  scanf("%s", gastos[indice].descricao);

  printf("Insira o novo valor: ");
  scanf("%f", &gastos[indice].valor);

  printf("Insira a nova data (dd/mm/yyyy): ");
  scanf("%s", gastos[indice].data);

  printf("Gasto editado com sucesso!\n");
}


int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Gasto gastos[100];
    int numGastos = 0;
    int escolha;

    printf("Bem vindo ao seu Registro de Gastos\n");
    do {
        printf("\nNo que posso ajudar?\n");
        printf("1. Inserir novo gasto\n");
        printf("2. Exibir gastos\n");
        printf("3. Buscar nome do gasto\n");
        printf("4. Editar gasto\n");

        printf("0. Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                inserirGasto(gastos, &numGastos);
                break;
            case 2:
                exibirGastos(gastos, numGastos);
                break;
            case 3:
                buscarGasto(gastos, numGastos);
                break;
            case 4:
                editarGasto(gastos, numGastos);
                break;
            case 0:
                printf("Saindo do programa. Até mais!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}
