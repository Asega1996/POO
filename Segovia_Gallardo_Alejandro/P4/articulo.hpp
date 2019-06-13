#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>
#include <set>

using namespace std;

class Autor {

public:
 Autor(const Cadena&, const Cadena&, const Cadena&);
 Cadena nombre() const noexcept {return nombre_;}
 Cadena apellidos() const noexcept {return apellidos_;}
 Cadena direccion() const noexcept {return direccion_;}

private:
 Cadena nombre_, apellidos_, direccion_;

};

class Articulo {

public:
  typedef set<Autor*> Autores;
  Articulo(const Autores&, const Cadena&, const Cadena&, const Fecha&, double);
  const Cadena& referencia() const {return referencia_;}
  const Cadena& titulo() const {return titulo_;}
  const Fecha& f_publi() const {return f_publi_;}
  double precio() const {return precio_;}
  double& precio() {return precio_;}
  const Autores& autores() const {return autores_;}
  virtual void impresion_especifica(ostream&) const = 0;
  virtual ~Articulo() {}
  class Autores_vacios {};

private:
  Autores autores_;
  Cadena referencia_, titulo_;
  Fecha f_publi_;
  double precio_;

};

ostream& operator <<(ostream& os, const Articulo& art);

class ArticuloAlmacenable: public Articulo{

public:

  ArticuloAlmacenable(const Autores&, const Cadena&, const Cadena&,
    const Fecha&, double, unsigned = 0);

  unsigned stock() const {return stock_;}
  unsigned& stock() {return stock_;}

protected:
  unsigned stock_;

};

class Libro: public ArticuloAlmacenable {

public:
 Libro(const Articulo::Autores&, const Cadena&, const Cadena&,const Fecha&,
   double, unsigned , unsigned = 0);

 unsigned n_pag() const {return n_pag_;}
 void impresion_especifica(ostream& os) const;

private:
 const unsigned n_pag_;

};

class Cederron: public ArticuloAlmacenable {

public:
 Cederron(const Articulo::Autores&, const Cadena&, const Cadena&, const Fecha&,
   double, unsigned, unsigned = 0 );

 unsigned tam() const {return tam_;}
 void impresion_especifica(ostream& os) const;

private:
 unsigned tam_;

};

class LibroDigital: public Articulo {

public:
  LibroDigital(const Articulo::Autores&,const Cadena&, const Cadena&,
      const Fecha&, double, const Fecha&);

  Fecha f_expir() const {return f_expir_;}
  void impresion_especifica(ostream& os) const;

private:
  Fecha f_expir_;

};

#endif // ARTICULO_HPP_
