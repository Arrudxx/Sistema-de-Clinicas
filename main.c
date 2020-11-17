#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <TIME.H>

//variaveis globais
int volta_menu; //variavel global para retornar ao menu


//função para abrir arquivo
FILE* AbreArquivo(char modo, char caminho[30]);
FILE* AbreArquivo(char modo, char caminho[30])
{
    FILE *arquivo;
    switch(modo)
    {
    case 'g':
        arquivo = fopen(caminho,"wt"); //abre o arquivo em modo de gravação
        break;
    case 'l':
        arquivo = fopen(caminho,"rt"); //abre o arquivo em modo de leitura
        break;
    case 'a':
        arquivo = fopen(caminho,"a"); //abre o arquivo em um modo append
        break;
    }
    if(arquivo==NULL)  //Se houver algum erro, o ponteiro apontará para NULL
    {
        printf("Nao foi possivel abrir o arquivo");
        exit(0);
    }
    return arquivo;
}

//void para fechar arquivo
void FecharArquivo(FILE *arquivo);
void FecharArquivo(FILE *arquivo)
{
    fclose(arquivo); //apenas usa a função para fechar o arquivo com o ponteiro arquivo
}

// Função para Cadastrar Feedbacks
void CadastraFeedback(char nome_medico[30], int nota_medico, int nota_atendimento);
void CadastraFeedback(char nome_medico[30], int nota_medico, int nota_atendimento)
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;

    arquivo = AbreArquivo('a', "Listafeedback.txt");//Abre o arquivo Lista de Feedbacks em modo append
    fprintf(arquivo, "%s %d %d \n", nome_medico, nota_medico, nota_atendimento);//Cadastra as variáveis no arquivo texto
    FecharArquivo(arquivo);//fecha arquivo
}

//função para Listar Feedbacks
void ListarFeedback();
void ListarFeedback()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Variáveis e ponteiros
    FILE *arquivo;
    char nome_medico[30];
    int nota_medico;
    int nota_atendimento;

    arquivo = AbreArquivo('l',"ListaFeedback.txt");//Abre o arquivo Lista de Feedbacks em modo leitura
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %d %d",&nome_medico, &nota_medico, &nota_atendimento);//Escaneia todos as tudo que tem e adiciona nas variáveis
        printf("| Nome Do Medico:... %s         |\n| Nota do Medico:............... %d |\n| Nota do atendimento:.......... %d |\n\n",nome_medico, nota_medico, nota_atendimento);//Printa na tela a Lista de Feedback
    }
    FecharArquivo(arquivo);//fecha arquivo

}

//função para Deletar Feedbacks
void DeletarFeedback();
void DeletarFeedback()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;//Ponteiro

    remove("ListaFeedback.txt");//Deleta o arquivo Lista de Feedback
    remove("ListaFeedbackTemp.txt");//Deleta o arquivo Lista de Feedback Temp

    arquivo = AbreArquivo('g', "Listafeedback.txt");//Cria o arquivo Lista de Feedback novamente
    FecharArquivo(arquivo);//Fecha arquivo

    printf("\nFeedbacks Deletados\n\n");//Avisa que os feedbacks foram deletados
}


// função para Agendar consultas
void Agendar(char nome[30], char ult_nome[30], char nome_medico[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], int dia_consulta, int hora_consulta, int minuto_consulta, char especialidade[30], char num_carteira[30], char unidade[20]);
void Agendar(char nome[30], char ult_nome[30], char nome_medico[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], int dia_consulta, int hora_consulta, int minuto_consulta, char especialidade[30], char num_carteira[30], char unidade[20])
{
    //ponteiro
    FILE *arquivo;

    arquivo = AbreArquivo('a', "ListaAgendamento.txt");//Abre o arquivo Lista Agendamento em modo append
    fprintf(arquivo, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//Escreve o foi pedido e estar nas variáveis para o arquivo texto
    FecharArquivo(arquivo);//Fecha arquivo
}

// função para Listar consultas
void ListarAgenda();
void ListarAgenda()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e Variáveis
    FILE *arquivo;
    char nome[50];
    char ult_nome[50];
    char nome_medico[30];
    char numAnterior[50];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char unidade[20];

    arquivo = AbreArquivo('l',"ListaAgendamento.txt");//Abre arquivo Lista Agendamento em modo append
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);//Escaneia todos as tudo que tem e adiciona nas variáveis
        if(strcmp(numAnterior,num_carteira) != 0)//Compara os números de carteira para não dar um bug que aparecer a mesma consulta 2 vezes
        {
            strcpy(numAnterior,num_carteira);//Copia a variavel numAnterior no e cola em numCarteira para não ocorrer o bug que ira repetir 2 vezes a consulta
            printf("|------------------------------------------------------\n|Nome:...................... %s %s\n|Nome Do Medico:............ %s\n|Telefone:.................. %s\n|CPF:....................... %s-%s\n|Dia da Consulta:........... %d\n|Horario da Consulta:....... %d:%d\n|Especialidade:............. %s\n|Nc:........................ %s\n|Unidade:................... %s\n|------------------------------------------------------\n\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//printa todas as informações de agendamento
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
}

//função para pesquisar consulta
void PesquisaAgendamento (char pesquisa_num[30]);
void PesquisaAgendamento (char pesquisa_num[30])
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //ponteiros e variáveis
    FILE *arquivo;
    FILE *arquivoTemp;
    char nome[50];
    char ult_nome[50];
    char telefone[20];
    char nome_medico[30];
    char cpf_sdigito[15];
    char cpf_digito[15];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char numAnterior[50];
    char nomeAnterior[50];
    char unidade[20];
    bool achou = false;//Coloca essa variável em FALSE para ter uma confirmação de deletado mais a frente

    arquivo = AbreArquivo('l', "ListaAgendamento.txt");//Abre o arquivo Lista Agendamento em modo de leitura
    arquivoTemp = AbreArquivo('g', "PesquisaTemp.txt");//Abre o arquivo Lista Agendamento em modo de gravação
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas variáveis
        // Zero = são iguais
        // Diferente de Zero = não são iguais
        if(strcmp(nomeAnterior,nome) != 0)//Compara os nomes para não dar um bug que aparecer a mesma consulta 2 vezes
        {
            strcpy(nomeAnterior,nome);//Copia a variavel nomeAnterior no e cola em nome para não ocorrer o bug que ira repetir 2 vezes a consulta
            if(strcmp(pesquisa_num,num_carteira) == 0)//Compara o número de carteira, se for igual printa no arquivo Temp a linha toda
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//printa a linha que seja igual os parâmetros
            }
            else//Se não ele coloca a variável "achou" em true
            {
                achou = true;
            }
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivo Temp


    arquivo = AbreArquivo('l',"PesquisaTemp.txt");//Abre arquivo Pesquisa Temp em modo leitura

    strcpy(nomeAnterior,"");//Copia nomeAnterior para "NULL" para a variável ficar vazia
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas variáveis

        if(strcmp(nomeAnterior,nome) != 0 && strcmp(pesquisa_num,num_carteira) == 0)//Se nomeAnterior for diferente de nome e pesquisa_num por igual a num_carteira ele irá printa as informações de pesquisa encontrados
        {
            strcpy(nomeAnterior,nome);
            printf("\n|------------------------------------------------------\n|Nome:...................... %s %s\n|Nome Do Medico:............ %s\n|Telefone:.................. %s\n|CPF:....................... %s-%s\n|Dia da Consulta:........... %d\n|Horario da Consulta:....... %d:%d\n|Especialidade:............. %s\n|Nc:........................ %s\n|Unidade:................... %s\n|------------------------------------------------------\n\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
            printf("Consulta(s) encontrado(s) com sucesso!\n\n");
        }
        if(strcmp(pesquisa_num,num_carteira) !=0)//se pesquisa_num for diferente de num_carteira ira printa Usuario não encontrado!
        {
            printf("Usuario não encontrado!\n\n");
        }
    }
}

// função para Deletar consultas //pronta
void DeletarAgendamento(char nomeDeletarAgenda[50], char num_carteiraDeletar[30], int diaDeletar, int horarioDeletar, int minutoDeletar);
void DeletarAgendamento(char nomeDeletarAgenda[50], char num_carteiraDeletar[30], int diaDeletar, int horarioDeletar, int minutoDeletar)
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e Variáveis
    FILE *arquivo;
    FILE *arquivoTemp;
    char nome[50];
    char ult_nome[50];
    char telefone[20];
    char nome_medico[30];
    char cpf_sdigito[15];
    char cpf_digito[15];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char numAnterior[50];
    char unidade[20];
    bool apagou = false;//Coloca essa variável em FALSE para ter uma confirmação de deletado mais a frente

    arquivo = AbreArquivo('l', "ListaAgendamento.txt");//Abre o arquivo Lista Agendamento em modo leitura
    arquivoTemp = AbreArquivo('g', "ListaAgendamentoTemp.txt");//Abre o arquivo Lista Agendamento em modo gravação

    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas variáveis
        // Zero = são iguais
        // Diferente de Zero = não são iguais
        if(strcmp(numAnterior,num_carteira) != 0))//Compara os nomes para não dar um bug que deleta 2 consultas
        {
            strcpy(numAnterior,num_carteira);//Copia a variavel numAnterior no e cola em num_carteira para não ocorrer o bug descrito acima
            if(strcmp(nomeDeletarAgenda,nome) != 0 && strcmp(num_carteiraDeletar,num_carteira) != 0 && diaDeletar != dia_consulta && horarioDeletar != hora_consulta && minutoDeletar != minuto_consulta)//compara os parâmetros do If para confirmar se é a consulta certa antes de apagar
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//printa todas as consulta menos a que o usuario deseja apagar em Pesquisa Agendamento Temp
            }
            else
            {
                apagou = true;//se der algum erro apagou vira True
            }
        }
    }
    FecharArquivo(arquivo);//fecha arquivo
    FecharArquivo(arquivoTemp);//fecha arquivo Temp

    arquivo = AbreArquivo('g', "ListaAgendamento.txt");//Abre arquivo Lista Agendamento em modo gravação
    arquivoTemp = AbreArquivo('l', "ListaAgendamentoTemp.txt");//Abre arquivo Lista Agendamento em modo de leitura

    strcpy(numAnterior,"");//Copia numAnterior para "NULL" para a variável ficar vazia

    while(!feof(arquivoTemp))//Usa o loop para ler o arquivo todo com o ponteiro *arquivoTemp
    {
        fscanf(arquivoTemp,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);
        if(strcmp(numAnterior,num_carteira))
        {
            strcpy(numAnterior,num_carteira);
            fprintf(arquivo, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
        }
    }

    FecharArquivo(arquivo);
    FecharArquivo(arquivoTemp);

    if(apagou)
    {
        printf("Agendamento de Consulta apagada com sucesso!\n\n");
    }
    else
    {
        printf("Usuario não encontrado!\n\n");

    }
}


//função cadastra conveniado //pronta
void Cadastra(char nome[30], char ult_nome[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], char rg[15], int nascimento, char email[40], char num_carteira[30]);
void Cadastra(char nome[30], char ult_nome[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], char rg[15], int nascimento, char email[40], char num_carteira[30])
{

    FILE *arquivo;
    arquivo = AbreArquivo('a', "ListaCadastro.txt");
    fprintf(arquivo, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
    FecharArquivo(arquivo);
}

//função para listar conveniados //pronta
void Listar();
void Listar()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR

    FILE *arquivo;
    char nome[50];
    char ult_nome[50];
    char nomeAnterior[50];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    char rg[15];
    int nascimento;
    char email[40];
    char num_carteira[30];

    printf("LISTA DE CONVENIADOS");
    arquivo = AbreArquivo('l',"ListaCadastro.txt");
    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
        if(strcmp(nomeAnterior,nome) != 0)
        {
            strcpy(nomeAnterior,nome);
            printf("\n|------------------------------------------------------\n|Nome:............. %s %s\n|Telefone:......... %s\n|CPF:.............. %s-%s\n|RG:............... %s\n|Nascimento:....... %d\n|Email:............ %s\n|Nc:............... %s\n|------------------------------------------------------\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
        }
    }
    FecharArquivo(arquivo);
}

//função para pesquisar conveniado
void PesquisaConveniado (char pesquisa_nome[50]);
void PesquisaConveniado (char pesquisa_nome[50])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR

    FILE *arquivo;
    FILE *arquivoTemp;

    char nome[50];
    char ult_nome[50];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    char rg[15];
    int nascimento;
    char email[40];
    char num_carteira[30];
    char numAnterior[50];
    bool achou = false;

    arquivo = AbreArquivo('l', "ListaCadastro.txt");
    arquivoTemp = AbreArquivo('g', "PesquisaTemp.txt");

    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
        // Zero = são iguais
        // Diferente de Zero = não são iguais
        if(strcmp(numAnterior,num_carteira) != 0)
        {
            strcpy(numAnterior,num_carteira);
            if(strcmp(pesquisa_nome,nome) == 0)
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            }
            else
            {
                achou = true;
            }
        }
    }
    FecharArquivo(arquivo);
    FecharArquivo(arquivoTemp);


    arquivo = AbreArquivo('l',"PesquisaTemp.txt");

    strcpy(numAnterior,"");
    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
        if(strcmp(numAnterior,num_carteira) != 0 && strcmp(pesquisa_nome,nome) == 0)
        {
            strcpy(numAnterior,num_carteira);
            printf("\n\n|------------------------------------------------------\n|Nome:............. %s %s\n|Telefone:......... %s\n|CPF:.............. %s-%s\n|RG:............... %s\n|Nascimento:....... %d\n|Email:............ %s\n|Nc:............... %s\n|------------------------------------------------------\n\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            printf("Usuario encontrado com sucesso!\n\n");
        }
        if(strcmp(pesquisa_nome,nome) !=0)
        {
            printf("Usuario não encontrado!\n\n");
        }
    }
}

//função para deletar conveniado
void Deletar(char num_Deletar[50]);
void Deletar(char num_Deletar[50])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;
    FILE *arquivoTemp;
    char nome[50];
    char ult_nome[50];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    char rg[15];
    int nascimento;
    char email[40];
    char num_carteira[30];
    char nomeAnterior[50];
    bool apagou = false;

    arquivo = AbreArquivo('l', "ListaCadastro.txt");
    arquivoTemp = AbreArquivo('g', "ListaCadastroTemp.txt");

    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
        // Zero = são iguais
        // Diferente de Zero = não são iguais
        if(strcmp(nomeAnterior,nome) != 0)
        {
            strcpy(nomeAnterior,nome);
            if(strcmp(num_Deletar,num_carteira) != 0)
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            }
            else
            {
                apagou = true;
            }
        }
    }
    FecharArquivo(arquivo);
    FecharArquivo(arquivoTemp);
    arquivo = AbreArquivo('g', "ListaCadastro.txt");
    arquivoTemp = AbreArquivo('l', "ListaCadastroTemp.txt");

    strcpy(nomeAnterior,"");

    while(!feof(arquivoTemp))
    {
        fscanf(arquivoTemp,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
        if(strcmp(nomeAnterior,nome) != 0)
        {
            strcpy(nomeAnterior,nome);
            fprintf(arquivo, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
        }
    }

    FecharArquivo(arquivo);
    FecharArquivo(arquivoTemp);

    if(apagou)
    {
        printf("Conveniado deletado com sucesso!\n\n");
    }
    else
    {
        printf("Conveniado não encontrado!\n\n");
    }
}


//função para cadastrar Atendimento
void CadastraUserGeral(char login[30], char senha[30], char permissao[30]);
void CadastraUserGeral(char login[30], char senha[30], char permissao[30])
{

    FILE *arquivo;

    arquivo = AbreArquivo('a', "SistemadeLoginGeral.txt");
    fprintf(arquivo, "%s %s %s \n", login, senha, permissao);
    FecharArquivo(arquivo);
}

//função para deletar o usuario na sessão de atendimento
void DeletarUserGeral(char deletarlogin[30]);
void DeletarUserGeral(char deletarlogin[30])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;
    FILE *arquivoTemp;

    char login [30];
    char senha[30];
    char permissao[30];
    char verificalogin[30];
    char verificasenha[30];
    char loginAnterior[30];
    bool apagou = false;

    arquivo = AbreArquivo('l', "SistemadeLoginGeral.txt");
    arquivoTemp = AbreArquivo('g', "SistemadeLoginGeralTemp.txt");

    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s %s %s", &login, &senha, &permissao);
        // Zero = são iguais
        // Diferente de Zero = não são iguais
        if(strcmp(loginAnterior,login) != 0)
        {
            strcpy(loginAnterior,login);
            if(strcmp(deletarlogin,login) != 0)
            {
                fprintf(arquivoTemp, "%s %s %s\n", login, senha, permissao);
            }
            else
            {
                apagou = true;
            }
        }
    }
    FecharArquivo(arquivo);
    FecharArquivo(arquivoTemp);
    arquivo = AbreArquivo('g', "SistemadeLoginGeral.txt");
    arquivoTemp = AbreArquivo('l', "SistemadeLoginGeralTemp.txt");

    strcpy(loginAnterior,"");

    while(!feof(arquivoTemp))
    {
        fscanf(arquivoTemp,"%s %s %s", &login, &senha, &permissao);
        if(strcmp(loginAnterior,login) != 0)
        {
            strcpy(loginAnterior,login);
            fprintf(arquivo, "%s %s %s\n", login, senha, permissao);
        }
    }

    FecharArquivo(arquivo);
    FecharArquivo(arquivoTemp);

    if(apagou)
    {
        printf("Usuario deletado com sucesso!\n\n");
    }
    else
    {
        printf("Usuario não encontrado!\n\n");

    }
}

void ListarUserGeral();
void ListarUserGeral()
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR

    FILE *arquivo;
    char login[30];
    char senha[30];
    char permissao[30];
    char nomeAnterior[50];

    printf("LISTA DE USUARIOS\n");

    arquivo = AbreArquivo('l',"SistemadeLoginGeral.txt");
    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s %s %s", &login, &senha, &permissao);
        if(strcmp(nomeAnterior,login) != 0)
        {
            strcpy(nomeAnterior,login);
            printf("\n|------------------------------------------------------\n|Nome:............. %s \n|Senha:............. %s \n|Permissão:............. %s", login, senha, permissao);
        }
    }
    FecharArquivo(arquivo);
}

//função para cadastrar consulta no faturamento
void CadastraRelatorioFaturamento(char nome[30], char ult_nome[30], char num_carteira[30], int gasto_consulta, int dia_consulta, int mes_consulta, int ano_consulta);
void CadastraRelatorioFaturamento(char nome[30], char ult_nome[30], char num_carteira[30], int gasto_consulta, int dia_consulta, int mes_consulta, int ano_consulta)
{

    FILE *arquivo;
    arquivo = AbreArquivo('a', "Relatorio.txt");
    fprintf(arquivo, "%s %s %s %d %d %d %d\n", nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta);
    FecharArquivo(arquivo);

}

//função para listar o faturamento
void ListarRelatorioFaturamento();
void ListarRelatorioFaturamento()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;
    char nome[50];
    char ult_nome[50];
    char numAnterior[30];
    char num_carteira[30];
    int gasto_consulta;
    int dia_consulta;
    int mes_consulta;
    int ano_consulta;

    printf("\nFaturamento Mensal: \n");

    arquivo = AbreArquivo('l',"Relatorio.txt");
    while(!feof(arquivo))
    {
        fscanf(arquivo,"%s %s %s %d %d %d %d", &nome, &ult_nome, &num_carteira, &gasto_consulta, &dia_consulta, &mes_consulta, &ano_consulta);
        printf("|Nome: \t\tNC: \t   Gastos do paciente:   data: \n|%s %s  |  %s |  %d                | %d/%d/%d \n\n", nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta);
    }
    FecharArquivo(arquivo);
}

int volta_menu_login();
int volta_menu_login()
{

    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    do
    {
        printf("Digite 0 para sair para o menu: ");
        scanf("%d", &volta_menu);

        if(volta_menu == 0)
        {
            system("cls");
            return main();
        }
        else
        {
            system("cls");
            printf("\nOpção Invalida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 0);
}

int volta_menu_antedimento();
int volta_menu_antedimento()
{

    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    do
    {
        printf("Digite 1 para retornar ao menu: ");
        scanf("%d", &volta_menu);

        if(volta_menu == 1)
        {
            return principal_atendente();
        }
        else
        {
            printf("\nOpção Invalida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

int volta_menu_medico();
int volta_menu_medico()
{

    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    do
    {
        printf("Digite 1 para retornar ao menu: ");
        scanf("%d", &volta_menu);

        if(volta_menu == 1)
        {
            return principal_medico();
        }
        else
        {
            printf("\nOpção Invalida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

int volta_menu_conveniado();
int volta_menu_conveniado()
{

    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    do
    {
        printf("Digite 1 para retornar ao menu: ");
        scanf("%d", &volta_menu);

        if(volta_menu == 1)
        {
            return principal_conveniado();
        }
        else
        {
            printf("\nOpção Invalida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

int volta_menu_adm();
int volta_menu_adm()
{

    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    do
    {
        printf("\nDigite 1 para retornar ao menu: ");
        scanf("%d", &volta_menu);

        if(volta_menu == 1)
        {
            return principal_adm();
        }
        else
        {
            printf("\nOpção Invalida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

//função para logar Atendimento //pronta
void sistemadeloginGeral();
void sistemadeloginGeral()
{
    FILE *arquivo;
    char login [30];
    char senha[30];
    char permissao[30];
    char verificalogin[30];
    char verificasenha[30];
    bool achou = false;

    do
    {
        printf("Digite seu login: ");
        setbuf(stdin,NULL);
        gets(verificalogin);
        printf("\nDigite sua senha: ");
        setbuf(stdin,NULL);
        gets(verificasenha);


        arquivo = AbreArquivo('l',"SistemadeLoginGeral.txt");
        while(!feof(arquivo))
        {
            fscanf(arquivo, "%s %s %s", &login, &senha, &permissao);
            if(strcmp(verificalogin, login) == 0 && strcmp(verificasenha, senha) == 0)
            {
                achou = true;
                if(strcmp(permissao, "Medico") == 0 )
                {
                    printf("Bem vindo Doutor (a).");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(2);
                    system("cls");
                    principal_medico();
                }

                if(strcmp(permissao, "Atendente") == 0 )
                {
                    principal_atendente();
                    printf("Bem vindo Atendente");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(2);
                    system("cls");
                }

                if(strcmp(permissao, "Administrador") == 0 )
                {
                    printf("Bem vindo Administrador");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(2);
                    system("cls");
                    principal_adm();
                }

            }
            else
            {
                printf("Caso Esqueceu seu login ou senha entre em contato com o administrador\nd4niel.arruda@gmail.com\n\nESPERE\n");
                sleep(2);
                system("cls");
            }
        }

    }
    while(!achou);
    FecharArquivo(arquivo);

}

//tela de menu do atendimento e suas funções
void principal_atendente();
void principal_atendente()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //variaveis
    int escolha_tela_atendente;
    char nome[30];
    char nome_medico[30];
    char ult_nome[30];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    char rg[15];
    int nascimento;
    char email[40];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char unidade[20];
    //variaveis

    system("cls");
    printf("\n\t\tMENU");
    printf("\n");
    printf("\t ------------------------------------------");
    printf("\n\t| 1 - Cadastrar conveniado                 |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 2 - Listar conveniados                   |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 3 - Pesquisar conveniados                |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 4 - Deletar cadastro                     |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 5 - Agendar Consulta                     |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 6 - Listar Consultas                     |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 7 - Pesquisar Consultas                  |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 8 - Deletar Consultas                    |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 9 - Situação dos feedbacks               |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 10 - Deletar feedbacks                   |\n");
    printf("\t|------------------------------------------");
    printf("\n\t| 11 - Relatorios de faturamento  e tabela |\n");
    printf("\t ------------------------------------------");
    printf("\n\t| 0 - Sair                                 |\n");
    printf("\t ------------------------------------------");


    printf("\nDigite uma opcao: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_atendente);

    sleep(1);
    system("cls");//limpa a tela

    switch (escolha_tela_atendente)
    {
    case 1:
        //Cadastrar conveniado

        printf("\nDigite o nome: ");
        setbuf(stdin,NULL);
        gets(nome);
        printf("\nDigite o ultimo nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite o telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite os 9 primeiros numero do seu CPF sem ponto ou traço: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os ultimos 2 numeros do seu CPF: ");
        setbuf(stdin,NULL);
        gets(cpf_digito);
        printf("\nDigite o RG: ");
        setbuf(stdin,NULL);
        gets(rg);
        printf("\nDigite o Nascimento: ");
        scanf("%d", &nascimento);
        printf("\nDigite o Email: ");
        setbuf(stdin,NULL);
        gets(email);
        printf("\nDigite o numero da carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteira);
        Cadastra(nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
        volta_menu_antedimento();
        break;

    case 2:
        //Listar conveniados
        Listar();
        volta_menu_antedimento();
        break;

    case 3:
        //pesquisar conveniado
        ;
        char pesquisa_nome[50];

        printf("\nDigite o nome do conveniado que deseja procurar: ");
        setbuf(stdin,NULL);
        gets(pesquisa_nome);
        PesquisaConveniado(pesquisa_nome);
        volta_menu_antedimento();
        break;

    case 4:
        ;//por causa do char precisa dar esse ";"
        //Deletar cadastro

        char num_Deletar[50];
        printf("\nDigite o numero de carteira do conveniado que deseja deletar: ");
        setbuf(stdin,NULL);
        gets(num_Deletar);
        Deletar(num_Deletar);
        volta_menu_antedimento();
        break;

    case 5:
        //cadastrar agenadamento
        printf("\nDigite o nome: ");
        setbuf(stdin,NULL);
        gets(nome);
        printf("\nDigite o ultimo nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite o telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite o nome do medico: ");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite os 9 primeiros numero do seu CPF sem ponto ou traço: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os ultimos 2 numeros do seu CPF: ");
        setbuf(stdin,NULL);
        gets(cpf_digito);
        printf("\nDigite o dia, mês e ano da consulta sem barra: ");
        scanf("%d", &dia_consulta);
        printf("\nDigite a hora da consulta: ");
        scanf("%d", &hora_consulta);
        printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", hora_consulta);
        scanf("%d", &minuto_consulta);
        printf("\nDigite a especialidade da consulta: ");
        setbuf(stdin,NULL);
        gets(especialidade);
        printf("\nDigite o numero da carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteira);
        printf("\n| Paz | Cancioneiro | Paulista |");
        printf("\nDigite a o nome da unidade: ");
        setbuf(stdin,NULL);
        gets(unidade);
        Agendar(nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
        volta_menu_antedimento();
        break;

    case 6:
        //listar agendamentos
        ListarAgenda();
        volta_menu_antedimento();
        break;

    case 7:
        //pesquisa agendamento
        ;
        char pesquisa_num[30];

        printf("\nDigite o numero de carteirinha do paciente para vê as consultas do conveniado: ");
        setbuf(stdin,NULL);
        gets(pesquisa_num);
        PesquisaAgendamento(pesquisa_num);
        volta_menu_antedimento();
    case 8:
        //deletar agendamentos
        ;
        char nomeDeletar[50];
        char nomeDeletarAgenda[50];
        char num_carteiraDeletar[30];
        int diaDeletar;
        int horarioDeletar;
        int minutoDeletar;

        printf("\nDigite um nome: ");
        setbuf(stdin,NULL);
        gets(nomeDeletar);
        printf("\nDigite o numero de carterinha: ");
        setbuf(stdin,NULL);
        gets(num_carteiraDeletar);
        printf("\nDigite o dia, mês e ano da consulta sem barra: ");
        scanf("%d", &diaDeletar);
        printf("\nDigite a hora da sua consulta: ");
        scanf("%d", &horarioDeletar);
        printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", hora_consulta);
        scanf("%d", &minutoDeletar);
        DeletarAgendamento(nomeDeletarAgenda, num_carteiraDeletar, diaDeletar, horarioDeletar, minutoDeletar);
        volta_menu_antedimento();
        break;

    case 9:
        //listar feedbacks
        ListarFeedback();
        volta_menu_antedimento();
        break;

    case 10:
        //excluir feedbacks
        ;
        int excluir_feedback;

        printf("Para não haver manipulção dos feedbacks a função deletar feedback excluir todos os feedbacks de uma vez.\n\n");
        printf("Se tive certeza disso digite 1 se não digite 0 para voltar ao menu: ");
        scanf("%d", &excluir_feedback);


        if(excluir_feedback == 1)
        {
            DeletarFeedback();
        }
        else
        {
            volta_menu_antedimento();
        }
        break;

    case 11:
        ;
        //menu com relatorios
        int escolha_menu_relatorio;

        printf("\n\t\tRelatorios de faturamento");
        printf("\n");
        printf("\t ---------------------------------------------");
        printf("\n\t| 1 - Adicionar faturamento no relatorio    |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 2 - Listar Faturamento                    |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 3 - Tabela de Preço de Consultas e Exames |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 0 - Sair                                  |\n");
        printf("\t|---------------------------------------------");

        printf("\nDigite uma opcao: ");
        sleep(0,5);
        sleep(0,5);//pausa a tela por x segundos
        scanf("%d", &escolha_menu_relatorio);

        sleep(1);
        system("cls");//limpa a tela

        switch (escolha_menu_relatorio)
        {
        case 1:
            ;
            //Cadastrar relatorio

            char nome[30];
            char ult_nome[30];
            char num_carteira[30];
            int gasto_consulta;
            int dia_consulta;
            int mes_consulta;
            int ano_consulta;

            printf("\nDigite o nome do conveniado: ");
            setbuf(stdin,NULL);
            gets(nome);
            printf("\nDigite o ultimo nome do conveniado: ");
            setbuf(stdin,NULL);
            gets(ult_nome);
            printf("\nDigite o numero da carteirinha: ");
            setbuf(stdin,NULL);
            gets(num_carteira);
            printf("\nDigite o gasto da consulta hoje: ");
            scanf("%d", &gasto_consulta);
            printf("\nDigite o dia da consulta: ");
            scanf("%d", &dia_consulta);
            printf("\nDigite o mês da consulta: ");
            scanf("%d", &mes_consulta);
            printf("\nDigite o ano da consulta: ");
            scanf("%d", &ano_consulta);
            CadastraRelatorioFaturamento(nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta);
            volta_menu_antedimento();
            break;

        case 2:
            //Listar conveniados
            ListarRelatorioFaturamento();
            volta_menu_antedimento();
            break;

        case 3:
            printf("TABELA DE CONSULTAS E EXAMES\n\n");
            printf("|------------------------------------------------------------------\n");
            printf("|Consulta Com Clinico Geral:......................... R$ 50,00\n\n");
            printf("|Consulta Com Especialistas:......................... R$ 90,00\n\n");
            printf("|Hemograma Completo:................................. R$ 75,00\n\n");
            printf("|Raio X:............................................. R$ 40,00\n\n");
            printf("|Raio X Panorâmico:.................................. R$ 40,00\n\n");
            printf("|Ressonância Magnética Mama:......................... R$ 300,00\n\n");
            printf("|Ressonância Magnética Próstata:..................... R$ 320,00\n\n");
            printf("|Ultrasson Mamas:.................................... R$ 55,00\n\n");
            printf("|Ultrasson Próstata Abdominal:....................... R$ 55,00\n\n");
            printf("|Ultrasson Próstata Transretal:...................... R$ 65,00\n\n");
            printf("|Urografia Venosa Excretora:......................... R$ 160,00\n\n");
            printf("|Urografia Venosa Minutada:.......................... R$ 220,00\n");
            printf("|-------------------------------------------------------------------\n");

            volta_menu_antedimento();

            break;
        case 0:
            //volta ao menu de Atendimento
            volta_menu_antedimento();
            break;

        default:
            printf("Opção incorreta\n");
            sleep(1,25);
            volta_menu_antedimento();
            break;
        }
        break;

    case 0:
        //volta ao menu de login
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\n\nOpcao invalida! Tente Novamente!\n\n");
        sleep(1,5);
        volta_menu_antedimento();
        break;
    }



}

//tela de menu do conveniado e suas funções
void principal_conveniado();
void principal_conveniado()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    int escolha_tela_conveniado;
    char nome[30];
    char nome_medico[30];
    char ult_nome[30];
    char telefone[20];
    char cpf_sdigito[15];
    char cpf_digito[15];
    int dia_consulta;
    int hora_consulta;
    int minuto_consulta;
    char especialidade[30];
    char num_carteira[30];
    char unidade[20];

    system("cls");
    printf("\n\t\tMENU");
    printf("\n");

    printf("\t|-----------------------------");
    printf("\n\t| 1 -  Agendar Consulta       |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 2 - Listar Suas Consultas   |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 3 - Deletar Suas consultas  |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 4 - Dar um feedback         |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 5 - Nossos Endereços        |\n");
    printf("\t| -----------------------------");
    printf("\n\t| 0 - Sair                    |\n");
    printf("\t|-----------------------------");

    printf("\nDigite uma opcao: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_conveniado);

    sleep(1);
    system("cls");//limpa a tela

    switch(escolha_tela_conveniado)
    {
    case 1:
        printf("\nDigite seu primeiro nome: ");
        setbuf(stdin,NULL);
        gets(nome);
        printf("\nDigite seu ultimo nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite seu telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite o nome do medico");
        printf("(Andre) (Osvaldo) (Luis):");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite os 9 primeiros numero do seu CPF sem ponto ou traço: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os ultimos 2 numeros do seu CPF: ");
        setbuf(stdin,NULL);
        gets(cpf_digito);
        printf("\nDigite o dia, mês e ano que você deseja marcar a consulta sem barra: ");
        scanf("%d", &dia_consulta);
        printf("\nDigite o horario que você deseja para a sua consulta: ");
        scanf("%d", &hora_consulta);
        printf("\nHorario: %d:00 \nDigite o minuto que você deseja para a sua consulta: ", hora_consulta);
        scanf("%d", &minuto_consulta);
        printf("\nDigite a especialidade da consulta: ");
        setbuf(stdin,NULL);
        gets(especialidade);
        printf("\nDigite o numero da carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteira);
        printf("\n| Paz | Cancioneiro | Paulista |");
        printf("\nDigite a o nome da unidade: ");
        setbuf(stdin,NULL);
        gets(unidade);
        Agendar(nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
        volta_menu_conveniado();
        break;

    case 2:
        //pesquisa agendamento
        ;
        char pesquisa_num[30];

        printf("\nDigite o numero de carteirinha para vê suas consultas: ");
        setbuf(stdin,NULL);
        gets(pesquisa_num);
        PesquisaAgendamento(pesquisa_num);
        volta_menu_conveniado();
        break;

    case 3:
        //deletar agendamentos
        ;
        char nomeDeletar[50];
        char nomeDeletarAgenda[50];
        char num_carteiraDeletar[30];
        int diaDeletar;
        int horarioDeletar;
        int minutoDeletar;

        printf("\nDigite um nome: ");
        setbuf(stdin,NULL);
        gets(nomeDeletar);
        printf("\nDigite o numero de carterinha: ");
        setbuf(stdin,NULL);
        gets(num_carteiraDeletar);
        printf("\nDigite o dia, mês e ano da consulta sem barra: ");
        scanf("%d", &diaDeletar);
        printf("\nDigite o hora da sua consulta: ");
        scanf("%d", &horarioDeletar);
        printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", horarioDeletar);
        scanf("%d", &minutoDeletar);
        DeletarAgendamento(nomeDeletarAgenda, num_carteiraDeletar, diaDeletar, horarioDeletar, minutoDeletar);
        volta_menu_conveniado();
        break;

    case 4:
        ;
        char nome_medico[30];
        int nota_medico;
        int nota_atendimento;

        printf("\nDigite o nome do medico");
        printf("(Andre) (Osvaldo) (Luis): ");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite uma nota de 0 a 10 para o atendimento de seu medico: ");
        scanf("%d", &nota_medico);
        printf("\nDigite uma nota de 0 a 10 para seu atendimento em geral: ");
        scanf("%d", &nota_atendimento);
        printf("Muito Obrigado pelo seu Feedback :)\n\n");
        CadastraFeedback(nome_medico, nota_medico, nota_atendimento);
        volta_menu_conveniado();

        break;

    case 5:
        printf("Onde você pode nos encontrar :)\n");

        printf("\n|----------------------------------------------------------------------------------------------|\n");
        printf("|   CLINICA PRINCIPAL: R. da Paz, 797 - Chácara Santo Antônio, São Paulo - SP, 04713-000\n");
        printf("|   Tel.: (11) 5181-4055 \n");
        printf("|----------------------------------------------------------------------------------------------|\n");

        printf("|   2° CLINICA: Rua Cancioneiro Popular, 210 - Chácara Santo Antônio São Paulo - SP, 04710-000\n");
        printf("|   Tel.: (11) 2114-4000 \n");
        printf("|----------------------------------------------------------------------------------------------|\n");

        printf("|   Av. Paulista, 900 - Cerqueira César São Paulo - SP CEP 01310-100\n");
        printf("|   Tel.: (11) 3170-3700 \n");
        printf("|----------------------------------------------------------------------------------------------|\n\n");

        volta_menu_conveniado();
        break;

    case 0:
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\n\nOpcao invalida! Tente Novamente!\n\n");
        sleep(1,5);
        volta_menu_conveniado();
        break;
    }
}

//tela de menu do administrador e suas funções
void principal_adm();
void principal_adm()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    char login[30];
    char senha[30];
    char permissao[30];
    int escolha_tela_adm;
    //MENU PRINCIPAL

    system("cls");
    printf("\n\t\tMENU");
    printf("\n");

    printf("\t|-----------------------------");
    printf("\n\t| 1 - Adicionar Usuarios      |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 2 - Listar Usuarios         |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 3 - Deletar Usuarios        |\n");
    printf("\t -----------------------------");
    printf("\n\t| 0 - Sair                    |\n");
    printf("\t -----------------------------");


    printf("\nDigite uma opcao: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_adm);

    sleep(1);
    system("cls");//limpa a tela

    switch (escolha_tela_adm)
    {
    case 1:
        printf("Digite o nome do novo usuario: ");
        setbuf(stdin,NULL);
        gets(login);
        printf("\nDigite a Senha do novo usuario: ");
        setbuf(stdin,NULL);
        gets(senha);
        printf("\nDigite o tipo de Permissão que desejar dar ao usuario");
        printf("\n(Administador) (Medico) (Atendimento) (Conveniado)");
        printf(": ");
        setbuf(stdin,NULL);
        gets(permissao);
        CadastraUserGeral(login, senha, permissao);
        volta_menu_adm();
        break;

    case 2:
        ListarUserGeral();
        volta_menu_adm();
        break;

    case 3:
        ;
        char deletarlogin[30];
        printf("\nDigite o nome do usuario que deseja deletar: ");
        setbuf(stdin,NULL);
        gets(deletarlogin);
        DeletarUserGeral(deletarlogin);
        volta_menu_adm();
        break;

    case 0:
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\n\nOpcao invalida! Tente Novamente!\n\n");
        sleep(1,5);
        volta_menu_adm();
        break;
    }
}

//tela de menu do medico e suas funções
void principal_medico();
void principal_medico()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    int escolha_tela_medico;

    system("cls");
    printf("\n\t\tMENU");
    printf("\n");

    printf("\t|--------------------------------------");
    printf("\n\t| 1 - Pesquisar Agendamento            |\n");
    printf("\t|--------------------------------------");
    printf("\n\t| 2 - Listar conveniados               |\n");
    printf("\t| -------------------------------------");
    printf("\n\t| 3 - Pesquisar conveniado             |\n");
    printf("\t|--------------------------------------");
    printf("\n\t| 0 - Sair                             |\n");
    printf("\t| -------------------------------------\n");

    printf("\nDigite uma opcao: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_medico);

    sleep(1);
    system("cls");//limpa a tela

    switch (escolha_tela_medico)
    {
    case 1:
        ;
        char pesquisa_num[30];

        printf("\nDigite o numero de carteirinha do paciente para vê suas consultas: ");
        setbuf(stdin,NULL);
        gets(pesquisa_num);
        PesquisaAgendamento(pesquisa_num);
        volta_menu_medico();
        break;

    case 2:
        //Listar conveniados
        Listar();
        volta_menu_medico();
        break;

    case 3:
        //pesquisar conveniado
        ;
        char pesquisa_nome[50];

        printf("\nDigite o nome do conveniado que deseja procurar: ");
        setbuf(stdin,NULL);
        gets(pesquisa_nome);
        PesquisaConveniado(pesquisa_nome);
        volta_menu_medico();
        break;

    case 0:
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\nOpção incorreta\n");
        sleep (1,2);
        principal_medico();
        break;
    }




}


int main ()
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR

    int login_escolha; // variavel usada no int main para escolher usuario
    int login_menu;

    printf("\n");
    printf("\t\t\t\t\t\t*!Bem vindo!*\n\n");
    printf("DATA : %s\n\n\n",__DATE__);
    sleep(1);

    printf("\n\t\t\t\t\t\t  | Usuarios | \t\t");
    printf("\n\t\t__________________________________________________________________________________\n\n");
    printf("\t\t|       0-Sair \t\t\t  1-Conveniado \t\t\t2-Usuários       |\n");
    printf("\t\t__________________________________________________________________________________\n\n");

    printf("\nEscolha um opção por favor --> ");

    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &login_escolha);
    sleep(1);
    system("cls");//limpa a tela


    switch(login_escolha)
    {
    case 0:
        return 0;
        break;

    case 1:
        printf("Bem vindo Conveniado");
        sleep(2);
        system("cls");
        printf("Carregando...");
        sleep(2);
        system("cls");
        principal_conveniado();

    case 2:
        sistemadeloginGeral();
        break;
    default:
        printf("opção incorreta");
        sleep(1,25);
        system("cls");
    }
    return 0;
}
