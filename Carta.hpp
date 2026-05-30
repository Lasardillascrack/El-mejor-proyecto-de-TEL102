#ifndef CARTA_HPP
#define CARTA_HPP

#include <string>

class Carta {
private:
    std::string tipoPinta;    
    std::string textoValor;   
    int puntos;               

public:
    Carta(std::string _tipoPinta, std::string _textoValor, int _puntos);

    std::string obtenerPinta() const;
    std::string obtenerValor() const;
    int obtenerPuntos() const;

    void mostrar() const;
};

#endif
