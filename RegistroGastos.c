#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Gasto {
    char descricao[100];
    float valor;
    char data[11];
} Gasto;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void esperarTecla() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}

void somaMediaGastos(Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("\nNenhum gasto cadastrado.\n");
        esperarTecla();
        return;
    }

    float soma = 0;
    for (int i = 0; i < numGastos; i++) {
        soma += gastos[i].valor;
    }

    float media = soma / numGastos;
    printf("\nSoma total dos gastos: %.2f\n", soma);
    printf("Média dos gastos: %.2f\n", media);

    esperarTecla();
}

void salvarGastos(Gasto *gastos, int numGastos, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para salvar.\n");
        esperarTecla();
        return;
    }

    for (int i = 0; i < numGastos; i++) {
        fprintf(arquivo, "Descrição: %s\n", gastos[i].descricao);
        fprintf(arquivo, "Valor: %.2f\n", gastos[i].valor);
        fprintf(arquivo, "Data: %s\n", gastos[i].data);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    printf("\nGastos salvos com sucesso no arquivo %s!\n", nomeArquivo);

    esperarTecla();
}

void inserirGasto(Gasto *gastos, int *numGastos) {
    if (*numGastos >= 100) {
        printf("Limite de gastos atingido.\n");
        esperarTecla();
        return;
    }

    printf("\nDigite a descrição do gasto: ");
    limparBuffer();
    fgets(gastos[*numGastos].descricao, 100, stdin);
    gastos[*numGastos].descricao[strcspn(gastos[*numGastos].descricao, "\n")] = '\0';

    printf("Digite o valor do gasto: ");
    scanf("%f", &gastos[*numGastos].valor);

    int dia, mes, ano;
    printf("Digite a data do gasto (dd/mm/yyyy): ");
    if (scanf("%d/%d/%d", &dia, &mes, &ano) != 3) {
        printf("\nFormato de data inválido!\n");
        esperarTecla();
        return;
    }
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100) {
        printf("\nData inválida!\n");
        esperarTecla();
        return;
    }

    sprintf(gastos[*numGastos].data, "%02d/%02d/%04d", dia, mes, ano);
    (*numGastos)++;

    printf("\nGasto adicionado com sucesso!\n");

    esperarTecla();
}

void exibirGastos(Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("\nNenhum gasto cadastrado.\n");
        esperarTecla();
        return;
    }

    printf("\nLista de gastos:\n");
    for (int i = 0; i < numGastos; i++) {
        printf("[%d] Descrição: %s\n", i + 1, gastos[i].descricao);
        printf("    Valor: %.2f\n", gastos[i].valor);
        printf("    Data: %s\n", gastos[i].data);
        printf("\n");
    }

    esperarTecla();
}

void buscarGasto(Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("\nNenhum gasto cadastrado.\n");
        esperarTecla();
        return;
    }

    char nomeBusca[100];
    limparBuffer();
    printf("\nDigite o nome do gasto buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int indice = -1;
    for (int i = 0; i < numGastos; i++) {
        if (strcmp(gastos[i].descricao, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\nGasto não encontrado.\n");
        esperarTecla();
        return;
    }

    getchar();

    printf("Gasto encontrado:\n");
    printf("Descrição: %s\n", gastos[indice].descricao);
    printf("Valor: %.2f\n", gastos[indice].valor);
    printf("Data: %s\n", gastos[indice].data);

    esperarTecla();
}

void editarGasto(Gasto *gastos, int numGastos) {
    if (numGastos == 0) {
        printf("\nNenhum gasto cadastrado.\n");
        esperarTecla();
        return;
    }

    char nomeBusca[100];
    limparBuffer();
    printf("\nDigite o nome do gasto que deseja editar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int indice = -1;
    for (int i = 0; i < numGastos; i++) {
        if (strcmp(gastos[i].descricao, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\nGasto não encontrado.\n");
        esperarTecla();
        return;
    }

    getchar();

    printf("Escolha qual informação deseja editar:\n\n");
    printf("1. Descrição\n");
    printf("2. Valor\n");
    printf("3. Data\n");

    int escolha;
    scanf("%d", &escolha);
    limparBuffer();

    switch (escolha) {
        case 1:
            printf("\nInsira a nova descrição: ");
            fgets(gastos[indice].descricao, 100, stdin);
            gastos[indice].descricao[strcspn(gastos[indice].descricao, "\n")] = '\0';
            break;
        case 2:
            printf("\nInsira o novo valor: ");
            scanf("%f", &gastos[indice].valor);
            break;
        case 3:
            printf("\nInsira a nova data (dd/mm/yyyy): ");
            scanf("%s", gastos[indice].data);
            break;
        default:
            printf("\nOpção inválida.\n");
            return;
    }

    printf("\nGasto editado com sucesso!\n");

    esperarTecla();
}

void removerGasto(Gasto *gastos, int *numGastos) {
    if (*numGastos == 0) {
        printf("\nNenhum gasto cadastrado.\n");
        esperarTecla();
        return;
    }

    char nomeBusca[100];
    limparBuffer();
    printf("\nDigite o nome do gasto que deseja remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *numGastos; i++) {
        if (strcmp(gastos[i].descricao, nomeBusca) == 0) {
            gastos[i] = gastos[*numGastos - 1];
            (*numGastos)--;
            encontrado = 1;
            printf("\nGasto removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nGasto não encontrado.\n");
    }

    esperarTecla();
}

void somarMedia(Gasto *gastos, int numGastos) {
    somaMediaGastos(gastos, numGastos);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Gasto *gastos = (Gasto *)malloc(100 * sizeof(Gasto));
    int *numGastos = (int *)malloc(sizeof(int));
    *numGastos = 0;
    int escolha;

    printf("Bem vindo ao seu Registro de Gastos\n");
    do {
#ifdef _WIN32
        system("cls");
#endif
        printf("\nNo que posso ajudar?\n\n");
        printf("1. Inserir novo gasto\n");
        printf("2. Exibir gastos\n");
        printf("3. Buscar nome do gasto\n");
        printf("4. Editar gasto\n");
        printf("5. Remover gasto\n");
        printf("6. Somar média de gastos\n");
        printf("7. Salvar lista de gastos em um arquivo\n");

        printf("0. Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                inserirGasto(gastos, numGastos);
                break;
            case 2:
                exibirGastos(gastos, *numGastos);
                break;
            case 3:
                buscarGasto(gastos, *numGastos);
                break;
            case 4:
                editarGasto(gastos, *numGastos);
                break;
            case 5:
                removerGasto(gastos, numGastos);
                break;
            case 6:
                somarMedia(gastos, *numGastos);
                break;
            case 7:
                salvarGastos(gastos, *numGastos, "gastos.txt");
                break;
            case 0:
                printf("\nSaindo do programa. Até mais!\n");
                break;
            default:
                printf("\nOperação inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    free(gastos);
    free(numGastos);

    return 0;
}
