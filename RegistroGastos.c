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
        system("pause");
    }
}

void buscarGasto(struct Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("Nenhum gasto cadastrado.\n");
        return;
    }

    char nomeBusca[100];
    printf("Digite o nome do gasto buscado: ");
    scanf("%s", nomeBusca);

    int indice = -1;  
    for (int i = 0; i < numGastos; i++) {
        if (strcmp(gastos[i].descricao, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Gasto não encontrado.\n");
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
    if (numGastos == 0) {
        printf("Nenhum gasto cadastrado.\n");
        return;
    }

    char nomeBusca[100];
    printf("Digite o nome do gasto que deseja editar: ");
    scanf("%s", nomeBusca);

    int indice = -1;  
    for (int i = 0; i < numGastos; i++) {
        if (strcmp(gastos[i].descricao, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Gasto não encontrado.\n");
        return;
    }

    getchar();  

    printf("Escolha qual informação deseja editar:\n");
    printf("1. Descrição\n");
    printf("2. Valor\n");
    printf("3. Data\n");

    int escolha;
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            printf("Insira a nova descrição: ");
            scanf("%s", gastos[indice].descricao);
            break;
        case 2:
            printf("Insira o novo valor: ");
            scanf("%f", &gastos[indice].valor);
            break;
        case 3:
            printf("Insira a nova data (dd/mm/yyyy): ");
            scanf("%s", gastos[indice].data);
            break;
        default:
            printf("Opção inválida.\n");
            return;
    }

    printf("Gasto editado com sucesso!\n");
}
void removerGasto(struct Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("Nenhum gasto cadastrado.\n");
        return;
    }

    char nomeBusca[100];
    printf("Digite o nome do gasto que deseja remover: ");
    scanf("%s", nomeBusca);

    int encontrado = 0;
    for (int i = 0; i < numGastos; i++) {
        if (strcmp(gastos[i].descricao, nomeBusca) == 0) {
            gastos[i] = gastos[numGastos - 1];
            (numGastos)--;
            encontrado = 1;
            printf("Gasto removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Gasto não encontrado.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Gasto gastos[100];
    int numGastos = 0;
    int escolha;

    printf("Bem vindo ao seu Registro de Gastos\n");
    do {
      #ifdef _WIN32
      system("cls");
      #endif
      printf("\nNo que posso ajudar?\n");
        printf("\nNo que posso ajudar?\n");
        printf("1. Inserir novo gasto\n");
        printf("2. Exibir gastos\n");
        printf("3. Buscar nome do gasto\n");
        printf("4. Editar gasto\n");
        printf("5. Remover gasto\n");

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
            case 5:
                removerGasto(gastos, numGastos);
                break;
            case 0:
                printf("Saindo do programa. Até mais!\n");
                break;
            default:
                printf("Operação inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}
