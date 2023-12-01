#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARROS 100
#define NOME_ARQUIVO "dados_loja_carros.txt"

struct Carro {
    int id;
    char marca[50];
    char modelo[50];
    int ano;
    float preco;
    int quantidade;
};

void boasVindas();
void menu(struct Carro carros[], int *totalCarros);
void cadastrarCarro(struct Carro carros[], int *totalCarros);
void consultarEstoque(struct Carro carros[], int totalCarros);
void excluirCarro(struct Carro carros[], int *totalCarros);
void salvarDados(struct Carro carros[], int totalCarros);
void carregarDados(struct Carro carros[], int *totalCarros);

int main() {
    struct Carro carros[MAX_CARROS];
    int totalCarros = 0;

    carregarDados(carros, &totalCarros);

    boasVindas();
    menu(carros, &totalCarros);

    return 0;
}

void boasVindas() {
    printf("Bem-vindo à Loja Automotiva Marquinhos Vrumm!\n");
}

void menu(struct Carro carros[], int *totalCarros) {
    int opcao;

    do {
        printf("\n======= MENU =======\n");
        printf("1. Cadastrar Carro\n");
        printf("2. Consultar Estoque\n");
        printf("3. Excluir Carro\n");
        printf("4. Salvar Dados\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCarro(carros, totalCarros);
                break;
            case 2:
                consultarEstoque(carros, *totalCarros);
                break;
            case 3:
                excluirCarro(carros, totalCarros);
                break;
            case 4:
                salvarDados(carros, *totalCarros);
                break;
            case 5:
                printf("Saindo do programa. Até logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);
}

void cadastrarCarro(struct Carro carros[], int *totalCarros) {
    if (*totalCarros < MAX_CARROS) {
        printf("\n===== CADASTRO DE CARRO =====\n");

        struct Carro novoCarro;

        printf("ID: ");
        scanf("%d", &novoCarro.id);

        printf("Marca: ");
        scanf(" %[^\n]s", novoCarro.marca);

        printf("Modelo: ");
        scanf(" %[^\n]s", novoCarro.modelo);

        printf("Ano: ");
        scanf("%d", &novoCarro.ano);

        printf("Preco: ");
        scanf("%f", &novoCarro.preco);

        printf("Quantidade em Estoque: ");
        scanf("%d", &novoCarro.quantidade);

        carros[*totalCarros] = novoCarro;
        (*totalCarros)++;

        printf("Carro cadastrado com sucesso!\n");
    } else {
        printf("Limite de carros atingido. Impossível cadastrar mais.\n");
    }
}

void consultarEstoque(struct Carro carros[], int totalCarros) {
    if (totalCarros > 0) {
        printf("\n===== ESTOQUE DE CARROS =====\n");
        for (int i = 0; i < totalCarros; i++) {
            printf("ID: %d, Marca: %s, Modelo: %s, Ano: %d, Preco: %.2f, Quantidade: %d\n", 
                   carros[i].id, carros[i].marca, carros[i].modelo, carros[i].ano, carros[i].preco, carros[i].quantidade);
        }
    } else {
        printf("Nenhum carro cadastrado ainda.\n");
    }
}

void excluirCarro(struct Carro carros[], int *totalCarros) {
    if (*totalCarros > 0) {
        int idExcluir;
        printf("\n===== EXCLUIR CARRO =====\n");
        printf("Digite o ID do carro a ser excluído: ");
        scanf("%d", &idExcluir);

        int indiceExcluir = -1;
        for (int i = 0; i < *totalCarros; i++) {
            if (carros[i].id == idExcluir) {
                indiceExcluir = i;
                break;
            }
        }

        if (indiceExcluir != -1) {
            for (int i = indiceExcluir; i < *totalCarros - 1; i++) {
                carros[i] = carros[i + 1];
            }

            (*totalCarros)--;
            printf("Carro excluído com sucesso!\n");
        } else {
            printf("Carro com ID %d não encontrado.\n", idExcluir);
        }
    } else {
        printf("Nenhum carro cadastrado para exclusão.\n");
    }
}

void salvarDados(struct Carro carros[], int totalCarros) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    for (int i = 0; i < totalCarros; i++) {
        fprintf(arquivo, "%d %s %s %d %.2f %d\n", 
                carros[i].id, carros[i].marca, carros[i].modelo, carros[i].ano, carros[i].preco, carros[i].quantidade);
    }

    fclose(arquivo);
    printf("Dados salvos no arquivo %s com sucesso!\n", NOME_ARQUIVO);
}

void carregarDados(struct Carro carros[], int *totalCarros) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");

    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d %s %s %d %f %d", 
                      &carros[*totalCarros].id, 
                      carros[*totalCarros].marca, 
                      carros[*totalCarros].modelo, 
                      &carros[*totalCarros].ano, 
                      &carros[*totalCarros].preco, 
                      &carros[*totalCarros].quantidade) == 6) {
            (*totalCarros)++;
            if (*totalCarros >= MAX_CARROS) {
                break;
            }
        }

        fclose(arquivo);
    }
}
