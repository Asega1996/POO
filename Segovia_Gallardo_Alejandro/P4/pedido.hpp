#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "fecha.hpp"
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

using namespace std;

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido{

public:
  Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&,
    const Fecha& = Fecha());
  unsigned numero() const {return numpedido_;}
  Tarjeta const* tarjeta() const {return tarjeta_;}
  Fecha fecha() const {return fecha_;}
  double total() const {return importe_;}
  static unsigned n_total_pedidos() {return N_pedidos;}

  class Vacio{
  public:
    Vacio(Usuario * usuario): usuario_(usuario){}
    Usuario& usuario() const{return *usuario_;}
  private:
    Usuario * usuario_;
  };

  class Impostor{
  public:
    Impostor(Usuario * usuario): usuario_(usuario){}
    Usuario& usuario() const{return *usuario_;}
  private:
    Usuario * usuario_;
  };

  class SinStock{
  public:
    SinStock(Articulo* articulo): articulo_(articulo){}
    Articulo& articulo() const{return *articulo_;}
  private:
    Articulo * articulo_;
  };

private:
  int numpedido_;
  Tarjeta const * tarjeta_;
  Fecha fecha_;
  double importe_;
  static int N_pedidos;
};

ostream& operator << (ostream& os, const Pedido& pedido);


#endif
