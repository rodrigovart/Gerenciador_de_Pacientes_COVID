#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "string_to_int.c"

#define MAX_LENGTH 100
#define NUM_STRINGS 10

//Chamada de funções internas
void primeiroAcesso();
void login();
void menu();
void comorbidade();
void grupoRisco();
int cadastro();
int listar();
int validaLogin(char * str1, char * str2);

struct VarG {
    int Op;
    char Cd;
}; //Variáveis do tipo GlobalPaciente

struct Cadastro {
    char Nome[25];
    char Email[35];
    char Cpf[15];
    char Telefone[15];
    char Nascimento[10];
    char DataDiagnostico[10];
    char Comorbidade[20];
    char Endereco[100];
    char CEP[20];
}; // Variáveis do tipo Cadastro.Paciente

struct Login {
    char Usuario[25];
    char Senha[6];
}; // Variáveis do tipo Login.Usuario

FILE * DBLOGIN; //Ponteiro do Banco de dados do login
FILE * DB; //Ponteiro do Banco de dados

// Definição das Structs
struct VarG GlobalLogin;
struct VarG GlobalPaciente;
struct Cadastro Paciente;
struct Login LoginUsuario;

typedef enum {
    E_GRUPO_RISCO = 65,
    N_E_GRUPO_RISCO
} grupo_risco;

int main() {

    //Limpa a tela (Windows)
    system("clear");
    printf("=========================\n");
    printf(" LOGIN NO SISTEMA 🔐\n");
    printf("=========================\n\n");

    printf("1️⃣ - Primeiro Acesso ✅\n");
    printf("2️⃣ - Login ✅\n");

    printf("3️⃣ - Encerrar ❌\n");
    printf("===============\n");
    printf("Opcao 🧐: ");
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
    DBLOGIN = fopen("dadoslogin.txt", "a"); //Abertura do DB para a inserção de dados

    if (DBLOGIN == NULL) { //Verificação do Banco de Dados
        printf("\nErro no Banco de Dados...\n");
    } else {
        printf("===================================\n");
        printf("PRIMEIRO ACESSO NO SISTEMA 🆕✅\n");
        printf("===================================\n\n");

        printf("\nDigite o seu Usuario desejado: ");
        fgets(LoginUsuario.Usuario, 25, stdin); //Recebe a String Nome

        printf("\nDigite a sua Senha desejada: ");
        fgets(LoginUsuario.Senha, 20, stdin); //Recebe a String Email
    }

    fprintf(DBLOGIN, "%s", LoginUsuario.Usuario);
    fprintf(DBLOGIN, "%s", LoginUsuario.Senha);

    fclose(DBLOGIN); //Fecha o Banco de dados

    login();
}

void login(int clear) {

    if (clear != 1)
        system("clear");

    char * filename = "dadoslogin.txt";
    FILE * fp = fopen(filename, "r");

    if (fp == NULL) { //Verificação do Banco de Dados
        printf("\nErro no Banco de Dados...\n");
    } else {
        printf("==============================\n");
        printf("LOGIN NO SISTEMA 🔐✅\n");
        printf("==============================\n\n");

        printf("Usuario: ");
        fgets(LoginUsuario.Usuario, 25, stdin); //Recebe a String Nome

        printf("\nSenha: ");
        fgets(LoginUsuario.Senha, 6, stdin); //Recebe a String Email

        system("clear");

        char buffer[MAX_LENGTH];
        char arr[NUM_STRINGS][MAX_LENGTH] = {""};

        int i = 0;

        while (fgets(buffer, MAX_LENGTH, fp)) {
            if (i == 0) {
                strcpy(arr[0], buffer);
                i++;
            } else {
                strcpy(arr[1], buffer);
                i = 0;
            }

            if (i == 0) {
                int result = validaLogin(arr[0], LoginUsuario.Usuario);
                int result2 = validaLogin(arr[1], LoginUsuario.Senha);

                system("clear");

                if (result == 0 && result2 == 0) {
                    menu();
                } else {
                    printf("Usuário ou Senha Inválidos ❌🔐! Tente novamente...\n\n\n");
                    login(1);
                }
            }
        }

        // close the file
        fclose(fp);
    }
}

int validaLogin(char * str1, char * str2) {
    return strcmp(str1, str2);
}

void menu() {
    //Limpa a tela (Windows)
    system("clear");
    printf("=================================\n");
    printf(" GERENCIADOR DE PACIENTES 🚑👨🏻‍⚕️\n");
    printf("=================================\n\n");

    printf("1️⃣ - Cadastrar ✅\n");
    printf("2️⃣ - Alterar ✅\n");
    printf("3️⃣ - Listar ✅\n");
    printf("4️⃣ - Remover 🗑\n\n");

    printf("5️⃣ - Encerrar ❌\n");
    printf("=================================\n");
    printf("Opcao 🧐: ");
    scanf("%d", & GlobalPaciente.Op);
    getchar(); //Limpa o Buffer

    switch (GlobalPaciente.Op) {
        case 1:
            cadastro(); //Funcão Cadastro é iniciada
            break;
        case 2:

            system("clear");

            printf("==============\n");
            printf(" ALTERAR ✅\n");
            printf("==============\n\n");

            printf("Para alterar os dados de um cadastro, acesse o\narquivo ");
            printf("dados.txt e modifique manualmente através\nde um editor ");
            printf("de texto.\n\n");

            printf("\nVoltar ao Menu Principal? [s/n]: ");
            scanf("%c", & GlobalPaciente.Cd);

            if (GlobalPaciente.Cd == 's') {
                menu();
            } else if (GlobalPaciente.Cd != 's' && GlobalPaciente.Cd != 'n') {
                printf("Valor inválido.\nVoltando ao Menu Principal...\n");
                menu();
            }
            break;
        case 3:
            listar(); //Função Listar é iniciada
            break;
        case 4:

            system("clear");

            printf("==============\n");
            printf(" REMOVER ❌\n");
            printf("==============\n\n");

            printf("Para remover os dados de um paciente, acesse\no arquivo ");
            printf("dados.txt e realize o processo \nmanualmente, salvando o ");
            printf("arquivo logo em seguida.\n\n");

            printf("\nVoltar ao Menu Principal? [s/n]: ");
            scanf("%c", & GlobalPaciente.Cd);

            if (GlobalPaciente.Cd == 's') {
                menu();
            } else if (GlobalPaciente.Cd != 's' && GlobalPaciente.Cd != 'n') {
                printf("Valor inválido.\nVoltando ao Menu Principal...\n");
                menu();
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
    DB = fopen("dadospaciente.txt", "a"); //Abertura do DB para a inserção de dados

    if (DB == NULL) { //Verificação do Banco de Dados
        printf("\nErro no Banco de Dados...\n");
        return 1;

    } else {
        printf("==============\n");
        printf(" CADASTRO ✅\n");
        printf("==============\n");

        printf("\nDigite seu Nome: ");
        fgets(Paciente.Nome, 25, stdin); //Recebe a String Nome

        printf("\nDigite seu E-mail: ");
        fgets(Paciente.Email, 35, stdin); //Recebe a String Email

        printf("\nDigite seu CPF: ");
        fgets(Paciente.Cpf, 15, stdin); //Recebe a String Cpf

        printf("\nDigite a Data de Nascimento (dd/mm/aaaa): ");
        fgets(Paciente.Nascimento, 10, stdin); //Recebe a String Nascimento

        printf("\nDigite seu Telefone: ");
        fgets(Paciente.Telefone, 15, stdin); //Recebe a String Telefone

        printf("\nDigite seu Endereço Completo: ");
        fgets(Paciente.Endereco, 100, stdin); //Recebe a String Endereço

        printf("\nDigite seu CEP: ");
        fgets(Paciente.CEP, 20, stdin); //Recebe a String CEP

        printf("\nDigite a Data do Diagnóstico: ");
        fgets(Paciente.DataDiagnostico, 15, stdin); //Recebe a String DataDiagnostico

        comorbidade();

        system("clear");
        printf("\n=============================\n");
        printf("Finalizar cadastro? [s/n]: ");
        scanf("%c", & GlobalPaciente.Cd); //Conclusão do cadastro

        if (GlobalPaciente.Cd == 's') {
            fprintf(DB, "Nome: %sE-mail: %sCPF: %sTelefone: %sData Nascimento: %sEndereço: %sData Diagnostico: %s", Paciente.Nome, Paciente.Email, Paciente.Cpf, Paciente.Telefone, Paciente.Nascimento, Paciente.Endereco, Paciente.DataDiagnostico);
            fprintf(DB, "----------------------\n"); //Salva os dados

            fclose(DB); //Fecha o Banco de dados

            system("clear");
            printf("##########################\n");
            printf("# Cadastro Concluído ✅#\n");
            printf("#########################\n");
            menu();
        } else if (GlobalPaciente.Cd == 'n') {
            system("clear");
            printf("Cadastro Cancelado.\nVoltando ao Menu Principal...\n");
            fclose(DB); //Fecha DB
            getchar(); //Corrige bug quando GlobalPaciente.Cd != 's' && 'n'
            menu();
        } else {
            printf("Valor inválido. Tente novamente...\n");
            fclose(DB); //Fecha DB
            cadastro();
        }
    }

    return 0;
} //Fim da função Cadastro

void comorbidade() {
    system("clear");

    char * filename = "comorbidades.txt";
    FILE * fp = fopen(filename, "r");

    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp)) {
        printf("\n%s", buffer);
    }

    printf("\n\nDigite alguma comorbidade do paciente: ");
    fgets(Paciente.Comorbidade, 20, stdin); //Recebe a String Comorbidade

    grupoRisco();
}

void grupoRisco() {
    //ponteiro para struct que armazena data e hora  
    struct tm *data_hora_atual;     

    //variável do tipo time_t para armazenar o tempo em segundos  
    time_t segundos;

    //obtendo o tempo em segundos  
    time(&segundos);   

    //para converter de segundos para o tempo local  
    //utilizamos a função localtime  
    data_hora_atual = localtime(&segundos);

    int dia = data_hora_atual->tm_mday;
    int mes = (data_hora_atual->tm_mon+1);
    int ano = (data_hora_atual->tm_year+1900);

    int init_size = strlen(Paciente.Nascimento);
    char delim[] = "/";

    char *ptr = strtok(Paciente.Nascimento, delim);

    int i = 0;
    int data[3] = {0};

    while (ptr != NULL) {
        if (str2int(&data[i], ptr, 10) == STR2INT_SUCCESS) {
            ptr = strtok(NULL, delim);
            i++;
        }
    }

    int totalIdade = 365 * ano + 30 * mes + dia - 365 * data[2] - 30 * data[1] - data[0];
    int anos = totalIdade / 365;

    int comorbidade = 0;
    if (str2int(&comorbidade, Paciente.Comorbidade, 10) == STR2INT_SUCCESS) {
        if ((anos >= E_GRUPO_RISCO) || (anos >= E_GRUPO_RISCO && comorbidade < 5)) {
                DB = fopen("dadoscomorbidade.txt", "a"); //Abertura do DB para a inserção de dados
                fprintf(DB, "Nome: %sIdade: %dCEP: %s", Paciente.Nome, anos, Paciente.CEP);
                fprintf(DB, "----------------------\n"); //Salva os dados
                fclose(DB); //Fecha o Banco de dados
        }
    }

    system("clear");
    cadastro();
}

int listar() {
    system("clear");
    DB = fopen("dadospaciente.txt", "r"); //Abertura do DB para leitura de dados

    if (DB == NULL) { //Verificação do Banco de dados
        printf("\nErro no Banco de Dados...\n");
        return 1;
    } else {
        printf("===========================\n");
        printf(" LISTAGEM DE PACIENTES 📄\n");
        printf("===========================\n\n");

        char listagem[250]; //String geral para os dados

        while (fgets(listagem, 250, DB) != NULL) {
            printf("%s", listagem);
        } //Considera todos os dados como uma String e exibe na tela

        fclose(DB);

        printf("\nVoltar ao Menu Principal? [s/n]: ");
        scanf("%c", & GlobalPaciente.Cd);

        if (GlobalPaciente.Cd == 's') {
            menu();
        } else if (GlobalPaciente.Cd != 's' && GlobalPaciente.Cd != 'n') {
            printf("Valor inválido.\nVoltando ao Menu Principal...\n");
            menu();
        }
    }

    return 0;

} //Fim da função Listar