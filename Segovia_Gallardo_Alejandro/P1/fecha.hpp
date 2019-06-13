#ifndef FECHA_HPP_
#define FECHA_HPP_

#include <iostream>
using namespace std;

class Fecha{

  public:
    explicit Fecha(int dia = 0, int mes = 0, int anno = 0);                             //Constructor de la clase
    Fecha(const char*);                             //Constructor de Fecha cadena
    class Invalida{                                  //Clase para interactuar con los errores
      public:
        Invalida(const char* error): error_(error){}
        const char* por_que() const;
      private:
        const char* error_;
    };

    //Metodos observadores

    int dia() const;
    int mes() const;
    int anno() const;

    //Constantes de la clase

    static const int AnnoMaximo=2037;
    static const int AnnoMinimo=1902;

    //Sobrecarga de Operadores

    Fecha& operator ++();
    Fecha operator ++(int);
    Fecha& operator --();
    Fecha operator --(int);
    Fecha& operator +=(int);
    Fecha& operator -=(int);
    Fecha operator +(int) const;
    Fecha operator -(int) const;

    //Operador conversion a cadena

    const char* cadena() const;

  private:
    int dia_, mes_, anno_;                             //Variables usadas en la clase
    void fechaValida() const;         //Funcion para verificar si la fecha es correcta
    //tm& corregido() const;         //Funcion para convertir la fecha
};

//Sobrecarga de operadores externos

bool operator <(const Fecha&, const Fecha&) noexcept;
bool operator >(const Fecha&, const Fecha&) noexcept;
bool operator ==(const Fecha&, const Fecha&) noexcept;
bool operator !=(const Fecha&, const Fecha&) noexcept;
bool operator <=(const Fecha&, const Fecha&) noexcept;
bool operator >=(const Fecha&, const Fecha&) noexcept;
long operator -(const Fecha&, const Fecha&);
ostream& operator <<(ostream&, const Fecha&);
istream& operator >>(istream&, Fecha&);


#endif
