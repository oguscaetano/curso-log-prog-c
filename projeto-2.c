#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
};

struct Cliente {
    int codigo;
    char nome[50];
};

struct Pedido {
    int codCliente;
    int codProduto;
    int quantidade;
};

struct Produto produtos[100];
int totalProdutos = 0;

struct Cliente clientes[100];
int totalClientes = 0;

struct Pedido pedidos[100];
int totalPedidos = 0;

// === Arquivos ===

void salvarDados() {
    FILE *f;

    f = fopen("produtos.txt", "w");
    for (int i = 0; i < totalProdutos; i++) {
        fprintf(f, "%d;%s;%.2f\n",
            produtos[i].codigo,
            produtos[i].nome,
            produtos[i].preco);
    }
    fclose(f);

    f = fopen("clientes.txt", "w");
    for (int i = 0; i < totalClientes; i++) {
        fprintf(f, "%d;%s\n",
            clientes[i].codigo,
            clientes[i].nome);
    }
    fclose(f);

    f = fopen("pedidos.txt", "w");
    for (int i = 0; i < totalPedidos; i++) {
        fprintf(f, "%d;%d;%d\n",
            pedidos[i].codCliente,
            pedidos[i].codProduto,
            pedidos[i].quantidade);
    }
    fclose(f);
}

void carregarDados() {
    FILE *f;

    f = fopen("produtos.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%49[^;];%f\n",
                      &produtos[totalProdutos].codigo,
                      produtos[totalProdutos].nome,
                      &produtos[totalProdutos].preco) != EOF) {
            totalProdutos++;
        }
        fclose(f);
    }

    f = fopen("clientes.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%49[^\n]\n",
                      &clientes[totalClientes].codigo,
                      clientes[totalClientes].nome) != EOF) {
            totalClientes++;
        }
        fclose(f);
    }

    f = fopen("pedidos.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%d;%d\n",
                      &pedidos[totalPedidos].codCliente,
                      &pedidos[totalPedidos].codProduto,
                      &pedidos[totalPedidos].quantidade) != EOF) {
            totalPedidos++;
        }
        fclose(f);
    }
}

// === Funcoes ===

void cadastrarProduto() {
    struct Produto p;
    printf("Codigo do produto: ");
    scanf("%d", &p.codigo);
    getchar();
    printf("Nome do produto: ");
    scanf(" %[^\n]", p.nome);
    printf("Preco: ");
    scanf("%f", &p.preco);

    produtos[totalProdutos++] = p;
    salvarDados();
    printf("Produto cadastrado com sucesso!\n");
}

void cadastrarCliente() {
    struct Cliente c;
    printf("Codigo do cliente: ");
    scanf("%d", &c.codigo);
    getchar();
    printf("Nome do cliente: ");
    scanf(" %[^\n]", c.nome);

    clientes[totalClientes++] = c;
    salvarDados();
    printf("Cliente cadastrado com sucesso!\n");
}

void fazerPedido() {
    int codCliente, codProduto, qtd;

    printf("Codigo do cliente: ");
    scanf("%d", &codCliente);
    printf("Codigo do produto: ");
    scanf("%d", &codProduto);
    printf("Quantidade: ");
    scanf("%d", &qtd);

    struct Pedido p;
    p.codCliente = codCliente;
    p.codProduto = codProduto;
    p.quantidade = qtd;

    pedidos[totalPedidos++] = p;
    salvarDados();
    printf("Pedido registrado com sucesso!\n");
}

void listarProdutos() {
    printf("\n--- Produtos Disponiveis ---\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("%d - %s | R$ %.2f\n",
            produtos[i].codigo,
            produtos[i].nome,
            produtos[i].preco);
    }
}

void listarClientes() {
    printf("\n--- Lista de Clientes ---\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("%d - %s\n", clientes[i].codigo, clientes[i].nome);
    }
}

void listarPedidos() {
    printf("\n--- Pedidos Registrados ---\n");
    for (int i = 0; i < totalPedidos; i++) {
        printf("Cliente %d pediu %d unidades do produto %d\n",
            pedidos[i].codCliente,
            pedidos[i].quantidade,
            pedidos[i].codProduto);
    }
}

// === Menu ===

void menu() {
    int opcao;
    carregarDados();

    do {
        printf("\n===== MENU LANCHONETE =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Cadastrar cliente\n");
        printf("3 - Fazer pedido\n");
        printf("4 - Listar produtos\n");
        printf("5 - Listar clientes\n");
        printf("6 - Listar pedidos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarProduto(); break;
            case 2: cadastrarCliente(); break;
            case 3: fazerPedido(); break;
            case 4: listarProdutos(); break;
            case 5: listarClientes(); break;
            case 6: listarPedidos(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
