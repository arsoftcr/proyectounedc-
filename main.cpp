#include <iostream>
#include <stdexcept>
#include <string>
#include <Chofer.h>
#include <Paquete.h>
#include <Paquetes_Vehiculos.h>
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
#include <string.h>
#include <algorithm>
#include <time.h>
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

//************************************ESPACIO*************************************
bool  grabarEspacio(float espacio);
string cargarEspacio();
//************************************ESPACIO*************************************

//************************************REPORTES*************************************
void reportePaquetesXVehiculo();
void reporteTotales();
//************************************REPORTES*************************************

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

//************************************MANTENIMIENTO PAQUETESXVEHICULO*************************************
bool  grabarEnviados(vector<int> enviados);
vector<int> cargarEnviados();
//************************************MANTENIMIENTO PAQUETESXVEHICULO*************************************


//************************************MANTENIMIENTO PAQUETES*************************************
void EscucharOpcionesPaquetes();
int MostrarMenuPaquetes();
void ProcesamientoDeDatosSubmenuPaquetes(int solicitud);
void borrarEspacioYPendientes();
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
bool ValidarSiEsCedula(string cadena);
bool ValidarSiEsFloat(string cadena);
bool ValidarSiEsEntero(string cadena);
bool esCadenaValida(string dato);
bool ValidarSiEsFecha(string cadena);
string quitarEspaciosEnBlanco(string cadena);
bool ValidarSiEsEstado(string cadena);
bool ValidarSiEsLicencia(string cadena);
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

//Para no utilizar variables globales, se me ocurrió utilizar un struct/////////////////////////////
struct globales
{
    ofstream escritura;
    ifstream lectura;
    string archivoClientes="cliente.txt";
    string archivoChoferes="chofer.txt";
    string archivoPaquetes="paquete.txt";
    string archivoEnvios="envio.txt";
    string archivoEspacio="espacio.txt";
    string archivoEnviados="enviados.txt";
    string espacio;
    vector<int> enviados;
    float espacioMaximo=3000;
};

//************************************MANTENIMIENTO PAQUETESXVEHICULO*************************************
//Este método graba en el archivo de envíos los datos de los cierres
bool  grabarCierre(vector<Paquetes_Vehiculos> cierres)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoEnvios,ios::out);


    if(global.escritura.fail())
    {
        cout <<"No se pudo abrir el archivo";
        exit(1);
    }

    for(Paquetes_Vehiculos pe:cierres)
    {
        global.escritura
                << pe.GetVehiculo()<<' '
                << pe.GetChofer()<<' '
                << pe.GetEnvio()<<' ';
    }


    global.escritura.flush();
    global.escritura.close();
    resultado=true;


    return resultado;
}
//Este método carga todos los datos del archivo de cierres
vector<Paquetes_Vehiculos> cargarCierre()
{
    globales global;
    vector<Paquetes_Vehiculos> cerrados;
    global.lectura.open(global.archivoEnvios,ios::in);
    if(global.lectura.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    string vehiculo;
    string chofer;
    string envio;
    Paquetes_Vehiculos pes;
    while(global.lectura >> vehiculo >> chofer >> envio )
    {
        pes.SetVehiculo(vehiculo);
        pes.SetChofer(chofer);
        pes.SetEnvio(envio);
        cerrados.push_back(pes);

    }
    global.lectura.close();

    return cerrados;
}

//************************************MANTENIMIENTO PAQUETESXVEHICULO*************************************


//************************************ESPACIO*************************************
//Este método guarda todos los paquetes que estan pendientes por enviar
bool  grabarEnviados(vector<int> enviados)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoEnviados,ios::out);


    if(global.escritura.fail())
    {
        cout <<"No se pudo abrir el archivo";
        exit(1);
    }

    for(int e:enviados)
    {
        global.escritura
                << to_string(e) <<' ';
    }


    global.escritura.flush();
    global.escritura.close();
    resultado=true;


    return resultado;
}
//Este método carga los paquetes que estan pendientes de enviar
vector<int> cargarEnviados()
{
    globales global;
    vector<int> enviados;
    global.lectura.open(global.archivoEnviados,ios::in);
    if(global.lectura.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    string env;
    while(global.lectura >> env )
    {
        enviados.push_back(stoi(env));

    }
    global.lectura.close();

    return enviados;
}
//Este método graba los datos del espacio que ocupan actualmente los paquetes pendientes de envío
bool  grabarEspacio(float espacio)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoEspacio,ios::out);


    if(global.escritura.fail())
    {
        cout <<"No se pudo abrir el archivo";
        exit(1);
    }


    global.escritura
            << espacio;

    global.escritura.flush();
    global.escritura.close();
    resultado=true;


    return resultado;
}
//Este método devuelve el espacio ocupado actualmente por los paquetes
//pendientes de envío con el fin de validar cuanto espacio queda
string cargarEspacio()
{
    globales global;
    string space;
    global.lectura.open(global.archivoEspacio,ios::in);
    if(global.lectura.fail())
    {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    string espacio;
    while(global.lectura >> espacio )
    {
        space=espacio;

    }
    global.lectura.close();

    return space;
}
//************************************ESPACIO*************************************

//************************************MANTENIMIENTO CLIENTES*************************************
//Modifica los datos de un cliente
void modificarCliente()
{
    string id;
    string nombre;
    string apellidos;
    string telefono;
    string email;
    string direccion;
    cout << "Ingrese el número de identificación del cliente que desea modificar"<<endl;
    getline(cin,id);

    if(esCadenaValida(id))
    {
        id=quitarEspaciosEnBlanco(id);//quitar espacios para evitar inconsistencias

        if(ValidarSiEsCedula(id))
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
                    nombre=quitarEspaciosEnBlanco(nombre);
                    c.SetNombre(nombre);
                }
                cout << "\nLos apellidos actuales del cliente son : "<<c.GetApellidos()<<endl;
                cout << "Digite los nuevos apellidos o presione enter para mantener los mismos apellidos"<<endl;
                getline(cin,apellidos);
                if(esCadenaValida(apellidos))
                {
                    apellidos=quitarEspaciosEnBlanco(apellidos);
                    c.SetApellidos(apellidos);
                }
                cout << "\nLa dirección actual del cliente es : "<<c.GetDireccion()<<endl;
                cout << "Digite la nueva dirección o presione enter para mantener la misma dirección"<<endl;
                getline(cin,direccion);
                if(esCadenaValida(direccion))
                {
                    direccion=quitarEspaciosEnBlanco(direccion);
                    c.SetDireccion(direccion);
                }
                cout << "\nEl email actual del cliente es : "<<c.GetEmail()<<endl;
                cout << "Digite el nuevo email o presione enter para mantener el mismo email"<<endl;
                getline(cin,email);
                if(esCadenaValida(email))
                {
                    email=quitarEspaciosEnBlanco(email);
                    c.SetEmail(email);
                }
                cout << "\nEl teléfono actual del cliente es : "<<c.GetTelefono()<<endl;
                cout << "Digite el nuevo teléfono o presione enter para mantener el mismo teléfono"<<endl;
                getline(cin,telefono);
                if(esCadenaValida(telefono))
                {
                    telefono=quitarEspaciosEnBlanco(telefono);
                    c.SetTelefono(telefono);
                }

                clientesXGrabar.push_back(c);
                bool grabado=grabarClientes(clientesXGrabar);
                if(grabado)
                {
                    cout << "El cliente con la identificación : "<<c.GetIdentificacion()<<" ha sido modificado satisfactoriamente"<<endl;
                }
                else
                {
                    cout << "El cliente no pudo ser modificado por un problema desconocido"<<endl;
                }
            }
            else
            {
                cout << "No se encontró ningún cliente con la identificación : "<<id<<endl;
            }
        }
        else
        {
            cout << "No se encontró ningún cliente con la identificación : "<<id<<endl;
        }
    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }

}
//Elimina de un vector los datos de un cliente
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
//Carga los clientes, elimina el cliente de memoria y posteriormente sobreescribe los datos en el archivo
void eliminarCliente()
{
    string id;
    cout << "Ingrese el número de identificación del cliente que desea eliminar"<<endl;
    getline(cin,id);

    if(esCadenaValida(id))
    {
        id=quitarEspaciosEnBlanco(id);

        if(ValidarSiEsCedula(id))
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
                    cout << "El cliente con la identificación : "<<c.GetIdentificacion()<<" ha sido eliminado satisfactoriamente"<<endl;
                }
                else
                {
                    cout << "El cliente no pudo ser modificado por un problema desconocido"<<endl;
                }
            }
            else
            {
                cout << "No se encontró ningún cliente con la identificación : "<<id<<endl;
            }
        }
        else
        {
            cout << "No se encontró ningún cliente con la identificación : "<<id<<endl;
        }


    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }
};
//Busca un cliente cargando los datos en memoria
void buscarCliente()
{
    string id;
    cout << "Ingrese el número de identificación del cliente que desea buscar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id))
    {
        id=quitarEspaciosEnBlanco(id);

        if(ValidarSiEsCedula(id))
        {
            vector<Cliente> clientes=cargarClientes();
            bool busqueda=busquedaCliente(clientes,id);
            if(busqueda)
            {
                Cliente c=RetornarbusquedaCliente(clientes,id);
                cout
                        << "\nIdentificación : "<<c.GetIdentificacion()
                        << "\nNombre : "<<c.GetNombre()
                        << "\nApellidos : "<<c.GetApellidos()
                        << "\nDirección : "<<c.GetDireccion()
                        << "\nEmail : "<<c.GetEmail()
                        << "\nTeléfono : "<<c.GetTelefono()
                        <<endl;
            }
            else
            {
                cout << "No se encontró ningún cliente con la identificación : "<<id<<endl;
            }
        }
        else
        {
            cout << "No se encontró ningún cliente con la identificación : "<<id<<endl;
        }


    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }
}
//Muestra todos los clientes existentes
void listarClientes()
{
    vector<Cliente> clientes=cargarClientes();
    if(clientes.size()>0)
    {
        for(Cliente c:clientes)
        {
            cout << "\nIdentificación : " << c.GetIdentificacion()
                 <<"\nNombre : "<< c.GetNombre()
                 <<"\nApellidos : "<<c.GetApellidos()
                 <<"\nDirección : "<<c.GetDireccion()
                 <<"\nEmail : "<<c.GetEmail()
                 <<"\nTeléfono : "<< c.GetTelefono()<< endl;
        }
    }
    else
    {
        cout << "No hay clientes que mostrar"<<endl;
    }


}
//Carga los datos del archivo de clientes
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

//Valida si un cliente existe
bool busquedaCliente(vector<Cliente> clientes,string dato)
{
    dato=quitarEspaciosEnBlanco(dato);
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


//Devuelve los datos de la busqueda de un cliente
Cliente RetornarbusquedaCliente(vector<Cliente> clientes,string buscado)
{
    buscado=quitarEspaciosEnBlanco(buscado);

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
//Guarda los clientes en memoria en el archivo de clientes
bool  grabarClientes(vector<Cliente> clientes)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoClientes,ios::out);


    if(global.escritura.fail())
    {
        cout <<"No se pudo abrir el archivo";
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
//Solicita los datos al usuario para agregar un cliente al archivo
void ingresoCliente()
{

    Cliente cliente=Cliente();
    string id;
    string email;
    string nombre;
    string apellidos;
    string direccion;
    string telefono;
    cout <<"Ingrese la identificación del cliente,este debe ser un dato numérico y debe contener mas de 8 caracteres y  menos de 11 caracteres"<<endl;
    getline(std::cin,id);
    bool proceso=esCadenaValida(id)?true:false;
    id=quitarEspaciosEnBlanco(id);
    if(proceso)
    {
        proceso=ValidarSiEsCedula(id)?true:false;
    }
    if(proceso)
    {

        cout <<"Ingrese el nombre del cliente"<<endl;
        getline(std::cin,nombre);
        proceso=esCadenaValida(nombre)?true:false;

        if(proceso)
        {
            nombre=quitarEspaciosEnBlanco(nombre);

            cout <<"Ingrese los apellidos del cliente"<<endl;
            getline(std::cin,apellidos);
            proceso=esCadenaValida(apellidos)?true:false;
            if(proceso)
            {
                apellidos=quitarEspaciosEnBlanco(apellidos);
                cout <<"Ingrese la dirección del cliente"<<endl;
                getline(std::cin,direccion);
                proceso=esCadenaValida(direccion)?true:false;
                if(proceso)
                {
                    direccion=quitarEspaciosEnBlanco(direccion);
                    cout <<"Ingrese el  teléfono del cliente"<<endl;
                    getline(std::cin,telefono);
                    proceso=esCadenaValida(telefono)?true:false;
                    if(proceso)
                    {
                        telefono=quitarEspaciosEnBlanco(telefono);
                        cout <<"Ingrese el  email del cliente"<<endl;
                        getline(std::cin,email);
                        proceso=esCadenaValida(email)?true:false;
                        if(proceso)
                        {
                            email=quitarEspaciosEnBlanco(email);
                        }
                    }
                }
            }
        }
    }

    if(proceso)
    {
        vector<Cliente> clientes=cargarClientes();

        cliente.SetIdentificacion(quitarEspaciosEnBlanco(id));
        cliente.SetApellidos(apellidos);
        cliente.SetDireccion(direccion);
        cliente.SetEmail(quitarEspaciosEnBlanco(email));
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
//NOTA :SOLO SE PERMITE MODIFICAR LA LICENCIA Y EL ESTADO SEGÚN INDICA EL PDF DEL PROYECTO.

//Modifica los datos de un chofer
void modificarChofer()
{
    string id;
    string nombre;
    string apellidos;
    string numero;
    string estado;
    string tipo;
    cout << "Ingrese el número de identificación del chofer que desea modificar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id))
    {
        if(ValidarSiEsEntero(id))
        {
            id=quitarEspaciosEnBlanco(id);
            vector<Chofer> chofers=cargarChofers();
            bool busqueda=busquedaChofer(chofers,id);
            if(busqueda)
            {
                Chofer c=RetornarbusquedaChofer(chofers,id);
                vector<Chofer> chofersXGrabar=removerChofer(chofers,c);
                cout<< "\nEl tipo de licencia actual del chofer es : "<<c.GetTipoLicencia()<<endl;
                cout << "Digite el nuevo tipo de licencia o presione enter para mantener el mismo tipo."
                     <<"Los valores válidos son: B2,E2";
                getline(cin,tipo);
                if(esCadenaValida(tipo))
                {
                    if(ValidarSiEsLicencia(tipo))
                    {
                        tipo=quitarEspaciosEnBlanco(tipo);
                        c.SetTipoLicencia(tipo);
                    }

                }
                cout << "\nEl estado actual del chofer es : "<<c.GetEstado()<<endl;
                cout << "Digite el nuevo estado o presione enter para mantener el mismo estado. Ingrese un 1 para indicar que está activo o ingrese un 2 para indicar que esta inactivo"<<endl;
                getline(cin,estado);
                if(esCadenaValida(estado))
                {
                    if(ValidarSiEsEstado(estado))
                    {
                        estado=quitarEspaciosEnBlanco(estado);
                        c.SetEstado(estado);
                    }
                }

                chofersXGrabar.push_back(c);
                bool grabado=grabarChofers(chofersXGrabar);
                if(grabado)
                {
                    cout << "El chofer con la identificación : "<<c.GetIdentificacion()<<" ha sido modificado satisfactoriamente"<<endl;
                }
                else
                {
                    cout << "El chofer no pudo ser modificado por un problema desconocido"<<endl;
                }
            }
            else
            {
                cout << "No se encontró ningún chofer con la identificación : "<<id<<endl;
            }

        }
        else
        {

            cout << "El dato ingresado no es válido"<<endl;
        }

    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }
}
//Elimina un chofer en memoria
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
//Elimina un chofer del archivo
void eliminarChofer()
{
    string id;
    cout << "Ingrese el número de identificación del chofer que desea eliminar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id))
    {
        id=quitarEspaciosEnBlanco(id);
        if(ValidarSiEsEntero(id))
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
                    cout << "El chofer con el número : "<<c.GetIdentificacion()<<" ha sido eliminado satisfactoriamente"<<endl;
                }
                else
                {
                    cout << "El chofer no pudo ser modificado por un problema desconocido"<<endl;
                }
            }
            else
            {
                cout << "No se encontró ningún chofer con el número de identificacion: "<<id<<endl;
            }
        }
        else
        {
            cout << "No se encontró ningún chofer con el número de identificación: "<<id<<endl;
        }


    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }
};
//Busca un chofer
void buscarChofer()
{
    string id;
    cout << "Ingrese el número de identificación  del chofer que desea buscar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id))
    {
        id=quitarEspaciosEnBlanco(id);
        if(ValidarSiEsEntero(id))
        {
            vector<Chofer> chofers=cargarChofers();
            bool busqueda=busquedaChofer(chofers,id);
            if(busqueda)
            {
                Chofer c=RetornarbusquedaChofer(chofers,id);
                cout
                        << "\nIdentificación : "<<c.GetIdentificacion()
                        << "\nNombre : "<<c.GetNombre()
                        << "\nApellidos : "<<c.GetApellidos()
                        << "\nNúmero : "<<c.GetNumero()
                        << "\nEstado : "<<c.GetEstado()
                        << "\nTipo de licencia : "<<c.GetTipoLicencia()
                        <<endl;
            }
            else
            {
                cout << "No se encontró ningún chofer con el número  : "<<id<<endl;
            }
        }
        else
        {
            cout << "No se encontró ningún chofer con el número  : "<<id<<endl;
        }


    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }
}
//Muestra los datos de los choferes
void listarChofers()
{
    vector<Chofer> chofers=cargarChofers();
    if(chofers.size()>0)
    {
        for(Chofer c:chofers)
        {
            cout << "\nIdentificación : " << c.GetIdentificacion()
                 <<"\nNombre : "<< c.GetNombre()
                 <<"\nApellidos : "<<c.GetApellidos()
                 <<"\nNúmero : "<<c.GetNumero()
                 <<"\nEstado : "<<c.GetEstado()
                 <<"\nTipo de licencia : "<< c.GetTipoLicencia()<< endl;
        }
    }
    else
    {
        cout << "No hay choferes que mostrar"<<endl;
    }


}
//Carga los choferes del archivo
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

//Valida si existe un chofer
bool busquedaChofer(vector<Chofer> chofers,string dato)
{
    bool resultado=false;
    dato=quitarEspaciosEnBlanco(dato);

    for(Chofer c:chofers)
    {
        if(c.GetIdentificacion()==dato)
        {
            resultado=true;
        }
    }

    return resultado;
}
//Retorna los datos de un chofer
Chofer RetornarbusquedaChofer(vector<Chofer> chofers,string buscado)
{
    Chofer chofer;
    buscado=quitarEspaciosEnBlanco(buscado);
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
//Guarda los choferes
bool  grabarChofers(vector<Chofer> chofers)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoChoferes,ios::out);


    if(global.escritura.fail())
    {
        cout <<"No se pudo abrir el archivo";
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
//Solicita los datos al usuario para guardar un chofer
void ingresoChofer()
{
    try
    {
        Chofer chofer=Chofer();
        string id;
        string estado;
        string nombre;
        string apellidos;
        string numero;
        string tipo;
        cout <<"Ingrese la identificación del chofer,este debe ser un dato numérico y debe contener mas de 8 caracteres y  menos de 11 caracteres"<<endl;
        getline(std::cin,id);
        bool proceso=esCadenaValida(id)?true:false;
        if(proceso)
        {
            id=quitarEspaciosEnBlanco(id);
            proceso=ValidarSiEsCedula(id)?true:false;
        }

        if(proceso)
        {

            cout <<"Ingrese el nombre del chofer"<<endl;
            getline(std::cin,nombre);
            proceso=esCadenaValida(nombre)?true:false;
            if(proceso)
            {
                nombre=quitarEspaciosEnBlanco(nombre);
                cout <<"Ingrese los apellidos del chofer"<<endl;
                getline(std::cin,apellidos);
                proceso=esCadenaValida(apellidos)?true:false;
                if(proceso)
                {
                    apellidos=quitarEspaciosEnBlanco(apellidos);
                    cout <<"Ingrese el  tipo de licencia del chofer."
                         << "Los valores válidos son: B2,E2"<<endl;
                    getline(std::cin,tipo);
                    proceso=esCadenaValida(tipo)?true:false;
                    tipo=quitarEspaciosEnBlanco(tipo);
                    proceso=ValidarSiEsLicencia(tipo);
                    if(proceso)
                    {

                        cout <<"Ingrese el  estado del chofer. Ingrese un 1 para indicar que está activo o ingrese un 2 para indicar que esta inactivo"<<endl;
                        getline(std::cin,estado);
                        proceso=esCadenaValida(estado)?true:false;
                        if(proceso)
                        {
                            estado=quitarEspaciosEnBlanco(estado);
                            proceso=ValidarSiEsEstado(estado)?true:false;

                            if(proceso==false)
                            {
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
            int ultimo;

            ultimo=chofers.empty()?0:stoll(chofers.at(chofers.size()-1).GetNumero());



            autoincremento=ultimo+1;
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

            bool busqueda=busquedaChofer(chofers,chofer.GetNumero());

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
    catch (const std::out_of_range& oor)
    {
        std::cerr <<  oor.what() << '\n';
    }



}
//************************************MANTENIMIENTO CHOFERES*************************************

//************************************MANTENIMIENTO PAQUETES*************************************
//Modifica los datos de un paquete
void modificarPaquete()
{
    string id;
    string emisor;
    string receptor;
    string fecha;
    vector<Cliente> clientes;

    cout << "Ingrese el número del paquete que desea modificar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id))
    {
        id=quitarEspaciosEnBlanco(id);
        if(ValidarSiEsEntero(id))
        {
            clientes=cargarClientes();
            vector<Paquete> paquetes=cargarPaquetes();
            bool busqueda=busquedaPaquete(paquetes,id);
            if(busqueda)
            {
                Paquete c=RetornarbusquedaPaquete(paquetes,id);
                vector<Paquete> paquetesXGrabar=removerPaquete(paquetes,c);
                cout<< "\nLa identificación del cliente que envía  es : "<<c.GetClienteEmisor()<<endl;
                cout << "Digite el nuevo cliente o presione enter para mantener el mismo cliente"<<endl;
                getline(cin,emisor);
                if(esCadenaValida(emisor))
                {
                    emisor=quitarEspaciosEnBlanco(emisor);

                    c.SetClienteEmisor(emisor);

                }
                cout<< "\nLa identificación del cliente que recibe  es : "<<c.GetClienteEmisor()<<endl;
                cout << "Digite el nuevo cliente o presione enter para mantener el mismo cliente"<<endl;
                getline(cin,receptor);
                if(esCadenaValida(receptor))
                {
                    receptor=quitarEspaciosEnBlanco(receptor);

                    c.SetClienteReceptor(receptor);

                }
                cout << "\nLa fecha de registro es : "<<c.GetFechaRegistro()<<endl;
                cout << "Digite la nueva fecha o presione enter para mantener la misma"<<endl;
                getline(cin,fecha);
                if(esCadenaValida(fecha))
                {
                    fecha=quitarEspaciosEnBlanco(fecha);
                    if(ValidarSiEsFecha(fecha))
                    {
                        c.SetFechaRegistro(fecha);
                    }
                    else
                    {
                        cout <<"Se ingresó una fecha inválida"<<endl;
                    }

                }

                paquetesXGrabar.push_back(c);
                bool grabado=grabarPaquetes(paquetesXGrabar);
                if(grabado)
                {
                    cout << "El paquete con el número : " << c.GetNumeroEnvio() << " ha sido modificado satisfactoriamente" << endl;
                }
                else
                {
                    cout << "El paquete no pudo ser modificado por un problema desconocido"<<endl;
                }
            }
            else
            {
                cout << "No se encontró ningún paquete con el número : "<<id<<endl;
            }
        }
        else
        {
            cout << "No se encontró ningún paquete con el número : "<<id<<endl;
        }


    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }
}
//Elimina un paquete de memoria
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
//Elimina un paquete del archivo
void eliminarPaquete()
{
    string id;
    cout << "Ingrese el número  del paquete que desea eliminar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id))
    {
        if(ValidarSiEsEntero(id))
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
                    cout << "El paquete con el número : "<<c.GetNumeroEnvio()<<" ha sido eliminado satisfactoriamente"<<endl;
                }
                else
                {
                    cout << "El paquete no pudo ser modificado por un problema desconocido"<<endl;
                }
            }
            else
            {
                cout << "No se encontró ningún paquete con el número : "<<id<<endl;
            }
        }
        else
        {
            cout << "No se encontró ningún paquete con el número : "<<id<<endl;
        }


    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }
};
//Realiza el cierre, asignando los paquetes a los vehículos
void asignacionPaquetesXVehiculo(vector<int> enviados)
{
    globales global;

    vector<Paquete> paquetes=cargarPaquetes();
    vector<Paquete> paquetesAProcesar;

    global.lectura.open(global.archivoEnvios,ios::in);
    if(global.lectura.fail())
    {
        global.escritura.open(global.archivoEnvios,ios::out);
        if(global.escritura.fail())
        {
            cout <<"No se pudo crear el archivo de envíos";
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


    for(int e:enviados)
    {
        for(Paquete p:paquetes)
        {
            if(to_string(e)==p.GetNumeroEnvio())
            {
                paquetesAProcesar.push_back(p);
            }
        }
    }

    int vehiculo=1;
    float capacidad=0;
    vector<Paquete> vehiculo1;
    vector<Paquete> vehiculo2;
    vector<Paquete> vehiculo3;
    Chofer chofer1;
    Chofer chofer2;
    Chofer chofer3;

    vector<Chofer> choferes;
    choferes=cargarChofers();

    if(choferes.size()>2)
    {
        // asignar choferes
        int chofer=1;
        for(Chofer c:choferes)
        {
            if(c.GetEstado()=="1")
            {
                switch(chofer)
                {
                case 1:
                    chofer1=c;
                    break;
                case 2:
                    chofer2=c;
                    break;
                case 3:
                    chofer3=c;
                    break;
                default:
                    break;
                }
                chofer++;
            }
        }
        //asignar paquetes a los vehiculos
        for(Paquete p:paquetesAProcesar)
        {
            float peso=stof(p.GetPeso());
            capacidad=capacidad+peso;

            if(peso<=1000&&capacidad<=1000)
            {
                switch(vehiculo)
                {
                case 1:
                    vehiculo1.push_back(p);
                    break;
                case 2:
                    vehiculo2.push_back(p);
                    break;
                case 3:
                    vehiculo3.push_back(p);
                    break;
                default:
                    break;
                }
            }
            else
            {
                capacidad=0;
                vehiculo++;
                capacidad=capacidad+peso;
                switch(vehiculo)
                {
                case 1:
                    vehiculo1.push_back(p);
                    break;
                case 2:
                    vehiculo2.push_back(p);
                    break;
                case 3:
                    vehiculo3.push_back(p);
                    break;
                default:
                    break;
                }
            }
        }

        vector<Paquetes_Vehiculos> paquetesVehiculos=cargarCierre();
         vector<Paquetes_Vehiculos> procesados;
        Paquetes_Vehiculos paqueteVehiculo;

        for(Paquete p:vehiculo1)
        {
            paqueteVehiculo.SetVehiculo("1");
            paqueteVehiculo.SetChofer(chofer1.GetNumero());
            paqueteVehiculo.SetEnvio(p.GetNumeroEnvio());
            procesados.push_back(paqueteVehiculo);
            paquetesVehiculos.push_back(paqueteVehiculo);

        }
        for(Paquete p:vehiculo2)
        {
            paqueteVehiculo.SetVehiculo("2");
            paqueteVehiculo.SetChofer(chofer2.GetNumero());
            paqueteVehiculo.SetEnvio(p.GetNumeroEnvio());
             procesados.push_back(paqueteVehiculo);
            paquetesVehiculos.push_back(paqueteVehiculo);
        }
        for(Paquete p:vehiculo3)
        {
            paqueteVehiculo.SetVehiculo("3");
            paqueteVehiculo.SetChofer(chofer3.GetNumero());
            paqueteVehiculo.SetEnvio(p.GetNumeroEnvio());
             procesados.push_back(paqueteVehiculo);
            paquetesVehiculos.push_back(paqueteVehiculo);
        }

        bool guardado=grabarCierre(paquetesVehiculos);

        float pesoTotal=0;
        float ganancia=0;
        if(guardado)
        {
            for(Paquetes_Vehiculos pv:procesados)
            {
                cout<<"Vehículo: "<<pv.GetVehiculo()<<endl;
                cout<<"Chofer asignado: "<<pv.GetChofer()<<endl;
                cout<<"Paquete asignado: "<<pv.GetEnvio()<<endl;
                Paquete paq=RetornarbusquedaPaquete(paquetes,pv.GetEnvio());
                pesoTotal=pesoTotal+stof(paq.GetPeso());
                ganancia=ganancia+stof(paq.GetMonto());
                cout<<"Peso del paquete: "<<paq.GetPeso()<<endl;

            }

            cout<<"Total de paquetes enviados: "<<paquetesVehiculos.size()<<endl;
            cout<<"Peso total de paquetes enviados: "<<pesoTotal<<endl;
            cout<<"Ganancia total de paquetes enviados: "<<ganancia<<endl;

            borrarEspacioYPendientes();
        }
        else
        {
            cout <<"Un error desconocido ha sucedido por lo que no fue posible guardar los datos del cierre"<<endl;
        }


    }
    else
    {
        cout <<"No existe la cantidad mínima de choferes para asignarlos en el cierre. Por favor agregue más choferes"<<endl;
    }




}
//Borra los datos del archivo de espacio y pendientes para permitir realizar otros envíos
void borrarEspacioYPendientes()
{
    globales global;
    global.escritura.open(global.archivoEspacio,ios::out);
    if(global.escritura.fail())
    {
        cout <<"No se pudo crear el archivo de espacio";
        exit(1);
    }
    else
    {
        global.escritura.close();
    }

    global.escritura.open(global.archivoEnviados,ios::out);
    if(global.escritura.fail())
    {
        cout <<"No se pudo crear el archivo de enviados";
        exit(1);
    }
    else
    {
        global.escritura.close();
    }
}
//Busca un paquete
void buscarPaquete()
{
    string id;
    cout << "Ingrese el número  del paquete que desea buscar"<<endl;
    getline(cin,id);
    if(esCadenaValida(id))
    {
        if(ValidarSiEsEntero(id))
        {
            vector<Paquete> paquetes=cargarPaquetes();
            bool busqueda=busquedaPaquete(paquetes,id);
            if(busqueda)
            {
                Paquete c=RetornarbusquedaPaquete(paquetes,id);
                cout
                        << "\nNúmero de paquete : "<<c.GetNumeroEnvio()
                        << "\nFecha de creación : "<<c.GetFechaRegistro()
                        << "\nCliente que envía : "<<c.GetClienteEmisor()
                        << "\nCliente que recibe : "<<c.GetClienteReceptor()
                        << "\nPeso: "<<c.GetPeso()
                        << "\nMonto : "<<c.GetMonto()
                        <<endl;
            }
            else
            {
                cout << "No se encontró ningún paquete con el número : "<<id<<endl;
            }
        }
        else
        {
            cout << "No se encontró ningún paquete con el número : "<<id<<endl;
        }


    }
    else
    {
        cout << "El dato ingresado no es válido"<<endl;
    }
}
//Muestra los datos de todos los paquetes del archivo
void listarPaquetes()
{
    vector<Paquete> paquetes=cargarPaquetes();
    if(paquetes.size()>0)
    {
        for(Paquete c:paquetes)
        {
            cout
                    << "\nNúmero de paquete : "<<c.GetNumeroEnvio()
                    << "\nFecha de creación : "<<c.GetFechaRegistro()
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
//Carga los paquetes del archivo
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

//Busca un paquete
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
//Retorna los datos de un paquete
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
//Guarda los datos de los paquetes
bool  grabarPaquetes(vector<Paquete> paquetes)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoPaquetes,ios::out);


    if(global.escritura.fail())
    {
        cout <<"No se pudo abrir el archivo";
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
//Agrega un paquete solicitándole los datos al usuario
void ingresoPaquete()
{
    cin.sync();
    string opc="";
    try
    {
        Paquete paquete=Paquete();
        string numero;
        string fecha;
        string emisor;
        string receptor;
        string peso;
        string monto;
        float pesoFloat=0;
        float montoFloat=0;
        vector<Cliente> clientes;
        bool proceso=false;
        globales global;
        cout <<"Ingrese la identificación del cliente que envía el paquete"<<endl;
        getline(std::cin,emisor);
        proceso=esCadenaValida(emisor)?true:false;
        if(proceso)
        {
            clientes=cargarClientes();
            emisor=quitarEspaciosEnBlanco(emisor);
            proceso=busquedaCliente(clientes,emisor);

            if(!proceso)
            {
                cin.sync();
                string opc;
                cout <<"El cliente ingresado no ha sido previamente registrado"
                     <<".Desea registrarlo ahora? S/N"<<endl;
                getline(cin,opc);
                if(esCadenaValida(opc))
                {
                    if(opc=="s"||opc=="S")
                    {
                        ingresoCliente();
                        proceso=true;
                    }
                    else
                    {
                        proceso=false;
                    }

                }
                else
                {
                    proceso=false;
                    cout <<"Se ingreso un valor inválido"<< endl;
                }

            }

            if(proceso)
            {

                cout <<"Ingrese la fecha de registro. La fecha debe apegarse al siguiente formato: dd/mm/yyyy"<<endl;
                getline(std::cin,fecha);
                proceso=esCadenaValida(fecha)?true:false;
                if(proceso)
                {
                    proceso=ValidarSiEsFecha(fecha);
                    if(proceso)
                    {
                        cout <<"Ingrese la identificación del cliente que recibe el paquete"<<endl;
                        getline(std::cin,receptor);
                        proceso=esCadenaValida(receptor)?true:false;
                        receptor=quitarEspaciosEnBlanco(receptor);
                        proceso=busquedaCliente(clientes,receptor);

                        if(!proceso)
                        {
                            cin.sync();
                            string opc;
                            cout <<"El cliente ingresado no ha sido previamente registrado"
                                 <<".Desea registrarlo ahora? S/N"<<endl;
                            getline(cin,opc);
                            if(esCadenaValida(opc))
                            {
                                if(opc=="s"||opc=="S")
                                {
                                    ingresoCliente();
                                    proceso=true;
                                }
                                else
                                {
                                    proceso=false;
                                }

                            }
                            else
                            {
                                proceso=false;
                                cout <<"Se ingreso un valor inválido"<< endl;
                            }

                        }

                        if(proceso)
                        {
                            cout <<"Ingrese el  peso del paquete en kilogramos por favor.El peso límite son 1000 kilos"<<endl;
                            getline(std::cin,peso);
                            proceso=esCadenaValida(peso)?true:false;

                            if(proceso)
                            {
                                bool proceso=ValidarSiEsFloat(peso);

                                if(proceso)
                                {
                                    string spaceString=cargarEspacio();

                                    float espacio=spaceString.empty()?0:std::stof(spaceString);

                                    if(espacio<global.espacioMaximo)
                                    {
                                        pesoFloat=std::stof(peso);
                                        if(pesoFloat<=1000)
                                        {
                                            if((pesoFloat+espacio)<=global.espacioMaximo)
                                            {
                                                float nuevoEspacio=(pesoFloat+espacio);
                                                grabarEspacio(nuevoEspacio);

                                                if(pesoFloat<1)
                                                {
                                                    montoFloat=50;
                                                }
                                                else
                                                {
                                                    montoFloat=100*pesoFloat;
                                                }

                                                vector<Paquete> paquetes=cargarPaquetes();

                                                int autoincremento=0;
                                                int ultimo;

                                                ultimo=paquetes.empty()?0:stoll(paquetes.at(paquetes.size()-1).GetNumeroEnvio());



                                                autoincremento=ultimo+1;
                                                if(autoincremento<1)
                                                {
                                                    autoincremento=1;
                                                }
                                                numero=to_string(autoincremento);
                                                paquete.SetNumeroEnvio(numero);
                                                paquete.SetClienteEmisor(emisor);
                                                paquete.SetClienteReceptor(receptor);
                                                paquete.SetFechaRegistro(fecha);
                                                paquete.SetPeso(to_string(pesoFloat));
                                                paquete.SetMonto(to_string(montoFloat));


                                                paquetes.push_back(paquete);
                                                bool registrado=grabarPaquetes(paquetes);
                                                vector<int> losenviados= cargarEnviados();
                                                losenviados.push_back(autoincremento);
                                                grabarEnviados(losenviados);
                                                if(registrado)
                                                {
                                                    cout<<"El paquete "<<paquete.GetNumeroEnvio() <<" ha sido registrado satisfactoriamente."<<endl;

                                                }
                                                else
                                                {
                                                    cout<<"El paquete "<<paquete.GetNumeroEnvio() <<" no pudo ser registrado debido a un problema desconocido."<<endl;
                                                }
                                            }
                                            else
                                            {
                                                cout<<"No hay espacio para transportar ese peso"<<endl;
                                                proceso=false;
                                            }

                                        }
                                        else
                                        {
                                            cout << "El peso ingresado es inválido"<<endl;
                                            proceso=false;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Ya no hay espacio para transportar."<<endl;
                                        proceso=false;
                                    }
                                }
                                else
                                {
                                    proceso=false;
                                    cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
                                }

                            }
                            else
                            {
                                proceso=false;
                                cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
                            }

                        }
                        else
                        {
                            proceso=false;
                            cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
                        }
                    }
                    else
                    {
                        proceso=false;
                        cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
                    }
                }
                else
                {
                    proceso=false;
                    cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
                }


            }
            else
            {
                proceso=false;
                cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
            }


        }
        else
        {
            proceso=false;
            cout << "Lo sentimos, se ingresaron datos incorrectos.Por favor revise los datos e intente de nuevo"<<endl;
        }



    }
    catch (const std::out_of_range& oor)
    {
        std::cerr <<  oor.what() << '\n';
    }


}
//************************************MANTENIMIENTO PAQUETES*************************************


//************************************UTILITARIOS*************************************
//Método para validar si una cadena es un float
bool ValidarSiEsFloat(string cadena)
{
    bool EsNumero=true;
    try
    {
        float numero=std::stof(cadena);

    }
    catch(const std::invalid_argument &no_es_numero)
    {
        EsNumero=false;
    }

    return EsNumero;
}
//Método para validar que una cédula sea válida
bool ValidarSiEsCedula(string cadena)
{
    bool EsNumero=true;
    try
    {
        if(cadena.size()<11&&cadena.size()>8)
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
//Verifica que una cadena sea un  número entero
bool ValidarSiEsEntero(string cadena)
{
    bool EsNumero=true;
    int conteo=0;
    for(int i=0; i<cadena.size()-1; i++)
    {
        if(isdigit(cadena[i]))
        {
            conteo++;

        }
    }

    if(conteo!=(cadena.size()-1))
    {
        EsNumero=false;
    }

    return EsNumero;
}
//Verifica que una cadena no tenga espacios en blanco y no sea una cadena vacía
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
//Verifica que una cadena sea una fecha con el formato correcto (dd/mm/yyyy)
bool ValidarSiEsFecha(string cadena)
{
    bool proceso=false;
    std::tm tm;

    if (stringstream(cadena) >> std::get_time(&tm, "%d/%m/%Y"))
    {
        proceso=true;
    }
    else
    {
        proceso=false;
    }
    return proceso;
}
//Quita los espacios en blanco de una cadena
string quitarEspaciosEnBlanco(string cadena)
{
    std::remove_if(cadena.begin(), cadena.end(), ::isspace);
    return cadena;
}
//Verifica que sea un estado válido para los choferes
bool ValidarSiEsEstado(string cadena)
{
    bool proceso=true;

    if(cadena.size()>0&&cadena.size()<2)
    {
        proceso=ValidarSiEsEntero(cadena);

        if(proceso)
        {
            if(cadena=="1"||cadena=="2")
            {
                proceso=true;
            }
            else
            {
                proceso=false;
            }
        }

    }
    else
    {
        proceso=false;
    }



    return proceso;
}
//Verifica que una cadena sea un tipo de licencia permitido
bool ValidarSiEsLicencia(string cadena)
{
    bool proceso=true;

    if(cadena.size()>0&&cadena.size()<3)
    {
        if(cadena=="b2"||cadena=="B2"||cadena=="e2"||cadena=="E2")
        {
            proceso=true;
        }
        else
        {
            proceso=false;
        }
    }
    else
    {
        proceso=false;
    }

    return proceso;
}
//Verifica que un archivo ya tiene datos para no borrarlo o también para crearlo si no existe
void inicializarArchivos()
{
    globales global;

    global.lectura.open(global.archivoClientes,ios::in);
    if(global.lectura.fail())
    {
        global.escritura.open(global.archivoClientes,ios::out);
        if(global.escritura.fail())
        {
            cout <<"No se pudo crear el archivo de clientes";
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

    global.lectura.open(global.archivoEnviados,ios::in);
    if(global.lectura.fail())
    {
        global.escritura.open(global.archivoEnviados,ios::out);
        if(global.escritura.fail())
        {
            cout <<"No se pudo crear el archivo de enviados";
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
    global.lectura.open(global.archivoEspacio,ios::in);
    if(global.lectura.fail())
    {
        global.escritura.open(global.archivoEspacio,ios::out);
        if(global.escritura.fail())
        {
            cout <<"No se pudo crear el archivo de espacio";
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
            cout <<"No se pudo crear el archivo de choferes";
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


    global.lectura.open(global.archivoPaquetes,ios::in);
    if(global.lectura.fail())
    {
        global.escritura.open(global.archivoPaquetes,ios::out);
        if(global.escritura.fail())
        {
            cout <<"No se pudo crear el archivo de paquetes";
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


//************************************REPORTES*************************************
//Reporte de paquetes por vehículo
void reportePaquetesXVehiculo()
{
    vector<Paquetes_Vehiculos> pes=cargarCierre();

    if(pes.size()>0)
    {
        cout <<"-----------------Reporte de paquetes por vehículo---------------"<<endl;
        for(Paquetes_Vehiculos pv:pes)
        {
            cout <<"Vehículo: "<<pv.GetVehiculo()<<endl;
            cout <<"Chofer: "<<pv.GetChofer()<<endl;
            cout <<"Paquete: "<<pv.GetEnvio()<<endl;
            cout <<"------------------------------------------------------------"<<endl;
        }
    }
    else
    {
        cout <<"No hay datos para realizar el reporte"<<endl;
    }

}
//Reporte de totales
void reporteTotales()
{
    vector<Paquetes_Vehiculos> pes=cargarCierre();

    vector<Paquete> paquetes=cargarPaquetes();
    if(pes.size()>0)
    {
        cout <<"-----------------Reporte de Totales---------------"<<endl;
        float peso=0;
        float monto=0;
        for(Paquetes_Vehiculos pv:pes)
        {
            Paquete p=RetornarbusquedaPaquete(paquetes,pv.GetEnvio());
            peso=peso+stof(p.GetPeso());
            monto=monto+stof(p.GetMonto());

        }

        cout <<"Peso total enviado de todos los paquetes: "<<peso<<"--------"<<endl;
        cout <<"Ganancia total  de todos los paquetes  : "<<monto<<"--------"<<endl;
        cout <<"------------------------------------------------------------"<<endl;
    }
    else
    {
        cout <<"No hay datos para realizar el reporte"<<endl;
    }
}
//************************************REPORTES*************************************

//************************************PROCESAMIENTO DE DATOS*************************************
//Realiza un acción de acuerdo a la opción elegida por el usuario
void ProcesamientoDeDatosSubmenuReportes(int eleccion)
{
    cin.sync();
    switch (eleccion)
    {
    case 1:
    {
        reportePaquetesXVehiculo();
    }
    break;
    case 2:
    {
        reporteTotales();
    }
    break;
    case 3:
        // no se hace nada solo vuelve al menu principal
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
//Realiza un acción de acuerdo a la opción elegida por el usuario
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
            cout << "Desea ingresar más clientes? S/N" << endl;
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
    case 6:
        // no se hace nada solo vuelve al menu principal
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
//Realiza un acción de acuerdo a la opción elegida por el usuario
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
            ingresoPaquete();
            cout << "Desea ingresar más paquetes? S/N" << endl;
            cin >> seguir;

        }
        while(seguir=="S" || seguir=="s");
    }

    break;
    case 2:
        modificarPaquete();
        break;
    case 3:
        listarPaquetes();
        break;
    case 4:
        buscarPaquete();
        break;
    case 5:
        eliminarPaquete();
        break;
    case 6:
        // no se hace nada solo vuelve al menu principal
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
//Realiza un acción de acuerdo a la opción elegida por el usuario
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
            cout << "Desea ingresar más choferes? S/N" << endl;
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
    case 6:
        // no se hace nada solo vuelve al menu principal
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
//Muestra un menú
int MostrarMenu()
{
    cin.sync();
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Mantenimiento de choferes" << endl;
    cout << "[2] Mantenimiento de clientes" << endl;
    cout << "[3] Envío de paquetes" << endl;
    cout << "[4] Cierre de envíos" << endl;
    cout << "[5] Reportes" << endl;
    cout << "[6] Salir" << endl;
    cin >> option;


    if(ValidarSiEsEntero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}
//Muestra un menú
int MostrarMenuReportes()
{
    cin.sync();
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Reporte de paquetes por vehículo" << endl;
    cout << "[2] Reporte de totales" << endl;
    cout << "[3] Volver al menú principal" << endl;
    cin >> option;

    if(ValidarSiEsEntero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}
//Muestra un menú
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
    cout << "[6] Volver al menú principal" << endl;
    cin >> option;

    if(ValidarSiEsEntero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}
//Muestra un menú
int MostrarMenuChoferes()
{
    cin.sync();
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Ingresar un chofer" << endl;
    cout << "[2] Modificar un chofer" << endl;
    cout << "[3] Listar choferes" << endl;
    cout << "[4] Buscar chofer" << endl;
    cout << "[5] Eliminar un chofer" << endl;
    cout << "[6] Volver al menú principal" << endl;
    cin >> option;

    if(ValidarSiEsEntero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}
//Muestra un menú
int MostrarMenuPaquetes()
{
    cin.sync();
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Ingresar un paquete" << endl;
    cout << "[2] Modificar un paquete" << endl;
    cout << "[3] Listar paquetes" << endl;
    cout << "[4] Buscar paquete" << endl;
    cout << "[5] Eliminar un paquete" << endl;
    cout << "[6] Volver al menú principal" << endl;
    cin >> option;

    if(ValidarSiEsEntero(option))
    {
        intOpcion=stoll(option);
    }
    return intOpcion;
}
//Escucha las opciones elegidas por el usuario en el menú correspondiente
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
//Escucha las opciones elegidas por el usuario en el menú correspondiente
void EscucharOpcionesReportes()
{
    int solicitud=-1;
    do
    {
        solicitud=MostrarMenuReportes();
        ProcesamientoDeDatosSubmenuReportes(solicitud);
    }
    while(solicitud != 3);
}
//Escucha las opciones elegidas por el usuario en el menú correspondiente
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
//Escucha las opciones elegidas por el usuario en el menú correspondiente
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
//Realiza una acción de acuerdo a una opción elegida
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
        EscucharOpcionesPaquetes();
        break;
    case 4:
    {
        cin.sync();
        string realizar;
        cout <<"Desea realizar el cierre de envíos? S/N"<<endl;
        getline(cin,realizar);
        if(esCadenaValida(realizar))
        {
            if(realizar=="S"||realizar=="s")
            {
                vector<int> enviados=cargarEnviados();
                if(enviados.size()>0)
                {
                    asignacionPaquetesXVehiculo(enviados);
                }
                else
                {
                    cout <<"No hay paquetes por enviar"<<endl;
                }
            }
        }
        else
        {
            cout <<"Se ingreso un valor inválido"<<endl;
        }

    }
    break;
    case 5:
        EscucharOpcionesReportes();
        break;
    case 6:
        exit(1);
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
//Escucha las opciones elegidas por el usuario
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
