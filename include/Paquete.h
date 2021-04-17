#ifndef PAQUETE_H
#define PAQUETE_H
#include<string>
using std::string;

class Paquete
{

    public:
        Paquete();

        string GetNumeroEnvio() { return NumeroEnvio; }
        void SetNumeroEnvio(string val) { NumeroEnvio = val; }
        string GetFechaRegistro() { return FechaRegistro; }
        void SetFechaRegistro(string val) { FechaRegistro = val; }
        string GetClienteEmisor() { return ClienteEmisor; }
        void SetClienteEmisor(string val) { ClienteEmisor = val; }
        string GetClienteReceptor() { return ClienteReceptor; }
        void SetClienteReceptor(string val) { ClienteReceptor = val; }
        string GetPeso() { return Peso; }
        void SetPeso(string val) { Peso = val; }
        string GetMonto() { return Monto; }
        void SetMonto(string val) { Monto = val; }

    protected:

    private:
        string NumeroEnvio;
        string FechaRegistro;
        string ClienteEmisor;
        string ClienteReceptor;
        string Peso;
        string Monto;
};

#endif // PAQUETE_H
