#ifndef CHOFER_H
#define CHOFER_H
#include<string>
using std::string;

class Chofer
{
    public:
        Chofer();

        string GetNumero() { return Numero; }
        void SetNumero(string val) { Numero = val; }
        string GetIdentificacion() { return Identificacion; }
        void SetIdentificacion(string val) { Identificacion = val; }
        string GetNombre() { return Nombre; }
        void SetNombre(string val) { Nombre = val; }
        string GetApellidos() { return Apellidos; }
        void SetApellidos(string val) { Apellidos = val; }
        string GetTipoLicencia() { return TipoLicencia; }
        void SetTipoLicencia(string val) { TipoLicencia = val; }
        string GetEstado() { return Estado; }
        void SetEstado(string val) { Estado = val; }

    protected:

    private:
        string Numero;
        string Identificacion;
        string Nombre;
        string Apellidos;
        string TipoLicencia;
        string Estado;
};

#endif // CHOFER_H
