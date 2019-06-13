#include "pedido-articulo.hpp"

using namespace std;

void Pedido_Articulo::pedir(Pedido& pedido,Articulo& articulo, double precio,
	unsigned cant)
{
	ped_art_[&pedido].insert(make_pair(&articulo,LineaPedido(precio,cant)));
	art_ped_[&articulo].insert(make_pair(&pedido,LineaPedido(precio,cant)));
}


void Pedido_Articulo::pedir(Articulo& articulo,Pedido& pedido,double precio,
	unsigned cant)
{
	pedir(pedido,articulo,precio,cant);
}


const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& pedido)
{
	return ped_art_.find(&pedido)->second;
}


Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& articulo)
{
	if(art_ped_.find(&articulo) == art_ped_.end())
	{
		Pedido_Articulo::Pedidos vacio;
		return vacio;
	}
	else
		return art_ped_.find(&articulo)->second;
}


ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os) const
{
	double precio = 0;
 	map<Pedido*, Pedido_Articulo::ItemsPedido, OrdenaPedidos>::const_iterator iter;
 	for(iter = ped_art_.begin() ; iter != ped_art_.end() ; iter ++)
 	{
 	os << "Pedido núm. " << iter->first->numero();
 	os << "\tCliente: " << iter->first->tarjeta()->titular()->nombre() << " "
		 << "\n";
 	os << "Fecha: " << iter->first->fecha() << iter->second;
 	precio += iter->first->total();
 	}
 	os << fixed;
 	os << "TOTAL VENTAS: " << setprecision(2) << precio << " €" << endl;
 	return os;
}

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os) const
{
	map<Articulo*, Pedido_Articulo::Pedidos,OrdenaArticulos>::const_iterator iter;
	for(iter = art_ped_.begin() ; iter != art_ped_.end() ; iter ++)
	{
 		os << "Ventas de " << "[" << iter->first->referencia() << "]";
	 	os << "\"" << iter->first->titulo() << "\" \n" << iter->second << endl;
 	}
	return os;
}


ostream& operator <<(ostream& os,const Pedido_Articulo::ItemsPedido& ip)
{
  double precio = 0;
  Pedido_Articulo::ItemsPedido::const_iterator i;
  os << endl << "====================================================" << endl;
  os << " PVP \t Cant. \t Articulo \n";
  os << "====================================================" << endl;
  for(i = ip.begin(); i != ip.end(); ++i){
  	os << " " << i->second.precio_venta() << "€\t";
    os << i->second.cantidad() << "\t";
    os << "[" << i->first->referencia() << "] ";
    os << "\"" << i->first->titulo() << "\" " << endl;
    precio = precio + i->second.precio_venta() * i->second.cantidad();
    }
  os << "===================================================" << endl;
  os << fixed;
  os << setprecision(2) << precio << " €" << endl;
  return os;
}


ostream& operator <<(ostream& os,const Pedido_Articulo::Pedidos& pedidos)
{
  double precio = 0;
  unsigned total = 0;
  Pedido_Articulo::Pedidos::const_iterator i;
  os << "====================================================" << endl;
  os << " PVP \t Cant. \t Fecha venta \n";
  os << "====================================================" << endl;
  for(auto i : pedidos){
    os << " " << i.second.precio_venta() << "€\t";
    os << i.second.cantidad() << "\t";
    os << i.first->fecha() << endl;
    precio = precio + i.second.precio_venta() * i.second.cantidad();
    total = total + i.second.cantidad();
    }
  os << "====================================================" << endl;
  os << fixed;
  os << setprecision(2) << precio << " €\t" << total <<endl ;

 	return os;
}


bool OrdenaPedidos::operator()(const Pedido* p1,const Pedido* p2) const
{
  return (p1->numero() < p2->numero());
}


ostream& operator <<(ostream& os, const LineaPedido& lp)
{
	os << fixed << setprecision(2) << lp.precio_venta()
	   << " €\t"<< lp.cantidad();
	return os;
}
