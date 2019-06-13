#include "fecha.hpp"
#include <ctime>
#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

//CONSTRUCTORES

Fecha::Fecha(int dia,int mes, int anno):dia_(dia),mes_(mes),anno_(anno)
{
  time_t tiempo = time(NULL);
  tm* aTime = localtime(&tiempo);
  if(dia_ == 0)
    dia_ = aTime->tm_mday;

  if(mes_ == 0)
    mes_ = aTime->tm_mon + 1;

  if(anno_ == 0)
    anno_ = aTime->tm_year + 1900;

  fechaValida();

}

Fecha::Fecha(const char* c)
{
  int valida;
  valida = sscanf(c, "%d/%d/%d", &dia_ , &mes_ , &anno_);
  if( 3 != valida)
    throw Invalida("Formato de escritura incorrecto\n");
  *this = Fecha(dia_, mes_, anno_);
}

//OBSERVADORES

int Fecha::dia() const
{
    return dia_;
}

int Fecha::mes() const
{
    return mes_;
}

int Fecha::anno() const
{
    return anno_;
}

//OPERADORES

Fecha& Fecha::operator ++()
{
  return *this+=1;
}

Fecha Fecha::operator ++(int)
{
  Fecha aux (*this);
    *this += 1;
    return aux;
}

Fecha& Fecha::operator --()
{
  return *this -= 1;
}

Fecha Fecha::operator --(int)
{
  Fecha aux (*this);
    *this += -1;
    return aux;
}

Fecha& Fecha::operator +=(int dias)
{
  tm f = {};
  f.tm_mday = dia_ + dias;
  f.tm_mon = mes_ - 1;
  f.tm_year = anno_ - 1900;
  mktime(&f);   //Ordena la fecha
  dia_ = f.tm_mday;
  mes_ = f.tm_mon + 1;
  anno_ = f.tm_year + 1900;
  mktime(&f);

  fechaValida();
  return *this;
}

Fecha& Fecha::operator -=(int dias)
{
  return *this += -dias;
}


Fecha Fecha::operator +(int dias) const
{
  Fecha aux(*this);
  aux += dias;
  return aux;

}

Fecha Fecha::operator -(int dias) const
{
  Fecha aux(*this);
  aux += -dias;
  return aux;
}

bool operator <(const Fecha& f, const Fecha& f2) noexcept
{
  if (f - f2 < 0) return true;
  else
  {
    return false;
  }
}

bool operator >(const Fecha& f, const Fecha& f2) noexcept
{
  if(f - f2 > 0) return true;
  else return false;
}

bool operator ==(const Fecha& f, const Fecha& f2) noexcept
{
  if((f - f2 )== 0) return true;
  else return false;
}

bool operator !=(const Fecha& f, const Fecha& f2) noexcept
{
  if(f == f2) return false;
  else return true;
}

bool operator <=(const Fecha& f, const Fecha& f2) noexcept
{
  if(f == f2 || f < f2) return true;
  else return false;
}

bool operator >=(const Fecha& f, const Fecha& f2) noexcept
{
  if(f > f2 || f == f2) return true;
  else return false;
}


long operator -(const Fecha& f, const Fecha& f2)
{
  tm F = {};
  F.tm_mday = f.dia();
  F.tm_mon = f.mes() - 1;
  F.tm_year = f.anno() - 1900;

  tm F2 = {};
  F2.tm_mday = f2.dia();
  F2.tm_mon = f2.mes() - 1;
  F2.tm_year = f2.anno() - 1900;

  long segundos;

  segundos = difftime(mktime(&F),mktime(&F2));
  long D = segundos/(3600*24);

  return D;
}


//VALIDACION DE LA FECHA

void Fecha::fechaValida() const
{
    tm f {};
    f.tm_mday = dia_;
    f.tm_mon = mes_ - 1;
    f.tm_year = anno_ - 1900;
    mktime(&f);

    if (dia_ != f.tm_mday) throw Invalida("El dia es incorrecto\n");
    if (mes_ != f.tm_mon + 1) throw Invalida("El mes es incorrecto\n");
    if (anno_ != f.tm_year + 1900) throw Invalida("El año es incorrecto\n");

    if(anno_ < Fecha::AnnoMinimo)
      throw Invalida("Error: Año introducido por debajo del minimo(1902)\n");

    if(anno_ > Fecha::AnnoMaximo)
      throw Invalida("Error: Año introducido por encima del maximo (2037)\n");
}

const char* Fecha::cadena() const
{
  static const char* semana[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
  static const char* meses[]  = {"enero", "febrero", "marzo","abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre","\0"};

  tm nuevo {};
  nuevo.tm_mday = dia_;
  nuevo.tm_mon = mes_ - 1;
  nuevo.tm_year = anno_ - 1900;
  nuevo.tm_isdst = -1;
  mktime(&nuevo);

  char* cadena = new char[40];

  sprintf (cadena, "%s %d de %s de %d", semana[nuevo.tm_wday],
    nuevo.tm_mday, meses[nuevo.tm_mon], nuevo.tm_year + 1900);

  return (const char*)cadena;

}

const char* Fecha::Invalida::por_que() const
{
  return error_;
}

ostream& operator <<(ostream& os, const Fecha& f){
  os << f.cadena();
  return os;

}

istream& operator>>(istream& is, Fecha& f)
{
  char* cad = new char[11];
  is >> setw(11) >> cad;

  int dia = -1, mes = -1, anno = -1;
  sscanf(cad, "%2d/%2d/%4d", &dia, &mes, &anno);
  delete[] cad;

  try {

    f = Fecha(dia, mes, anno);

  } catch (...) {
    is.setstate(std::ios_base::failbit);
    throw;

  }

  return is;
}
