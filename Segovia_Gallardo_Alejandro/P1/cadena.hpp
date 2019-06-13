#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <string.h>
#include <iterator>

using namespace std;
class   Cadena
{
public:
  explicit Cadena(size_t t = 0, char c = ' ' );
  Cadena(const char* x, const size_t t= npos); //
  Cadena(const Cadena& f, const size_t ini, const size_t n = npos);
  size_t length() const;
  static const size_t npos = -1;


  Cadena& operator= (const Cadena&);
  Cadena(const Cadena&);
  Cadena& operator= (const char*);
  Cadena& operator+= (const Cadena&);
  char operator[] (size_t) const;
  char& operator[] (size_t);
  const char* c_str() const; //OPERADOR DE CONVERSION
  char at(size_t) const;
  char& at(size_t);
  Cadena substr(size_t, size_t) const;

  ~Cadena();

  Cadena(Cadena&& cad);
  Cadena& operator= (Cadena&&);

  //ITERADORES
  typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator>reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  //metodos begin
  iterator begin();
  const_iterator begin() const;
  //metodos end
  iterator end();
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator crend() const;
  const_reverse_iterator crbegin() const;
  const_reverse_iterator rend() const;

private:
  size_t tam_;
  char* c_;
};

ostream& operator <<(std::ostream&, const Cadena&);
istream& operator >>(std::istream&, Cadena&);

Cadena operator+ (const Cadena&, const Cadena&);
bool operator < (const Cadena& , const Cadena& ) ;
bool operator > (const Cadena& , const Cadena& ) ;
bool operator == (const Cadena& , const Cadena& ) ;
bool operator != (const Cadena& , const Cadena& ) ;
bool operator <= (const Cadena& , const Cadena& ) ;
bool operator >= (const Cadena& , const Cadena& ) ;

namespace std {
template <> struct hash<Cadena> {
size_t operator()(const Cadena& cad) const
{ // conversión const char* ->string
return hash<string>{}(cad.c_str());
}
};
}

#endif
