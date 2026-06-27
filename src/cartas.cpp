#include "cartas.hpp"
#include <iostream>
#include <string>
#include <vector>
//constructores
carta::carta(PINTA pinta, VALOR valor, int fichas_base)
    : pinta(pinta), valor(valor), fichas_base(fichas_base){}
carta_normal::carta_normal(PINTA pinta, VALOR valor, int fichas_base)
    : carta (pinta, valor, fichas_base){}


PINTA carta::get_pinta(){return pinta;}
VALOR carta::get_valor(){return valor;}
int carta::get_fichas_base(){return fichas_base;};

int carta::get_valor_int(){
    switch (valor){
        case VALOR::DOS: return 2;
        case VALOR::TRES: return 3;
        case VALOR::CUATRO: return 4;
        case VALOR::CINCO: return 5;
        case VALOR::SEIS: return 6;
        case VALOR::SIETE: return 7;
        case VALOR::OCHO: return 8;
        case VALOR::NUEVE: return 9;
        case VALOR::DIEZ: return 10;
        case VALOR::J: return 10;
        case VALOR::K: return 10;
        case VALOR::Q: return 10;
        case VALOR::As: return 11;
        default: return 0;
    }
}
int carta::get_valor_secuencial () {//esto sirve para detectar una escala por ejemnplo
        switch(valor) {
            case VALOR::DOS: return 2;
            case VALOR::TRES: return 3;
            case VALOR::CUATRO: return 4;
            case VALOR::CINCO: return 5;
            case VALOR::SEIS: return 6;
            case VALOR::SIETE: return 7;
            case VALOR::OCHO: return 8;
            case VALOR::NUEVE: return 9;
            case VALOR::DIEZ: return 10;
            case VALOR::J: return 11;
            case VALOR::Q: return 12;
            case VALOR::K: return 13;
            case VALOR::As: return 14;
            default: return 0;
        }
    };
std::string carta::get_valor_string(){
    switch (valor){
        case VALOR::DOS: return "2";
        case VALOR::TRES: return "3";
        case VALOR::CUATRO: return "4";
        case VALOR::CINCO: return "5";
        case VALOR::SEIS: return "6";
        case VALOR::SIETE: return "7";
        case VALOR::OCHO: return "8";
        case VALOR::NUEVE: return "9";
        case VALOR::DIEZ: return "10";
        case VALOR::J: return "J";
        case VALOR::K: return "K";
        case VALOR::Q: return "Q";
        case VALOR::As: return "As";
        default: return "N/A";
    }
}
std::string carta::get_pinta_string(){
    switch (pinta){
        case PINTA::CORAZON: return "Corazon";
        case PINTA::DIAMANTE: return "Diamante";
        case PINTA::PICA: return "Pica";
        case PINTA::TREBOL: return "Trebol";
        default: return "N/A";
    }
}

int carta_normal::calcular_puntaje(){ return fichas_base; }

std::string carta_normal::get_description(){
    return"["+ get_valor_string()+ " de "+get_pinta_string() +"]";
}

carta* carta_normal::clonar(){
    // Crea una carta idéntica en una NUEVA dirección de memoria
    return new carta_normal(pinta, valor, fichas_base);
}
