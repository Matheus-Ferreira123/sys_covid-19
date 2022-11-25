#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
/*nome, CPF, telefone, endereço (rua, número, bairro,
cidade, estado e CEP), data de nascimento e e-mail, data do diagnóstico e, se for o caso,
informar existentes comorbidades (diabetes, obesidade, hipertensão, tuberculose etc.)*/

FILE *listaPacientes;
FILE *grupoRisco;

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
	int idade;
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
    printf(" 3 - CONSULTAR PACIENTES DO GRUPO DE RISCO.\n\n");
    printf (" 0 - SAIR.\n\n");
    printf(" Selecione uma das opcoes para continuar: ");
    scanf("%s", &opcao);

    //Validando opções
    if(opcao == '1'){
        telaCadastro();
    }else if(opcao == '2'){
        telaConsulta();
    }else if(opcao == '3'){
        telaConsultaRisco();
    }else if(opcao == '0'){
        telaCreditos();
    }else{
        limparTela();
        printf("\n\n OPÇÃO INCORRETA");
        sleep(1);
        limparTela();
        telaMenu();
    }
}
void abrir_arqRisco(){
    grupoRisco = fopen("grupo_de_risco.txt", "a+b");
    if(grupoRisco == NULL){
        printf("Erro na abertura do arquivo\n");
        system("pause");
        exit(1);
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
    printf("\n 0 - voltar");
    printf("\n\nInforme o cpf do paciente para emitir a ficha: ");
    scanf("%s", &cpf);

    if(igual(cpf, "0") == 1){
        fclose(listaPacientes);
        telaMenu();
    }

    buscarPacientePorCpf(cpf);
    fclose(listaPacientes);
}

void buscarPacientePorCpfRisco(cpf){
    int a=0;

    fseek(grupoRisco,SEEK_SET,1);
    fread(&paciente,sizeof(paciente),1,grupoRisco);

    if(igual(paciente.cpf, cpf) == 1){
        a++;
        mostrarFichaRisco(paciente);
    }

    while(!feof(grupoRisco)){
        if(igual(paciente.cpf, cpf) == 1){
            a++;
            printf("CPF: %s -", paciente.cpf);
            printf(" Nome: %s\n", paciente.nome);
            mostrarFichaRisco(paciente);
        }

        fread(&paciente,sizeof(paciente),1,grupoRisco);
    }
    if(a == 0){
        printf("\n Paciente não encontrado!");
        sleep(2);
        telaConsultaRisco();
    }



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
        printf("\n Paciente não encontrado!");
        sleep(2);
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
    printf("\n Comorbidades: %s", paciente.comorbidades);
    printf("\n\n0 - Voltar\n");
    printf("\nSelecione a opção para continuar: ");
    scanf("%s", opcao);

    telaConsulta();
}

void telaConsultaRisco(){
    system("cls");
    char cpf[20];

    imprimirCabecalho();
    abrir_arqRisco();
    listarPacientesRisco();
    fclose(grupoRisco);

    abrir_arqRisco();
    printf("\n 0 - voltar");
    printf("\n\nInforme o cpf do paciente para emitir a ficha: ");
    scanf("%s", &cpf);

    if(igual(cpf, "0") == 1){
        fclose(grupoRisco);
        telaMenu();
    }

    buscarPacientePorCpfRisco(cpf);
    fclose(grupoRisco);
}

int mostrarFichaRisco(){
    char opcao[40] = "";
    limparTela();
    imprimirCabecalho();

    printf(" Nome: %s\n", paciente.nome);
    printf(" CPF: %s\n", paciente.cpf);
    printf(" Idade: %d\n", paciente.idade);
    printf(" CEP: %s\n", paciente.endereco.cep);

    printf("\n\n0 - Voltar\n");
    printf("\nSelecione a opção para continuar: ");
    scanf("%s", opcao);

    telaConsulta();

}

void listarPacientesRisco(){
    int a=0;

    fseek(grupoRisco,SEEK_SET,1);
    fread(&paciente,sizeof(paciente),1,grupoRisco);

    printf("Pacientes encontrados: \n\n");
    while(!feof(grupoRisco)){
        a++;

        printf(" CPF: %s - ", paciente.cpf);
        printf("Nome: %s\n", paciente.nome);

        fread(&paciente,sizeof(paciente),1,grupoRisco);
    }
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
    int temComorbidades = 0;
    Paciente pacienteRisco;

    limparTela();
    imprimirCabecalho();

    printf("Dados do paciente:\n");
    printf(" Nome: ");
    fflush(stdin);
    gets(paciente.nome);

    strcpy(nomeArquivo, paciente.nome);
    strcat(nomeArquivo, ".txt");

    abrir_arqRisco();
    abrir_arq();

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
    paciente.idade = calcIdade(paciente.dataNascimento.dia, paciente.dataNascimento.mes, paciente.dataNascimento.ano);

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

    printf(" Contêm comorbidades? (1 = Sim| 2 = Não) ");
    scanf("%i", &temComorbidades);

    if(temComorbidades == 1){
        printf(" Qual(is): ");
        scanf("%s", &paciente.comorbidades);

        if(paciente.idade > 65 && temComorbidades == 1){
            fseek(grupoRisco,SEEK_END,1);
            fwrite(&paciente,sizeof(paciente),1,grupoRisco);
        }

        fclose(grupoRisco);
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

int calcIdade(diaNasc, mesNasc, anoNasc) {
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    int year_diff;

    int dia, mes, ano;

    dia = tm.tm_mday;
    mes = tm.tm_mon + 1;
    ano = tm.tm_year + 1900;

    diaNasc = atoi(diaNasc);
    mesNasc = atoi(mesNasc);
    anoNasc = atoi(anoNasc);

    if(dia < diaNasc){
        if (mes == 3){
            if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
                dia += 29;
            }else{
                dia += 28;
            }
        }else if (mes == 5 || mes == 7 || mes == 10 || mes == 12){
           dia += 30;
        }else{
           dia += 31;
        }

        mes = mes - 1;
    }

    if (mes < mesNasc){
        mes += 12;
        ano -= 1;
    }


    year_diff = ano - anoNasc;
    return year_diff;
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
    limparTela();
    printf(" \n\n\n\n    UNIP PIM IV 2022");
    sleep(1);
    exit(0);
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
