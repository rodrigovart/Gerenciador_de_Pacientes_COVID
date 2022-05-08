#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Chamada de funções internas
void primeiroAcesso();
void login();
void menu();
int cadastro();
int listar();

struct VarG {
    int Op;
    char Cd;
}; //Variáveis do tipo GlobalPaciente

struct Cadastro {
    char Nome[25];
    char Email[35];
    char Cpf[15];
    char Telefone[15];
}; // Variáveis do tipo Cadastro.Paciente

struct Login {
    char Usuario[25];
    int Senha[6];
}; // Variáveis do tipo Login.Usuario

FILE * DBLOGIN; //Ponteiro do Banco de dados do login
FILE * DB; //Ponteiro do Banco de dados

// Definição das Structs
struct VarG GlobalLogin;
struct VarG GlobalPaciente;
struct Cadastro Paciente;
struct Login LoginUsuario;

int main() {
    system("clear"); //Limpa a tela (Linux)
    printf("=========================\n");
    printf(" LOGIN NO SISTEMA\n");
    printf("=========================\n\n");

    printf("[1] - Primeiro Acesso\n");
    printf("[2] - Login\n");

    printf("[3] - Encerrar\n");
    printf("===============\n");
    printf("Opção: ");
    scanf("%d", & GlobalLogin.Op);
    getchar(); //Limpa o Buffer

    switch (GlobalLogin.Op) {
        case 1:
            primeiroAcesso(); //Funcão Cadastro é iniciada
            break;

        case 2:
            login();
            break;
    }
} //Fim da Função Principal

void primeiroAcesso() {
    system("clear");

    DBLOGIN = fopen("dadoslogin.txt", "r"); //Abertura do DB para a inserção de dados

    if (DBLOGIN == NULL) { //Verificação do Banco de Dados
        printf("\nErro no Banco de Dados...\n");
    } else {
        printf("\nDigite o seu Usuario desejado: ");
        fgets(LoginUsuario.Usuario, 25, stdin); //Recebe a String Nome

        printf("\nDigite a sua Senha desejada: ");
        fgets(LoginUsuario.Senha, 20, stdin); //Recebe a String Email
    }

    fprintf(DBLOGIN, "Usuario: %sSenha: %s", LoginUsuario.Usuario, LoginUsuario.Senha);

    fclose(DBLOGIN); //Fecha o Banco de dados

    login();
}

void login() {
    system("clear"); //Limpa a tela (Linux)

    DBLOGIN = fopen("dadoslogin.txt", "r");

    if (DBLOGIN == NULL) { //Verificação do Banco de dados
        printf("\nErro no Banco de Dados...\n");
    } else {
        printf("Usuario: ");
        fgets(LoginUsuario.Usuario, 25, stdin); //Recebe a String Nome

        printf("\nSenha: ");
        fgets(LoginUsuario.Senha, 6, stdin); //Recebe a String Email

        char listagem[250]; //String geral para os dados
        system("clear"); //Limpa a tela (Linux)

        int count = 0;

        while (fgets(listagem, 250, DBLOGIN) != NULL) {
            if (strstr(listagem, LoginUsuario.Usuario) != NULL) {
                // printf("found substring at address %s\n", LoginUsuario.Usuario);
                // printf(listagem);
            } else {
                // printf("no substring found!\n");
            }

            if (strstr(listagem, LoginUsuario.Senha) != NULL) {
                // printf("found substring at address %s\n", LoginUsuario.Senha);
                // printf(listagem);
            } else {
                // printf("no substring found!\n");
            }

            printf(count);
            count++;
        } //Considera todos os dados como uma String e exibe na tela

        // printf("usuario=%s and senha=%d\n", listagem);
        // printf("usuario=%s and u=%s\n", LoginUsuario.Usuario, listagem);
        // printf("senha=%s and s=%s\n", LoginUsuario.Senha, listagem);

        fclose(DB);
    }
}

void menu() {
    system("clear"); //Limpa a tela (Linux)

    printf("=========================\n");
    printf(" GERENCIADOR DE PACIENTES\n");
    printf("=========================\n\n");

    printf("[1] - Cadastrar\n");
    printf("[2] - Alterar\n");
    printf("[3] - Listar\n");
    printf("[4] - Remover\n\n");

    printf("[5] - Encerrar\n");
    printf("===============\n");
    printf("Opção: ");
    scanf("%d", & GlobalPaciente.Op);
    getchar(); //Limpa o Buffer

    switch (GlobalPaciente.Op) {
        case 1:
            cadastro(); //Funcão Cadastro é iniciada
            break;
        case 2:
            system("clear");

            printf("=========\n");
            printf(" ALTERAR\n");
            printf("=========\n\n");

            printf("Para alterar os dados de um cadastro, acesse o\narquivo ");
            printf("dados.txt e modifique manualmente através\nde um editor ");
            printf("de texto.\n\n");

            printf("\nVoltar ao Menu Principal? [s/n]: ");
            scanf("%c", & GlobalPaciente.Cd);

            if (GlobalPaciente.Cd == 's') {
                main();
            } else if (GlobalPaciente.Cd != 's' && GlobalPaciente.Cd != 'n') {
                printf("Valor inválido.\nVoltando ao Menu Principal...\n");
                main();
            }
            break;
        case 3:
            listar(); //Função Listar é iniciada
            break;
        case 4:
            system("clear");

            printf("=========\n");
            printf(" REMOVER\n");
            printf("=========\n\n");

            printf("Para remover os dados de um paciente, acesse\no arquivo ");
            printf("dados.txt e realize o processo \nmanualmente, salvando o ");
            printf("arquivo logo em seguida.\n\n");

            printf("\nVoltar ao Menu Principal? [s/n]: ");
            scanf("%c", & GlobalPaciente.Cd);

            if (GlobalPaciente.Cd == 's') {
                main();
            } else if (GlobalPaciente.Cd != 's' && GlobalPaciente.Cd != 'n') {
                printf("Valor inválido.\nVoltando ao Menu Principal...\n");
                main();
            }
            break;
        case 5:
            system("clear");
            printf("######################\n");
            printf("# Fim da Execução... #\n");
            printf("######################\n\n");
            break;
        default:
            printf("Valor inválido! Tente novamente...\n");
            main();
            break;
    }
}

int cadastro() {
    system("clear");

    DB = fopen("dados.txt", "a"); //Abertura do DB para a inserção de dados

    if (DB == NULL) { //Verificação do Banco de Dados
        printf("\nErro no Banco de Dados...\n");
        return 1;

    } else {
        printf("==========\n");
        printf(" CADASTRO\n");
        printf("==========\n");

        printf("\nNome: ");
        fgets(Paciente.Nome, 25, stdin); //Recebe a String Nome

        printf("\nE-mail: ");
        fgets(Paciente.Email, 35, stdin); //Recebe a String Email

        printf("\nDigite seu CPF: ");
        fgets(Paciente.Cpf, 15, stdin); //Recebe a String Cpf

        printf("\nDigite seu Telefone: ");
        fgets(Paciente.Telefone, 15, stdin); //Recebe a String Telefone

        system("clear");

        printf("\n=============================\n");
        printf("Finalizar cadastro? [s/n] : ");
        scanf("%c", & GlobalPaciente.Cd); //Conclusão do cadastro

        if (GlobalPaciente.Cd == 's') {
            fprintf(DB, "Nome: %sE-mail: %sCPF: %s", Paciente.Nome, Paciente.Email, Paciente.Cpf, Paciente.Telefone);
            fprintf(DB, "----------------------\n"); //Salva os dados

            fclose(DB); //Fecha o Banco de dados

            system("clear");

            printf("######################\n");
            printf("# Cadastro Concluído #\n");
            printf("######################\n");
            main();
        } else if (GlobalPaciente.Cd == 'n') {
            system("clear");
            printf("Cadastro Cancelado.\nVoltando ao Menu Principal...\n");
            fclose(DB); //Fecha DB
            getchar(); //Corrige bug quando GlobalPaciente.Cd != 's' && 'n'        
            main();
        } else {
            printf("Valor inválido. Tente novamente...\n");
            fclose(DB); //Fecha DB
            cadastro();
        }

    }

    return 0;
} //Fim da função Cadastro

int listar() {
    system("clear");
    DB = fopen("dados.txt", "r"); //Abertura do DB para leitura de dados

    if (DB == NULL) { //Verificação do Banco de dados
        printf("\nErro no Banco de Dados...\n");
        return 1;
    } else {
        printf("======================\n");
        printf(" LISTAGEM DE PACIENTES\n");
        printf("======================\n\n");

        char listagem[250]; //String geral para os dados

        while (fgets(listagem, 250, DB) != NULL) {
            printf("%s", listagem);
        } //Considera todos os dados como uma String e exibe na tela

        fclose(DB);

        printf("\nVoltar ao Menu Principal? [s/n]: ");
        scanf("%c", & GlobalPaciente.Cd);

        if (GlobalPaciente.Cd == 's') {
            main();
        } else if (GlobalPaciente.Cd != 's' && GlobalPaciente.Cd != 'n') {
            printf("Valor inválido.\nVoltando ao Menu Principal...\n");
            main();
        }
    }

    return 0;

} //Fim da função Listar