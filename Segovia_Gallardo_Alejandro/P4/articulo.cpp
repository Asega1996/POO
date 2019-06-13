#include "articulo.hpp"
#include <iomanip>

Autor::Autor(const Cadena& nombre, const Cadena& apellidos,
  const Cadena& direccion): nombre_(nombre), apellidos_(apellidos),
  direccion_(direccion)
{}


Articulo::Articulo(const Autores& autores, const Cadena& ref,
  const Cadena& tit, const Fecha& fecha, double p):
autores_(autores), referencia_(ref), titulo_(tit), f_publi_(fecha),
precio_(p)
{
 if(autores.empty()) throw Autores_vacios();
}


ArticuloAlmacenable::ArticuloAlmacenable(const Articulo::Autores& autores,
  const Cadena& ref, const Cadena& titulo, const Fecha& fecha,
  double p, unsigned stock):
    Articulo(autores, ref, titulo, fecha, p), stock_(stock) {}


Libro::Libro(const Articulo::Autores& autores, const Cadena& referencia,
  const Cadena& titulo, const Fecha& fecha, double p, unsigned n_pag,
  unsigned stock):
    ArticuloAlmacenable(autores, referencia, titulo, fecha, p, stock),
    n_pag_(n_pag) {}


Cederron::Cederron(const Articulo::Autores& autores, const Cadena& referencia,
  const Cadena& titulo, const Fecha& fecha, double p, unsigned tam,
  unsigned stock):
    ArticuloAlmacenable(autores, referencia, titulo, fecha, p, stock),
    tam_(tam) {}


LibroDigital::LibroDigital(const Articulo::Autores& autores,
  const Cadena& referencia, const Cadena& titulo, const Fecha& fecha,
  double p, const Fecha& fexp):
    Articulo(autores, referencia, titulo, fecha, p), f_expir_(fexp) {}


ostream& operator <<(ostream& os, const Articulo& articulo)
{
  os <<"[" << articulo.referencia() << "] "<< "\"" << articulo.titulo()
     << "\", de ";

  const auto& autores = articulo.autores();

  auto iter = autores.begin();
  os << (*iter)->apellidos();
  while (++iter != autores.end()){
    os << ", " << (*iter)->apellidos();
  }
  os << ". " << articulo.f_publi().anno() << ". "
     << fixed << setprecision(2) << articulo.precio() << " €\n\t";

  articulo.impresion_especifica(os);
  return os;
}


void Libro::impresion_especifica(ostream& os) const
{
  os << n_pag_ << " págs., " << stock_ << " unidades.";
}


void Cederron::impresion_especifica(ostream& os) const
{
  os << tam_ << " MB, " << stock_ << " unidades.";
}


void LibroDigital::impresion_especifica(ostream& os) const
{
  os << "A la venta hasta el " << f_expir_ <<".";
}
