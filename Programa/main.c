#include <stdio.h> // Biblioteca para entrada e saida de dados
#include <string.h> // Biblioteca para tratar strings
#include <ctype.h> // Biblioteca para transformar minuscula -> maiuscula
#include <stdlib.h> // Biblioteca para converter numero para string

/* Nas funções foram usados ponteiros para que os valores
   das variaveis locais sejam repassados para as variaveis de
   escopo global
*/

// Função que recebe uma informação em forma de texto, por exemplo
// o nome completo, e faz uma validação para receber apenas letras

void receber_texto(char *informacao,char *variavel, int tamanho ,FILE *arq1)
{
    // condicao = 1 continua, condicao = 0 para = uma letra
    int condicao = 1;
    while (condicao){
        printf("\n %s: ",informacao);
        fflush(stdin); // limpar o enter do teclado
        fgets(variavel,tamanho,stdin); // lendo variavel
        // stdin: entrada padrao, ou seja, o teclado
        int i=0;
        // Teste para saber se o usuario digitou apenas enter (\n)
        if (variavel[i]=='\n'){
            printf("Erro! Digite apenas letras");
        }else{
        // Enquanto variavel na posicao i for diferente de enter (\n)
        // != significa diferente
        while (variavel[i] != '\n'){
                // toupper tornar para maiusculo
                // && operador E || operador OU
            if ( (toupper(variavel[i]) >= 'A' && toupper(variavel[i]) <= 'Z') ||
                 (variavel[i] == ' ') ){
                condicao = 0; // condicao = 0, igual a letra
            }else{
                condicao = 1; // condicao = 1, diferente de letra
                printf("Erro! Digite apenas letras \n");
                break; // Freio do while
                }
            i++; // i++, ou seja, i recebe o valor de i + 1
        }; // fim da  validacao
        variavel[i] = '\0';
        } // endelse
    }; // fim da coleta
    fprintf(arq1,"%s: %s\n",informacao,variavel); // guardar informacao no arquivo
} // fim da funcao receber_texto

// Função que recebe uma informação em forma de texto, por exemplo
// o cpf, e faz uma validação para receber apenas numeros
void receber_numero(char *informacao,char *variavel, int tamanho ,FILE *arq1){
    // condicao = 1 continua, condicao = 0 para
    int condicao = 1;
    while (condicao){
        printf("\n %s: ",informacao);
        fflush(stdin);
        fgets(variavel,tamanho,stdin);
        int i=0;
        if (variavel[i]=='\n'){
            printf("Erro! Digite apenas numeros");
        }else{
        while (variavel[i] != '\n'){
            if (variavel[i] >= '0' && variavel[i] <= '9')
                {
                condicao = 0;
            } else{
                condicao = 1;
                printf("Erro! Digite apenas numeros\n");
                break;
                }
            i++;
        }; // fim validacao
        variavel[i] = '\0';
        } // endelse
    }; // fim coleta
    fprintf(arq1,"%s: %s\n",informacao,variavel);
} // fim da funcao receber_numero

// struct = dicionario
struct data{
    char dia[4],mes[4],ano[6];
};

struct dados_endereco{
    char rua[100], bairro[100], cidade[100], estado[4], numero[10], cep[20];
};

struct dados_paciente{
    char nome[100], cpf[20], telefone[20], email[100], comorbidade[200];
    struct data nascimento;
    struct data diagnostico;
    struct dados_endereco endereco;
}paciente;

int login(int id_usuario, int senha){
    // 1 = a condicao verdadeira, ou seja, True
    while(1){
        printf("\nDigite o ID de usuario com 4 digitos: ");
        scanf("%d",&id_usuario); // le dados do teclado
        fflush(stdin); // anular o enter do teclado
        printf("\nDigite a senha de usuario com 4 digitos: ");
        scanf("%d",&senha);

        if( id_usuario==1234 && senha==4321 ){
            printf("\nAcesso Liberado. \nEntrando no sistema");
            //sleep(5); // dar pausa de 5 segundo
            break;
        }else{
            system("cls"); // limpar tela
            printf("Acesso negado!");
            }
    }; // fim do while
    return 1; // 1 == Verdadeiro, True
}

// Parte pratica do programa
int main(){

    int id_usuario,senha;
    // ID do usuario cadastrado = 1234
    // Senha do usuário cadastrado = 4321

    if( login (id_usuario,senha) ){

        char nome_arquivo[] = "Paciente"; // Nome do arquivo
        FILE *arq1; // definicao do ponteiro para o arquivo
        do{
        // Criacao de arquivo texto
            arq1 = fopen(nome_arquivo,"w"); // abre o arquivo, parametro 'w' para escrever informacoes
        // w - escrita, cria novo arquivo ou substitui anterior(apenas escrever, + escrever e ler)
        }while (arq1==NULL); // quando arq for diferente de NULL, significa que o arquivo foi aberto

        system("cls");

        receber_texto("nome",paciente.nome,100,arq1);
        receber_numero("CPF",paciente.cpf,13,arq1);
        receber_numero("telefone com DDD",paciente.telefone,13,arq1);

        int condicao = 1, i = 0;
        while(condicao){
          //system("cls");
          printf(" \nDigite o e-mail do paciente: ");
          fflush(stdin);
          fgets(paciente.email,50,stdin);
          i = 0;
          while(paciente.email[i]!='\n'){
            if ( (toupper(paciente.email[i]) >= 'A' && toupper(paciente.email[i]) <= 'Z') ||
                ( paciente.email[i] =='@' || paciente.email[i] == '.') ||
                ( paciente.email[i] >='0' && paciente.email[i] <= '9') ){
                condicao = 0;
            }else{
                condicao = 1;
                printf("Digite um e-mail válido");
                break;
            }
            i++;
          }; // fim validacao
        }; // fim coleta
        paciente.email[i] = '\0';
        fprintf(arq1,"E-mail: %s\n",paciente.email);

        printf("\nEndereco");
        receber_texto("rua",paciente.endereco.rua,100,arq1);
        receber_numero("numero",paciente.endereco.numero,7,arq1);
        receber_texto("bairro",paciente.endereco.bairro,40,arq1);
        receber_texto("cidade",paciente.endereco.cidade,30,arq1);
        receber_texto("estado",paciente.endereco.estado,4,arq1);
        receber_numero("CEP",paciente.endereco.cep,12,arq1);
        system("cls");
        printf("\nData de nascimento");
        receber_numero("dia do nascimento",paciente.nascimento.dia,4,arq1);
        receber_numero("mes do nascimento",paciente.nascimento.mes,4,arq1);
        receber_numero("ano do nascimento",paciente.nascimento.ano,6,arq1);
        system("cls");
        int ano_atual = 2021;
        int ano_nascimento = atoi(paciente.nascimento.ano);
         // atoi converte string (texto) para int (numero)
        fflush(stdin);
        int idade = ano_atual - ano_nascimento; // calcula idade

        // transformar idade para idade_em_texto
        char idade_em_texto[4];

        // itoa transformar numero para texto
        itoa(idade, idade_em_texto, 10);

        char tem_comorbidade[4];
        while (1){
            printf("Tem comorbidade [S para sim, N para nao]: ");
            fflush(stdin);
            fgets(tem_comorbidade,4,stdin);

            if ( (toupper(tem_comorbidade[0]) != 'S') &&
                 (toupper(tem_comorbidade[0]) != 'N') ){
                    system("cls");
                    printf("Erro! Digite apenas S ou N\n");
            }else{
                break; // interrompe
            }
        };

        if (toupper(tem_comorbidade[0]) == 'S'){
            receber_texto("as comorbidades",paciente.comorbidade,200, arq1);
        }else{
            strcpy(paciente.comorbidade,"Nao tem comorbidade");
            fprintf(arq1,"Comorbidade: %s",paciente.comorbidade);
        }
        system("cls");
        fclose(arq1); // fecha o arquivo 1

        system("cls");
        printf("\nDados coletados\n");

        printf("Nome: %s\n",paciente.nome);
        printf("CPF: %s\n",paciente.cpf);
        printf("Telefone: %s\n",paciente.telefone);

        printf("\nEndereco\n");
        printf("Rua: %s\n",paciente.endereco.rua);
        printf("Numero: %s\n",paciente.endereco.numero);
        printf("Bairro: %s\n",paciente.endereco.bairro);
        printf("Cidade: %s\n",paciente.endereco.cidade);
        printf("Estado: %s\n",paciente.endereco.estado);
        printf("CEP: %s\n",paciente.endereco.cep);

        printf("Comorbidades: %s\n",paciente.comorbidade);

        printf("\nData nascimento: %s / %s / %s\n",
               paciente.nascimento.dia,paciente.nascimento.mes,paciente.nascimento.ano);
        printf("Idade: %d\n",idade);

        //  caso idade >= 65 anos ou tenha alguma comorbidade
        if ( ( idade >= 65 ) || ( toupper(tem_comorbidade[0]) == 'S') ) {
                printf("\nPaciente no grupo de risco\n");
                strcpy(nome_arquivo,"Controle de pacientes do grupo de risco");
                FILE *arq2;
                do{
                    arq2 = fopen("Controle de pacientes do grupo de risco","w");
                }while(arq2==NULL);
                fprintf(arq2,"CEP: %s\n",paciente.endereco.cep);

                // Transformamos a idade para idade_em_texto pois
                // arquivos leem tudo como texto
                fprintf(arq2,"Idade: %s\n",idade_em_texto);
                fclose(arq2); // fechando arquivo 2
            }
    printf("\n\n");
    } // fim do programa
    system("pause");
    return 0; // para mostrar que o programa rodou corretamente
}
