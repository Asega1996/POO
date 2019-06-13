#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_


#include <iostream>
#include "articulo.hpp"
#include "pedido.hpp"
#include <iomanip>


using namespace std;

class Pedido;
class Articulo;

class LineaPedido
{

public:
  explicit LineaPedido(double precio, unsigned c = 1u): precio_(precio), cantidad_(c){}
  double precio_venta() const {return precio_;}
  unsigned cantidad() const {return cantidad_;}

private:
  double precio_;
  unsigned cantidad_;

};

ostream& operator <<(ostream& os, const LineaPedido& lp);

class OrdenaPedidos: public binary_function<Pedido*,Pedido*,bool>
{
public:
  bool operator()(const Pedido* p1,const Pedido* p2) const;
};

class OrdenaArticulos: public binary_function<Articulo*,Articulo*,bool>
{
public:
  bool operator()(const Articulo* a1,const Articulo* a2) const
  {
  return (a1->referencia() < a2->referencia());
  }
};


class Pedido_Articulo{

public:
  typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
  typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
  typedef map<Pedido*, ItemsPedido, OrdenaPedidos> mpedido;
  typedef map<Articulo*, Pedidos, OrdenaArticulos> marticulo;

  void pedir (Pedido&, Articulo&, double, unsigned = 1);
  void pedir (Articulo&, Pedido&, double, unsigned = 1);

  const ItemsPedido& detalle(Pedido&);
  Pedidos ventas(Articulo&);

  ostream& mostrarDetallePedidos(ostream&) const;
	ostream& mostrarVentasArticulos(ostream&) const;


private:
  mpedido ped_art_;
  marticulo art_ped_;

};

ostream& operator <<(ostream& os,const Pedido_Articulo::ItemsPedido&);
ostream& operator <<(ostream& os,const Pedido_Articulo::Pedidos&);


#endif
