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

    printf("Digite a descri��o do gasto: ");
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
        printf("[%d] Descri��o: %s\n", i, gastos[i].descricao);
        printf("    Valor: %.2f\n", gastos[i].valor);
        printf("    Data: %s\n", gastos[i].data);
        printf("\n");
    }
}

int buscarGasto(struct Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("Nenhum gasto cadastrado.\n");
        return -1;
    }

    int indice;
    printf("Digite o �ndice do gasto: ");
    scanf("%d", &indice);

    if (indice < 0 || indice >= numGastos) {
        printf("�ndice inv�lido.\n");
        return -1;
    }

    return indice;
}

void editarGasto(struct Gasto *gastos, int numGastos) {
    int indice = buscarGasto(gastos, numGastos);

    if (indice != -1) {
        printf("Novas informa��es para o gasto:\n");
        printf("Digite a descri��o do gasto: ");
        scanf("%s", gastos[indice].descricao);

        printf("Digite o valor do gasto: ");
        scanf("%f", &gastos[indice].valor);

        printf("Digite a data do gasto (dd/mm/yyyy): ");
        scanf("%s", gastos[indice].data);

        printf("Gasto editado com sucesso!\n");
    }
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
        printf("3. Editar gasto\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                inserirGasto(gastos, &numGastos);
                break;
            case 2:
                exibirGastos(gastos, numGastos);
                break;
            case 3:
                editarGasto(gastos, numGastos);
                break;
            case 0:
                printf("Saindo do programa. At� mais!\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}

