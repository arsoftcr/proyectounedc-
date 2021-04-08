#ifndef CLIENTE_H
#define CLIENTE_H
#include<string>
using std::string;
class Cliente
{
    public:
        Cliente();

         string GetIdentificacion() {return Identificacion;}
        void SetIdentificacion( string val){Identificacion=val;}
             string GetNombre() {return Nombre;}
        void SetNombre(     string val){Nombre=val;}
             string GetApellidos() {return Apellidos;}
        void SetApellidos(     string val){Apellidos=val;}
             string GetDireccion() {return Direccion;}
        void SetDireccion(     string val){Direccion=val;}
             string GetTelefono() {return Telefono;}
        void SetTelefono(     string val){Telefono=val;}
             string GetEmail() {return Email;}
        void SetEmail(     string val){Email=val;}

    protected:

    private:
             string Identificacion;
             string Nombre;
             string Apellidos;
             string Direccion;
             string Telefono;
             string Email;
};

#endif // CLIENTE_H
