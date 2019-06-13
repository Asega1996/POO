#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include "usuario.hpp"
#include "pedido.hpp"

using namespace std;


class Pedido;
class Usuario;

class Usuario_Pedido {

public:
  typedef set<Pedido*> Pedidos;
  typedef map<Usuario*, Pedidos> UsuarioP;
  typedef map<Pedido*, Usuario*> PedidoU;

  void asocia(Usuario& usuario, Pedido& pedido)
  {
    usu_ped_[&usuario].insert(&pedido);
    ped_usu_[&pedido] = &usuario;
  }

  void asocia(Pedido& pedido, Usuario& usuario)
  {
    asocia(usuario, pedido);
  }

  Pedidos& pedidos(Usuario& usuario)
  {
    return usu_ped_.find(&usuario)->second;

  }

  Usuario* cliente(Pedido& pedido)
  {
    return ped_usu_.find(&pedido)->second;
  }


private:
  UsuarioP usu_ped_;
  PedidoU ped_usu_;

};



#endif
