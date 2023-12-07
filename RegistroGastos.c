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

void imprimirSeparador() {
    printf("\n----------------------------------------\n");
}

void imprimirCabecalho(const char *mensagem) {
    printf("\033[1;34m");  // Configura a cor do texto 
    imprimirSeparador();
    printf("%s\n", mensagem);
    imprimirSeparador();
    printf("\033[0m");  // Restaura a cor do texto para padrão
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

void salvarGastos(Gasto *gastos, int numGastos) {
    char nomeArquivo[100];

    printf("\nDigite o nome do arquivo para salvar os gastos: ");
    limparBuffer();
    fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';

    // Adiciona a extensão ".txt" ao nome do arquivo
    strcat(nomeArquivo, ".txt");

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

    printf("\n\033[1;92mGastos salvos com sucesso no arquivo\033[0m %s!\n", nomeArquivo);

    esperarTecla();
}

void inserirGasto(Gasto *gastos, int *numGastos) {
	imprimirCabecalho("Novo gasto:");
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
        printf("\n\033[1;31mFormato de data inválido!\033[0m\n");
        esperarTecla();
        return;
    }
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100) {
        printf("\n\033[1;31mData inválida!\033[0m\n");
        esperarTecla();
        return;
    }

    sprintf(gastos[*numGastos].data, "%02d/%02d/%04d", dia, mes, ano);
    (*numGastos)++;

    printf("\n\033[1;92mGasto adicionado com sucesso!\033[0m\n");

    esperarTecla();
}

void exibirGastos(Gasto *gastos, int numGastos) {
	 imprimirCabecalho("Lista de Gastos:");
    if (numGastos == 0) {
        printf("\n\033[1;31mNenhum gasto cadastrado.\033[0m\n");
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

void buscarGasto(Gasto *gastos, int numGastos, const char *nomeBusca) {
	 imprimirCabecalho("Busca de Gasto:");
    int indice = -1;
    for (int i = 0; i < numGastos; i++) {
        if (strcmp(gastos[i].descricao, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\n\033[1;31mGasto não encontrado.\033[0m\n");
        esperarTecla();
        return;
    }

    printf("Gasto encontrado:\n");
    printf("Descrição: %s\n", gastos[indice].descricao);
    printf("Valor: %.2f\n", gastos[indice].valor);
    printf("Data: %s\n", gastos[indice].data);

    printf("\nPressione Enter para continuar...");
    getchar();
}

void editarGasto(Gasto *gastos, int numGastos) {
	imprimirCabecalho("Edição de gasto:");
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
        printf("\n\033[1;31mGasto não encontrado.\033[0m\n");
        esperarTecla();
        return;
    }

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
            printf("\n\033[1;31mOpção inválida.\033[0m\n");
            return;
    }

    printf("\n\033[1;92mGasto editado com sucesso!\033[0m\n");

    esperarTecla();
}

void removerGasto(Gasto *gastos, int *numGastos) {
	imprimirCabecalho("Remoção de gasto");
    char nomeBusca[100];
    limparBuffer();
    printf("\nDigite o nome do gasto que deseja remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

     int encontrado = 0;
    for (int i = 0; i < *numGastos - 1; i++) {
        if (strcmp(gastos[i].descricao, nomeBusca) == 0) {
            gastos[i] = gastos[*numGastos - 1];
            encontrado = 1;
            printf("\n\033[1;92mGasto removido com sucesso!\033[0m\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\n\033[1;31mGasto não encontrado.\033[0m\n");
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void somarMedia(Gasto *gastos, int numGastos) {
	imprimirCabecalho("Soma e Média de Gastos:");
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
            case 3: {
                char nomeBusca[100];
                limparBuffer();
                printf("\nDigite o nome do gasto buscado: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscarGasto(gastos, *numGastos, nomeBusca);
                break;
            }
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
                salvarGastos(gastos, *numGastos);
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
