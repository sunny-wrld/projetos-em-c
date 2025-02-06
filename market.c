#include <stdio.h>
#include <string.h>

#define MAXPRODUCTS 100

typedef struct {
    char user[20];
    char senha[20];
} Login;

typedef struct {
    char name[20];
    int quant;
    float price;
    int disponivel;
} product;

product Estoque[MAXPRODUCTS] = {
    {"Excalibur",    1,   1005.99f, 1},
    {"Sorting Hat",  8,   1000.99f, 1},
    {"UnoEscada",   15,      4.20f, 1}
};

int totalProducts = 3;

void cadastrarProduto() {
    if (totalProducts >= MAXPRODUCTS) {
        printf("Estoque cheio! Nao e possivel cadastrar mais produtos.\n");
        return;
    }

    printf("Nome do produto: ");
    scanf(" %s", &Estoque[totalProducts].name);
    fflush(stdin);

    printf("Quantidade: ");
    scanf("%d", &Estoque[totalProducts].quant);

    printf("Preco: ");
    scanf("%f", &Estoque[totalProducts].price);

    Estoque[totalProducts].disponivel = 1;
    totalProducts++;

    printf("\nProduto cadastrado com sucesso!\n");
}

void exibirProdutos() {
    if (totalProducts == 0) {
        printf("Nao ha produtos no estoque!\n");
        return;
    }

    for (int i = 0; i < totalProducts; i++) {
        if (Estoque[i].disponivel == 1) {
            printf("Produto %d: %s | Quantidade: %d | Preco: R$%.2f\n",
                   i + 1, Estoque[i].name, Estoque[i].quant, Estoque[i].price);
        } else {
            printf("Produto %d: %s | Indisponivel\n", i + 1, Estoque[i].name);
        }
    }
}

void removerProduto() {
    if (totalProducts == 0) {
        printf("Nao ha produtos para remover!\n");
        return;
    }

    int indice;

    printf("Digite o numero do produto para remover (1 a %d): ", totalProducts);
    scanf("%d", &indice);

    if (indice < 1 || indice > totalProducts) {
        printf("\nOpcao invalida!\n");
        return;
    }

    int pos = indice - 1;
    Estoque[pos].disponivel = 0;

    printf("Produto '%s' agora esta indisponivel.\n", Estoque[pos].name);
}

void funcaoAdmin() {
    int valueadmin;

    do {
        printf("Escolha uma opcao:\n ");
        printf("1 - Cadastrar novo produto\n");
        printf("2 - Exibir todos os produtos\n");
        printf("3 - Remover um produto do sistema\n");
        printf("4 - Sair da conta de administrador\n");


        scanf("%d", &valueadmin);

        switch (valueadmin) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                exibirProdutos();
                break;
            case 3:
                removerProduto();
                break;
            case 4:
                printf("Saindo da conta de administrador.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (valueadmin != 4);
}

void admin() {
    char useradm[20];
    char passadm[20];

    Login adm = {"luka", "fox"};

    printf("Digite o usuario: ");
    scanf("%s", useradm);

    printf("Digite a senha: ");
    scanf("%s", passadm);

    if (strcmp(useradm, adm.user) == 0 && strcmp(passadm, adm.senha) == 0) {
        printf("Login bem-sucedido! Bem-vindo, %s.\n", adm.user);
        funcaoAdmin();
    } else {
        printf("Erro: Usuario ou senha incorretos!\n");
    }
}

void user() {
    printf("Usuario logado com sucesso!\n");
}

void newUser() {
    printf("Novo usuario cadastrado com sucesso!\n");
}

int main() {
    int value;

    do {
        printf("Escolha uma opcao:\n ");
        printf("1 - Administrador\n");
        printf("2 - Usuario cadastrado\n");
        printf("3 - Novo usuario\n");
        printf("4 - Sair\n");

        scanf("%d", &value);

        switch (value) {
            case 1:
                admin();
                break;
            case 2:
                user();
                break;
            case 3:
                newUser();
                break;
            case 4:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (value != 4);

    return 0;
}
