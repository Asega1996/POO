#include <cstring>
#include "cadena.hpp"
#include <stdexcept>
#include <iterator>
#include <iomanip>

using namespace std;

Cadena::Cadena(size_t t, char c)
  : tam_(t) , c_(new char[tam_ + 1])
{
  for(size_t i = 0; i < tam_ ; i++)
		c_[i] = c;

	c_[tam_] = '\0';
}


Cadena::Cadena(const Cadena& cad): tam_(cad.tam_)
{
  c_ = new char [tam_ + 1];
  strcpy(c_ , cad.c_);
  c_[tam_] = '\0';
}


Cadena::Cadena(const char* c,const size_t n )
{
  tam_ = strlen(c);
  if (n < tam_)
    tam_ = n;
  c_ = new char[tam_ + 1];
  strncpy(c_, c, tam_);
  c_[tam_] = '\0';
}


Cadena::Cadena(const Cadena& c,const size_t ini , const size_t n)
{
  if(ini > c.tam_)
    throw out_of_range("CADENA FUERA RANGO");

  tam_ = c.tam_ - ini ;

  if(n < tam_) tam_ = n ;

  c_ = new char[tam_ +1];
  strncpy(c_ , c.c_ + ini , tam_ );
  c_[tam_] = '\0';
}


size_t Cadena::length()const
{
	return tam_;
}


Cadena::~Cadena()
{
  delete[] c_;
  c_ = nullptr;
  tam_ = 0;
}


Cadena::Cadena(Cadena&& cad) : tam_(cad.tam_), c_(cad.c_)
{
  cad.c_ = nullptr;
  cad.tam_ = 0;
}


Cadena& Cadena::operator=(Cadena&& cad)
{
  if (this == &cad)
    return *this;

  delete[] c_;

  c_ = cad.c_;
  tam_ = cad.tam_;

  cad.c_ = nullptr;
  cad.tam_ = 0;

  return *this;
}


char Cadena::at(size_t i) const
{
    if(i < tam_)
      return c_[i] ;
    else throw std::out_of_range("Rango incorrecto");
}


char& Cadena::at(size_t i)
{
  if(i < tam_)
    return c_[i] ;
  else throw std::out_of_range("Rango incorrecto");
}


Cadena Cadena::substr(size_t ini, size_t n) const
{
  if(ini >= tam_ || n > tam_ - ini) throw std::out_of_range("Posicion fuera de rango");
  return Cadena(*this, ini, n);
}


Cadena& Cadena::operator=(const Cadena& cad)
{
  if (this == &cad)
    return *this;

  tam_ = cad.tam_ ;
  c_ = new char [tam_ + 1];
  strcpy(c_, cad.c_ );
  return *this;
}


Cadena& Cadena::operator= (const char* cad)
{
  tam_ = strlen(cad);
  delete [] c_ ;
  c_ = new char [tam_ + 1];
  strcpy(c_, cad);
  return *this;
}


Cadena& Cadena::operator+= (const Cadena& cad)
{
  tam_ += cad.tam_;
  char* aux = new char [tam_ + 1]{'\0'};

  strcat(aux, c_);
  strcat(aux, cad.c_);
  delete[] c_;
  c_ = aux;

  return *this;
}


Cadena operator+ (const Cadena& cad1, const Cadena& cad2)
{
  return Cadena(cad1) += cad2;
}


char Cadena::operator[](size_t i) const
{
  return c_[i] ;
}


char& Cadena::operator[](size_t i)
{
  return c_[i];
}


const char* Cadena::c_str() const
{
  return c_ ;
}


bool operator==(Cadena const& cad1, Cadena const& cad2)
{
  return strcmp(cad1.c_str(), cad2.c_str()) == 0;
}


bool operator <(const Cadena& cad1, const Cadena& cad2)
{
  return strcmp(cad1.c_str(), cad2.c_str()) < 0;
}


bool operator <=(const Cadena& cad1, const Cadena& cad2)
{
    return (cad1 < cad2 || cad1 == cad2);
}


bool operator >(const Cadena& cad1, const Cadena& cad2)
{
    return cad2 < cad1;
}


bool operator >=(const Cadena& cad1, const Cadena& cad2)
{
    return (cad2 < cad1 || cad1 == cad2);
}


bool operator !=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad1 == cad2);
}


Cadena::iterator Cadena::begin() {return c_;}


Cadena::const_iterator Cadena::begin() const {return c_;}


Cadena::iterator Cadena::end() {return c_ + tam_;}


Cadena::const_iterator Cadena::end() const {return c_ + tam_;}


Cadena::const_iterator Cadena::cbegin() const {return c_;}


Cadena::const_iterator Cadena::cend() const {return c_ + tam_;}


Cadena::reverse_iterator Cadena::rbegin() {return reverse_iterator(end());}


Cadena::reverse_iterator Cadena::rend() {return reverse_iterator(begin());}


Cadena::const_reverse_iterator Cadena::crend() const
{return const_reverse_iterator(cbegin());}


Cadena::const_reverse_iterator Cadena::crbegin() const
{return const_reverse_iterator(cend());}


Cadena::const_reverse_iterator Cadena::rend() const
{return const_reverse_iterator(cbegin());}


Cadena::const_reverse_iterator Cadena::rbegin() const
{return const_reverse_iterator(cend());}


istream& operator >>(istream& is, Cadena& cad)
{
  char* aux = new char[32]{'\0'};
  is >> setw(32) >> aux;
  cad = Cadena(aux);
  delete[] aux;
  return is;
}


ostream& operator <<(ostream& os, const Cadena& cad)
{
  os << cad.c_str();
  return os;
}
