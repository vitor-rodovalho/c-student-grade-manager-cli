/*
Este projeto consiste em um gerenciador de notas de alunos por matrícula e por código de disciplina.
O projeto uiltiza arquivo binário como banco de dados local, por tal, seus resultados variam de acordo
com a máquina utilizada e cadastros dentro do programa já realizados anteriormente.
O programa, quando solicitado, apresenta um boletim de todas as notas do aluno em todas as discplinas,
tal como apresenta um relatório de todos os alunos aprovados e reprovados em uma determinada diciplina
para o professor.
Ordem correta de utilização do programa:
1 - Cadastro de Disciplnas;
2 - Cadastro de Alunos;
3 - Cadastro de notas.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NOMEARQUIVO "arquivoBinario"



int QTD_ALUNOS;
int QTD_DISCIPLINAS;
int QTD_NOTAS;


//Junção Typedef com Structs
typedef struct Aluno {
    int matriculaAluno;
    char nomeAluno[100];
} Aluno;


typedef struct Disciplina {
    char nomeDisciplina[100];
    int codDisciplina;
} Disciplina;


typedef struct Notas {
    int codDisciplina;
    int matriculaAluno; 
    int qtdNotas;
    double pesos[10];
    double notas[10];
    double media;
} Notas;



//Protótipos de Funções
void inserirNotas(int matricula, Disciplina *disciplina, Notas **notas);
void adicionarAluno(Aluno **aluno, Disciplina *disciplina, Notas **notas);
int buscaRecursivaDisciplina(int encontrar, Disciplina *disciplina, int i);
int buscaRecursivaAluno(int encontrar, Aluno *aluno, int i);
void Boletim(int indice, int matricula, Aluno *aluno, Disciplina *disciplina, Notas *notas);
void buscarAluno(Aluno **aluno, Disciplina *disciplina, Notas **notas);
void excluirAluno(Aluno *aluno);
void criarDisciplina(Disciplina **disciplina);
void buscarDisciplina(Disciplina *disciplina);
int menu();
void leituraArquivo(FILE *arquivo, Aluno **aluno, Disciplina **disciplina, Notas **notas);
void escreveArquivo(FILE *arquivo, Aluno *aluno, Disciplina *disciplina, Notas *notas);



int main() {
    // Inicializa com NULL
    Aluno *aluno = NULL;
    Disciplina *disciplina = NULL;
    Notas *notas = NULL;

    FILE *arquivo = fopen(NOMEARQUIVO, "rb");
    

    if(arquivo == NULL){
        // Inicia alocação básica para evitar NULL pointer se o arquivo não existir
        aluno = malloc(sizeof(Aluno)); 
        disciplina = malloc(sizeof(Disciplina));
        notas = malloc(sizeof(Notas));
    }
    else{
        // Passa o endereço (&) para a função poder alocar memória
        leituraArquivo(arquivo, &aluno, &disciplina, &notas);
        fclose(arquivo);
    }


    int escolha;
    while (1) {
        escolha = menu();

        switch (escolha) {
            case 1:
                criarDisciplina(&disciplina);
                break;

            case 2:
                adicionarAluno(&aluno, disciplina, &notas);
                break;

            case 3:
                buscarAluno(&aluno, disciplina, &notas);
                break;

            case 4:
                buscarDisciplina(disciplina);
                break;

            case 5:
                excluirAluno(aluno);
                break;

            case 0:
                arquivo = fopen(NOMEARQUIVO, "wb");

                if (arquivo != NULL) {
                    escreveArquivo(arquivo, aluno, disciplina, notas);
                    fclose(arquivo);
                }

                free(aluno);
                free(disciplina);
                free(notas);
                return 0;

            default:
                break;
        }
    }
}



void inserirNotas(int matricula, Disciplina *disciplina, Notas **notas) {
    int i, j;
    
    // Realoca memória
    Notas *temp = realloc(*notas, (QTD_NOTAS + 1) * sizeof(Notas));
    if (temp == NULL) return;
    *notas = temp;

    printf("Selecione a disciplina para incluir as notas do aluno:\n");
    for (i = 0; i < QTD_DISCIPLINAS; i++) {
        printf("%d - Código %d - %s\n", i + 1, disciplina[i].codDisciplina, disciplina[i].nomeDisciplina);
    }
    printf("(Escolha o numero da opcao desejada.)\n");

    scanf("%d", &j);
    j -= 1;

    // Proteção contra índice inválido
    if (j < 0 || j >= QTD_DISCIPLINAS) {
        printf("Disciplina invalida.\n");
        return;
    }

    printf("Quantas notas a disciplina possui?\n");
    scanf("%d", &(*notas)[QTD_NOTAS].qtdNotas);
    
    for (i = 0; i < (*notas)[QTD_NOTAS].qtdNotas; i++) {
        printf("Qual o peso da N%d? (Final 10.0)\n", i + 1);
        scanf("%lf", &(*notas)[QTD_NOTAS].pesos[i]);
    }
    for (i = 0; i < (*notas)[QTD_NOTAS].qtdNotas; i++){
        printf("Insira a N%d:\n", i+1);
        scanf("%lf", &(*notas)[QTD_NOTAS].notas[i]);
    }
    
    double media = 0;
    for (i = 0; i < (*notas)[QTD_NOTAS].qtdNotas; i++){
        media += (*notas)[QTD_NOTAS].notas[i] * ((*notas)[QTD_NOTAS].pesos[i] / 10.0);
    }

    (*notas)[QTD_NOTAS].media = media;
    (*notas)[QTD_NOTAS].codDisciplina = disciplina[j].codDisciplina;
    (*notas)[QTD_NOTAS].matriculaAluno = matricula;

    QTD_NOTAS++;
}



void adicionarAluno(Aluno **aluno, Disciplina *disciplina, Notas **notas) {
    char nome[100];

    // Realoca memória
    Aluno *temp = realloc(*aluno, (QTD_ALUNOS + 1) * sizeof(Aluno));
    if (temp == NULL) return;
    *aluno = temp;

    printf("Insira a matricula do aluno:\n");
    scanf("%d%*c", &(*aluno)[QTD_ALUNOS].matriculaAluno);
    
    printf("Insira o nome completo do aluno:\n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    strcpy((*aluno)[QTD_ALUNOS].nomeAluno, nome);
    
    printf("\nALUNO ADICIONADO COM SUCESSO!\n");

    inserirNotas((*aluno)[QTD_ALUNOS].matriculaAluno, disciplina, notas);

    QTD_ALUNOS++;
}



int buscaRecursivaDisciplina(int encontrar, Disciplina *disciplina, int i) {

    if (i >= QTD_DISCIPLINAS) return -1;

    if (disciplina[i].codDisciplina == encontrar) return i;

    return buscaRecursivaDisciplina(encontrar, disciplina, i + 1);
}



int buscaRecursivaAluno(int encontrar, Aluno *aluno, int i) {

    if (i >= QTD_ALUNOS) return -1;

    if (aluno[i].matriculaAluno == encontrar) return i;

    return buscaRecursivaAluno(encontrar, aluno, i + 1);
}



void Boletim(int indice, int matricula, Aluno *aluno, Disciplina *disciplina, Notas *notas){

    printf("\n\nBOLETIM DO ALUNO\n\n");
    printf("Aluno(a): %s\n", aluno[indice].nomeAluno);

    for(int i = 0; i < QTD_NOTAS; i++){
        if(matricula == notas[i].matriculaAluno){
            for(int j = 0; j < QTD_DISCIPLINAS; j++){
                if(notas[i].codDisciplina == disciplina[j].codDisciplina){
                    printf("Disciplina: %s   ", disciplina[j].nomeDisciplina);
                }
            }
            printf("Nota: %.2lf\n\n\n", notas[i].media);
        }
    }
}



void buscarAluno(Aluno **aluno, Disciplina *disciplina, Notas **notas ) {

    int encontrar;
    printf("Insira a matricula (0 para voltar):\n");
    scanf("%d%*c", &encontrar);
    if (encontrar == 0) return;

    int indice = buscaRecursivaAluno(encontrar, *aluno, 0);
    
    if (indice < 0) {
        printf("MATRICULA NAO ENCONTRADA.\n");
    } else {
        printf("1 - Inserir Nota\n2 - Mostrar Boletim\n");
        int caso;
        scanf("%d", &caso);

        switch (caso) {
        case 1:
            inserirNotas((*aluno)[indice].matriculaAluno, disciplina, notas);
            break;

        case 2:
            Boletim(indice, (*aluno)[indice].matriculaAluno, *aluno, disciplina, *notas);
            break;

        default:
            return;
        }
    }
}



void excluirAluno(Aluno *aluno) {

    int i, excluida;
    printf("Insira a matricula do aluno que deseja excluir:\n");
    scanf("%d%*c", &excluida);

    int indice = buscaRecursivaAluno(excluida, aluno, 0);

    if (indice >= 0) {
        for (i = indice; i < QTD_ALUNOS - 1; i++) {
            aluno[i] = aluno[i + 1];
        }
        QTD_ALUNOS--;
        printf("Aluno excluido com sucesso.\n");
    } else {
        printf("MATRICULA NAO ENCONTRADA.\n");
    }
}



void criarDisciplina(Disciplina **disciplina) {
    char nome[100];
    
    // Realoca memória antes de adicionar
    Disciplina *temp = realloc(*disciplina, (QTD_DISCIPLINAS + 1) * sizeof(Disciplina));
    if (temp == NULL) return;
    *disciplina = temp;

    printf("Insira o nome da disciplina:\n");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    strcpy((*disciplina)[QTD_DISCIPLINAS].nomeDisciplina, nome);
    
    printf("Insira o codigo da disciplina:\n");
    scanf("%d", &(*disciplina)[QTD_DISCIPLINAS].codDisciplina);

    QTD_DISCIPLINAS++;
    printf("Disciplina criada com sucesso.\n");
}



void buscarDisciplina(Disciplina *disciplina) {

    int encontrar;
    printf("Digite o codigo da disciplina a ser encontrada (ou tecle 0 para voltar ao menu anterior):\n");
    scanf("%d", &encontrar);
    if (encontrar == 0) {
        return;
    }

    int i = buscaRecursivaDisciplina(encontrar, disciplina, 0);
    if (i < 0) {
        printf("DISCIPLINA NAO ENCONTRADA.\n");
    } else {
        printf("%d - %s\n", disciplina[i].codDisciplina, disciplina[i].nomeDisciplina);
    }
}



int menu() {

    int escolha;

    do {
        printf("\n\tGERENCIADOR DE NOTAS\n");
        printf("1 - Adicionar nova disciplina\n");
        printf("2 - Adicionar novo aluno\n");
        printf("3 - Buscar aluno\n");
        printf("4 - Buscar disciplina\n");
        printf("5 - Excluir aluno\n");
        printf("0 - Finalizar o programa\n");
        printf("Escolha a opcao desejada: \n");
        scanf("%d%*c", &escolha);
    } while (escolha < 0 || escolha > 5);

    return escolha;
}



void leituraArquivo(FILE *arquivo, Aluno **aluno, Disciplina **disciplina, Notas **notas) {
    int i;
    
    fread(&QTD_ALUNOS, sizeof(int), 1, arquivo);
    fread(&QTD_DISCIPLINAS, sizeof(int), 1, arquivo);
    fread(&QTD_NOTAS, sizeof(int), 1, arquivo);

    free(*aluno);
    free(*disciplina);
    free(*notas);

    // Aloca a quantidade exata lida do arquivo
    *aluno = malloc((QTD_ALUNOS > 0 ? QTD_ALUNOS : 1) * sizeof(Aluno));
    *disciplina = malloc((QTD_DISCIPLINAS > 0 ? QTD_DISCIPLINAS : 1) * sizeof(Disciplina));
    *notas = malloc((QTD_NOTAS > 0 ? QTD_NOTAS : 1) * sizeof(Notas));

    for(i = 0; i < QTD_ALUNOS; i++){
        fread(&(*aluno)[i].matriculaAluno, sizeof(int), 1, arquivo);
        fread((*aluno)[i].nomeAluno, sizeof(char), 100, arquivo);
    }
    for(i = 0; i < QTD_DISCIPLINAS; i++){
        fread((*disciplina)[i].nomeDisciplina, sizeof(char), 100, arquivo);
        fread(&(*disciplina)[i].codDisciplina, sizeof(int), 1, arquivo);
    }
    for(i = 0; i < QTD_NOTAS; i++){
        fread(&(*notas)[i].codDisciplina, sizeof(int), 1, arquivo);
        fread(&(*notas)[i].matriculaAluno, sizeof(int), 1, arquivo);
        fread(&(*notas)[i].qtdNotas, sizeof(int), 1, arquivo);
        fread((*notas)[i].pesos, sizeof(double), 10, arquivo);
        fread((*notas)[i].notas, sizeof(double), 10, arquivo);
        fread(&(*notas)[i].media, sizeof(double), 1, arquivo);
    }
}



void escreveArquivo(FILE *arquivo, Aluno *aluno, Disciplina *disciplina, Notas *notas) {

    int i;
    
    fwrite(&QTD_ALUNOS, sizeof(int), 1, arquivo);
    fwrite(&QTD_DISCIPLINAS, sizeof(int), 1, arquivo);
    fwrite(&QTD_NOTAS, sizeof(int), 1, arquivo);

    for(i = 0; i < QTD_ALUNOS; i++) {
        fwrite(&aluno[i].matriculaAluno, sizeof(int), 1, arquivo);
        fwrite(aluno[i].nomeAluno, sizeof(char), 100, arquivo);
    }

    for(i = 0; i < QTD_DISCIPLINAS; i++){
        fwrite(disciplina[i].nomeDisciplina, sizeof(char), 100, arquivo);
        fwrite(&disciplina[i].codDisciplina, sizeof(int), 1, arquivo);
    }

    for(i = 0; i < QTD_NOTAS; i++){
        fwrite(&notas[i].codDisciplina, sizeof(int), 1, arquivo);
        fwrite(&notas[i].matriculaAluno, sizeof(int), 1, arquivo);
        fwrite(&notas[i].qtdNotas, sizeof(int), 1, arquivo);
        fwrite(notas[i].pesos, sizeof(double), 10, arquivo);
        fwrite(notas[i].notas, sizeof(double), 10, arquivo);
        fwrite(&notas[i].media, sizeof(double), 1, arquivo);
    }
}