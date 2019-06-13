#include <cstring>
#include "tarjeta.hpp"
#include "usuario.hpp"
#include <iomanip>
#include <functional>
#include <algorithm>

bool luhn(const Cadena& numero);

void eliminarChar(Cadena& cad, size_t pos)
{
    Cadena nuevo = cad.substr(0, pos);

    if ((pos + 1) < cad.length())
        nuevo += Cadena(cad, pos + 1);

    cad = move(nuevo);    //DABA FALLOS EN EL CTOR MOVTO DE CADENA
}


Numero::Numero(Cadena numero): numero_(numero)
{
  bool luhn(const Cadena& numero);

  Cadena::iterator fin = remove_if(numero_.begin(),numero_.end(),EsBlanco());
  if(fin != numero_.end())
  {
    *fin = '\0';
    Cadena sd (numero_.c_str());
    numero_ = sd;
  }
  if(find_if(numero_.begin(),numero_.end(), not1(EsDigito())) != numero_.end())
    throw Incorrecto(DIGITOS);

  if (numero_.length() < 13 or numero_.length() > 19)
    throw Incorrecto(Razon::LONGITUD);

  if (!luhn(numero_))
    throw Incorrecto(Razon::NO_VALIDO);
}


bool operator < (const Numero& n1, const Numero& n2)
{
  return (std::strcmp(n1,n2) < 0);

}


Numero::operator const char*() const
{
  return (numero_.c_str());

}


class Usuario;


Tarjeta::Tarjeta(Tipo tipo, const Numero& n, Usuario& usuario,
  const Fecha& caducidad):
tipo_(tipo), n_(n), usuario_(&usuario), caducidad_(caducidad),
titular_facial_(usuario.nombre() + " " + usuario.apellidos())
{
if (caducidad < Fecha())
  throw Caducada(caducidad);

usuario_->es_titular_de(*this);
}


Tarjeta::~Tarjeta()
{
  if (usuario_) usuario_->no_es_titular_de(*this);
}


void Tarjeta::anula_titular()
{
  const_cast<Usuario*&>(usuario_) = nullptr;
}


bool operator <(const Tarjeta& t1, const Tarjeta& t2)
{
  return (t1.numero() < t2.numero());
}


ostream& operator << (ostream& os, Tarjeta::Tipo const& tipo)
{
  switch (tipo)
  {
    case 0:    os << " VISA ";  break;
    case 1: os << " Mastercard "; break;
    case 2: os << " Maestro ";  break;
    case 3: os << " JCB "; break;
    case 4: os << " AmericanExpress "; break;
  }

  return os;
}

ostream& operator << (ostream& os , const Tarjeta& tar)
{
  os << tar.tipo() << "\n" << tar.numero() << "\n";
  os << tar.titular_facial() << "\n" << "Caduca: ";
  os << setfill('0') << setw(2);
  os << tar.caducidad().mes() << "/" << setw(2);
  os << (tar.caducidad().anno() % 100);

    return os;
}
