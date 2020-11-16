#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <TIME.H>

//variaveis globais
int login_escolha; // variavel usada no int main para escolher usuario
int volta_menu; //variavel global para retornar ao menu



//função para abrir arquivo
FILE* AbreArquivo(char modo, char caminho[30]);
FILE* AbreArquivo(char modo, char caminho[30]){
    FILE *arquivo;
    switch(modo){
        case 'g':
            arquivo = fopen(caminho,"wt"); //abre o arquivo em modo de gravação
            break;
        case 'l':
            arquivo = fopen(caminho,"rt"); //abre o arquivo em modo de leitura
            break;
        case 'a':
            arquivo = fopen(caminho,"a"); //abre o arquivo em um modo que adiciona no final do arquivo
            break;
    }
    if(arquivo==NULL){ //Se houver algum erro, o ponteiro apontará para NULL
        printf("Nao foi possivel abrir o arquivo");
        exit(0);
    }
    return arquivo;
}

//void para fechar arquivo
void FecharArquivo(FILE *arquivo);
void FecharArquivo(FILE *arquivo){
    fclose(arquivo); //apenas usa a função para fechar o arquivo com o ponteiro arquivo
}

// função para Cadastrar Feedbacks //pronta
void CadastraFeedback(char nome_medico[30], int nota_medico, int nota_atendimento);
void CadastraFeedback(char nome_medico[30], int nota_medico, int nota_atendimento){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;

    arquivo = AbreArquivo('a', "Listafeedback.txt");
    fprintf(arquivo, "%s %d %d \n", nome_medico, nota_medico, nota_atendimento);
    FecharArquivo(arquivo);
}

//função para Listar Feedbacks //pronta
void ListarFeedback();
void ListarFeedback(){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
	FILE *arquivo;
    char nome_medico[30];
    int nota_medico;
    int nota_atendimento;

    arquivo = AbreArquivo('l',"ListaFeedback.txt");

    while(!feof(arquivo)){
        fscanf(arquivo,"%s %d %d",&nome_medico, &nota_medico, &nota_atendimento);

            printf("| Nome Do Medico:... %s|\n| Nota do Medico:............... %d |\n| Nota do atendimento:.......... %d |\n\n",nome_medico, nota_medico, nota_atendimento);
        }
    FecharArquivo(arquivo);

}

//função para Deletar Feedbacks //pronta
void DeletarFeedback();
void DeletarFeedback(){

	setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;

    remove("ListaFeedback.txt");
    remove("ListaFeedbackTemp.txt");

    arquivo = AbreArquivo('g', "Listafeedback.txt");
    FecharArquivo(arquivo);

    printf("\nFeedbacks Deletados\n\n");
}


// função para Agendar consultas //pronta
void Agendar(char nome[30], char ult_nome[30], char nome_medico[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], int dia_consulta, int hora_consulta, int minuto_consulta, char especialidade[30], char num_carteira[30], char unidade[20]);
void Agendar(char nome[30], char ult_nome[30], char nome_medico[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], int dia_consulta, int hora_consulta, int minuto_consulta, char especialidade[30], char num_carteira[30], char unidade[20]){

    FILE *arquivo;
    arquivo = AbreArquivo('a', "ListaAgendamento.txt");
    fprintf(arquivo, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
    FecharArquivo(arquivo);
}

// função para Listar consultas //pronta
void ListarAgenda();
void ListarAgenda(){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
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

    arquivo = AbreArquivo('l',"ListaAgendamento.txt");

    while(!feof(arquivo)){
        fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);
        if(strcmp(numAnterior,num_carteira) != 0){
            strcpy(numAnterior,num_carteira);
            printf("|------------------------------------------------------\n|Nome:...................... %s %s\n|Nome Do Medico:............ %s\n|Telefone:.................. %s\n|CPF:....................... %s-%s\n|Dia da Consulta:........... %d\n|Horario da Consulta:....... %d:%d\n|Especialidade:............. %s\n|Nc:........................ %s\n|Unidade:................... %s\n|------------------------------------------------------\n\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
        }
    }
    FecharArquivo(arquivo);
}

//função para pesquisar consulta
void PesquisaAgendamento (char pesquisa_num[30]);
void PesquisaAgendamento (char pesquisa_num[30]){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
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
    bool achou = false;

        arquivo = AbreArquivo('l', "ListaAgendamento.txt");
        arquivoTemp = AbreArquivo('g', "PesquisaTemp.txt");

        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);
            // Zero = são iguais
            // Diferente de Zero = não são iguais
            if(strcmp(nomeAnterior,nome) != 0){
                strcpy(nomeAnterior,nome);
                if(strcmp(pesquisa_num,num_carteira) == 0){
                    fprintf(arquivoTemp, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
                }else{
                    achou = true;
                }
            }
        }
        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);


        arquivo = AbreArquivo('l',"PesquisaTemp.txt");

        strcpy(nomeAnterior,"");
        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, unidade);

            if(strcmp(nomeAnterior,nome) != 0 && strcmp(pesquisa_num,num_carteira) == 0){
                strcpy(nomeAnterior,nome);
                printf("\n|------------------------------------------------------\n|Nome:...................... %s %s\n|Nome Do Medico:............ %s\n|Telefone:.................. %s\n|CPF:....................... %s-%s\n|Dia da Consulta:........... %d\n|Horario da Consulta:....... %d:%d\n|Especialidade:............. %s\n|Nc:........................ %s\n|Unidade:................... %s\n|------------------------------------------------------\n\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
                printf("Consulta(s) encontrado(s) com sucesso!\n\n");
            }
            if(strcmp(pesquisa_num,num_carteira) !=0){
                printf("Usuario não encontrado!\n\n");
        }
    }
}

// função para Deletar consultas //pronta
void DeletarAgendamento(char nomeDeletarAgenda[50], char num_carteiraDeletar[30], int diaDeletar, int horarioDeletar, int minutoDeletar);
void DeletarAgendamento(char nomeDeletarAgenda[50], char num_carteiraDeletar[30], int diaDeletar, int horarioDeletar, int minutoDeletar){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
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
    bool apagou = false;

        arquivo = AbreArquivo('l', "ListaAgendamento.txt");
        arquivoTemp = AbreArquivo('g', "ListaAgendamentoTemp.txt");

        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);
            // Zero = são iguais
            // Diferente de Zero = não são iguais
            if(strcmp(numAnterior,num_carteira) != 0){
                strcpy(numAnterior,num_carteira);
                if(strcmp(nomeDeletarAgenda,nome) != 0 && strcmp(num_carteiraDeletar,num_carteira) != 0 && diaDeletar != dia_consulta && horarioDeletar != hora_consulta && minutoDeletar != minuto_consulta){
                    fprintf(arquivoTemp, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
                }else{
                    apagou = true;
                }
            }
        }
        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);

        arquivo = AbreArquivo('g', "ListaAgendamento.txt");
        arquivoTemp = AbreArquivo('l', "ListaAgendamentoTemp.txt");

        strcpy(numAnterior,"");

        while(!feof(arquivoTemp)){
            fscanf(arquivoTemp,"%s %s %s %s %s %s %d %d %d %s %s %s", &nome, &ult_nome, &nome_medico, &telefone, &cpf_sdigito, &cpf_digito, &dia_consulta, &hora_consulta, &minuto_consulta, &especialidade, &num_carteira, &unidade);
            if(strcmp(numAnterior,num_carteira)){
                strcpy(numAnterior,num_carteira);
                fprintf(arquivo, "%s %s %s %s %s %s %d %d %d %s %s %s\n", nome, ult_nome, nome_medico, telefone, cpf_sdigito, cpf_digito, dia_consulta, hora_consulta, minuto_consulta, especialidade, num_carteira, unidade);
            }
        }

        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);

        if(apagou){
            printf("Agendamento de Consulta apagada com sucesso!\n\n");
        }else{
            printf("Usuario não encontrado!\n\n");

        }
}



//função cadastra conveniado //pronta
void Cadastra(char nome[30], char ult_nome[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], char rg[15], int nascimento, char email[40], char num_carteira[30]);
void Cadastra(char nome[30], char ult_nome[30], char telefone[20], char cpf_sdigito[15], char cpf_digito[15], char rg[15], int nascimento, char email[40], char num_carteira[30]){

    FILE *arquivo;
    arquivo = AbreArquivo('a', "ListaCadastro.txt");
    fprintf(arquivo, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
    FecharArquivo(arquivo);
}

//função para listar conveniados //pronta
void Listar();
void Listar(){

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

    arquivo = AbreArquivo('l',"ListaCadastro.txt");
    while(!feof(arquivo)){
        fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
        if(strcmp(nomeAnterior,nome) != 0){
            strcpy(nomeAnterior,nome);
            printf("LISTA DE CONVENIADO\n\n|------------------------------------------------------\n|Nome:............. %s %s\n|Telefone:......... %s\n|CPF:.............. %s-%s\n|RG:............... %s\n|Nascimento:....... %d\n|Email:............ %s\n|Nc:............... %s\n|------------------------------------------------------\n\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
        }
    }
    FecharArquivo(arquivo);
}

//função para pesquisar conveniado
void PesquisaConveniado (char pesquisa_nome[50]);
void PesquisaConveniado (char pesquisa_nome[50]){

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
    bool achou = false;

        arquivo = AbreArquivo('l', "ListaCadastro.txt");
        arquivoTemp = AbreArquivo('g', "PesquisaTemp.txt");

        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
            // Zero = são iguais
            // Diferente de Zero = não são iguais
            if(strcmp(nomeAnterior,nome) != 0){
                strcpy(nomeAnterior,nome);
                if(strcmp(pesquisa_nome,nome) == 0){
                    fprintf(arquivoTemp, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
                }else{
                    achou = true;
                }
            }
        }
        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);


        arquivo = AbreArquivo('l',"PesquisaTemp.txt");
        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
            if(strcmp(nomeAnterior,nome) != 0 && strcmp(pesquisa_nome,nome) == 0){
                strcpy(nomeAnterior,nome);
                printf("\n\n|------------------------------------------------------\n|Nome:............. %s %s\n|Telefone:......... %s\n|CPF:.............. %s-%s\n|RG:............... %s\n|Nascimento:....... %d\n|Email:............ %s\n|Nc:............... %s\n|------------------------------------------------------\n\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
                printf("Usuario encontrado com sucesso!\n\n");
            }
            if(strcmp(pesquisa_nome,nome) !=0){
                printf("Usuario não encontrado!\n\n");
        }
    }
}

//função para deletar conveniado
void Deletar(char num_Deletar[50]);
void Deletar(char num_Deletar[50]){

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

        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
            // Zero = são iguais
            // Diferente de Zero = não são iguais
            if(strcmp(nomeAnterior,nome) != 0){
                strcpy(nomeAnterior,nome);
                if(strcmp(num_Deletar,num_carteira) != 0){
                    fprintf(arquivoTemp, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
                }else{
                    apagou = true;
                }
            }
        }
        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);
        arquivo = AbreArquivo('g', "ListaCadastro.txt");
        arquivoTemp = AbreArquivo('l', "ListaCadastroTemp.txt");

        strcpy(nomeAnterior,"");

        while(!feof(arquivoTemp)){
            fscanf(arquivoTemp,"%s %s %s %s %s %s %d %s %s", &nome, &ult_nome, &telefone, &cpf_sdigito, &cpf_digito, &rg, &nascimento, &email, &num_carteira);
            if(strcmp(nomeAnterior,nome) != 0){
                strcpy(nomeAnterior,nome);
                fprintf(arquivo, "%s %s %s %s %s %s %d %s %s\n", nome, ult_nome, telefone, cpf_sdigito, cpf_digito, rg, nascimento, email, num_carteira);
            }
        }

        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);

        if(apagou){
            printf("Conveniado deletado com sucesso!\n\n");
        }else{
            printf("Conveniado não encontrado!\n\n");
        }
}


//função para cadastrar Atendimento //falta add no adm
void CadastraUsuariosAtendimento(char login[30], char senha[30]);
void CadastraUsuariosAtendimento(char login[30], char senha[30]){

    FILE *arquivo;

    arquivo = AbreArquivo('a', "SistemadeLoginAtendimento.txt");
    fprintf(arquivo, "%s %s \n", login, senha);
    FecharArquivo(arquivo);
}

//função para cadastrar medico //falta add no adm
void CadastraUsuariosMedico(char login[30], char senha[30]);
void CadastraUsuariosMedico(char login[30], char senha[30]){

    FILE *arquivo;

    arquivo = AbreArquivo('a', "SistemadeLoginMedico.txt");
    fprintf(arquivo, "%s %s \n", login, senha);
    FecharArquivo(arquivo);
}

//função para deletar o usuario na sessão de medico
void DeletarUserMedico(char deletarlogin[30]);
void DeletarUserMedico(char deletarlogin[30]){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;
    FILE *arquivoTemp;
    char login [30];
    char senha[30];
    char verificalogin[30];
    char verificasenha[30];
    char loginAnterior[30];
    bool apagou = false;

        arquivo = AbreArquivo('l', "SistemadeLoginMedico.txt");
        arquivoTemp = AbreArquivo('g', "SistemadeLoginMedicoTemp.txt");

        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s", &login, &senha);
            // Zero = são iguais
            // Diferente de Zero = não são iguais
            if(strcmp(loginAnterior,login) != 0){
                strcpy(loginAnterior,login);
                if(strcmp(deletarlogin,login) != 0){
                    fprintf(arquivoTemp, "%s %s\n", login, senha);
                }else{
                    apagou = true;
                }
            }
        }
        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);
        arquivo = AbreArquivo('g', "SistemadeLoginMedico.txt");
        arquivoTemp = AbreArquivo('l', "SistemadeLoginMedicoTemp.txt");

        strcpy(loginAnterior,"");

        while(!feof(arquivoTemp)){
            fscanf(arquivoTemp,"%s %s", &login, &senha);
            if(strcmp(loginAnterior,login) != 0){
                strcpy(loginAnterior,login);
                fprintf(arquivo, "%s %s\n", login, senha);
            }
        }

        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);

        if(apagou){
            printf("Usuario deletado com sucesso!\n\n");
        }else{
            printf("Usuario não encontrado!\n\n");

        }

}

//função para deletar o usuario na sessão de atendimento
void DeletarUserAtendimento(char deletarlogin[30]);
void DeletarUserAtendimento(char deletarlogin[30]){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;
    FILE *arquivoTemp;

    char login [30];
    char senha[30];
    char verificalogin[30];
    char verificasenha[30];
    char loginAnterior[30];
    bool apagou = false;

        arquivo = AbreArquivo('l', "SistemadeLoginAtendimento.txt");
        arquivoTemp = AbreArquivo('g', "SistemadeLoginAtendimentoTemp.txt");

        while(!feof(arquivo)){
            fscanf(arquivo,"%s %s", &login, &senha);
            // Zero = são iguais
            // Diferente de Zero = não são iguais
            if(strcmp(loginAnterior,login) != 0){
                strcpy(loginAnterior,login);
                if(strcmp(deletarlogin,login) != 0){
                    fprintf(arquivoTemp, "%s %s\n", login, senha);
                }else{
                    apagou = true;
                }
            }
        }
        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);
        arquivo = AbreArquivo('g', "SistemadeLoginAtendimento.txt");
        arquivoTemp = AbreArquivo('l', "SistemadeLoginAtendimentoTemp.txt");

        strcpy(loginAnterior,"");

        while(!feof(arquivoTemp)){
            fscanf(arquivoTemp,"%s %s", &login, &senha);
            if(strcmp(loginAnterior,login) != 0){
                strcpy(loginAnterior,login);
                fprintf(arquivo, "%s %s\n", login, senha);
            }
        }

        FecharArquivo(arquivo);
        FecharArquivo(arquivoTemp);

        if(apagou){
            printf("Usuario deletado com sucesso!\n\n");
        }else{
            printf("Usuario não encontrado!\n\n");

        }
}


//função para cadastrar consulta no faturamento
void CadastraRelatorioFaturamento(char nome[30], char ult_nome[30], char num_carteira[30], int gasto_consulta, int dia_consulta, int mes_consulta, int ano_consulta);
void CadastraRelatorioFaturamento(char nome[30], char ult_nome[30], char num_carteira[30], int gasto_consulta, int dia_consulta, int mes_consulta, int ano_consulta){

    FILE *arquivo;
    arquivo = AbreArquivo('a', "Relatorio.txt");
    fprintf(arquivo, "%s %s %s %d %d %d %d\n", nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta);
    FecharArquivo(arquivo);

}

//função para listar o faturamento
void ListarRelatorioFaturamento();
void ListarRelatorioFaturamento(){

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

    arquivo = AbreArquivo('l',"Relatorio.txt");
    while(!feof(arquivo)){
        fscanf(arquivo,"%s %s %s %d %d %d %d", &nome, &ult_nome, &num_carteira, &gasto_consulta, &dia_consulta, &mes_consulta, &ano_consulta);
            printf("Nome: %s %s  |  NC: %s | Gastos do paciente: %d | data: %d/%d/%d \n\n", nome, ult_nome, num_carteira, gasto_consulta, dia_consulta, mes_consulta, ano_consulta);
        }

        printf("\nFaturamento Mensal: %d%d\n", gasto_consulta);
    FecharArquivo(arquivo);

}


int volta_menu_antedimento();
int volta_menu_antedimento(){

    do{
    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    printf("Digite 1 para retornar ao menu: ");
    scanf("%d", &volta_menu);

    principal_atendente();
    }while(volta_menu != 1);

    return principal_atendente();
}

int volta_menu_medico();
int volta_menu_medico(){

    do{
    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    printf("Digite 1 para retornar ao menu: ");
    scanf("%d", &volta_menu);

    principal_atendente();
    }while(volta_menu != 1);

    return principal_medico();
}

int volta_menu_conveniado();
int volta_menu_conveniado(){

    do{
    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    printf("Digite 1 para retornar ao menu: ");
    scanf("%d", &volta_menu);

    principal_atendente();
    }while(volta_menu != 1);

    return principal_conveniado();
}

int volta_menu_adm();
int volta_menu_adm(){
    do{
    //Pede pra o usuario escolher voltar pro menu ou fazer outra ação
    printf("Digite 1 para retornar ao menu: ");
    scanf("%d", &volta_menu);

    principal_atendente();
    }while(volta_menu != 1);

    return principal_adm();
}

//função para logar Atendimento //pronta
void sistemadeloginAtendimento();
void sistemadeloginAtendimento(){
    FILE *arquivo;
    char login [30];
    char senha[30];
    char permissao[30];
    char verificalogin[30];
    char verificasenha[30];
    bool achou = false;

    do{
        printf("Digite seu login: ");
        setbuf(stdin,NULL);
        gets(verificalogin);
        printf("\nDigite sua senha: ");
        setbuf(stdin,NULL);
        gets(verificasenha);


        arquivo = AbreArquivo('l',"SistemadeLoginAtendimento.txt");
        while(!feof(arquivo)){
            fscanf(arquivo, "%s %s %s", &login, &senha, &permissao);
            if(strcmp(verificalogin, login) == 0 && strcmp(verificasenha, senha) == 0){
                achou = true;
                if(strcmp(permissao, "Medico") == 0 ){
                    printf("Bem vindo Doutor (a).");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(2);
                    system("cls");
                    principal_medico();
                }

                if(strcmp(permissao, "Atendente") == 0 ){
                    principal_atendente();
                    printf("Bem vindo Atendente");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(2);
                    system("cls");
                }

                if(strcmp(permissao, "Administrador") == 0 ){
                    printf("Bem vindo Administrador");
                    sleep(2);
                    system("cls");
                    printf("Carregando...");
                    sleep(2);
                    system("cls");
                    principal_adm();
                }

            }else{
                printf("Caso Esqueceu seu login ou senha entre em contato com o administrador\nd4niel.arruda@gmail.com\n\nESPERE\n");
                sleep(2);
                system("cls");
            }
        }

    }while(!achou);
    FecharArquivo(arquivo);

}

//função para logar medico //pronta
void sistemadeloginMedico();
void sistemadeloginMedico(){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    FILE *arquivo;
    char login [30];
    char senha[30];
    char verificalogin[30];
    char verificasenha[30];

    do{
    printf("Digite seu login: ");
    setbuf(stdin,NULL);
    gets(verificalogin);
    printf("\nDiigte sua senha: ");
    setbuf(stdin,NULL);
    gets(verificasenha);


    arquivo = AbreArquivo('l',"SistemadeLoginMedico.txt");
    while(!feof(arquivo)){
        fscanf(arquivo, "%s %s", &login, &senha);
        if(strcmp(verificalogin, login) == 0){
            if(strcmp(verificasenha, senha) == 0){
            }
        }else{
            printf("Caso Esqueceu seu login ou senha entre em contato com o administrador\n d4niel.arruda@gmail.com\n");
            sleep(1,5);
            system("cls");
        }
    }

    }while(strcmp(verificalogin, login) != 0);
    FecharArquivo(arquivo);

}

//função para o sistema de login
void login_e_menu_usuario ();
void login_e_menu_usuario(){

    do{
    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR

    switch(login_escolha)
    {
    case 0:
        return 0;
        break;

    case 1:
        sistemadeloginMedico();
        break;

    case 2:
        sistemadeloginAtendimento();

        break;

    case 3:
        printf("Tudo Ok!");
        sleep(1,25);
        system ("cls");

        break;

    case 4:
        ;
        char senhaCase4[15] = "123456789"; //Tem que ter mais espaço que a string. Pelo menos 1 a mais que a palavra.
        char senhaCase4_1[15]; //Pode ser do mesmo tamanho que o login

        do{
            printf("SENHA: ");
            scanf("%s",senhaCase4_1); //String se lê com %s
            if (strcmp(senhaCase4, senhaCase4_1) == 0){
                printf("logado\n");
                sleep(1,5);
                system("cls");
            }else{
                printf("senha errada\n");
                sleep(1);
                system("cls");
            }
        }while(strcmp(senhaCase4, senhaCase4_1) !=0);
        break;

    default:
        printf("opção incorreta");
        sleep(1,25);
        system("cls");

    }
    } while (login_escolha >4);
}

//tela de menu do atendimento e suas funções
void principal_atendente();
void principal_atendente(){

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
    printf("\t -------------------------------");
    printf("\n\t| 1 - Cadastrar conveniado      |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 2 - Listar conveniados        |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 3 - Pesquisar conveniados     |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 4 - Deletar cadastro          |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 5 - Agendar Consulta          |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 6 - Listar agendamento        |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 7 - Pesquisar agendamento     |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 8 - Deletar agendamento       |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 9 - Situação dos feedbacks    |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 10 - Deletar feedbacks        |\n");
    printf("\t|-------------------------------");
    printf("\n\t| 11 - Relatorios de faturamento|\n");
    printf("\t -------------------------------");
    printf("\n\t| 0 - Sair                      |\n");
    printf("\t -------------------------------");


    printf("\nDigite uma opcao: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_atendente);

    sleep(1);
    system("cls");//limpa a tela

    switch (escolha_tela_atendente){
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
            printf("\nDigite seu Nascimento: ");
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
            printf("\nDigite o hora da consulta: ");
            scanf("%d", &hora_consulta);
            printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", hora_consulta);
            scanf("%d", &minuto_consulta);
            printf("\nDigite a especialidade da consulta: ");
            setbuf(stdin,NULL);
            gets(especialidade);
            printf("\nDigite o numero da carteirinha: ");
            setbuf(stdin,NULL);
            gets(num_carteira);
            printf("\n\n| Paz | Cancioneiro | Paulista |");
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
            printf("\nDigite o horario da sua consulta: ");
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


            if(excluir_feedback == 1){
                DeletarFeedback();
            }else{
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

            switch (escolha_menu_relatorio){
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
                    //volta ao menu do atendente
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
            exit(0);
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
void principal_conveniado(){

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

    switch(escolha_tela_conveniado){
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
            printf("(Andre) (Osvaldo) (Luis)");
            printf(": ");
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
            printf("\n\n| Paz | Cancioneiro | Paulista |");
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
            printf("\nDigite o horario da sua consulta: ");
            scanf("%d", &horarioDeletar);
            printf("\nHorario: %d:00 \nDigite o minuto da consulta: ", hora_consulta);
            scanf("%d", &minutoDeletar);
            DeletarAgendamento(nomeDeletarAgenda, num_carteiraDeletar, diaDeletar, horarioDeletar, minutoDeletar);
            volta_menu_conveniado();
        break;

        case 4:
            ;
            char nome_medico[30];
            int nota_medico;
            int nota_atendimento;

            printf("\nDigite o nome do medico: ");
            setbuf(stdin,NULL);
            gets(nome_medico);
            printf("\nDigite uma nota de 0 a 10 para o atensimento de seu medico: ");
            scanf("%d", &nota_medico);
            printf("\nDigite uma nota de 0 a 10 para seu atendimento em geral: ");
            scanf("%d", &nota_atendimento);
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
            printf("|----------------------------------------------------------------------------------------------|\n");

            volta_menu_conveniado();
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
void principal_adm(){

    setlocale(LC_ALL, "Portuguese");//Coloca acento na linguagem PTBR
    char login[30];
    char senha[30];
    int escolha_tela_adm;
    //MENU PRINCIPAL

    system("cls");
    printf("\n\t\tMENU");
    printf("\n");

    printf("\t|-----------------------------");
    printf("\n\t| 1 - Adicionar Usuarios      |\n");
    printf("\t|-----------------------------");
    printf("\n\t| 2 - Deletar Usuarios        |\n");
    printf("\t|-----------------------------");
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
        ;
        int escolha_tela_add_user_adm;
        //MENU ADD USUARIO
        printf("\n\n\t|-----------------------------");
        printf("\n\t| 1 - Adicionar Usuario Medico    |\n");
        printf("\t|---------------------------------");
        printf("\n\t| 2 - Adcionar Usuario Atendimento|\n");
        printf("\t|---------------------------------");
        printf("\n\t| 0 - Sair                        |\n");
        printf("\t|---------------------------------");

        printf("\nDigite uma opcao: ");
        sleep(0,5);
        sleep(0,5);//pausa a tela por x segundos
        scanf("%d", &escolha_tela_add_user_adm);

        sleep(1);
        system("cls");//limpa a tela

        switch(escolha_tela_add_user_adm){
            //OPÇÕES PARA ADD USER
            case 1:
                CadastraUsuariosMedico(login, senha);
                volta_menu_adm();
            break;

            case 2:
                CadastraUsuariosAtendimento(login, senha);
                volta_menu_adm();
            break;

            case 0:
                volta_menu_adm();
            break;

            default:
                system("cls");
                printf("\n\nOpcao invalida! Tente Novamente!\n\n");
                sleep(1,5);
                volta_menu_adm();
            break;
            }

    case 2:
        ;
        int escolha_tela_delete_user_adm;

        printf("\n\n\t|-----------------------------");
        printf("\n\t| 1 - Deletar Usuario Medico    |\n");
        printf("\t|---------------------------------");
        printf("\n\t| 2 - Deletar Usuario Atendimento|\n");
        printf("\t|---------------------------------");

        printf("\nDigite uma opcao: ");
        sleep(0,5);
        sleep(0,5);//pausa a tela por x segundos
        scanf("%d", &escolha_tela_delete_user_adm);

        sleep(1);
        system("cls");//limpa a tela

        switch(escolha_tela_delete_user_adm){
            case 1:
                ;
                char deletarlogin[30];
                printf("\nDigite o nome do usuario que deseja deletar: ");
                setbuf(stdin,NULL);
                gets(deletarlogin);
                DeletarUserMedico(deletarlogin);
                volta_menu_adm();
            break;

            case 2:
                DeletarUserAtendimento(deletarlogin);
                volta_menu_adm();
            break;

            default:
                system("cls");
                printf("\n\nOpcao invalida! Tente Novamente!\n\n");
                sleep(1,5);
                volta_menu_adm();
            break;
            }

    case 0:
        system("cls");
        printf("\n\nOpcao invalida! Tente Novamente!\n\n");
        sleep(1,5);
        volta_menu_adm();
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
void principal_medico(){

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
    printf("\t| -----------------------------------\n");

    printf("\nDigite uma opcao: ");
    sleep(0,5);
    sleep(0,5);//pausa a tela por x segundos
    scanf("%d", &escolha_tela_medico);

    sleep(1);
    system("cls");//limpa a tela

    switch (escolha_tela_medico){
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


    int login_menu;

    printf("\n");
    printf("\t\t\t\t\t\t*!Bem vindo!*\n\n");
    printf("DATA : %s\n\n\n",__DATE__);
    sleep(1);


    printf("\n\t\t\t\t\t\t  | Usuarios | \t\t");
    printf("\n\t\t__________________________________________________________________________________\n\n");
    printf("\t\t|0-Sair \t 1-Conveniado \t2-Usuários  |\n");
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
    	sistemadeloginAtendimento();
        break;
    default:
        printf("opção incorreta");
        sleep(1,25);
        system("cls");
    }
    return 0;
}
