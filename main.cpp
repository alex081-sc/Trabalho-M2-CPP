#include <iostream>
using namespace std;

typedef struct{
    int hora_inicial, hora_final;
    string tipo, assunto, local;
} Compromisso;

typedef struct{
    int dia, mes, ano, qntd_compromissos;

    Compromisso compromissos[5];
} Data;

int apresentar_menu();
int ler_numero_inteiro(string);
void iniciar_agenda(Data[]);
string ler_string(string);


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
                cout << "escreva: " << endl;
                ler_string(teste);
                cout << "teste deu certo";
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
                for(int i = 0; i<7; i++){
                    cout << dia_semana[i] << endl;
                    cout << "[" << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].ano << "]" << endl;
                }
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
    int numero ;
    bool valido = true;
    cout << mensagem;
    getline(cin, texto);
    do{
        // 1) tipo: so digitos, nao vazio, tamanho que cabe num int
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

        // 2) intervalo: so converte depois de validar o tipo
        if(valido){
            numero = stoi(texto);
            if(numero < minimo || numero > maximo){
                valido = false;
            }
        }

        if(!valido){
            system("cls");
            cout << "Entrada invalida..." << endl;
            system("pause");
            return 0;
        }
    }while(!valido);
    return numero;
}

string ler_string(string mensagem){
    string texto;
    bool valido = true;
    cout << mensagem;
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
            system("cls");
            cout << "Entrada invalida..." << endl;
            system("pause");
            return 0;
        }
    }while(!valido);
    return texto;
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

    dia = ler_numero_inteiro("Informe o dia de início: ", 1, 31);
    mes = ler_numero_inteiro("Informe o mes de início: ", 1, 12);
    ano = ler_numero_inteiro("Informe o ano: ", 0, 2100);

    cout << "Confirme a data de inicio (" << dia << "/" << mes << "/" << ano << "): "; cin >> resp1;
    cin.ignore();

    if(resp1 == 'n'){
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

