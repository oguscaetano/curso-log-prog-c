#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Livro {
    int codigo;
    char titulo[50];
    char autor[50];
    int quantidade_total;
    int quantidade_disponivel;
};

struct Usuario {
    int codigo;
    char nome[50];
    int idade;
};

struct Emprestimo {
    int codUsuario;
    int codLivro;
};

struct Livro livros[100];
int totalLivros = 0;

struct Usuario usuarios[100];
int totalUsuarios = 0;

struct Emprestimo emprestimos[100];
int totalEmprestimos = 0;

// ======= Arquivos =======

void salvarDados() {
    FILE *f;

    // Salva livros
    f = fopen("livros.txt", "w");
    for (int i = 0; i < totalLivros; i++) {
        fprintf(f, "%d;%s;%s;%d;%d\n",
                livros[i].codigo,
                livros[i].titulo,
                livros[i].autor,
                livros[i].quantidade_total,
                livros[i].quantidade_disponivel);
    }
    fclose(f);

    // Salva usuarios
    f = fopen("usuarios.txt", "w");
    for (int i = 0; i < totalUsuarios; i++) {
        fprintf(f, "%d;%s;%d\n",
                usuarios[i].codigo,
                usuarios[i].nome,
                usuarios[i].idade);
    }
    fclose(f);

    // Salva emprestimos
    f = fopen("emprestimos.txt", "w");
    for (int i = 0; i < totalEmprestimos; i++) {
        fprintf(f, "%d;%d\n",
                emprestimos[i].codUsuario,
                emprestimos[i].codLivro);
    }
    fclose(f);
}

void carregarDados() {
    FILE *f;

    // Carrega livros
    f = fopen("livros.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%49[^;];%49[^;];%d;%d\n",
                      &livros[totalLivros].codigo,
                      livros[totalLivros].titulo,
                      livros[totalLivros].autor,
                      &livros[totalLivros].quantidade_total,
                      &livros[totalLivros].quantidade_disponivel) != EOF) {
            totalLivros++;
        }
        fclose(f);
    }

    // Carrega usuarios
    f = fopen("usuarios.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%49[^;];%d\n",
                      &usuarios[totalUsuarios].codigo,
                      usuarios[totalUsuarios].nome,
                      &usuarios[totalUsuarios].idade) != EOF) {
            totalUsuarios++;
        }
        fclose(f);
    }

    // Carrega emprestimos
    f = fopen("emprestimos.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%d\n",
                      &emprestimos[totalEmprestimos].codUsuario,
                      &emprestimos[totalEmprestimos].codLivro) != EOF) {
            totalEmprestimos++;
        }
        fclose(f);
    }
}

// ======= Funcoes do sistema =======

void cadastrarLivro() {
    struct Livro l;
    printf("Codigo do livro: ");
    scanf("%d", &l.codigo);
    getchar(); // limpa o \n do buffer

    printf("Titulo: ");
    scanf(" %[^\n]", l.titulo);

    printf("Autor: ");
    scanf(" %[^\n]", l.autor);

    printf("Quantidade total: ");
    scanf("%d", &l.quantidade_total);

    l.quantidade_disponivel = l.quantidade_total;
    livros[totalLivros++] = l;

    printf("Livro cadastrado com sucesso!\n");
    salvarDados();
}

void cadastrarUsuario() {
    struct Usuario u;
    printf("Codigo do usuario: ");
    scanf("%d", &u.codigo);
    getchar(); // limpa o \n do buffer

    printf("Nome: ");
    scanf(" %[^\n]", u.nome);

    printf("Idade: ");
    scanf("%d", &u.idade);

    usuarios[totalUsuarios++] = u;
    printf("Usuario cadastrado com sucesso!\n");
    salvarDados();
}

void listarLivros() {
    printf("\nLista de Livros:\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("%d - %s (%s) | Total: %d | Disponiveis: %d\n",
               livros[i].codigo,
               livros[i].titulo,
               livros[i].autor,
               livros[i].quantidade_total,
               livros[i].quantidade_disponivel);
    }
}

void listarUsuarios() {
    printf("\nLista de Usuarios:\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("%d - %s | Idade: %d\n",
               usuarios[i].codigo,
               usuarios[i].nome,
               usuarios[i].idade);
    }
}

void emprestarLivro() {
    int codLivro, codUsuario;
    printf("Codigo do usuario: ");
    scanf("%d", &codUsuario);
    printf("Codigo do livro: ");
    scanf("%d", &codLivro);

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].codigo == codLivro) {
            if (livros[i].quantidade_disponivel > 0) {
                livros[i].quantidade_disponivel--;

                struct Emprestimo e;
                e.codUsuario = codUsuario;
                e.codLivro = codLivro;

                emprestimos[totalEmprestimos++] = e;

                printf("Emprestimo realizado com sucesso!\n");
                salvarDados();
                return;
            } else {
                printf("Livro indisponivel.\n");
                return;
            }
        }
    }
    printf("Livro nao encontrado.\n");
}

void listarEmprestimos() {
    printf("\nEmprestimos em andamento:\n");
    for (int i = 0; i < totalEmprestimos; i++) {
        printf("Usuario %d emprestou o livro %d\n",
               emprestimos[i].codUsuario,
               emprestimos[i].codLivro);
    }
}

// ======= Menu Principal =======

void menu() {
    int opcao;
    carregarDados();

    do {
        printf("\n===== Menu Principal =====\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Cadastrar Usuario\n");
        printf("3 - Listar Livros\n");
        printf("4 - Listar Usuarios\n");
        printf("5 - Realizar Emprestimo\n");
        printf("6 - Listar Emprestimos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarLivro(); break;
            case 2: cadastrarUsuario(); break;
            case 3: listarLivros(); break;
            case 4: listarUsuarios(); break;
            case 5: emprestarLivro(); break;
            case 6: listarEmprestimos(); break;
            case 0: printf("Encerrando o programa...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
