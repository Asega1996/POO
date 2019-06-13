#include <cstring>
#include <unordered_set>
#include <random>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <set>
#include "usuario.hpp"

using namespace std;

Usuario::Usuarios Usuario::st_id;

Clave::Clave(const char* cad)
{
  if (strlen(cad) < 5)
    throw Incorrecta(Razon::CORTA);

  random_device r;
  uniform_int_distribution<size_t> dist(0, 63);

  char const MD5chars[] =
      "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

  char salt[2] = {MD5chars[dist(r)],MD5chars[dist(r)]};

  char* aux = crypt(cad, salt);

  if(aux == nullptr)
    throw Incorrecta(Razon::ERROR_CRYPT);

  contrasenna_ = aux;
}


bool Clave::verifica(const char* cad) const
{
  return strcmp(crypt(cad, contrasenna_.c_str()), contrasenna_.c_str()) == 0;
}


Usuario::Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apellidos,
  const Cadena& direccion,const Clave& cl):
id_(id), nombre_(nombre), apellidos_(apellidos), direccion_(direccion),
contrasenna(cl)
{
   if (!st_id.insert(id).second)
       throw Id_duplicado(id_);
}


Usuario::~Usuario()
{
    for (auto& i : Mtarjetas)
        i.second->anula_titular();

    st_id.erase(id_);
}


void Usuario::es_titular_de(const Tarjeta& tar)
{
  if(tar.titular() == this)
    Mtarjetas[tar.numero()] = const_cast<Tarjeta*>(&tar);
}


void Usuario::no_es_titular_de(Tarjeta& tar)
{
  Mtarjetas.erase(tar.numero());
}


void Usuario::compra(const Articulo& art, unsigned c)
{
  if (c == 0)
    Nart.erase(const_cast<Articulo*>(&art));
  else
    Nart[const_cast<Articulo*>(&art)] = c;
}


ostream& operator<<(ostream& os, const Usuario& u)
{
  os << u.id_ << "[" << u.contrasenna.clave() << "]" << u.nombre_;
  os << u.apellidos_ << endl << u.direccion_ << endl << "Tarjetas:" << endl;

  for (auto& t : u.Mtarjetas)
    os << *t.second << endl;

    return os;
}


void mostrar_articulo(ostream& os, const Articulo& articulo)
{
  os << "[" << articulo.referencia() << "] "
     << "\"" << articulo.titulo() << "\", "
     << articulo.f_publi().anno() << ". "
     << fixed << setprecision(2) << articulo.precio() << " €"
     << endl;

}


void mostrar_carro(ostream& os, const Usuario& u)
{
  os << "Carrito de compra de " << u.id() << " [Artículos: "
    << u.n_articulos() << "]" << endl;
  if (u.n_articulos() == 0) return;

  os << " Cant. Artículo" << endl
     << setw(65) << setfill('=') << '\n'  << setfill(' ');

  for (auto const& i : u.compra()) {
      os << setw(4) << i.second << "   ";
      mostrar_articulo(os, *(i.first));
    }

    os << endl;
}
