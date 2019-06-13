#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <cstring>
#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include <unordered_set>
#include <unordered_map>
#include <unistd.h>
#include <ctime>
#include <map>
#include <set>

using namespace std;

class Clave {

  public:
    enum Razon{CORTA,ERROR_CRYPT}; //ENUM PARA LA CLASE Incorrecta
    Clave(const char* cad);
    const Cadena& clave() const {return contrasenna_;}
    bool verifica(const char* cad) const;

    class Incorrecta{

      public:
        Incorrecta(const Clave::Razon razon):razon_(razon){}
        Clave::Razon razon() const {return razon_;}

      private:
        Clave::Razon razon_;

    };

  private:
    Cadena contrasenna_;
};


class Usuario {

  public:
    typedef map<Numero, Tarjeta*> Tarjetas;

    typedef unordered_map<Articulo*, unsigned> Articulos;

    typedef unordered_set<Cadena> Usuarios;

    Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apellido,
      const Cadena& direccion,const Clave& cl);

    Usuario(const Usuario&) = delete;
    Usuario& operator = (const Usuario&) = delete;

    ~Usuario();

    const Cadena& id() const noexcept{return id_;}
    const Cadena& nombre() const noexcept{return nombre_;}
    const Cadena& apellidos() const noexcept{return apellidos_;}
    const Cadena& direccion() const noexcept{return direccion_;}
    const Tarjetas& tarjetas() const noexcept{return Mtarjetas;}
    const Articulos& compra() const noexcept{return Nart;}
    size_t n_articulos() const noexcept{return Nart.size();}


    void es_titular_de(const Tarjeta& tar);
    void no_es_titular_de(Tarjeta& tar);

    void compra(const Articulo& a, unsigned c = 1);

    friend ostream& operator<<(ostream& os, const Usuario& u);

    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena& idd) : idd_(idd) {}
        const Cadena& idd() const {return idd_;}
    private:
        Cadena idd_;
    };

  private:
    Cadena id_, nombre_, apellidos_, direccion_;

    Clave contrasenna;

    Tarjetas Mtarjetas;
    Articulos Nart;

    static Usuarios st_id;
};

void mostrar_carro(ostream& os, const Usuario& usuario);


#endif
