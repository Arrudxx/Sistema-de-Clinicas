#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <TIME.H>

//variaveis globais
int volta_menu; //variável global para retornar ao menu


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
        printf("Nao foi possível abrir o arquivo");
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
        printf("| Nome Do Médico:... %s         |\n| Nota do Médico:............... %d |\n| Nota do atendimento:.......... %d |\n\n",nome_medico, nota_medico, nota_atendimento);//Printa na tela a Lista de Feedback
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
            strcpy(numAnterior,num_carteira);//Copia a variável numAnterior no e cola em numCarteira para não ocorrer o bug que ira repetir 2 vezes a consulta
            printf("|------------------------------------------------------\n|Nome:...................... %s %s\n|Nome Do Médico:............ %s\n|Telefone:.................. %s\n|CPF:....................... %s-%s\n|Dia da Consulta:........... %d\n|Horário da Consulta:....... %d:%d\n|Especialidade:............. %s\n|Nc:........................ %s\n|Unidade:................... %s\n|------------------------------------------------------\n\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//printa todas as informações de agendamento
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
            strcpy(nomeAnterior,nome);//Copia a variável nomeAnterior no e cola em nome para não ocorrer o bug que ira repetir 2 vezes a consulta
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

    strcpy(nomeAnterior,"");//Copia nomeAnterior para "" para a variável ficar vazia
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas variáveis

        if(strcmp(nomeAnterior,nome) != 0 && strcmp(pesquisa_num,num_carteira) == 0)//Se nomeAnterior for diferente de nome e pesquisa_num por igual a num_carteira ele irá printa as informações de pesquisa encontrados
        {
            strcpy(nomeAnterior,nome);
            printf("\n|------------------------------------------------------\n|Nome:...................... %s %s\n|Nome Do Médico:............ %s\n|Telefone:.................. %s\n|CPF:....................... %s-%s\n|Dia da Consulta:........... %d\n|Horário da Consulta:....... %d:%d\n|Especialidade:............. %s\n|Nc:........................ %s\n|Unidade:................... %s\n|------------------------------------------------------\n\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
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
        if(strcmp(numAnterior,num_carteira) != 0)//Compara os nomes para não dar um bug que deleta 2 consultas
        {
            strcpy(numAnterior,num_carteira);//Copia a variável numAnterior no e cola em num_carteira para não ocorrer o bug descrito acima
            if(strcmp(nomeDeletarAgenda,nome) != 0 && strcmp(num_carteiraDeletar,num_carteira) != 0 && diaDeletar != dia_consulta && horarioDeletar != hora_consulta && minutoDeletar != minuto_consulta)//compara os parâmetros do If para confirmar se é a consulta certa antes de apagar
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//printa todas as consulta menos a que o usuário deseja apagar em Pesquisa Agendamento Temp
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
        fscanf(arquivoTemp,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);//Escaneia tudo que estar em Lista Agendamento e joga nas variáveis
        if(strcmp(numAnterior,num_carteira))//Compara numAnterior com num_carteira
        {
            strcpy(numAnterior,num_carteira);//Copia a variável numAnterior no e cola em num_carteira
            fprintf(arquivo, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);//Printa todas as consultas menos a que foi deletada
        }
    }

    FecharArquivo(arquivo);//Fecha Arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivoTemp

    if(apagou)//Se apagou virou true ele irá printar que o a consulta foi apagada com sucesso
    {
        printf("Agendamento de Consulta apagada com sucesso!\n\n");
    }
    else//Se apagou for falso ele irá printar que o conveniado não foi encontrado
    {
        printf("Conveniado não encontrado!\n\n");

    }
}

//função cadastra conveniado
void Cadastra(char nome[30], char ult_nome[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], char rg[15], int nascimento, char email[40], char num_carteira[30]);
void Cadastra(char nome[30], char ult_nome[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], char rg[15], int nascimento, char email[40], char num_carteira[30])
{
    //Ponteiros
    FILE *arquivo;

    arquivo = AbreArquivo('a', "ListaCadastro.txt");//Abre o arquivo Lista Cadastro em modo de append
    fprintf(arquivo, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);//Escreve o foi pedido e estar nas variáveis para o arquivo texto
    FecharArquivo(arquivo);//Fecha arquivo
}

//função para listar conveniados //pronta
void Listar();
void Listar()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e variáveis
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
    arquivo = AbreArquivo('l',"ListaCadastro.txt");//Abre o arquivo Lista Cadastro em modo de leitura
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que tem e adiciona nas variáveis
        if(strcmp(nomeAnterior,nome) != 0)//Compara o nomeAnterior com o nome para não dar um bug que aparecer o mesmo conveniado 2 vezes
        {
            strcpy(nomeAnterior,nome);//Copia a variável nomeAnteiror e cola em nome para não ocorrer o bug que ira repetir 2 vezes a consulta
            printf("\n|------------------------------------------------------\n|Nome:............. %s %s\n|Telefone:......... %s\n|CPF:.............. %s-%s\n|RG:............... %s\n|Nascimento:....... %d\n|Email:............ %s\n|Nc:............... %s\n|------------------------------------------------------\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
}

//função para pesquisar conveniado
void PesquisaConveniado (char pesquisa_nome[50]);
void PesquisaConveniado (char pesquisa_nome[50])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e variáveis
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

    arquivo = AbreArquivo('l', "ListaCadastro.txt");//Abre o arquivo Lista Cadastro em modo de leitura
    arquivoTemp = AbreArquivo('g', "PesquisaTemp.txt");//Abre o arquivo Lista Cadastro em modo de gravação
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que tem e adiciona nas variáveis
        // Zero = são iguais
        // Diferente de Zero = não são iguais
        if(strcmp(numAnterior,num_carteira) != 0)//Compara numAnterior com num_carteira para não ocorre o erro que repetirar 2 vezes o ultimo conveniado
        {
            strcpy(numAnterior,num_carteira);//Se o IF for diferente ele ira copiar o numAnterior e cola no num_carteira
            if(strcmp(pesquisa_nome,nome) == 0)//Compara o pesquisa_nome com o nome, se for igual ele irar printar em pesquisa Temp
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            }
            else
            {
                achou = true;
            }
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivoTemp


    arquivo = AbreArquivo('l',"PesquisaTemp.txt");//Abre o arquivo Pesquisa Temp em modo leitura

    strcpy(numAnterior,"");//Copia nomeAnterior para "NULL" para a variável ficar vazia
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que tem e adiciona nas variáveis
        if(strcmp(numAnterior,num_carteira) != 0 && strcmp(pesquisa_nome,nome) == 0)
        {
            strcpy(numAnterior,num_carteira);//Copia a variável nomeAnterior no e cola em nome para não ocorrer o bug que copia 2 vezes
            printf("\n\n|------------------------------------------------------\n|Nome:............. %s %s\n|Telefone:......... %s\n|CPF:.............. %s-%s\n|RG:............... %s\n|Nascimento:....... %d\n|Email:............ %s\n|Nc:............... %s\n|------------------------------------------------------\n\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            printf("Usuario encontrado com sucesso!\n\n");
        }
        if(strcmp(pesquisa_nome,nome) !=0)//compara o pesquisa_nome e nome, se for diferente ele printa usuário não encontrado
        {
            printf("Usuário não encontrado!\n\n");
        }
    }
}

//função para deletar conveniado
void Deletar(char num_Deletar[50]);
void Deletar(char num_Deletar[50])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e Variáveis
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
    bool apagou = false;//Coloca essa variável em FALSE para ter uma confirmação de deletado mais a frente

    arquivo = AbreArquivo('l', "ListaCadastro.txt");//Abre o arquivo Lista Cadastro em modo leitura
    arquivoTemp = AbreArquivo('g', "ListaCadastroTemp.txt");//Abre o arquivo Lista Cadastro Temp em modo gravação

    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo
    {
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que estar em Lista Cadastro e joga nas variáveis
        // Zero = são iguais
        // Diferente de Zero = não são iguais
        if(strcmp(nomeAnterior,nome) != 0)//Compara os nomes para não dar um bug que deleta 2 consultas
        {
            strcpy(nomeAnterior,nome);//Copia o nomeAnterior e cola em nome para não ocorrer o bug descrito acima
            if(strcmp(num_Deletar,num_carteira) != 0)//compara num_Deletar com num_carteira se for diferente ele copiar para lista cadastro temp
            {
                fprintf(arquivoTemp, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            }
            else//Se não apagou vira true
            {
                apagou = true;
            }
        }
    }
    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivo Temp
    arquivo = AbreArquivo('g', "ListaCadastro.txt");//Abre arquivo Lista Cadastro em modo de gravação
    arquivoTemp = AbreArquivo('l', "ListaCadastroTemp.txt");//Abre arquivo Lista Cadastro em modo de leitura

    strcpy(nomeAnterior,"");//Copia nomeAnterior para "NULL" para a variável ficar vazia

    while(!feof(arquivoTemp))//Usa o loop para ler o arquivo todo com o ponteiro *arquivoTemp
    {
        fscanf(arquivoTemp,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);//Escaneia tudo que estar em Lista Cadastro e joga nas variáveis
        if(strcmp(nomeAnterior,nome) != 0)//Se nomeAnterior for diferente de nome ele copiar todos os arquivos de volta para Lista Cadastro
        {
            strcpy(nomeAnterior,nome);//Copia o nomeAnterior e cola em nome para não ocorrer o bug que ira apararecer o ultimo conveniado 2 vezes
            fprintf(arquivo, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
        }
    }

    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivo Temp

    if(apagou)//Se apagou for False ele irá printar Conveniado deletado com sucesso
    {
        printf("Conveniado deletado com sucesso!\n\n");
    }
    else//Se apagou for true ele printa Conveniado não encontrado
    {
        printf("Conveniado não encontrado!\n\n");
    }
}


//função para cadastrar Atendimento
void CadastraUserGeral(char login[30], char senha[30], char permissao[30]);
void CadastraUserGeral(char login[30], char senha[30], char permissao[30])
{
    //Ponteiro
    FILE *arquivo;

    arquivo = AbreArquivo('a', "SistemadeLoginGeral.txt");//Abre o arquivo Sistema de Login Geral em modo append
    fprintf(arquivo, "%s %s %s \n", login, senha, permissao); //printa as variáveis no arquivo
    FecharArquivo(arquivo);//Fecha arquivo
}

//função para deletar o usuário na sessão de atendimento
void DeletarUserGeral(char deletarlogin[30]);
void DeletarUserGeral(char deletarlogin[30])
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e Variáveis
    FILE *arquivo;
    FILE *arquivoTemp;
    char login [30];
    char senha[30];
    char permissao[30];
    char verificalogin[30];
    char verificasenha[30];
    char loginAnterior[30];
    bool apagou = false;

    arquivo = AbreArquivo('l', "SistemadeLoginGeral.txt");//Abre o arquivo Sistema de Login Geral em modo de leitura
    arquivoTemp = AbreArquivo('g', "SistemadeLoginGeralTemp.txt");//Abre o arquivo Sistema de Login Geral em modo de gravação

    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro arquivo
    {
        fscanf(arquivo,"%s %s %s", &login, &senha, &permissao);//Escaneia tudo que estar em Sistema de login Geral e joga nas variáveis
        // Zero = são iguais
        // Diferente de Zero = não são iguais
        if(strcmp(loginAnterior,login) != 0)
        {
            strcpy(loginAnterior,login);
            if(strcmp(deletarlogin,login) != 0)//Compara os deletarlogin com login, se for diferente printa todos em Sistema de login Geral Temp
            {
                fprintf(arquivoTemp, "%s %s %s\n", login, senha, permissao);
            }
            else//Se não apagou vira True
            {
                apagou = true;
            }
        }
    }
    FecharArquivo(arquivo);//Fechar arquivo
    FecharArquivo(arquivoTemp);//Fechar arquivo Temp
    arquivo = AbreArquivo('g', "SistemadeLoginGeral.txt");//Abre o arquivo Sistema de Login Geral em modo de gravação
    arquivoTemp = AbreArquivo('l', "SistemadeLoginGeralTemp.txt");//Abre o arquivo Sistema de Login Geral Temp em modo de leitura

    strcpy(loginAnterior,"");//Copia loginAnterior para "NULL" para a variável ficar vazia

    while(!feof(arquivoTemp))//Usa o loop para ler o arquivo todo com o ponteiro *arquivo Temp
    {
        fscanf(arquivoTemp,"%s %s %s", &login, &senha, &permissao);//Escaneia tudo que estar em Lista Cadastro e joga nas variáveis
        if(strcmp(loginAnterior,login) != 0)//compara loginAnteriror com login se for diferente ele printa em Sistema de Login Geral Temp
        {
            strcpy(loginAnterior,login);//copiar loginAnterior e cola em login para não ocorrer o bug que apaga os 2 últimos logins da lista
            fprintf(arquivo, "%s %s %s\n", login, senha, permissao);
        }
    }

    FecharArquivo(arquivo);//Fecha arquivo
    FecharArquivo(arquivoTemp);//Fecha arquivo Temp

    if(apagou)//Se apagou for False ele irá printar usuário deletado com sucesso
    {
        printf("Usuário deletado com sucesso!\n\n");
    }
    else//Se apagou for True printar usuário não encontrado
    {
        printf("Usuario não encontrado!\n\n");

    }
}

//Função que lista todos os usuários no sistema
void ListarUserGeral();
void ListarUserGeral()
{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiro e Variáveis
    FILE *arquivo;
    char login[30];
    char senha[30];
    char permissao[30];
    char nomeAnterior[50];

    printf("LISTA DE USUARIOS\n");

    arquivo = AbreArquivo('l',"SistemadeLoginGeral.txt");//Abre o arquivo Sistema de Login Geral em modo de leitura
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro arquivo
    {
        fscanf(arquivo,"%s %s %s", &login, &senha, &permissao);//Escaneia tudo que estar em Sistema de login Geral e joga nas variáveis
        if(strcmp(nomeAnterior,login) != 0)//Compara o nomeAnterior com login para não acontecer um bug que mostra o ultimo login, senha e permissão 2 vezes
        {
            strcpy(nomeAnterior,login);//copia nomeAnterior com login para não ocorrer o bug descrito acima
            printf("\n|------------------------------------------------------\n|Nome:............. %s \n|Senha:............. %s \n|Permissão:............. %s", login, senha, permissao);//printa na tela os logins com senha e permissão
        }
    }
    FecharArquivo(arquivo);//Fechar arquivo
}

//função para cadastrar consulta no faturamento
void CadastraRelatorioFaturamento(char nome[30], char ult_nome[30], char num_carteira[30], int gasto_consulta, int dia_consulta, int mes_consulta, int ano_consulta);
void CadastraRelatorioFaturamento(char nome[30], char ult_nome[30], char num_carteira[30], int gasto_consulta, int dia_consulta, int mes_consulta, int ano_consulta)
{

    //Ponteiro
    FILE *arquivo;

    arquivo = AbreArquivo('a', "Relatorio.txt");//Abre o arquivo Relatorio em modo append
    fprintf(arquivo, "%s %s %s %d %d %d %d\n", nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta); //printa as variáveis no arquivo
    FecharArquivo(arquivo);//fecha arquivo

}

//função para listar o faturamento
void ListarRelatorioFaturamento();
void ListarRelatorioFaturamento()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Ponteiros e variáveis
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

    arquivo = AbreArquivo('l',"Relatorio.txt");//Abre o arquivo Relatório em modo de leitura
    while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro arquivo
    {
        fscanf(arquivo,"%s %s %s %d %d %d %d", &nome, &ult_nome, &num_carteira, &gasto_consulta, &dia_consulta, &mes_consulta, &ano_consulta);//Escaneia tudo que estar em Relatorio e joga nas variáveis
        printf("|Nome: \t\tNC: \t   Gastos do paciente:   data: \n|%s %s  |  %s |  %d                | %d/%d/%d \n\n", nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta);//printa nas telas as variáveis
    }
    FecharArquivo(arquivo);//fecha arquivo
}

//Pede pra o usuario escolher voltar pro menu ou fazer outra ação
int volta_menu_login();
int volta_menu_login()
{

    do
    {
        printf("Digite 0 para sair para o menu: ");//pergunta para o usuário se deseja retornar ao menu de login
        scanf("%d", &volta_menu);

        if(volta_menu == 0)//Se o usuário digitar 0 ele retorna ao menu de login
        {
            system("cls");
            return main();
        }
        else//Se ele digitar outra coisa printa na tela opção inválida e faz um loop para voltar ao começo da função
        {
            system("cls");
            printf("\nOpção Inválida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 0);
}

//Pede pra o usuário escolher voltar pro menu ou fazer outra ação
int volta_menu_atendimento();
int volta_menu_atendimento()
{

    do
    {
        printf("Digite 1 para retornar ao menu: ");//pergunta para o usuário se deseja retornar ao menu de atendimento
        scanf("%d", &volta_menu);

        if(volta_menu == 1)//Se o usuário digitar 0 ele retorna ao menu de atendimento
        {
            return principal_atendente();
        }
        else
        {
            printf("\nOpção Invalida\n\n");//Se ele digitar outra coisa printa na tela opção inválida e faz um loop para voltar ao começo da função
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

//Pede para o usuario escolher voltar para o menu ou fazer outra ação
int volta_menu_medico();
int volta_menu_medico()
{

    do
    {
        printf("Digite 1 para retornar ao menu: ");//pergunta para o usuário se deseja retornar ao menu de médico
        scanf("%d", &volta_menu);

        if(volta_menu == 1)
        {
            return principal_medico();//Se o usuário digitar 0 ele retorna ao menu de médico
        }
        else//Se ele digitar outra coisa printa na tela opção inválida e faz um loop para voltar ao começo da função
        {
            printf("\nOpção Invalida\n\n");
            sleep(0,5);
        }
    }
    while(volta_menu != 1);
}

//Pede para o usuário escolher voltar pro menu ou fazer outra ação
int volta_menu_conveniado();
int volta_menu_conveniado()
{

    do
    {
        printf("Digite 1 para retornar ao menu: ");//pergunta para o usuário se deseja retornar ao menu de médico
        scanf("%d", &volta_menu);

        if(volta_menu == 1){//Se o usuário digitar 0 ele retorna ao menu de conveniado


            return principal_conveniado();
        }else//Se ele digitar outra coisa printa na tela opção inválida e faz um loop para voltar ao começo da função
        {
            printf("\nOpção Invalida\n\n");
            sleep(0,5);
        }
    }while(volta_menu != 1);
}

//Pede pra o usuário escolher voltar pro menu ou fazer outra ação
int volta_menu_adm();
int volta_menu_adm()
{

    do
    {
        printf("\nDigite 1 para retornar ao menu: ");//pergunta para o usuário se deseja retornar ao menu de administrador
        scanf("%d", &volta_menu);

        if(volta_menu == 1)//Se o usuário digitar 0 ele retorna ao menu de conveniado
        {
            return principal_adm();
        }
        else//Se ele digitar outra coisa printa na tela opção inválida e faz um loop para voltar ao começo da função
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
    //Ponteiros e Variáveis
    FILE *arquivo;
    char login [30];
    char senha[30];
    char permissao[30];
    char verificalogin[30];
    char verificasenha[30];
    bool achou = false;//Coloca essa variável em FALSE para ter uma confirmação mais a frente

    do
    {
        printf("Digite seu login: ");//Aqui ele irá pedi o login e senha e adicionar nas variáveis
        setbuf(stdin,NULL);
        gets(verificalogin);
        printf("\nDigite sua senha: ");
        setbuf(stdin,NULL);
        gets(verificasenha);


        arquivo = AbreArquivo('l',"SistemadeLoginGeral.txt");//Abre o arquivo Sistema de login Geral em modo leitura
        while(!feof(arquivo))//Usa o loop para ler o arquivo todo com o ponteiro arquivo
        {
            fscanf(arquivo, "%s %s %s", &login, &senha, &permissao);//Escaneia todos os logins, senhas e permissões
            if(strcmp(verificalogin, login) == 0 && strcmp(verificasenha, senha) == 0)//compara o login, senha e permissões do arquivo com as digitadas pelo o usuário
            {
                achou = true;//se o login e senha forem iguais achou vira True
                if(strcmp(permissao, "Medico") == 0 )//Se a permissão que o usuário for igual a medico ele entrará no menu de médico
                {
                    printf("Bem vindo Doutor (a).");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(1,5);
                    system("cls");
                    principal_medico();
                }

                if(strcmp(permissao, "Atendente") == 0 )//Se a permissão que o usuário for igual a atendente ele entrará no menu de atendimento
                {
                    principal_atendente();
                    printf("Bem vindo Atendente");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(1,5);
                    system("cls");
                }

                if(strcmp(permissao, "Administrador") == 0 )//Se a permissão que o usuário for igual a Administrador ele entrará no menu de administrador
                {
                    printf("Bem vindo Administrador");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(1,5);
                    system("cls");
                    principal_adm();
                }

            }
            else//Se o login e a senha for diferente achou ira ser False e ele irá printa a mensagem na tela
            {
                printf("Caso Esqueceu seu login ou senha entre em contato com o administrador\nd4niel.arruda@gmail.com\n\nESPERE\n");
                sleep(2);
                system("cls");
            }
        }

    }
    while(!achou);//Depois irá dar o loop para repetir a função
    FecharArquivo(arquivo);//Fecha arquivo

}

//tela de menu do atendimento e suas funções
void principal_atendente();
void principal_atendente()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Variáveis
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

    //Menu do Atendimento
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
    printf("\n\t| 11 - Relatórios de faturamento  e tabela |\n");
    printf("\t ------------------------------------------");
    printf("\n\t| 0 - Sair                                 |\n");
    printf("\t ------------------------------------------");


    printf("\nDigite uma opcao: ");//Pede para escolher um opção
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_atendente);

    sleep(1);
    system("cls");//limpa a tela

    switch (escolha_tela_atendente)
    {
    case 1:
        //Cadastrar conveniado

        //Pede as informações para ser adicionada em Cadastra
        printf("\nDigite o nome: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(nome);
        printf("\nDigite o ultimo nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite o telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite os 9 primeiros número do seu CPF sem ponto ou traço: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os últimos 2 números do seu CPF: ");
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
        printf("\nDigite o número da carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteira);
        Cadastra(nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);//Depois que coloca o que foi pedido nas veriáveis ele começa a função cadastra
        volta_menu_atendimento();//Depois que ele terminar a função cadastra ele pode escolher se vai voltar para o menu
        break;

    case 2:
        //Listar conveniados
        Listar();//Função para listar
        volta_menu_atendimento();
        break;

    case 3:
        //pesquisar conveniado
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char pesquisa_nome[50];

        printf("\nDigite o nome do conveniado que deseja procurar: ");
        setbuf(stdin,NULL);
        gets(pesquisa_nome);
        PesquisaConveniado(pesquisa_nome);
        volta_menu_atendimento();
        break;

    case 4:
        //Deletar cadastro
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char num_Deletar[50];

        printf("\nDigite o número de carteira do conveniado que deseja deletar: ");
        setbuf(stdin,NULL);
        gets(num_Deletar);
        Deletar(num_Deletar);
        volta_menu_atendimento();
        break;

    case 5:
        //cadastrar agenadamento
        //Pede as informações para ser adicionada em Agendar
        printf("\nDigite o nome: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(nome);
        printf("\nDigite o ultimo nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite o telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite o nome do médico: ");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite os 9 primeiros número do seu CPF sem ponto ou traço: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os últimos 2 números do seu CPF: ");
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
        printf("\nDigite o número da carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteira);
        printf("\n| Paz | Cancioneiro | Paulista |");
        printf("\nDigite a o nome da unidade: ");
        setbuf(stdin,NULL);
        gets(unidade);
        Agendar(nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
        volta_menu_atendimento();
        break;

    case 6:
        //listar agendamentos
        ListarAgenda();
        volta_menu_atendimento();
        break;

    case 7:
        //pesquisa agendamento
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char pesquisa_num[30];

        printf("\nDigite o número de carteirinha do paciente para vê as consultas do conveniado: ");
        setbuf(stdin,NULL);
        gets(pesquisa_num);
        PesquisaAgendamento(pesquisa_num);
        volta_menu_atendimento();
    case 8:
        //deletar agendamentos
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char nomeDeletar[50];
        char nomeDeletarAgenda[50];
        char num_carteiraDeletar[30];
        int diaDeletar;
        int horarioDeletar;
        int minutoDeletar;

        printf("\nDigite um nome: ");
        setbuf(stdin,NULL);
        gets(nomeDeletar);
        printf("\nDigite o número de carteirinha: ");
        setbuf(stdin,NULL);
        gets(num_carteiraDeletar);
        printf("\nDigite o dia, mês e ano da consulta sem barra: ");
        scanf("%d", &diaDeletar);
        printf("\nDigite a hora da sua consulta: ");
        scanf("%d", &horarioDeletar);
        printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", hora_consulta);
        scanf("%d", &minutoDeletar);
        DeletarAgendamento(nomeDeletarAgenda, num_carteiraDeletar, diaDeletar, horarioDeletar, minutoDeletar);
        volta_menu_atendimento();
        break;

    case 9:
        //listar feedbacks
        ListarFeedback();
        volta_menu_atendimento();
        break;

    case 10:
        //excluir feedbacks
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        int excluir_feedback;

        printf("Para não haver manipulação dos feedbacks a função deletar feedback excluir todos os feedbacks de uma vez.\n\n");
        printf("Se tive certeza disso digite 1 se não digite 0 para voltar ao menu: ");
        scanf("%d", &excluir_feedback);


        if(excluir_feedback == 1)//If para ter a certeza de exclusão dos feedbacks
        {
            DeletarFeedback();
        }
        else
        {
            volta_menu_atendimento();
        }
        break;

    case 11:
        ;
        //menu com relatórios
        int escolha_menu_relatorio;
        //Menu de relatórios e tabela
        printf("\n\t\Relatórios de faturamento");
        printf("\n");
        printf("\t ---------------------------------------------");
        printf("\n\t| 1 - Adicionar faturamento no relatório    |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 2 - Listar Faturamento                    |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 3 - Tabela de Preço de Consultas e Exames |\n");
        printf("\t|---------------------------------------------");
        printf("\n\t| 0 - Sair                                  |\n");
        printf("\t|---------------------------------------------");

        printf("\nDigite uma opção: ");
        sleep(0,5);
        sleep(0,5);//pausa a tela por x segundos
        scanf("%d", &escolha_menu_relatorio);

        sleep(1);
        system("cls");//limpa a tela

        switch (escolha_menu_relatorio)
        {
        case 1:
            //Cadastrar relatório
            ;//Para pode colocar um char dentro de um case precisar adicionar este ";"

            char nome[30];
            char ult_nome[30];
            char num_carteira[30];
            int gasto_consulta;
            int dia_consulta;
            int mes_consulta;
            int ano_consulta;

            printf("\nDigite o nome do conveniado: ");
            setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
            gets(nome);
            printf("\nDigite o último nome do conveniado: ");
            setbuf(stdin,NULL);
            gets(ult_nome);
            printf("\nDigite o número da carteirinha: ");
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
            volta_menu_atendimento();
            break;

        case 2:
            //Listar Relatório
            ListarRelatorioFaturamento();//Lista Relatório
            volta_menu_atendimento();
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

            volta_menu_atendimento();
            break;
        case 0:
            //volta ao menu de Atendimento
            volta_menu_atendimento();
            break;

        default:
            printf("Opção incorreta\n");
            sleep(1,25);
            volta_menu_atendimento();
            break;
        }
        break;

    case 0:
        //volta ao menu de login
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\n\Opção invalida! Tente Novamente!\n\n");
        sleep(1,5);
        volta_menu_atendimento();
        break;
    }



}

//tela de menu do conveniado e suas funções
void principal_conveniado();
void principal_conveniado()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    //Variáveis
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

    //Menu de conveniado
    system("cls");
    printf("\n\t\tMENU");
    printf("\n");

    printf("\t|-----------------------------");
    printf("\n\t| 1 -  Agendar Consulta       |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 2 - Listar Suas Consultas   |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 3 - Desmarcar Suas consultas|\n");
    printf("\t|-----------------------------");
    printf("\n\t| 4 - Dar um feedback         |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 5 - Nossos Endereços        |\n");
    printf("\t| -----------------------------");
    printf("\n\t| 0 - Sair                    |\n");
    printf("\t|-----------------------------");

    printf("\nDigite uma opção: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_conveniado);

    sleep(1);
    system("cls");//limpa a tela
    //Switch para escolha de opções no menu
    switch(escolha_tela_conveniado)
    {
    case 1:
        //cadastrar agendamento
        //Pede as informações para ser adicionada em Agendar
        printf("\nDigite seu primeiro nome: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(nome);
        printf("\nDigite seu último nome: ");
        setbuf(stdin,NULL);
        gets(ult_nome);
        printf("\nDigite seu telefone: ");
        setbuf(stdin,NULL);
        gets(telefone);
        printf("\nDigite o nome do médico: ");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite os 9 primeiros número do seu CPF sem ponto ou traço: ");
        setbuf(stdin,NULL);
        gets(cpf_sdigito);
        printf("\nDigite os últimos 2 números do seu CPF: ");
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
        printf("\nDigite o número da carteirinha: ");
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
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char pesquisa_num[30];

        printf("\nDigite o número de carteirinha para ver suas consultas: ");
        setbuf(stdin,NULL);
        gets(pesquisa_num);
        PesquisaAgendamento(pesquisa_num);
        volta_menu_conveniado();
        break;

    case 3:
        //deletar agendamentos
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char nomeDeletar[50];
        char nomeDeletarAgenda[50];
        char num_carteiraDeletar[30];
        int diaDeletar;
        int horarioDeletar;
        int minutoDeletar;

        printf("\nDigite um nome: ");
        setbuf(stdin,NULL);
        gets(nomeDeletar);
        printf("\nDigite o número de carteirinha: ");
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
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char nome_medico[30];
        int nota_medico;
        int nota_atendimento;

        printf("\nDigite o nome do médico");
        printf("(Andre) (Osvaldo) (Luis): ");
        setbuf(stdin,NULL);
        gets(nome_medico);
        printf("\nDigite uma nota de 0 a 10 para o atendimento de seu médico: ");
        scanf("%d", &nota_medico);
        printf("\nDigite uma nota de 0 a 10 para seu atendimento em geral: ");
        scanf("%d", &nota_atendimento);
        printf("Muito Obrigado pelo seu Feedback :)\n\n");
        CadastraFeedback(nome_medico, nota_medico, nota_atendimento);
        volta_menu_conveniado();

        break;

    case 5:
        //Aqui mostra o endereço das clínicas e o contato das mesmas
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
        printf("\n\Opção invalida! Tente Novamente! \n\n");
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

    //Menu de Administrador do sistema
    system("cls");
    printf("\n\t\tMENU");
    printf("\n");

    printf("\t|-----------------------------");
    printf("\n\t| 1 - Adicionar Usuários      |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 2 - Listar Usuários         |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 3 - Deletar Usuários        |\n");
    printf("\t -----------------------------");
    printf("\n\t| 0 - Sair                    |\n");
    printf("\t -----------------------------");


    printf("\n\nDigite uma opção: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_adm);

    sleep(1);
    system("cls");//limpa a tela
    //Switch de escolha de opções no menu de Administrador
    switch (escolha_tela_adm)
    {
    case 1:
        //Pede as informações para ser adicionada como um novo usuário
        printf("Digite o nome do novo usuário: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(login);
        printf("\nDigite a Senha do novo usuário: ");
        setbuf(stdin,NULL);
        gets(senha);
        printf("\nDigite o tipo de Permissão que desejar dar ao usuário");
        printf("\n(Administador) (Medico) (Atendimento) (Conveniado)");
        printf(": ");
        setbuf(stdin,NULL);
        gets(permissao);
        CadastraUserGeral(login, senha, permissao);
        volta_menu_adm();
        break;

    case 2:
        //Lista todos os usuários
        ListarUserGeral();
        volta_menu_adm();
        break;

    case 3:
        //Deleta usuários
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char deletarlogin[30];
        printf("\nDigite o nome do usuário que deseja deletar: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
        gets(deletarlogin);
        DeletarUserGeral(deletarlogin);
        volta_menu_adm();
        break;

    case 0:
        volta_menu_login();
        break;

    default:
        system("cls");
        printf("\n\nOpção invalida! Tente Novamente! \n\n");
        sleep(1,5);
        volta_menu_adm();
        break;
    }
}

//tela de menu do médico e suas funções
void principal_medico();
void principal_medico()
{

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    int escolha_tela_medico;

    system("cls");
    printf("\n\t\tMENU");
    printf("\n");
    //Menu de Médico
    printf("\t|--------------------------------------");
    printf("\n\t| 1 - Pesquisar Agendamento            |\n");
    printf("\t|--------------------------------------");
    printf("\n\t| 2 - Listar conveniados               |\n");
    printf("\t| -------------------------------------");
    printf("\n\t| 3 - Pesquisar conveniado             |\n");
    printf("\t|--------------------------------------");
    printf("\n\t| 0 - Sair                             |\n");
    printf("\t| -------------------------------------\n");

    printf("\nDigite uma opção: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_medico);

    sleep(1);
    system("cls");//limpa a tela
    //Switch para escolha de opções no menu Médico
    switch (escolha_tela_medico)
    {
    case 1:
        ;//Para pode colocar um char dentro de um case precisar adicionar este ";"
        char pesquisa_num[30];

        printf("\nDigite o número de carteirinha do paciente para ver suas consultas: ");
        setbuf(stdin,NULL);//Sempre limpar o Buffer para receber uma nova entrada de dados.
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

    int login_escolha; // variável usada no int main para escolher usuário
    int login_menu;
    //No int main deixamos apenas a tela de login para uma melhor organização do código em si
    printf("\n");
    printf("\t\t\t\t\t\t*!Bem vindo!*\n\n");
    printf("\tDATA : %s\n\n\n",__DATE__);//Para aparecer a data perto do bem vindo
    sleep(1);

    printf("\n\t\t\t\t\t\t  | Usuários | \t\t");
    printf("\n\t\t__________________________________________________________________________________\n\n");
    printf("\t\t|       0-Sair \t\t\t  1-Conveniado \t\t\t2-Usuários       |\n");
    printf("\t\t__________________________________________________________________________________\n\n");

    printf("\n\tEscolha um opção por favor --> ");

    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &login_escolha);
    sleep(1);
    system("cls");//limpa a tela

    //Switch para escolha de login
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
