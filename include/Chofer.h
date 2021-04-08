#ifndef CHOFER_H
#define CHOFER_H


class Chofer
{
    public:
        Chofer();

        char GetIdentificacion() { return Identificacion[20]; }
        void SetIdentificacion(char val) { Identificacion[20] = val; }
        char GetNombre() { return Nombre[200]; }
        void SetNombre(char val) { Nombre[200] = val; }
        char GetApellidos() { return Apellidos[200]; }
        void SetApellidos(char val) { Apellidos[200] = val; }
        char GetDireccion() { return Direccion[500]; }
        void SetDireccion(char val) { Direccion[500] = val; }
        char GetTelefono() { return Telefono[50]; }
        void SetTelefono(char val) { Telefono[50] = val; }
        char GetEmail() { return Email[200]; }
        void SetEmail(char val) { Email[200] = val; }

    protected:

    private:
        char Identificacion[20];
        char Nombre[200];
        char Apellidos[200];
        char Direccion[500];
        char Telefono[50];
        char Email[200];
};

#endif // CHOFER_H
