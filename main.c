#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <conio.h>
/*nome, CPF, telefone, endereço (rua, número, bairro,
cidade, estado e CEP), data de nascimento e e-mail, data do diagnóstico e, se for o caso,
informar existentes comorbidades (diabetes, obesidade, hipertensão, tuberculose etc.)*/

FILE *listaPacientes;

typedef struct endereco Endereco ;
struct endereco
{
	char numero[40];
	char rua[40];
	char bairro[40];
    char cidade[40];
    char estado[40];
	char cep[40];
};

typedef struct data Data ;
struct data {
    char dia[40], mes[40], ano[40];
};

typedef struct paciente Paciente;
struct paciente
{
	char nome[40];
	char cpf[40];
	Endereco endereco;
	char telefone[40];
	Data dataNascimento;
	char email[40];
	Data diagnostico;
	char comorbidades[60];
	int idade[40];
}paciente;

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
    if(igual(usuario.nome, nome) == 1 && igual(usuario.senha, senha) == 1){
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
        telaConsulta();
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

void abrir_arq(){
    listaPacientes = fopen("fichas_pacientes.txt", "a+b");
    if(listaPacientes == NULL){
        printf("Erro na abertura do arquivo\n");
        system("pause");
        exit(1);
    }
}

void telaConsulta(){
    system("cls");
    char cpf[20];

    imprimirCabecalho();
    abrir_arq();
    listarPacientes();
    fclose(listaPacientes);

    abrir_arq();
    printf("\n\nInforme o cpf do paciente para emitir a ficha: ");
    scanf("%s", &cpf);

    buscarPacientePorCpf(cpf);
    fclose(listaPacientes);
}

void buscarPacientePorCpf(cpf){
    int a=0;

    fseek(listaPacientes,SEEK_SET,1);
    fread(&paciente,sizeof(paciente),1,listaPacientes);

    if(igual(paciente.cpf, cpf) == 1){
        a++;
        mostrarFicha(paciente);
    }

    while(!feof(listaPacientes)){
        if(igual(paciente.cpf, cpf) == 1){
            a++;
            printf("CPF: %s -", paciente.cpf);
            printf(" Nome: %s\n", paciente.nome);
            mostrarFicha(paciente);
        }

        fread(&paciente,sizeof(paciente),1,listaPacientes);
    }
    if(a == 0){
        printf("Paciente não encontrado\n");
        fclose(listaPacientes);
        sleep(3);
        telaConsulta();
    }



}

int mostrarFicha(Paciente paciente){
    char opcao[40] = "";

    limparTela();
    imprimirCabecalho();
    printf("Paciente encontrado:\n\n");
    printf(" Nome: %s\n", paciente.nome);
    printf(" CPF: %s\n", paciente.cpf);
    printf(" Email: %s\n", paciente.email);
    printf(" Telefone: %s\n", paciente.telefone);
    printf(" Data de nascimento: %s / %s / %s\n", paciente.dataNascimento.dia, paciente.dataNascimento.mes, paciente.dataNascimento.ano);
    printf(" \nDados de endereço: \n\n");
    printf(" CEP: %s\n", paciente.endereco.cep);
    printf(" Cidade: %s\n", paciente.endereco.cidade);
    printf(" Estado: %s\n", paciente.endereco.estado);
    printf(" Bairro: %s\n", paciente.endereco.bairro);
    printf(" Rua: %s\n", paciente.endereco.rua);
    printf(" Número: %s\n", paciente.endereco.numero);
    printf("\nData do Diagnóstico: %s / %s / %s\n", paciente.diagnostico.dia, paciente.diagnostico.mes, paciente.diagnostico.ano);
    printf("\n\n0 - Voltar\n");
    printf("\nSelecione uma das opcoes para continuar: ");
    scanf("%s", opcao);

    telaConsulta();
}

void listarPacientes(){
    int a=0;

    fseek(listaPacientes,SEEK_SET,1);
    fread(&paciente,sizeof(paciente),1,listaPacientes);

    printf("Pacientes encontrados: \n\n");
    while(!feof(listaPacientes)){
        a++;

        printf(" CPF: %s - ", paciente.cpf);
        printf("Nome: %s\n", paciente.nome);

        fread(&paciente,sizeof(paciente),1,listaPacientes);
    }
}

//Tela de cadastro do paciente
int telaCadastro(){

    char nomeArquivo[40];
    char temComorbidades[40];

    limparTela();
    imprimirCabecalho();

    printf("Dados do paciente:\n");
    printf(" Nome: ");
    fflush(stdin);
    gets(paciente.nome);

    strcpy(nomeArquivo, paciente.nome);
    strcat(nomeArquivo, ".txt");

    abrir_arq(nomeArquivo);

    printf(" CPF: ");
    fflush(stdin);
    gets(paciente.cpf);

    printf(" Email: ");
    fflush(stdin);
    gets(paciente.email);

    printf(" Telefone: ");
    fflush(stdin);
    gets(paciente.telefone);

    printf("\nData de nascimento: \n");
    printf(" Dia: ");
    fflush(stdin);
    gets(paciente.dataNascimento.dia);

    printf(" Mês: ");
    fflush(stdin);
    gets(paciente.dataNascimento.mes);

    printf(" Ano: ");
    fflush(stdin);
    gets(paciente.dataNascimento.ano);

    printf(" \nDados de endereço: \n");
    printf(" CEP: ");
    fflush(stdin);
    gets(paciente.endereco.cep);

    printf(" Cidade: ");
    fflush(stdin);
    gets(paciente.endereco.cidade);

    printf(" Estado: ");
    fflush(stdin);
    gets(paciente.endereco.estado);

    printf(" Bairro: ");
    fflush(stdin);
    gets(paciente.endereco.bairro);

    printf(" Rua: ");
    fflush(stdin);
    gets(paciente.endereco.rua);

    printf(" Número: ");
    fflush(stdin);
    gets(paciente.endereco.numero);

    printf("\nDiagnostico: \n");

    printf(" Data do diagnóstico: \n");
    printf(" Dia: ");
    fflush(stdin);
    gets(paciente.diagnostico.dia);

    printf(" Mês: ");
    fflush(stdin);
    gets(paciente.diagnostico.mes);

    printf(" Ano: ");
    fflush(stdin);
    gets(paciente.diagnostico.ano);

    printf(" Contêm comorbidades? (S|N) ");
    fflush(stdin);
    gets(temComorbidades);

    if(igual(temComorbidades, "S") == 1 || igual(temComorbidades, "S") == 1){
        printf(" Qual(is): ");
        scanf("%s", &paciente.comorbidades);
    }

    fseek(listaPacientes,SEEK_END,1);
    fwrite(&paciente,sizeof(paciente),1,listaPacientes);
    fclose(listaPacientes);

    limparTela();
    imprimirCabecalho();
    printf("Paciente cadastrado com sucesso!");
    sleep(2);
    telaMenu();
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

int igual(dado, dadoOriginal){
    return !strcmp(dado,dadoOriginal);
};
