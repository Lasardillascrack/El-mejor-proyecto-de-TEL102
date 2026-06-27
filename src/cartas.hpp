#ifndef CARTAS_H
#define CARTAS_H
#include <iostream>
#include <vector>
#include <string>

//enum class para las pintas y los numeros de cartas.
enum class PINTA{ CORAZON,TREBOL,DIAMANTE,PICA };
enum class VALOR{ DOS,TRES,CUATRO,CINCO,SEIS,SIETE,OCHO,NUEVE,DIEZ,J,Q,K,As };

class carta{
protected:
    PINTA pinta;
    VALOR valor;
    int fichas_base;
public:
    carta (PINTA pinta, VALOR valor, int fichas_base);
    virtual ~carta() {}

    VALOR get_valor();
    PINTA get_pinta();
    int get_fichas_base();
    int get_valor_int();
    int get_valor_secuencial ();
    std::string get_valor_string();
    std::string get_pinta_string();

    virtual carta* clonar() = 0;
    virtual int calcular_puntaje()= 0;
    virtual std::string get_description ()=0;
};

//clases derivadas, aqui se pueden crear cartas custom que se podran comprar en la tienda.
class carta_normal:public carta{
public:
    //constructor
    carta_normal(PINTA pinta, VALOR valor, int fichas_base);
    //clases derivadas del virtual
    carta* clonar()override; //clonamos las cartas para no modificar el mazo original, y generar un clon temporal que dura la partida
    int calcular_puntaje() override;
    std::string get_description() override;
};

#endif