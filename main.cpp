#include <iostream>
using namespace std;

/*Declaracao de uso de IA: Nesse trabalho, utilizamos IA para organizar as ideias e relembrar a estrutura de validacao de tipo de dados.
No entanto, conseguimos explicar cada linha das funcoes de entrada de dados*/

typedef struct{
    int hora, minuto;
} Horario;

typedef struct{
    Horario inicio, fim;
    string tipo, assunto, local;
} Compromisso;

typedef struct{
    int dia, mes, ano, qntd_compromissos = 0;
    Compromisso compromissos[5];
} Data;

// Subrotina entradas
int ler_numero_inteiro(string, int, int);
string ler_string();
char ler_char();

// Subrotinas operações
int apresentar_menu();
void iniciar_agenda(Data []);
void incluirCompromisso(Data []);
void excluirCompromisso(Data []);
void mostrarCompromisso(Data []);
void mostrarTodosCompromissos(Data [], string []);
void ordenar_vetor_horarioRec(Compromisso [], int);
int buscarCompromissoRec(Compromisso [], int, int, int, int = 0);
int buscarIndiceDiaRec(Data [], int , int);
void ImprimirCompromissoNaTela(Compromisso);

int main(){
    Data agenda[7];
    int opcao;
    bool iniciado = false;
    string teste;
    string dia_semana[7] = {"domingo", "segunda-feira", "terca-feira", "quarta,feira", "quinta-feira", "sexta-feira", "sabado"};
    do{
        system("cls");
        opcao = apresentar_menu();
        switch(opcao){
            case 1:
                system("cls");
                iniciar_agenda(agenda);
                iniciado = true;
                system("pause");
            break;
            case 2:
                system("cls");
                if(iniciado){
                    incluirCompromisso(agenda);
                    system("pause");
                    break;
                }
                cout << "Erro: Agenda nao foi iniciada..." << endl;
                system("pause");
            break;
            case 3:
                system("cls");
                if(iniciado){
                    excluirCompromisso(agenda);
                    cin.ignore();
                    system("pause");
                    break;
                }
                cout << "Erro: Agenda nao foi iniciada..." << endl;
                system("pause");
            break;
            case 4:
                system("cls");
                if(iniciado){
                    mostrarCompromisso(agenda);
                    system("pause");
                    break;
                }
                cout << "Erro: Agenda nao foi iniciada..." << endl;
                system("pause");
            break;
            case 5:
                system("cls");
                if(iniciado){
                    mostrarTodosCompromissos(agenda, dia_semana);
                    system("pause");
                    break;
                }
                cout << "Erro: Agenda nao foi iniciada..." << endl;
                system("pause");
            break;
            case 6:
                system("cls");
                cout << "Vejo voce novamente em breve!" << endl;
                system("pause");
            break;
        }
    }while(opcao != 6);
    return 0;

}

int ler_numero_inteiro(string mensagem, int minimo, int maximo){
    /*Essa funcao le a entrada e valida se e do tipo int*/
    string texto;
    int numero;
    bool valido;
    do{
        valido = true;
        cout << mensagem;
        getline(cin, texto);

        if(texto.empty()){
            valido = false;
        }
        else{
            for(size_t i = 0; i < texto.size(); i++){
                if(!isdigit(texto[i])){
                    valido = false;
                }
            }
        }

        if(valido){
            numero = stoi(texto);
            if(numero < minimo || numero > maximo){
                valido = false;
            }
        }

        if(!valido){
            if(mensagem == "Digite a opcao: "){
                cout << "Entrada invalida, ";
                system("pause");
                return -1; //para não apagar o menu principal caso o usuário coloque algo errado.
            }else{
            cout << "Entrada invalida..." << endl;
            valido = false;
            }
        }
    }while(!valido);
    return numero;
}

string ler_string(string mensagem){
    /*Essa funcao le a entrada e valida se e do tipo string*/
    string texto;
    bool valido;
    do{
        valido = true;
        cout << mensagem;
        getline(cin, texto);
        if(texto.empty()){
            valido = false;
        }
        else{
            for(size_t i = 0; i < texto.size(); i++){
                if(!isalpha(texto[i]) && !ispunct(texto[i]) && !isspace(texto[i])){
                    valido = false;
                }
            }
        }

        if(!valido){
            cout << "Erro: Entrada invalida, tente novamente..." << endl;
            system("pause");
            valido = false;
        }
    }while(!valido);
    return texto;
}

char ler_char(){
    /*Essa funcao le a entrada e valida se e do tipo char*/
    char caracter;
    bool valido;
    do{
        valido = true;
        cin >> caracter;
        caracter = toupper(caracter);
        if(caracter == ' '){
            valido = false;
        }else if(!isalpha(caracter)){
            valido = false;
        }

        if(!valido){
            cout << "Entrada invalida..." << endl;
            valido = false;
        }
    }while(!valido);
    return caracter;
}

int apresentar_menu(){
    /*Essa funcao apresenta o menu principal na tela do usuario*/
    int resp_int;
    cout << "--- AGENDA SEMANAL ---" << endl;
    cout << "1. Inicializar data" << endl;
    cout << "2. Incluir novo compromisso" << endl;
    cout << "3. Excluir compromisso" << endl;
    cout << "4. Buscar compromisso" << endl;
    cout << "5. Consultar todos os compromissos"  << endl;
    cout << "6. Sair" << endl;
    resp_int = ler_numero_inteiro("Digite a opcao: ", 1, 6);
    return resp_int;
}

void iniciar_agenda(Data agenda[]){
     /*Essa funcao inicia a agenda automaticamente com a data inicial informada pelo usuario*/
    int primeira_data = 1;
    int dia, mes, ano;
    char resp1;
    cout << "--- Inicializar Agenda ---" << endl;

    dia = ler_numero_inteiro("Informe o dia de inicio (DD): ", 1, 31);
    mes = ler_numero_inteiro("Informe o mes de inicio (MM): ", 1, 12);
    ano = ler_numero_inteiro("Informe o ano (AAAA): ", 1900, 2100);

    do{
        cout << "Deseja adicionar essa data de inicio?(" << dia << "/" << mes << "/" << ano << ") S/N: ";
        resp1 = ler_char();
        if(resp1 != 'S' && resp1 != 'N'){
            cout << "Erro: Resposta invalida, tente novamente..." << endl;
        }
    }while(resp1 != 'S' && resp1 != 'N');

    cin.ignore();

    if(resp1 == 'N'){
        system("cls");
        cout << "Data de inicio apagada, retornando..." << endl;



        return;
    }else{
        system("cls");
        cout << "Agenda iniciada com sucesso!" << endl;
        agenda[0].dia = dia;
        agenda[0].mes = mes;
        agenda[0].ano = ano;
    }
    for(int i = 1; i < 7; i++){
        if(agenda[i-1].dia == 31){
            agenda[i].dia = primeira_data;
            if(agenda[i-1].mes == 12){
                agenda[i].mes = primeira_data;
                agenda[i].ano = agenda[i-1].ano + 1;
            }else{
                agenda[i].mes = agenda[i-1].mes + 1;
                agenda[i].ano = agenda[i-1].ano;
            }
        }else{
            agenda[i].dia = agenda[i-1].dia + 1;
            agenda[i].mes = agenda[i-1].mes;
            agenda[i].ano = agenda[i-1].ano;
        }
    }
}

void incluirCompromisso(Data agenda[]){
    /*Essa funcao inclui um compromisso no vetor Data compromissos[], sendo escolhido a data e horario pelo user*/
    int hora_inicial, min_inicial, hora_final, min_final, horaIR, horaFR;
    cout << "--- Incluir Compromisso ---\n";
    cout << "escolha de " << agenda[0].dia << "/" << agenda[0].mes << "/" << agenda[0].ano << " ate " << agenda[6].dia << "/" << agenda[6].mes << "/" << agenda[6].ano << endl;
    int diaIn = ler_numero_inteiro("Dia: ", 1, 31);

    int indice = buscarIndiceDiaRec(agenda, diaIn, 0);

    if(indice == -1) {
        cout << "\nErro: Dia fora da semana da agenda!\n";
        return;
    }
    if(agenda[indice].qntd_compromissos >= 5){
        cout << "A agenda esta lotada." << endl;
        return;
    }else{
        hora_inicial = ler_numero_inteiro("Hora inicial: ", 0,23);
        min_inicial = ler_numero_inteiro("Minuto inicial: ", 0,59);
        hora_final  = ler_numero_inteiro("Hora final: ", 0,23);
        min_final = ler_numero_inteiro("Minuto final: ", 0,59);
        int horaIN = (hora_inicial *60) + min_inicial;
        int horaFN = (hora_final *60) + min_final;

        for(int j = 0; j < agenda[indice].qntd_compromissos; j++){
            horaIR = (agenda[indice].compromissos[j].inicio.hora*60) + agenda[indice].compromissos[j].inicio.minuto;
            horaFR = (agenda[indice].compromissos[j].fim.hora*60) + agenda[indice].compromissos[j].fim.minuto;
            if(horaIN <= horaFR && horaFN >= horaIR){
                cout << "Data ja ocupada!!";
                return;
            }
        }
    }
    agenda[indice].compromissos[agenda[indice].qntd_compromissos].inicio.hora = hora_inicial;
    agenda[indice].compromissos[agenda[indice].qntd_compromissos].inicio.minuto = min_inicial;
    agenda[indice].compromissos[agenda[indice].qntd_compromissos].fim.hora = hora_final;
    agenda[indice].compromissos[agenda[indice].qntd_compromissos].fim.minuto = min_final;

    //cout << "Tipo: ";
    agenda[indice].compromissos[agenda[indice].qntd_compromissos].tipo = ler_string("Tipo:");
    //cout << "Assunto: ";
    agenda[indice].compromissos[agenda[indice].qntd_compromissos].assunto= ler_string("Assunto: ");
    //cout << "Local: ";
    agenda[indice].compromissos[agenda[indice].qntd_compromissos].local= ler_string("Local: ");
    agenda[indice].qntd_compromissos++;
    ordenar_vetor_horarioRec(agenda[indice].compromissos, agenda[indice].qntd_compromissos);
    cout << "Evento criado com sucesso!!" << endl;
}

 void excluirCompromisso(Data agenda[]){
    /*Essa funcao busca por um comprimisso para ser excluido, caso seja encontrado, o user devera confirmar a exclusao*/
    cout << "--- Excluir Compromisso ---" << endl;
    int dia, indice, indice_compromisso, hora_inicial, min_inicial;
    string minutoI, minutoF;
    char resp;
    cout << "escolha de " << agenda[0].dia << "/" << agenda[0].mes << "/" << agenda[0].ano << " até " << agenda[6].dia << "/" << agenda[6].mes << "/" << agenda[6].ano << endl;
    dia = ler_numero_inteiro("Informe o dia de inicio (DD): ", 1, 31);
    indice = buscarIndiceDiaRec(agenda, dia, 0);

    if(indice == -1) { // se for -1, não achou o dia;
        system("cls");
        cout << "Erro: Dia fora da semana da agenda!\n";
        return;
    }
    hora_inicial = ler_numero_inteiro("Hora inicial: ", 0,23);
    min_inicial = ler_numero_inteiro("Minuto inicial: ", 0,59);
    indice_compromisso = buscarCompromissoRec(agenda[indice].compromissos, hora_inicial, min_inicial, agenda[indice].qntd_compromissos);
    if(indice_compromisso == -1){ // se for -1, não achou o compromisso
        system("cls");
        cout << "Erro: Compromisso nao encontrado" << endl;
        return;
    }
    // Mostrando o compromisso escolhido;
    ImprimirCompromissoNaTela(agenda[indice].compromissos[indice_compromisso]);
    do{
        cout << "Realmente deseja excluir esse compromisso?(" << dia << "/" << agenda[indice].mes << "/" << agenda[indice].ano << ") S/N: ";
        resp = ler_char();
        if(resp != 'S' && resp != 'N'){
            cout << "Erro: Resposta invalida, tente novamente..." << endl;
            system("pause");
        }
    }while(resp != 'S' && resp != 'N');
    if(resp == 'N'){
        system("cls");
        cout << "Erro: Exclusão de compromisso cancelado, retornando..." << endl;
    }else{
        if(agenda[indice].qntd_compromissos > 1){
            for(int i = indice_compromisso; i < agenda[indice].qntd_compromissos - 1; i++){
                agenda[indice].compromissos[i] = agenda[indice].compromissos[i+1];
            }
            agenda[indice].qntd_compromissos--;
        }else{
                agenda[indice].qntd_compromissos = 0;
        }
        cout << "Compromisso excluido com sucesso!" << endl;
     }

}

void mostrarCompromisso(Data agenda[]){
    /*Essa funcao busca e mostra todos compromissos de um dia*/
    cout << "--- Mostrar Compromisso ---" << endl;
    int dia, indice;
    string minutoI, minutoF;
    dia = ler_numero_inteiro("Informe o dia de inicio (DD): ", 1, 31);
    indice = buscarIndiceDiaRec(agenda, dia, 0);

    if(indice == -1) {
        system("cls");
        cout << "Erro: Dia fora da semana da agenda!\n";
        return;
    }
    if(agenda[indice].qntd_compromissos ==0){
        system("cls");
        cout << "Erro: Nenhum compromisso agendado para esse dia!";
        return;
    }

    cout << "[" << agenda[indice].dia << "/" << agenda[indice].mes << "]" << endl;
    for(int j = 0; j < agenda[indice].qntd_compromissos; j++){
        ImprimirCompromissoNaTela(agenda[indice].compromissos[j]);
    }
    cout << "===============" << endl;
}

void mostrarTodosCompromissos(Data agenda[], string dia_semana[]){
    /*Essa funcao mostra todos os compromisso da agenda*/
    string minutoI, minutoF;
    cout << "--- Mostrar Todos os Compromissos ---" << endl;
    cout << "===============" << endl;
    for(int i = 0; i<7; i++){
        cout << "[" << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].ano << "]" << endl;

        cout << dia_semana[i] << endl;
        if(agenda[i].qntd_compromissos == 0){
            cout << "Nenhum compromisso agendado." << endl;
        }else{
            for(int j = 0; j < agenda[i].qntd_compromissos; j++){
                ImprimirCompromissoNaTela(agenda[i].compromissos[j]);
                if(agenda[i].qntd_compromissos > 1){
                    cout << "--------------" << endl;
                }
            }
        }
        cout << "===============" << endl;
    }

}

int buscarIndiceDiaRec(Data agenda[], int diaB, int indice = 0) { //diaB = dia buscado
    /*Essa funcao busca o indice do dia de forma recursiva, usado para pesquisar o dia*/

    // caso chegue no final do vetor e nao ache
    if (indice > 6) {
        return -1;
    }
    // achou
    if (agenda[indice].dia == diaB) {
        return indice;
    }
    // recusividade
    return buscarIndiceDiaRec(agenda, diaB, indice + 1);
}

void ordenar_vetor_horarioRec(Compromisso compromissos[], int n) {
    /*Essa funcao ordena os horarios dos compromissos de um dia especifico de forma recursiva*/
    if (n <= 1) {
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        bool trocar = false;

        if (compromissos[i].assunto == "" && compromissos[i+1].assunto != "") {
            trocar = true;
        }
        else if (compromissos[i].assunto != "" && compromissos[i+1].assunto != "") {

            if (compromissos[i].inicio.hora > compromissos[i+1].inicio.hora ||
               (compromissos[i].inicio.hora == compromissos[i+1].inicio.hora && compromissos[i].inicio.minuto > compromissos[i+1].inicio.minuto)) {
                trocar = true;
            }
        }

        if (trocar) {
            Compromisso temp = compromissos[i];
            compromissos[i] = compromissos[i+1];
            compromissos[i+1] = temp;
        }
    }

    ordenar_vetor_horarioRec(compromissos, n - 1);
}

int buscarCompromissoRec(Compromisso comps[], int horaB, int minB, int n, int indice) { // minB = minuto buscado, horaB = hora buscada
    /*Essa funcao busca o indice do compromisso especifico de um dia informado pelo user de forma recursiva, usado para pesquisar o compromisso do dia*/
    if (n <= 0) {
        return -1;
    }

    if (comps[indice].assunto != "" && comps[indice].inicio.hora == horaB && comps[indice].inicio.minuto == minB) {
        return indice;
    }

    return buscarCompromissoRec(comps, horaB, minB, n - 1, indice+1);
}

void ImprimirCompromissoNaTela(Compromisso comp){
    string minutoI = to_string(comp.inicio.minuto);
    string minutoF = to_string(comp.fim.minuto);
    cout << "===============" << endl;
    cout << comp.inicio.hora << "h" << (comp.inicio.minuto < 10 ? "0"+minutoI : minutoI)<< " ate ";
    cout << comp.fim.hora << "h" << (comp.fim.minuto < 10 ?  "0"+minutoF : minutoF) << endl;
    cout << "Tipo: ";
    cout << comp.tipo << endl;
    cout << "Assunto: ";
    cout << comp.assunto << endl;
    cout << "Local: ";
    cout << comp.local << endl;
}
