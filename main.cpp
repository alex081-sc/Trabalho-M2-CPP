#include <iostream>
using namespace std;

typedef struct{
    int hora_inicial, hora_final;
    string tipo, assunto, local;
} Compromisso;

typedef struct{
    int dia, mes, ano, qntd_compromissos, dia_semana;
    Compromisso compromissos[5];
} Data;

int apresentar_menu();
int ler_numero_inteiro(string);
void iniciar_agenda(Data[]);


int main(){
    Data agenda[7];
    int opcao;
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
                cout << "caso 2" << endl;
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
                    cout << "[" << agenda[i].dia << "/" << agenda[i].mes << "]";
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

void iniciar_agenda(Data agenda[7]){
    int dia_comeco_mes = 1;
    cout << "--- Inicializar Agenda ---" << endl;
    agenda[0].dia = ler_numero_inteiro("Informe o dia de início: ", 1, 31);
    agenda[0].mes = ler_numero_inteiro("Informe o mes de início: ", 1, 12);
    agenda[0].ano = ler_numero_inteiro("Informe o ano: ", 0, 2100);

    for(int i = 1; i < 7; i++){
        if(agenda[i-1].dia == 31){
            agenda[i].dia = dia_comeco_mes;
            agenda[i].mes = agenda[i-1].mes + 1;
            agenda[i].ano = agenda[0].ano;
            dia_comeco_mes++;

        }else{
            agenda[i].dia = agenda[i-1].dia + 1;
            agenda[i].mes = agenda[i-1].mes;
            agenda[i].ano = agenda[0].ano;
        }
    }
}
//odajwopfawopifawjiopfawjf
