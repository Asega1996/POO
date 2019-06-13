#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

class EsBlanco: public unary_function<char,bool>
{
  public:
    bool operator()(char c) const {return isspace(c);}
};

class EsDigito: public unary_function<char,bool>
{
  public:
    bool operator()(char c) const {return isdigit(c);}
};

class Numero {
public:
  enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
  Numero (Cadena numero);
  operator const char*() const;

  class Incorrecto{
    public:
      Incorrecto (Numero::Razon razon): razon_(razon){}
      Numero::Razon razon() const{return razon_;}
    private:
      Numero::Razon razon_;
    };

private:
  Cadena numero_;
};

bool operator < (const Numero& n1, const Numero& n2);

class Usuario;

class Tarjeta {
public:
  enum Tipo{VISA,Mastercard,Maestro,JCB,AmericanExpress};
  Tarjeta(Tipo tipo, const Numero& n, Usuario& usuario, const Fecha& caducidad);

  Tarjeta(const Tarjeta&) = delete;
  Tarjeta& operator=(const Tarjeta&) = delete;

  ~Tarjeta();

  Tipo tipo() const {return tipo_;}
  Numero numero() const {return n_;}
  const Usuario* titular() const {return usuario_;}
  Fecha caducidad() const {return caducidad_;}
  Cadena titular_facial() const {return titular_facial_;}

  void anula_titular();

  class Caducada{
  public:
    Caducada(const Fecha& caducada) : caducada_(caducada){}
    const Fecha& cuando() const { return caducada_;}

  private:
    Fecha caducada_;
  };

private:
  Tipo tipo_;
  Numero n_;
  Usuario* const usuario_;
  Fecha caducidad_;
  Cadena titular_facial_;
};

bool operator < (const Tarjeta& t1,const Tarjeta& t2);
ostream& operator << (ostream& os , const Tarjeta& tar);
ostream& operator << (ostream& os, Tarjeta::Tipo const& tipo);


#endif
