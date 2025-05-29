#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS  100
#define MAX_USERS     100
#define MAX_NAME      50

#define MAX_CART      20
#define MAX_HISTORY   20
#define MAX_ITEMS     20

// Estruturas
typedef struct {
    char productName[MAX_NAME];
    int  quantity;
    float price;
} ItemCarrinho;

typedef struct {
    ItemCarrinho items[MAX_ITEMS];
    int  itemCount;
    float totalValue;
} Compra;

typedef struct {
    char username[MAX_NAME];
    char password[MAX_NAME];
    ItemCarrinho cart[MAX_CART];
    int  cartCount;
    Compra history[MAX_HISTORY];
    int  historyCount;
} User;

typedef struct {
    char name[MAX_NAME];
    float price;
    int  quantity;
    int  disponivel;
    int  buyers[MAX_USERS];
} Product;

// Variáveis globais
Product products[MAX_PRODUCTS];
int     totalProducts = 0;

User    users[MAX_USERS];
int     totalUsers = 0;

char    adminUser[] = "luka";
char    adminPass[] = "fox";

// Declarações das funções
void menuPrincipal();
void adminMenu();
void userMenu(int userIndex);

void adminCadastrarProduto();
void adminExibirProdutos();
void adminRemoverProduto();

void userBuscarProduto(int userIndex);
void userFinalizarCompra(int userIndex);
void userExibirHistorico(int userIndex);

int  loginAdmin();
int  loginUser();
void cadastrarNovoUser();
int  findProductByName(char nome[]);
void removeItemFromAllCarts(char nomeProd[]);
void removeItemFromCart(int userIndex, char nomeProd[]);

int main() {
    strcpy(products[0].name, "Excalibur");
    products[0].price     = 1000.0f;
    products[0].quantity  = 2;
    products[0].disponivel= 1;
    totalProducts++;

    strcpy(products[1].name, "SortingHat");
    products[1].price     = 500.0f;
    products[1].quantity  = 5;
    products[1].disponivel= 1;
    totalProducts++;

    strcpy(products[2].name, "UnoComEscada");
    products[2].price     = 2500.0f;
    products[2].quantity  = 5;
    products[2].disponivel= 1;
    totalProducts++;

    strcpy(users[0].username, "mj");
    strcpy(users[0].password, "fox");
    users[0].cartCount = 0;
    users[0].historyCount = 0;
    totalUsers++;

    strcpy(users[1].username, "curry");
    strcpy(users[1].password, "fox");
    users[1].cartCount = 0;
    users[1].historyCount = 0;
    totalUsers++;

    strcpy(users[2].username, "vasco");
    strcpy(users[2].password, "2");
    users[2].cartCount = 0;
    users[2].historyCount = 0;
    totalUsers++;

    menuPrincipal();
    return 0;
}

// Menu Principal
void menuPrincipal() {
    int opcao;
    do {
        printf("\n Fate Store \n");
        printf("1 - Entrar como Administrador\n");
        printf("2 - Cadastrar novo Cliente\n");
        printf("3 - Entrar como Cliente\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (loginAdmin()) {
                    adminMenu();
                }
                break;
            case 2:
                cadastrarNovoUser();
                break;
            case 3: {
                int indiceUser = loginUser();
                if (indiceUser != -1) {
                    userMenu(indiceUser);
                }
            } break;
            case 4:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);
}

// Login do Administrador
int loginAdmin() {
    char user[MAX_NAME], pass[MAX_NAME];
    printf("\n Login Admin \n");
    printf("Usuario: ");
    scanf("%49s", user);
    printf("Senha: ");
    scanf("%49s", pass);

    if (strcmp(user, adminUser) == 0 && strcmp(pass, adminPass) == 0) {
        printf("Login de administrador bem-sucedido!\n");
        return 1;
    } else {
        printf("Usuario ou senha invalidos.\n");
        return 0;
    }
}

// Menu do Administrador
void adminMenu() {
    int opc;
    do {
        printf("\n Menu Administrador \n");
        printf("1 - Cadastrar novo produto\n");
        printf("2 - Exibir todos os produtos\n");
        printf("3 - Remover um produto\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                adminCadastrarProduto();
                break;
            case 2:
                adminExibirProdutos();
                break;
            case 3:
                adminRemoverProduto();
                break;
            case 4:
                printf("Saindo do menu de administrador...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opc != 4);
}

// So o admin pode Cadastrar novo produto
void adminCadastrarProduto() {
    if (totalProducts >= MAX_PRODUCTS) {
        printf("Estoque cheio! Nao e possivel cadastrar mais produtos.\n");
        return;
    }

    Product novo;
    novo.disponivel = 1;
    for (int i = 0; i < MAX_USERS; i++) {
        novo.buyers[i] = 0;
    }

    printf("\n Cadastrar Novo Produto \n");
    printf("Nome do produto: ");
    scanf("%49s", novo.name);
    printf("Preco: ");
    scanf("%f", &novo.price);
    printf("Quantidade em estoque: ");
    scanf("%d", &novo.quantity);

    products[totalProducts] = novo;
    totalProducts++;

    printf("Produto cadastrado com sucesso!\n");
}

// Exibir produtos so o admin
void adminExibirProdutos() {
    printf("\n Lista de Produtos \n");
    if (totalProducts == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalProducts; i++) {
        Product p = products[i];
        if (p.disponivel == 1) {
            int countBuyers = 0;
            for (int u = 0; u < MAX_USERS; u++) {
                if (p.buyers[u] == 1) {
                    countBuyers++;
                }
            }
            printf("Produto %d:\n", i + 1);
            printf("  Nome: %s\n", p.name);
            printf("  Preco: %.2f\n", p.price);
            printf("  Em estoque: %d\n", p.quantity);
            printf("  Usuarios que ja compraram: %d\n", countBuyers);
        } else {
            printf("Produto %d: [REMOVIDO] (%s)\n", i + 1, p.name);
        }
    }
}

// So o admin pode remover produto
void adminRemoverProduto() {
    if (totalProducts == 0) {
        printf("Nao ha produtos para remover.\n");
        return;
    }

    char nome[MAX_NAME];
    printf("Digite o nome do produto a remover: ");
    scanf("%49s", nome);

    int indice = findProductByName(nome);
    if (indice == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    products[indice].disponivel = 0;
    removeItemFromAllCarts(nome);

    printf("Produto '%s' removido (indisponivel).\n", nome);
}

// Login de Usuário cliente
int loginUser() {
    char user[MAX_NAME], pass[MAX_NAME];
    printf("\n Login Cliente \n");
    printf("Usuario: ");
    scanf("%49s", user);
    printf("Senha: ");
    scanf("%49s", pass);

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].username, user) == 0 &&
            strcmp(users[i].password, pass) == 0) {
            printf("Login de cliente bem-sucedido!\n");
            return i;
        }
    }
    printf("Usuario ou senha invalidos.\n");
    return -1;
}

// Cadastrar novo cliente
void cadastrarNovoUser() {
    if (totalUsers >= MAX_USERS) {
        printf("Limite de usuarios atingido.\n");
        return;
    }

    User novo;
    novo.cartCount    = 0;
    novo.historyCount = 0;

    printf("\n Cadastro de Novo Cliente \n");
    printf("Username: ");
    scanf("%49s", novo.username);
    printf("Senha: ");
    scanf("%49s", novo.password);

    users[totalUsers] = novo;
    totalUsers++;

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].username,  novo.username) == 0 &&
            strcmp(users[i].password, novo.password) == 0) {
            printf("Login ja existente\n");
        }
            break;
    }
}

// Menu do Cliente
void userMenu(int userIndex) {
    int opc;

    adminExibirProdutos();

    do {
        printf("\n Menu Cliente (%s) \n", users[userIndex].username);
        printf("1 - Buscar Porduto\n");
        printf("2 - Finalizar compra\n");
        printf("3 - Exibir historico de compras\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                userBuscarProduto(userIndex);
                break;
            case 2:
                userFinalizarCompra(userIndex);
                break;
            case 3:
                userExibirHistorico(userIndex);
                break;
            case 4:
                printf("Saindo da conta de cliente.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opc != 4);
}

// Buscar Produto e Adicionar/Remover do Carrinho
void userBuscarProduto(int userIndex) {
    char nome[MAX_NAME];
    printf("Digite o nome do produto a buscar: ");
    scanf("%49s", nome);

    int indice = findProductByName(nome);
    if (indice == -1 || products[indice].disponivel == 0) {
        printf("Produto nao encontrado ou indisponivel.\n");
        return;
    }

    Product p = products[indice];
    printf("Produto: %s | Preco: %.2f | Estoque: %d\n",
           p.name, p.price, p.quantity);

    printf("1 - Adicionar ao carrinho\n");
    printf("2 - Remover do carrinho\n");
    printf("3 - Voltar\n");
    printf("Escolha: ");
    int op;
    scanf("%d", &op);

    if (op == 1) {
        int qtd;
        printf("Quantidade desejada: ");
        scanf("%d", &qtd);
        if (qtd <= 0) {
            printf("Quantidade invalida.\n");
            return;
        }
        // Ver se já existe no carrinho
        for (int i = 0; i < users[userIndex].cartCount; i++) {
            if (strcmp(users[userIndex].cart[i].productName, p.name) == 0) {
                users[userIndex].cart[i].quantity += qtd;
                printf("Quantidade atualizada no carrinho.\n");
                return;
            }
        }
        // Se não estava no carrinho
        if (users[userIndex].cartCount < MAX_CART) {
            int pos = users[userIndex].cartCount;
            strcpy(users[userIndex].cart[pos].productName, p.name);
            users[userIndex].cart[pos].price    = p.price;
            users[userIndex].cart[pos].quantity = qtd;
            users[userIndex].cartCount++;
            printf("Item adicionado ao carrinho.\n");
        } else {
            printf("Carrinho cheio.\n");
        }
    }
    else if (op == 2) {
        removeItemFromCart(userIndex, p.name);
        printf("Item removido do carrinho (se estava).\n");
    }
    else {
    }
    // Voltar
}

// Finalizar Compra
void userFinalizarCompra(int userIndex) {
    if (users[userIndex].cartCount == 0) {
        printf("Carrinho vazio.\n");
        return;
    }

    // Verificar estoque
    for (int i = 0; i < users[userIndex].cartCount; i++) {
        char nomeP[MAX_NAME];
        strcpy(nomeP, users[userIndex].cart[i].productName);

        int indice = findProductByName(nomeP);
        if (indice == -1 || products[indice].disponivel == 0) {
            printf("Produto '%s' indisponivel. Compra cancelada.\n", nomeP);
            return;
        }
        if (products[indice].quantity < users[userIndex].cart[i].quantity) {
            printf("Estoque insuficiente para '%s'. Compra cancelada.\n", nomeP);
            return;
        }
    }

    // Retira do estoque e registra a compra
    Compra c;
    c.itemCount  = users[userIndex].cartCount;
    c.totalValue = 0.0f;

    for (int i = 0; i < users[userIndex].cartCount; i++) {
        char nomeP[MAX_NAME];
        strcpy(nomeP, users[userIndex].cart[i].productName);

        int indice = findProductByName(nomeP);
        products[indice].quantity -= users[userIndex].cart[i].quantity;
        products[indice].buyers[userIndex] = 1;

        strcpy(c.items[i].productName, users[userIndex].cart[i].productName);
        c.items[i].price    = users[userIndex].cart[i].price;
        c.items[i].quantity = users[userIndex].cart[i].quantity;

        c.totalValue += (users[userIndex].cart[i].price * users[userIndex].cart[i].quantity);
    }

    // Adiciona ao histórico
    if (users[userIndex].historyCount < MAX_HISTORY) {
        users[userIndex].history[users[userIndex].historyCount] = c;
        users[userIndex].historyCount++;
    } else {
        printf("Historico cheio! Compra realizada, mas nao salva.\n");
    }

    // Exibe comprovante
    printf("\n Comprovante de Compra \n");
    for (int i = 0; i < c.itemCount; i++) {
        printf("  %d x %s (R$ %.2f)\n",
        c.items[i].quantity, c.items[i].productName, c.items[i].price);
    }
    printf("Total: R$ %.2f\n", c.totalValue);

    // Esvazia o carrinho
    users[userIndex].cartCount = 0;
}

// Exibir Historico
void userExibirHistorico(int userIndex) {
    if (users[userIndex].historyCount == 0) {
        printf("Nenhuma compra realizada ainda.\n");
        return;
    }
    printf("\n Historico de %s \n", users[userIndex].username);
    for (int i = 0; i < users[userIndex].historyCount; i++) {
        Compra comp = users[userIndex].history[i];
        printf("Compra %d:\n", i + 1);
        for (int j = 0; j < comp.itemCount; j++) {
            printf("  %d x %s (R$ %.2f)\n",
                   comp.items[j].quantity,comp.items[j].productName,
                   comp.items[j].price);
        }
        printf("  Total: R$ %.2f\n", comp.totalValue);
    }
}

// Acha produto pelo nome exato; retorna índice ou -1
int findProductByName(char nome[]) {
    for (int i = 0; i < totalProducts; i++) {
        if (strcmp(products[i].name, nome) == 0) {
            return i;
        }
    }
    return 1;
}

// Remove item de todos os carrinhos
void removeItemFromAllCarts(char nomeProd[]) {
    for (int u = 0; u < totalUsers; u++) {
        removeItemFromCart(u, nomeProd);
    }
}

// Remove item do carrinho de UM usuário (se existir)
void removeItemFromCart(int userIndex, char nomeProd[]) {
    for (int i = 0; i < users[userIndex].cartCount; i++) {
        if (strcmp(users[userIndex].cart[i].productName, nomeProd) == 0) {
            for (int j = i; j < users[userIndex].cartCount - 1; j++) {
                users[userIndex].cart[j] = users[userIndex].cart[j + 1];
            }
            users[userIndex].cartCount--;
            return;
        }
    }
}