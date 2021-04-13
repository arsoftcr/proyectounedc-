#include <iostream>
#include <stdexcept>
#include <string>
#include <Chofer.h>
#include <Paquete.h>
#include <Cliente.h>
#include <stdlib.h>
#include<ctype.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

//PROTOTIPOS

//************************************MANTENIMIENTO CLIENTES*************************************
void lecturaClientes();
vector<Cliente> cargarClientes();
void buscarCliente();
bool busquedaCliente(vector<Cliente> clientes,string dato);
Cliente RetornarbusquedaCliente(vector<Cliente> clientes,string buscado);
bool  grabarClientes(vector<Cliente> clientes);
Cliente solicitarDatosCliente();
vector<Cliente> removerCliente(vector<Cliente> clientes,Cliente aborrar);
//************************************MANTENIMIENTO CLIENTES*************************************


//************************************MANTENIMIENTO CHOFERES*************************************
void modificarChofer();
vector<Chofer> removerChofer(vector<Chofer> chofers,Chofer aborrar);
void eliminarChofer();
void buscarChofer();
void listarChofers();
vector<Chofer> cargarChofers();
bool busquedaChofer(vector<Chofer> chofers,string dato);
Chofer RetornarbusquedaChofer(vector<Chofer> chofers,string buscado);
bool  grabarChofers(vector<Chofer> chofers);
void ingresoChofer();
//************************************MANTENIMIENTO CHOFERES*************************************

//************************************MANTENIMIENTO PAQUETES*************************************
void EscucharOpcionesPaquetes();
int MostrarMenuPaquetes();
void ProcesamientoDeDatosSubmenuPaquetes(int solicitud);
//************************************MANTENIMIENTO PAQUETES*************************************
void modificarPaquete();
vector<Paquete> removerPaquete(vector<Paquete> paquetes,Paquete aborrar);
void eliminarPaquete();
void buscarPaquete();
void listarPaquetes();
vector<Paquete> cargarPaquetes();
bool busquedaPaquete(vector<Paquete> paquetes,string dato);
Paquete RetornarbusquedaPaquete(vector<Paquete> paquetes,string buscado);
bool  grabarPaquetes(vector<Paquete> paquetes);
void ingresoPaquete();
//************************************MANTENIMIENTO PAQUETES*************************************
//************************************MANTENIMIENTO PAQUETES*************************************

//************************************UTILITARIOS*************************************
bool ValidarSiEsNumero(string cadena);
bool esCadenaValida(string dato);
string FechaDelSistema();
void inicializarArchivos();
//************************************UTILITARIOS*************************************

//************************************PROCESAMIENTO DE DATOS*************************************
void ProcesamientoDeDatosSubmenuClientes(int eleccion);
void ProcesamientoDeDatosSubmenuChoferes(int eleccion);
int MostrarMenu();
int MostrarMenuClientes();
int MostrarMenuChoferes();
void ProcesamientoDeDatos(int eleccion);
void EscucharOpciones();
//************************************PROCESAMIENTO DE DATOS*************************************

//Para no utilizar variables globales, se me ocurri� utilizar un struct/////////////////////////////
struct globales
{
    ofstream escritura;
    ifstream lectura;
    string archivoClientes="cliente.txt";
    string archivoChoferes="chofer.txt";
    string archivoPaquetes="paquete.txt";
    string archivoEnvios="envio.txt";
};

//************************************MANTENIMIENTO CLIENTES*************************************
void modificarCliente()
{
    string id;
    string nombre;
    string apellidos;
    string telefono;
    string email;
    string direccion;
    bool actualizado=false;
    cout << "Ingrese el n�mero de identificaci�n del cliente que desea modificar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
    {
        vector<Cliente> clientes=cargarClientes();
        bool busqueda=busquedaCliente(clientes,id);
        if(busqueda)
        {
            Cliente c=RetornarbusquedaCliente(clientes,id);
            vector<Cliente> clientesXGrabar=removerCliente(clientes,c);
            cout<< "\nEl nombre actual del cliente es : "<<c.GetNombre()<<endl;
            cout << "Digite el nuevo nombre o presione enter para mantener el mismo nombre"<<endl;
            getline(cin,nombre);
            if(esCadenaValida(nombre))
            {
                c.SetNombre(nombre);
            }
            cout << "\nLos apellidos actuales del cliente son : "<<c.GetApellidos()<<endl;
            cout << "Digite los nuevos apellidos o presione enter para mantener los mismos apellidos"<<endl;
            getline(cin,apellidos);
            if(esCadenaValida(apellidos))
            {
                c.SetApellidos(apellidos);
            }
            cout << "\nLa direccion actual del cliente es : "<<c.GetDireccion()<<endl;
            cout << "Digite la nueva direccion o presione enter para mantener la misma direccion"<<endl;
            getline(cin,direccion);
            if(esCadenaValida(direccion))
            {
                c.SetDireccion(direccion);
            }
            cout << "\nEl email actual del cliente es : "<<c.GetEmail()<<endl;
            cout << "Digite el nuevo email o presione enter para mantener el mismo email"<<endl;
            getline(cin,email);
            if(esCadenaValida(email))
            {
                c.SetEmail(email);
            }
            cout << "\nEl telefono actual del cliente es : "<<c.GetTelefono()<<endl;
            cout << "Digite el nuevo telefono o presione enter para mantener el mismo telefono"<<endl;
            getline(cin,telefono);
            if(esCadenaValida(telefono))
            {
                c.SetTelefono(telefono);
            }
            clientesXGrabar.push_back(c);
            bool grabado=grabarClientes(clientesXGrabar);
            if(grabado)
            {
                cout << "El cliente con la identificaci�n : "<<c.GetIdentificacion()<<" ha sido modificado satisfactoriamente"<<endl;
            }
            else
            {
                cout << "El cliente no pudo ser modificado por un problema desconocido"<<endl;
            }
        }
        else
        {
            cout << "No se encontr� ning�n cliente con la identificaci�n : "<<id<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es v�lido"<<endl;
    }
}
vector<Cliente> removerCliente(vector<Cliente> clientes,Cliente aborrar)
{
    vector<Cliente> aux;
    for(Cliente c:clientes)
    {
        if(c.GetIdentificacion()!=aborrar.GetIdentificacion())
        {
            aux.push_back(c);
        }
    }
    return aux;
}
void eliminarCliente()
{
    string id;
    bool actualizado=false;
    cout << "Ingrese el n�mero de identificaci�n del cliente que desea eliminar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
    {
        vector<Cliente> clientes=cargarClientes();
        bool busqueda=busquedaCliente(clientes,id);
        if(busqueda)
        {
            Cliente c=RetornarbusquedaCliente(clientes,id);
            vector<Cliente> clientesXGrabar=removerCliente(clientes,c);
            bool grabado=grabarClientes(clientesXGrabar);
            if(grabado)
            {
                cout << "El cliente con la identificaci�n : "<<c.GetIdentificacion()<<" ha sido eliminado satisfactoriamente"<<endl;
            }
            else
            {
                cout << "El cliente no pudo ser modificado por un problema desconocido"<<endl;
            }
        }
        else
        {
            cout << "No se encontr� ning�n cliente con la identificaci�n : "<<id<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es v�lido"<<endl;
    }
};
void buscarCliente()
{
    string id;
    cout << "Ingrese el n�mero de identificaci�n del cliente que desea buscar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
    {
        vector<Cliente> clientes=cargarClientes();
        bool busqueda=busquedaCliente(clientes,id);
        if(busqueda)
        {
            Cliente c=RetornarbusquedaCliente(clientes,id);
            cout
                    << "\nIdentificaci�n : "<<c.GetIdentificacion()
                    << "\nNombre : "<<c.GetNombre()
                    << "\nApellidos : "<<c.GetApellidos()
                    << "\nDirecci�n : "<<c.GetDireccion()
                    << "\nEmail : "<<c.GetEmail()
                    << "\nTel�fono : "<<c.GetTelefono()
                    <<endl;
        }
        else
        {
            cout << "No se encontr� ning�n cliente con la identificaci�n : "<<id<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es v�lido"<<endl;
    }
}
void listarClientes()
{
    vector<Cliente> clientes=cargarClientes();
    if(clientes.size()>0)
    {
        for(Cliente c:clientes)
        {
            cout << "\nIdentificaci�n : " << c.GetIdentificacion()
                 <<"\nNombre : "<< c.GetNombre()
                 <<"\nApellidos : "<<c.GetApellidos()
                 <<"\nDirecci�n : "<<c.GetDireccion()
                 <<"\nEmail : "<<c.GetEmail()
                 <<"\nTel�fono : "<< c.GetTelefono()<< endl;
        }
    }
    else
    {
        cout << "No hay clientes que mostrar"<<endl;
    }


}

vector<Cliente> cargarClientes()
{
    globales global;
    vector<Cliente> clientes;
    Cliente cliente;
    global.lectura.open(global.archivoClientes,ios::in);
    if(global.lectura.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    string id;
    string nombre;
    string direccion;
    string apes;
    string email;
    string tel;
    while(global.lectura >> id >> nombre >> apes >> direccion >>  email >>tel )
    {
        cliente.SetIdentificacion(id);
        cliente.SetNombre(nombre);
        cliente.SetApellidos(apes);
        cliente.SetDireccion(direccion);
        cliente.SetEmail(email);
        cliente.SetTelefono(tel);
        clientes.push_back(cliente);

    }
    global.lectura.close();

    return clientes;
}


bool busquedaCliente(vector<Cliente> clientes,string dato)
{
    bool resultado=false;

    for(Cliente c:clientes)
    {
        if(c.GetIdentificacion()==dato)
        {
            resultado=true;
        }
    }

    return resultado;
}



Cliente RetornarbusquedaCliente(vector<Cliente> clientes,string buscado)
{
    Cliente cliente;
    for(Cliente c:clientes)
    {
        if(c.GetIdentificacion()==buscado)
        {
            cliente=c;
            break;
        }
    }

    return cliente;
}

bool  grabarClientes(vector<Cliente> clientes)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoClientes,ios::out);


    if(global.escritura.fail())
    {
        cout <<"no se pudo abrir el archivo";
        exit(1);
    }

    for(Cliente c:clientes)
    {
        global.escritura
                << c.GetIdentificacion()<<' '
                <<c.GetNombre()<<' '
                <<c.GetApellidos()<<' '
                <<c.GetDireccion()<< ' '
                <<c.GetEmail()<<' '
                <<c.GetTelefono()<<' ';

    }
    global.escritura.flush();
    global.escritura.close();
    resultado=true;


    return resultado;
}
void ingresoCliente()
{
    Cliente cliente=Cliente();
    string id;
    string email;
    string nombre;
    string apellidos;
    string direccion;
    string telefono;
    cout <<"Ingrese la identificaci�n del cliente,este debe ser un dato num�rico y debe contener menos de 11 caracteres"<<endl;
    getline(std::cin,id);
    bool proceso=esCadenaValida(id)?true:false;
    if(proceso)
    {
        proceso=ValidarSiEsNumero(id)?true:false;
    }
    if(proceso)
    {

        cout <<"Ingrese el nombre del cliente"<<endl;
        getline(std::cin,nombre);
        proceso=esCadenaValida(nombre)?true:false;
        if(proceso)
        {

            cout <<"Ingrese los apellidos del cliente"<<endl;
            getline(std::cin,apellidos);
            proceso=esCadenaValida(apellidos)?true:false;
            if(proceso)
            {

                cout <<"Ingrese la direcci�n del cliente"<<endl;
                getline(std::cin,direccion);
                proceso=esCadenaValida(direccion)?true:false;
                if(proceso)
                {

                    cout <<"Ingrese el  tel�fono del cliente"<<endl;
                    getline(std::cin,telefono);
                    proceso=esCadenaValida(telefono)?true:false;
                    if(proceso)
                    {

                        cout <<"Ingrese el  email del cliente"<<endl;
                        getline(std::cin,email);
                        proceso=esCadenaValida(email)?true:false;
                    }
                }
            }
        }
    }

    if(proceso)
    {
        vector<Cliente> clientes=cargarClientes();

        cliente.SetIdentificacion(id);
        cliente.SetApellidos(apellidos);
        cliente.SetDireccion(direccion);
        cliente.SetEmail(email);
        cliente.SetNombre(nombre);
        cliente.SetTelefono(telefono);

        bool busqueda=busquedaCliente(clientes,cliente.GetIdentificacion());

        if(busqueda)
        {
            cout << "Lo sentimos. No se puede registrar el cliente debido a que ya ha sido registrado anteriormente"<<endl;
        }
        else
        {
            clientes.push_back(cliente);
            bool registrado=grabarClientes(clientes);
            if(registrado)
            {
                cout<<"El cliente "<<cliente.GetIdentificacion() <<" ha sido registrado satisfactoriamente."<<endl;

            }
            else
            {
                cout<<"El cliente "<<cliente.GetIdentificacion() <<" no pudo ser registrado debido a un problema desconocido."<<endl;
            }
        }
    }
    else
    {
        cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
    }

}
//************************************MANTENIMIENTO CLIENTES*************************************


//************************************MANTENIMIENTO CHOFERES*************************************
void modificarChofer()
{
    string id;
    string nombre;
    string apellidos;
    string numero;
    string estado;
    string tipo;
    bool actualizado=false;
    cout << "Ingrese el n�mero de identificaci�n del chofer que desea modificar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
    {
        vector<Chofer> chofers=cargarChofers();
        bool busqueda=busquedaChofer(chofers,id);
        if(busqueda)
        {
            Chofer c=RetornarbusquedaChofer(chofers,id);
            vector<Chofer> chofersXGrabar=removerChofer(chofers,c);
            cout<< "\nEl nombre actual del chofer es : "<<c.GetNombre()<<endl;
            cout << "Digite el nuevo nombre o presione enter para mantener el mismo nombre"<<endl;
            getline(cin,nombre);
            if(esCadenaValida(nombre))
            {
                c.SetNombre(nombre);
            }
            cout << "\nLos apellidos actuales del chofer son : "<<c.GetApellidos()<<endl;
            cout << "Digite los nuevos apellidos o presione enter para mantener los mismos apellidos"<<endl;
            getline(cin,apellidos);
            if(esCadenaValida(apellidos))
            {
                c.SetApellidos(apellidos);
            }
            cout << "\nEl tipo de licencia actual del chofer es : "<<c.GetTipoLicencia()<<endl;
            cout << "Digite el nuevo tipo de licencia o presione enter para mantener el mismo tipo"<<endl;
            getline(cin,tipo);
            if(esCadenaValida(tipo))
            {
                c.SetTipoLicencia(tipo);
            }
            cout << "\nEl estado actual del chofer es : "<<c.GetEstado()<<endl;
            cout << "Digite el nuevo estado o presione enter para mantener el mismo estado. Ingrese un 1 para indicar que est� activo o ingrese un 2 para indicar que esta inactivo"<<endl;
            getline(cin,estado);
            if(esCadenaValida(estado))
            {
                c.SetEstado(estado);
            }

            chofersXGrabar.push_back(c);
            bool grabado=grabarChofers(chofersXGrabar);
            if(grabado)
            {
                cout << "El chofer con la identificaci�n : "<<c.GetIdentificacion()<<" ha sido modificado satisfactoriamente"<<endl;
            }
            else
            {
                cout << "El chofer no pudo ser modificado por un problema desconocido"<<endl;
            }
        }
        else
        {
            cout << "No se encontr� ning�n chofer con la identificaci�n : "<<id<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es v�lido"<<endl;
    }
}
vector<Chofer> removerChofer(vector<Chofer> chofers,Chofer aborrar)
{
    vector<Chofer> aux;
    for(Chofer c:chofers)
    {
        if(c.GetIdentificacion()!=aborrar.GetIdentificacion())
        {
            aux.push_back(c);
        }
    }
    return aux;
}
void eliminarChofer()
{
    string id;
    bool actualizado=false;
    cout << "Ingrese el n�mero de identificaci�n del chofer que desea eliminar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
    {
        vector<Chofer> chofers=cargarChofers();
        bool busqueda=busquedaChofer(chofers,id);
        if(busqueda)
        {
            Chofer c=RetornarbusquedaChofer(chofers,id);
            vector<Chofer> chofersXGrabar=removerChofer(chofers,c);
            bool grabado=grabarChofers(chofersXGrabar);
            if(grabado)
            {
                cout << "El chofer con la identificaci�n : "<<c.GetIdentificacion()<<" ha sido eliminado satisfactoriamente"<<endl;
            }
            else
            {
                cout << "El chofer no pudo ser modificado por un problema desconocido"<<endl;
            }
        }
        else
        {
            cout << "No se encontr� ning�n chofer con la identificaci�n : "<<id<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es v�lido"<<endl;
    }
};
void buscarChofer()
{
    string id;
    cout << "Ingrese el n�mero de identificaci�n del chofer que desea buscar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
    {
        vector<Chofer> chofers=cargarChofers();
        bool busqueda=busquedaChofer(chofers,id);
        if(busqueda)
        {
            Chofer c=RetornarbusquedaChofer(chofers,id);
            cout
                    << "\nIdentificaci�n : "<<c.GetIdentificacion()
                    << "\nNombre : "<<c.GetNombre()
                    << "\nApellidos : "<<c.GetApellidos()
                    << "\nNumero : "<<c.GetNumero()
                    << "\nEstado : "<<c.GetEstado()
                    << "\nTipo de licencia : "<<c.GetTipoLicencia()
                    <<endl;
        }
        else
        {
            cout << "No se encontr� ning�n chofer con la identificaci�n : "<<id<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es v�lido"<<endl;
    }
}
void listarChofers()
{
    vector<Chofer> chofers=cargarChofers();
    if(chofers.size()>0)
    {
        for(Chofer c:chofers)
        {
            cout << "\nIdentificaci�n : " << c.GetIdentificacion()
                 <<"\nNombre : "<< c.GetNombre()
                 <<"\nApellidos : "<<c.GetApellidos()
                 <<"\nNumero : "<<c.GetNumero()
                 <<"\nEstado : "<<c.GetEstado()
                 <<"\nTipo de licencia : "<< c.GetTipoLicencia()<< endl;
        }
    }
    else
    {
        cout << "No hay chofers que mostrar"<<endl;
    }


}

vector<Chofer> cargarChofers()
{
    globales global;
    vector<Chofer> chofers;
    Chofer chofer;
    global.lectura.open(global.archivoChoferes,ios::in);
    if(global.lectura.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    string id;
    string nombre;
    string numero;
    string apes;
    string estado;
    string tipo;
    while(global.lectura >> id >> nombre >> apes >> numero >>  estado >>tipo )
    {
        chofer.SetIdentificacion(id);
        chofer.SetNombre(nombre);
        chofer.SetApellidos(apes);
        chofer.SetNumero(numero);
        chofer.SetEstado(estado);
        chofer.SetTipoLicencia(tipo);
        chofers.push_back(chofer);

    }
    global.lectura.close();

    return chofers;
}


bool busquedaChofer(vector<Chofer> chofers,string dato)
{
    bool resultado=false;

    for(Chofer c:chofers)
    {
        if(c.GetIdentificacion()==dato)
        {
            resultado=true;
        }
    }

    return resultado;
}



Chofer RetornarbusquedaChofer(vector<Chofer> chofers,string buscado)
{
    Chofer chofer;
    for(Chofer c:chofers)
    {
        if(c.GetIdentificacion()==buscado)
        {
            chofer=c;
            break;
        }
    }

    return chofer;
}

bool  grabarChofers(vector<Chofer> chofers)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoChoferes,ios::out);


    if(global.escritura.fail())
    {
        cout <<"no se pudo abrir el archivo";
        exit(1);
    }

    for(Chofer c:chofers)
    {
        global.escritura
                << c.GetIdentificacion()<<' '
                <<c.GetNombre()<<' '
                <<c.GetApellidos()<<' '
                <<c.GetNumero()<< ' '
                <<c.GetEstado()<<' '
                <<c.GetTipoLicencia()<<' ';

    }
    global.escritura.flush();
    global.escritura.close();
    resultado=true;


    return resultado;
}
void ingresoChofer()
{
    Chofer chofer=Chofer();
    string id;
    string estado;
    string nombre;
    string apellidos;
    string numero;
    string tipo;
    cout <<"Ingrese la identificaci�n del chofer,este debe ser un dato num�rico y debe contener menos de 11 caracteres"<<endl;
    getline(std::cin,id);
    bool proceso=esCadenaValida(id)?true:false;
    if(proceso)
    {
        proceso=ValidarSiEsNumero(id)?true:false;
    }

    if(proceso)
    {

        cout <<"Ingrese el nombre del chofer"<<endl;
        getline(std::cin,nombre);
        proceso=esCadenaValida(nombre)?true:false;
        if(proceso)
        {

            cout <<"Ingrese los apellidos del chofer"<<endl;
            getline(std::cin,apellidos);
            proceso=esCadenaValida(apellidos)?true:false;
            if(proceso)
            {


                cout <<"Ingrese el  tipo de licencia del chofer"<<endl;
                getline(std::cin,tipo);
                proceso=esCadenaValida(tipo)?true:false;
                if(proceso)
                {

                    cout <<"Ingrese el  estado del chofer. Ingrese un 1 para indicar que est� activo o ingrese un 2 para indicar que esta inactivo"<<endl;
                    getline(std::cin,estado);
                    proceso=esCadenaValida(estado)?true:false;
                    if(proceso)
                    {
                        proceso=ValidarSiEsNumero(estado)?true:false;

                        if(estado=="1"||estado=="2")
                        {
                            proceso=true;
                        }
                        else
                        {
                            proceso=false;
                            cout << "El estado del cliente debe ser 1 o 2" << endl;
                        }
                    }
                }

            }
        }
    }

    if(proceso)
    {
        vector<Chofer> chofers=cargarChofers();

        int autoincremento=0;
        autoincremento=chofers.size()+1;
        if(autoincremento<1)
        {
            autoincremento=1;
        }
        numero=to_string(autoincremento);
        chofer.SetIdentificacion(id);
        chofer.SetApellidos(apellidos);
        chofer.SetNumero(numero);
        chofer.SetEstado(estado);
        chofer.SetNombre(nombre);
        chofer.SetTipoLicencia(tipo);

        bool busqueda=busquedaChofer(chofers,chofer.GetIdentificacion());

        if(busqueda)
        {
            cout << "Lo sentimos. No se puede registrar el chofer debido a que ya ha sido registrado anteriormente"<<endl;
        }
        else
        {
            chofers.push_back(chofer);
            bool registrado=grabarChofers(chofers);
            if(registrado)
            {
                cout<<"El chofer "<<chofer.GetIdentificacion() <<" ha sido registrado satisfactoriamente."<<endl;

            }
            else
            {
                cout<<"El chofer "<<chofer.GetIdentificacion() <<" no pudo ser registrado debido a un problema desconocido."<<endl;
            }
        }
    }
    else
    {
        cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
    }

}
//************************************MANTENIMIENTO CHOFERES*************************************

//************************************MANTENIMIENTO PAQUETES*************************************
void modificarPaquete()
{
    string numero;
    string emisor;
    string receptor;
    string fecha;
    string peso;
    string monto;
    bool actualizado=false;
    cout << "Ingrese el n�mero del paquete que desea modificar"<<endl;
    getline(cin,numero);
//    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
//    {
//        vector<Paquete> paquetes=cargarPaquetes();
//        bool busqueda=busquedaPaquete(paquetes,id);
//        if(busqueda)
//        {
//            Paquete c=RetornarbusquedaPaquete(paquetes,id);
//            vector<Paquete> paquetesXGrabar=removerPaquete(paquetes,c);
//            cout<< "\nEl nombre actual del chofer es : "<<c.GetClienteEmisor()<<endl;
//            cout << "Digite el nuevo nombre o presione enter para mantener el mismo nombre"<<endl;
//            getline(cin,nombre);
//            if(esCadenaValida(nombre))
//            {
//                c.SetNombre(nombre);
//            }
//            cout << "\nLos apellidos actuales del chofer son : "<<c.GetClienteReceptor()<<endl;
//            cout << "Digite los nuevos apellidos o presione enter para mantener los mismos apellidos"<<endl;
//            getline(cin,apellidos);
//            if(esCadenaValida(apellidos))
//            {
//                c.SetApellidos(apellidos);
//            }
//            cout << "\nEl tipo de licencia actual del chofer es : "<<c.GetTipoLicencia()<<endl;
//            cout << "Digite el nuevo tipo de licencia o presione enter para mantener el mismo tipo"<<endl;
//            getline(cin,tipo);
//            if(esCadenaValida(tipo))
//            {
//                c.SetTipoLicencia(tipo);
//            }
//            cout << "\nEl estado actual del chofer es : "<<c.GetEstado()<<endl;
//            cout << "Digite el nuevo estado o presione enter para mantener el mismo estado. Ingrese un 1 para indicar que est� activo o ingrese un 2 para indicar que esta inactivo"<<endl;
//            getline(cin,estado);
//            if(esCadenaValida(estado))
//            {
//                c.SetEstado(estado);
//            }
//
//            paquetesXGrabar.push_back(c);
//            bool grabado=grabarPaquetes(paquetesXGrabar);
//            if(grabado)
//            {
//                cout << "El chofer con la identificaci�n : "<<c.GetIdentificacion()<<" ha sido modificado satisfactoriamente"<<endl;
//            }
//            else
//            {
//                cout << "El chofer no pudo ser modificado por un problema desconocido"<<endl;
//            }
//        }
//        else
//        {
//            cout << "No se encontr� ning�n chofer con la identificaci�n : "<<id<<endl;
//        }
//
//    }
//    else
//    {
//        cout << "El dato ingresado no es v�lido"<<endl;
//    }
}
vector<Paquete> removerPaquete(vector<Paquete> paquetes,Paquete aborrar)
{
    vector<Paquete> aux;
    for(Paquete c:paquetes)
    {
        if(c.GetNumeroEnvio()!=aborrar.GetNumeroEnvio())
        {
            aux.push_back(c);
        }
    }
    return aux;
}
void eliminarPaquete()
{
    string id;
    bool actualizado=false;
    cout << "Ingrese el n�mero  del paquete que desea eliminar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
    {
        vector<Paquete> paquetes=cargarPaquetes();
        bool busqueda=busquedaPaquete(paquetes,id);
        if(busqueda)
        {
            Paquete c=RetornarbusquedaPaquete(paquetes,id);
            vector<Paquete> paquetesXGrabar=removerPaquete(paquetes,c);
            bool grabado=grabarPaquetes(paquetesXGrabar);
            if(grabado)
            {
                cout << "El paquete con la identificaci�n : "<<c.GetNumeroEnvio()<<" ha sido eliminado satisfactoriamente"<<endl;
            }
            else
            {
                cout << "El paquete no pudo ser modificado por un problema desconocido"<<endl;
            }
        }
        else
        {
            cout << "No se encontr� ning�n paquete con la identificaci�n : "<<id<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es v�lido"<<endl;
    }
};
void buscarPaquete()
{
    string id;
    cout << "Ingrese el n�mero  del paquete que desea buscar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id)&&ValidarSiEsNumero(id))
    {
        vector<Paquete> paquetes=cargarPaquetes();
        bool busqueda=busquedaPaquete(paquetes,id);
        if(busqueda)
        {
            Paquete c=RetornarbusquedaPaquete(paquetes,id);
            cout
                    << "\nNumero de paquete : "<<c.GetNumeroEnvio()
                    << "\nFecha de creacion : "<<c.GetFechaRegistro()
                    << "\nCliente que envia : "<<c.GetClienteEmisor()
                    << "\nCliente que recibe : "<<c.GetClienteReceptor()
                    << "\nPeso: "<<c.GetPeso()
                    << "\nMonto : "<<c.GetMonto()
                    <<endl;
        }
        else
        {
            cout << "No se encontr� ning�n paquete con la identificaci�n : "<<id<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es v�lido"<<endl;
    }
}
void listarPaquetes()
{
    vector<Paquete> paquetes=cargarPaquetes();
    if(paquetes.size()>0)
    {
        for(Paquete c:paquetes)
        {
            cout
                    << "\nNumero de paquete : "<<c.GetNumeroEnvio()
                    << "\nFecha de creacion : "<<c.GetFechaRegistro()
                    << "\nCliente que envia : "<<c.GetClienteEmisor()
                    << "\nCliente que recibe : "<<c.GetClienteReceptor()
                    << "\nPeso: "<<c.GetPeso()
                    << "\nMonto : "<<c.GetMonto()
                    <<endl;
        }
    }
    else
    {
        cout << "No hay paquetes que mostrar"<<endl;
    }


}

vector<Paquete> cargarPaquetes()
{
    globales global;
    vector<Paquete> paquetes;
    Paquete paquete;
    global.lectura.open(global.archivoPaquetes,ios::in);
    if(global.lectura.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    string id;
    string fecha;
    string emisor;
    string receptor;
    string peso;
    string monto;
    while(global.lectura >> id >> fecha >> emisor >> receptor >>  peso >>monto )
    {
        paquete.SetNumeroEnvio(id);
        paquete.SetFechaRegistro(fecha);
        paquete.SetClienteEmisor(emisor);
        paquete.SetClienteReceptor(receptor);
        paquete.SetPeso(peso);
        paquete.SetMonto(monto);
        paquetes.push_back(paquete);

    }
    global.lectura.close();

    return paquetes;
}


bool busquedaPaquete(vector<Paquete> paquetes,string dato)
{
    bool resultado=false;

    for(Paquete c:paquetes)
    {
        if(c.GetNumeroEnvio()==dato)
        {
            resultado=true;
        }
    }

    return resultado;
}



Paquete RetornarbusquedaPaquete(vector<Paquete> paquetes,string buscado)
{
    Paquete paquete;
    for(Paquete c:paquetes)
    {
        if(c.GetNumeroEnvio()==buscado)
        {
            paquete=c;
            break;
        }
    }

    return paquete;
}

bool  grabarPaquetes(vector<Paquete> paquetes)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoPaquetes,ios::out);


    if(global.escritura.fail())
    {
        cout <<"no se pudo abrir el archivo";
        exit(1);
    }

    for(Paquete c:paquetes)
    {
        global.escritura
                << c.GetNumeroEnvio()<<' '
                <<c.GetFechaRegistro()<<' '
                <<c.GetClienteEmisor()<<' '
                <<c.GetClienteReceptor()<< ' '
                <<c.GetPeso()<<' '
                <<c.GetMonto()<<' ';

    }
    global.escritura.flush();
    global.escritura.close();
    resultado=true;


    return resultado;
}
void ingresoPaquete()
{
    Paquete paquete=Paquete();
    string numero;
    string fecha;
    string emisor;
    string receptor;
    string peso;
    string monto;

    bool proceso=false;
    cout <<"Ingrese la identificacion del cliente que envia el paquete"<<endl;
    getline(std::cin,emisor);
    proceso=esCadenaValida(emisor)?true:false;
    //BUSCAR CLIENTE AQUI
    if(proceso)
    {

        cout <<"Ingrese la identificacion del cliente que recibe el paquete"<<endl;
        getline(std::cin,receptor);
        proceso=esCadenaValida(receptor)?true:false;
        //BUSCAR CLIENTE AQUI
        if(proceso)
        {


            cout <<"Ingrese el  peso del paquete"<<endl;
            getline(std::cin,peso);
            proceso=esCadenaValida(peso)?true:false;


        }
    }


    if(proceso)
    {
        vector<Paquete> paquetes=cargarPaquetes();

        int autoincremento=0;
        autoincremento=paquetes.size()+1;
        if(autoincremento<1)
        {
            autoincremento=1;
        }
        numero=to_string(autoincremento);
        paquete.SetNumeroEnvio(numero);
        paquete.SetClienteEmisor(emisor);
        paquete.SetClienteReceptor(receptor);
        paquete.SetFechaRegistro(fecha);
        paquete.SetPeso(peso);
        paquete.SetMonto(monto);

        bool busqueda=busquedaPaquete(paquetes,paquete.GetNumeroEnvio());

        if(busqueda)
        {
            cout << "Lo sentimos. No se puede registrar el paquete debido a que ya ha sido registrado anteriormente"<<endl;
        }
        else
        {
            paquetes.push_back(paquete);
            bool registrado=grabarPaquetes(paquetes);
            if(registrado)
            {
                cout<<"El paquete "<<paquete.GetNumeroEnvio() <<" ha sido registrado satisfactoriamente."<<endl;

            }
            else
            {
                cout<<"El paquete "<<paquete.GetNumeroEnvio() <<" no pudo ser registrado debido a un problema desconocido."<<endl;
            }
        }
    }
    else
    {
        cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
    }

}
//************************************MANTENIMIENTO PAQUETES*************************************


//************************************UTILITARIOS*************************************
bool ValidarSiEsNumero(string cadena)
{
    bool EsNumero=true;
    try
    {
        if(cadena.size()<11)
        {
            int entero=stoll(cadena);
        }
        else
        {
            EsNumero=false;
        }


    }
    catch(const std::invalid_argument &no_es_numero)
    {

        EsNumero=false;
    }

    return EsNumero;
}
bool esCadenaValida(string dato)
{
    if(dato.empty())
    {
        return false;
    }
    else
    {

        bool esblanco=false;
        int conteo=0;
        for(int i=0; i<dato.size(); i++)
        {
            if(isblank(dato[i]))
            {
                conteo++;
            }
        }
        if(conteo==dato.size())
        {
            esblanco=true;
        }
        if(esblanco)
        {
            return false;
        }
        else
        {
            return true;
        }

    }
}
string FechaDelSistema()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y");
    string str = oss.str();

    return str;
}
void inicializarArchivos()
{
    globales global;

    global.lectura.open(global.archivoClientes,ios::in);
    if(global.lectura.fail())
    {
        global.escritura.open(global.archivoClientes,ios::out);
        if(global.escritura.fail())
        {
            cout <<"no se pudo crear el archivo de clientes";
            exit(1);
        }
        else
        {
            global.escritura.close();
        }
    }
    else
    {
        global.lectura.close();
    }


    global.lectura.open(global.archivoChoferes,ios::in);
    if(global.lectura.fail())
    {
        global.escritura.open(global.archivoChoferes,ios::out);
        if(global.escritura.fail())
        {
            cout <<"no se pudo crear el archivo de choferes";
            exit(1);
        }
        else
        {
            global.escritura.close();
        }
    }
    else
    {
        global.lectura.close();
    }

}
//************************************UTILITARIOS*************************************


//************************************PROCESAMIENTO DE DATOS*************************************
void ProcesamientoDeDatosSubmenuClientes(int eleccion)
{
    cin.sync();
    switch (eleccion)
    {
    case 1:
    {
        string seguir="";
        do
        {
            cin.sync();
            ingresoCliente();
            cout << "Desea ingresar mas clientes? S/N" << endl;
            cin >> seguir;
        }
        while(seguir=="S" || seguir=="s");
    }
    break;
    case 2:
    {
        modificarCliente();
    }
    break;
    case 3:

        listarClientes();
        break;
    case 4:
    {
        buscarCliente();
    }

    break;
    case 5:
        eliminarCliente();
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}

void ProcesamientoDeDatosSubmenuPaquetes(int eleccion)
{
    cin.sync();
    switch (eleccion)
    {
    case 1:
    {
        string seguir="";
        do
        {
            cin.sync();
            ingresoChofer();
            cout << "Desea ingresar mas paquetes? S/N" << endl;
            cin >> seguir;

        }
        while(seguir=="S" || seguir=="s");
    }

    break;
    case 2:
        modificarChofer();
        break;
    case 3:
        listarChofers();
        break;
    case 4:
        buscarChofer();
        break;
    case 5:
        eliminarChofer();
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
void ProcesamientoDeDatosSubmenuChoferes(int eleccion)
{
    cin.sync();
    switch (eleccion)
    {
    case 1:
    {
        string seguir="";
        do
        {
            cin.sync();
            ingresoChofer();
            cout << "Desea ingresar mas choferes? S/N" << endl;
            cin >> seguir;

        }
        while(seguir=="S" || seguir=="s");
    }

    break;
    case 2:
        modificarChofer();
        break;
    case 3:
        listarChofers();
        break;
    case 4:
        buscarChofer();
        break;
    case 5:
        eliminarChofer();
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
int MostrarMenu()
{
    cin.sync();
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Mantenimiento de choferes" << endl;
    cout << "[2] Mantenimiento de clientes" << endl;
    cout << "[3] Env�o de paquetes" << endl;
    cout << "[4] Cierre de envios" << endl;
    cout << "[5] Reportes" << endl;
    cout << "[6] Salir" << endl;
    cin >> option;


    if(ValidarSiEsNumero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}
int MostrarMenuClientes()
{
    cin.sync();
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Ingresar un cliente" << endl;
    cout << "[2] Modificar un cliente" << endl;
    cout << "[3] Listar clientes" << endl;
    cout << "[4] Buscar cliente" << endl;
    cout << "[5] Eliminar un cliente" << endl;
    cout << "[6] Volver al men� principal" << endl;
    cin >> option;

    if(ValidarSiEsNumero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}
int MostrarMenuChoferes()
{
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Ingresar un chofer" << endl;
    cout << "[2] Modificar un chofer" << endl;
    cout << "[3] Listar choferes" << endl;
    cout << "[4] Buscar chofer" << endl;
    cout << "[5] Eliminar un chofer" << endl;
    cout << "[6] Volver al men� principal" << endl;
    cin >> option;

    if(ValidarSiEsNumero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}

int MostrarMenuPaquetes()
{
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Ingresar un paquete" << endl;
    cout << "[2] Modificar un paquete" << endl;
    cout << "[3] Listar paquetes" << endl;
    cout << "[4] Buscar paquete" << endl;
    cout << "[5] Eliminar un paquete" << endl;
    cout << "[6] Volver al men� principal" << endl;
    cin >> option;

    if(ValidarSiEsNumero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}
void EscucharOpcionesClientes()
{
    int solicitud=-1;
    do
    {
        solicitud=MostrarMenuClientes();
        ProcesamientoDeDatosSubmenuClientes(solicitud);
    }
    while(solicitud != 6);
}
void EscucharOpcionesPaquetes()
{
    int solicitud=-1;
    do
    {
        solicitud=MostrarMenuPaquetes();
        ProcesamientoDeDatosSubmenuPaquetes(solicitud);
    }
    while(solicitud != 6);
}
void EscucharOpcionesChoferes()
{
    int solicitud=-1;

    do
    {
        solicitud=MostrarMenuChoferes();
        ProcesamientoDeDatosSubmenuChoferes(solicitud);
    }
    while(solicitud != 6);
}
void ProcesamientoDeDatos(int eleccion)
{
    cin.sync();
    switch (eleccion)
    {
    case 1:

        EscucharOpcionesChoferes();
        break;
    case 2:

        EscucharOpcionesClientes();
        break;
    case 3:
        cout << "Env�o de paquetes\n\n\n";
        break;
    case 4:
        cout << "Cierre de envios\n\n\n";
        break;
    case 5:
        cout << "Reportes\n\n\n";
        break;
    case 6:
        cout << "Salir\n\n\n";
        exit(1);
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
void EscucharOpciones()
{
    int solicitud=-1;
    do
    {
        solicitud=MostrarMenu();
        ProcesamientoDeDatos(solicitud);
    }
    while(solicitud != 6);
}
//************************************PROCESAMIENTO DE DATOS*************************************




int main()
{
    setlocale(LC_ALL, "");//para los acentos
    inicializarArchivos();
    EscucharOpciones();
    return 0;

}
