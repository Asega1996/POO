#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

using namespace std;

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& UP, Pedido_Articulo& PA, Usuario& usuario,
	       const Tarjeta& tarjeta, const Fecha& f):numpedido_(N_pedidos+1), tarjeta_(&tarjeta), fecha_(f),importe_(0.) {
	if(usuario.compra().empty())
		throw Vacio(&usuario);
	if(tarjeta.titular() != &usuario)
		throw Impostor(&usuario);
	if(tarjeta.caducidad() < f)
		throw Tarjeta::Caducada(tarjeta.caducidad());

	auto carro = usuario.compra();

	for(auto iter = carro.begin() ; iter != carro.end() ; iter ++) {
		if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(iter->first)) {
			if(iter->second > AA->stock()) {
				for(auto iter = carro.begin() ; iter != carro.end() ; iter ++)
					usuario.compra(*iter->first, 0);
						throw SinStock(iter->first);
					}
				} else
				if(LibroDigital* LD = dynamic_cast<LibroDigital*>(iter->first)) {
					if(LD->f_expir() < f)
						usuario.compra(*iter->first, 0);
					}
		}
	if(usuario.compra().empty())
		throw Vacio(&usuario); //Comprobramos si se ha quedado vacio

	UP.asocia(*this, usuario);
	carro = usuario.compra();
	importe_ = 0;

	for(auto iter = carro.begin() ; iter != carro.end() ; iter ++) {
		importe_ += iter->first->precio() * iter->second;
		PA.pedir(*iter->first, *this, iter->first->precio(), iter->second);
		if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(iter->first))
			AA->stock() -= iter->second;
	}

	const_cast<Usuario::Articulos&>(usuario.compra()).clear();
	numpedido_ = ++ N_pedidos;
}


ostream& operator<< (ostream& os, const Pedido& pedido)
{
  os << "Núm. pedido: " << pedido.numero() << endl
    << "Fecha:       " << pedido.fecha() << endl
    << "Pagado con:  " << pedido.tarjeta()->tipo()
    << " nº: " << pedido.tarjeta()->numero() << endl
    << "Importe:     " << fixed << setprecision(2) << pedido.total()
    << " €" << endl;

  return os;
}
