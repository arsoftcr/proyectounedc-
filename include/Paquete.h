#ifndef PAQUETE_H
#define PAQUETE_H
#include <string>
using std::string;
//Se utiliza std::string  para poder hacer uso  de  el  tipo string  en la clase

class Paquete
{
    public:
        Paquete();

        int Getnumero() { return numero; }
        void Setnumero(int val) { numero = val; }
        char[200] Getfecha() { return fecha; }
        void Setfecha(char[200] val) { fecha = val; }
        char[20] Getemisor() { return emisor; }
        void Setemisor(char[20] val) { emisor = val; }
        char[20] Getreceptor() { return receptor; }
        void Setreceptor(char[20] val) { receptor = val; }
        float Getpeso() { return peso; }
        void Setpeso(float val) { peso = val; }
            float Getmonto() { return monto; }
        void Setmonto(float val) { monto = val; }

    protected:

    private:
        int numero;
        char[200] fecha;
        char[20] emisor;
        char[20] receptor;
        float peso;
        float monto;
};

#endif // PAQUETE_H
