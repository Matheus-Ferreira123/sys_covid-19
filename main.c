#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <conio.h>
/*nome, CPF, telefone, endereço (rua, número, bairro,
cidade, estado e CEP), data de nascimento e e-mail, data do diagnóstico e, se for o caso,
informar existentes comorbidades (diabetes, obesidade, hipertensão, tuberculose etc.)*/


typedef struct endereco Endereco ;
struct endereco
{
	char rua[30];
	char numero[10];
	char bairro[20];
    char cidade[20];
    char estado[20];
	char cep[8];
};

typedef struct data Data ;
struct data {
    char dia[2], mes[2], ano[4];
};

typedef struct paciente Paciente;
struct paciente
{
	char nome[40];
	char cpf[11];
	char telefone[11];
	Endereco endereco;
	Data dataNascimento;
	char email[20];
	Data diagnostico;
	char comorbidades[60];
	int idade[3];
};

typedef struct usuario Usuario;
struct usuario {
    char nome[12];
    char senha[99]
};

int main()
{
    setlocale(LC_ALL, "Portuguese");

    if(telaLogin() == 1){
        limparTela();
        telaMenu();
    }else{
        telaLogin();
    }
    return (0);
}

    //Tela de login
int telaLogin(){

    char nome[12] = "admin";
    char senha[12] = "123";

    Usuario usuario;

    // Solicitando nome de usuário
    imprimirCabecalho();
    printf(" DIGITE SEU NOME DE USUÁRIO: ");
    scanf("%s", &usuario.nome);

    limparTela();

    // Solicitando senha
    imprimirCabecalho();
    printf(" DIGITE SUA SENHA: ");
    scanf("%s", &usuario.senha);

    // Validando senha
    if(validaUsuario(usuario.nome, nome) == 1 && validaSenha(usuario.senha, senha) == 1){
        return 1;
    }else{
        limparTela();
        imprimirCabecalho();
        printf("\n Usuario ou senha incorreto(s) \n \n");
        sleep(1);
        limparTela();

        telaLogin();
    }


}
    // Chamando menu de opções
int telaMenu(){
    char opcao = 0;

    limparTela();
    imprimirCabecalho();

    printf(" 1 - CADASTRAR PACIENTES.\n");
    printf(" 2 - CONSULTAR PACIENTES CADASTRADOS.\n");
    printf(" 3 - CONSULTAR PACIENTES COM COMORBIDADES.\n\n\n");
    printf(" Selecione uma das opcoes para continuar: ");
    scanf("%s", &opcao);

    //Validando opções
    if(opcao == '1'){
        telaCadastro();
    }else if(opcao == '2'){
        telaCadastrado();
    }else if(opcao == '3'){
        telaComorbidade();
    }else{
        limparTela();
        printf("\n\n OPÇÃO INCORRETA");
        sleep(1);
        limparTela();
        telaMenu();
    }
}

//Tela de cadastro do paciente
int telaCadastro(){

    Paciente paciente;
    char nomeArquivo[40];
    char temComorbidades;

    limparTela();
    imprimirCabecalho();

    printf("Dados do paciente:\n");
    printf(" Nome: ");
    scanf("%s", &paciente.nome);

    printf(" CPF: ");
    scanf("%s", &paciente.cpf);

    printf(" Telefone: ");
    scanf("%s", &paciente.telefone);

    printf(" Email: ");
    scanf("%s", &paciente.email);

    printf("\nData de nascimento: \n");
    printf(" Dia: ");
    scanf("%s", &paciente.dataNascimento.dia);

    printf(" Mês: ");
    scanf("%s", &paciente.dataNascimento.mes);

    printf(" Ano: ");
    scanf("%s", &paciente.dataNascimento.ano);

    printf(" \nDados de endereço: \n");
    printf(" CEP: ");
    scanf("%s", &paciente.endereco.cep);

    printf(" Cidade: ");
    scanf("%s", &paciente.endereco.cidade);

    printf(" Estado: ");
    scanf("%s", &paciente.endereco.estado);

    printf(" Bairro: ");
    scanf("%s", &paciente.endereco.bairro);

    printf(" Rua: ");
    scanf("%s", &paciente.endereco.rua);

    printf(" Número: ");
    scanf("%s", &paciente.endereco.numero);

    printf("\nDiagnostico: \n");
    printf(" Data do diagnóstico: ");
    scanf("%s", &paciente.diagnostico);

    printf(" Contêm comorbidades? (S|N) ");
    scanf("%s", &temComorbidades);

    if(temComorbidades == 'S' || temComorbidades == 's'){
        printf(" Qual(is): ");
        scanf("%s", &paciente.comorbidades);
    }


    /*
     * Passando o nome do paciente para uma variável antes de a dicionar o prefixo ".txt"
     * para criar o nome do arquivo
     */
    strcpy(nomeArquivo, paciente.nome);
    strcat(nomeArquivo, ".txt");
    /*
     * Criando o arquivo com o nome do paciente
     */

    FILE *listaPacientes;
    listaPacientes = fopen(nomeArquivo, "w");
    /*
     * Inserindo os dados do paciente no arquivo
     */

    //limparTela();
    fprintf(listaPacientes, "Nome: %s \n", paciente.nome);
    fprintf(listaPacientes, "CPF: %s \n", paciente.cpf);
    fprintf(listaPacientes, "Telefone: %s \n", paciente.telefone);
    fprintf(listaPacientes, "Email: %s \n", paciente.email);
    fprintf(listaPacientes, "Data nascimento: %s / %s / %s \n", paciente.dataNascimento.dia, paciente.dataNascimento.mes, paciente.dataNascimento.ano);
    fprintf(listaPacientes, "CEP: %s \n", paciente.endereco.cep);
    fprintf(listaPacientes, "Cidade: %s \n", paciente.endereco.cidade);
    fprintf(listaPacientes, "Estado: %s \n", paciente.endereco.estado);
    fprintf(listaPacientes, "Bairro: %s \n", paciente.endereco.bairro);
    fprintf(listaPacientes, "Rua: %s \n", paciente.endereco.rua);
    fprintf(listaPacientes, "Número: %s \n", paciente.endereco.numero);
    fprintf(listaPacientes, "Diagnóstico: %s / %s / %s \n", paciente.diagnostico.dia, paciente.diagnostico.mes, paciente.diagnostico.ano);
    fprintf(listaPacientes, "Comorbidades: %s \n", paciente.comorbidades);

    //sleep(2);
    //limparTela();
    //telaMenu();
    fclose(listaPacientes);
}

    //Tela de pessoas com comorbidades
int telaComorbidade(){

    limparTela();
    imprimirCabecalho();
    printf("comorbidades");
    sleep(1);
    telaMenu();
}

    //Tela de pessoas cadastradas
int telaCadastrado(){

    limparTela();
    imprimirCabecalho();
    printf("cadastros");
    sleep(1);
    telaMenu();
}

int telaCreditos(){
    printf("UNIP PIM IV 2022");
}

void imprimirCabecalho(){
    printf("\n SISTEMA DE CADASTRO DE PACIENTES COM COVID-19\n\n\n\n");
};

void limparTela(){
    system("cls");
}

int validaUsuario (nome, nomePadrao){
    return !strcmp(nome,nomePadrao);
};

int validaSenha(senha, senhaPadrao){
    return !strcmp(senha,senhaPadrao);
}
