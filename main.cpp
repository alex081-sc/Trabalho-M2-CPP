#include <iostream>
using namespace std;

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

int apresentar_menu();
int ler_numero_inteiro(string, int, int);
void iniciar_agenda(Data[]);
void mostrarTodosCompromissos(Data[], string[]);
string ler_string();
void incluirCompromisso(Data[]);
int buscarIndiceDiaRec(Data [], int , int);
char ler_char();
void ordenar_vetor_horarioRec(Compromisso [], int);
int buscarCompromissoRec(Compromisso [], int, int, int);

int main(){
    Data agenda[7];
    int opcao;
    string teste;
    string dia_semana[7] = {"domingo", "segunda-feira", "terca-feira", "quarta,feira", "quinta-feira", "sexta-feira", "sabado"};
    do{
        system("cls");
        opcao = apresentar_menu();
        switch(opcao){
            case 1:
                system("cls");
                iniciar_agenda(agenda);
            break;
            case 2:
                system("cls");
                incluirCompromisso(agenda);
                system("pause");
            break;
            case 3:
                system("cls");
                cout << "caso 3" << endl;
                system("pause");
            break;

            case 4:
                system("cls");
                cout << "caso 4" << endl;
                system("pause");
            break;
            case 5:
                system("cls");
                mostrarTodosCompromissos(agenda, dia_semana);
                system("pause");
            break;
            case 6:
                system("cls");
                cout << "tchauu" << endl;
                system("pause");
            break;
        }
    }while(opcao != 6);
    return 0;

}

int ler_numero_inteiro(string mensagem, int minimo, int maximo){
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
                system("cls");
                cout << "Entrada invalida..." << endl;
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

string ler_string(){
    string texto;
    bool valido = true;
    getline(cin, texto);
    do{
        // 1) tipo: so digitos, nao vazio, tamanho que cabe num int
        if(texto.empty()){
            valido = false;
        }
        else{
            for(size_t i = 0; i < texto.size(); i++){
                if(!isalpha(texto[i])){
                    valido = false;
                }
            }
        }

        if(!valido){
            cout << "Entrada invalida..." << endl;
            system("pause");
            valido = false;
        }
    }while(!valido);
    return texto;
}

char ler_char(){
    char caracter;
    bool valido = true;
    cin >> caracter;
    caracter = toupper(caracter);
    do{
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
    int resp_int;

    cout << "--- AGENDA SEMANAL ---" << endl;
    cout << "1. Inicializar data" << endl;
    cout << "2. Incluir novo compromisso" << endl;
    cout << "3. Excluir novo compromisso" << endl;
    cout << "4. Consultar compromissos de um dia" << endl;
    cout << "5. Consultar todos os compromissos" << endl;
    cout << "6. Sair" << endl;
    resp_int = ler_numero_inteiro("Digite a opcao: ", 1, 6);

    return resp_int;
}

void iniciar_agenda(Data agenda[]){
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
            cout << "Resposta invalida... Tente novamente" << endl;
        }
    }while(resp1 != 'S' && resp1 != 'N');

    cin.ignore();

    if(resp1 == 'N'){
        system("cls");
        cout << "Data de inicio apagada, retornando..." << endl;
        system("pause");
        dia = 0;
        mes = 0;
        ano = 0;
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
    int diaIn, hora_inicial, min_inicial, hora_final, min_final, indice;
    cout << "--- Incluir Compromisso ---\n";
    diaIn = ler_numero_inteiro("Data Inicial: ", 1, 31);
    indice = buscarIndiceDiaRec(agenda, diaIn, 0);


    if(indice == -1) {
        cout << "Erro: Dia fora da semana da agenda!\n";
        return;
    }
    if(agenda[indice].qntd_compromissos > 5){
        cout << "A agenda esta lotada." << endl;
        return;
    }else{
        hora_inicial = ler_numero_inteiro("Hora inicial: ", 0,23);
        min_inicial = ler_numero_inteiro("Minuto inicial: ", 0,60);
        hora_final  = ler_numero_inteiro("Hora final: ", 0,23);
        min_final = ler_numero_inteiro("Minuto final: ", 0,60);
        for(int j = agenda[indice].qntd_compromissos; j < 5; j++){
            if(hora_inicial >= agenda[indice].compromissos[j].fim.hora || hora_final <= agenda[indice].compromissos[j].fim.hora){
                agenda[indice].compromissos[j].inicio.hora = hora_inicial;
                agenda[indice].compromissos[j].inicio.minuto = min_inicial;
                agenda[indice].compromissos[j].fim.hora = hora_final;
                agenda[indice].compromissos[j].fim.minuto = min_final;

                cout << "Tipo: ";
                agenda[indice].compromissos[j].tipo = ler_string();
                cout << "Assunto: ";
                agenda[indice].compromissos[j].assunto= ler_string();
                cout << "Local: ";
                agenda[indice].compromissos[j].local= ler_string();
                agenda[indice].qntd_compromissos++;
                ordenar_vetor_horarioRec(agenda[indice].compromissos, agenda[indice].qntd_compromissos);
                cout << "Evento criado com sucesso!!" << endl;
                return;
            }
        }
    }
    cin.ignore();

    cout << "Data ja ocupada!!";
    return;
}

void mostrarTodosCompromissos(Data agenda[], string dia_semana[]){
    for(int i = 0; i<7; i++){
        cout << "===============" << endl;
        cout << "[" << agenda[i].dia << "/" << agenda[i].mes << "]" << endl;
        cout << dia_semana[i] << endl;
        if(agenda[i].compromissos[i].tipo.empty()){ // se não tem nenhum tipo não existe evento pq nao foi iniciado.
            cout << "Nenhum evento agendado." << endl;
        }else{
            for(int j = 0; j < agenda[i].qntd_compromissos; j++){
                cout << agenda[i].compromissos[j].inicio.hora << "h" << agenda[i].compromissos[j].inicio.minuto << " ate ";
                cout << agenda[i].compromissos[j].fim.hora << "h" << agenda[i].compromissos[j].fim.minuto << endl;
                cout << agenda[i].compromissos[j].tipo << endl;
                cout << agenda[i].compromissos[j].local << endl;
                cout << agenda[i].compromissos[j].assunto << endl;
                if(agenda[i].qntd_compromissos > 1){
                    cout << "--------------" << endl;
                }
            }
        }
    }
}

int buscarIndiceDiaRec(Data agenda[], int diaB, int indice) { //diaB = dia buscado
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

int buscarCompromissoRec(Compromisso compromissos[], int horaB, int minB, int indice = 0) { // minB = minuto buscado, horaB = hora buscada
    if (indice >= 5) {
        return -1;
    }

    if (compromissos[indice].assunto != "" && compromissos[indice].inicio.hora == horaB && compromissos[indice].inicio.minuto == minB) {
        return indice;
    }

    return buscarCompromissoRec(compromissos, horaB, minB, indice + 1);
}
