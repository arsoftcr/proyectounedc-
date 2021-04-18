#ifndef PAQUETES_VEHICULOS_H
#define PAQUETES_VEHICULOS_H
#include<string>
using std::string;

class Paquetes_Vehiculos
{
    public:
        Paquetes_Vehiculos();

        string GetVehiculo() { return Vehiculo; }
        void SetVehiculo(string val) { Vehiculo = val; }
        string GetChofer() { return Chofer; }
        void SetChofer(string val) { Chofer = val; }
        string GetEnvio() { return Envio; }
        void SetEnvio(string val) { Envio = val; }

    protected:

    private:
        string Vehiculo;
        string Chofer;
        string Envio;
};

#endif // PAQUETES_VEHICULOS_H
