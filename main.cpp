#include <iostream>
#include <stdexcept>
#include <string>
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

using namespace std;

//prototipos
bool busquedaCliente(string buscado);
bool ValidarSiEsNumero(string cadena);
void ProcesamientoDeDatos(int eleccion);
bool esCadenaValida(string dato);
Cliente solicitarDatosCliente();
string FechaDelSistema();
int MostrarMenuClientes();
void lecturaClientes();
void EscucharOpcionesChoferes();
void EscucharOpcionesClientes();
void EscucharOpciones();
void ProcesamientoDeDatosSubmenuChoferes(int eleccion);
void ProcesamientoDeDatosSubmenuClientes(int eleccion);
int MostrarMenu();
bool ingresoCliente(Cliente c);
bool busquedaCliente(string buscado);
Cliente RetornarbusquedaCliente(string buscado);
void lecturaClientes();
//Para no utilizar variables globales, se me ocurrió utilizar un struct
struct globales
{
    ofstream escritura;
    ifstream lectura;
    string archivoClientes="cliente.txt";
    string archivoChoferes="chofer.txt";
};


bool ValidarSiEsNumero(string cadena)
{
    bool EsNumero=true;
    try
    {
        int entero=stoi(cadena);

    }
    catch(const std::invalid_argument &no_es_numero)
    {

        EsNumero=false;
    }

    return EsNumero;
}

//verifica que una cadena no sea un dato nulo o espacios en blanco
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
        //se hace un conteo de los espacios en blanco
        for(int i=0; i<dato.size(); i++)
        {
            if(isblank(dato[i]))
            {
                conteo++;
            }
        }
        // si el conteo es igual a el total de la cadena es porque solo son espacios en blanco
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
//Solicita los datos de un cliente y los valida
Cliente solicitarDatosCliente()
{
    Cliente cliente=Cliente();
    string id;
    string email;
    string nombre;
    string apellidos;
    string direccion;
    string telefono;
    cout <<"Ingrese la identificación del cliente,este debe ser un dato numérico"<<endl;
    getline(std::cin,id);
    bool proceso=esCadenaValida(id)?true:false;
    proceso=ValidarSiEsNumero(id)?true:false;
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

                cout <<"Ingrese la dirección del cliente"<<endl;
                getline(std::cin,direccion);
                proceso=esCadenaValida(direccion)?true:false;
                if(proceso)
                {

                    cout <<"Ingrese el  teléfono del cliente"<<endl;
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
        cliente.SetIdentificacion(id);
        cliente.SetApellidos(apellidos);
        cliente.SetDireccion(direccion);
        cliente.SetEmail(email);
        cliente.SetNombre(nombre);
        cliente.SetTelefono(telefono);

        bool busqueda=busquedaCliente(cliente.GetIdentificacion());

        if(busqueda)
        {
            cout << "Lo sentimos. No se puede registrar el cliente debido a que ya ha sido registrado anteriormente"<<endl;
        }
        else
        {
            bool registrado=ingresoCliente(cliente);
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
    return cliente;

}


//procesa los datos según la opción elegida por el usuario en el mantenimiento de clientes
void ProcesamientoDeDatosSubmenuClientes(int eleccion)
{
    cin.sync();
    switch (eleccion)
    {
    case 1:
    {
        cout << "Ingreso\n\n\n"<<endl;
        Cliente cliente=solicitarDatosCliente();
    }
    break;
    case 2:
        cout << "Modificar\n\n\n";
        break;
    case 3:
        cout << "Listar\n\n\n";
        lecturaClientes();
        break;
    case 4:
    {
        cout << "Buscar\n\n\n";
        string id;
        cout << "Ingrese el número de identificación del cliente que desea buscar"<<endl;
        getline(cin,id);
        if(esCadenaValida(id)&&ValidarSiEsNumero(id))
        {
            bool busqueda=busquedaCliente(id);
            if(busqueda)
            {
                Cliente c=RetornarbusquedaCliente(id);
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
            cout << "El dato ingresado no es válido"<<endl;
        }

    }

    break;
    case 5:
        cout << "Eliminar\n\n\n";
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}
//procesa los datos según la opción elegida por el usuario en el mantenimiento de clientes
void ProcesamientoDeDatosSubmenuChoferes(int eleccion)
{
    cin.sync();
    switch (eleccion)
    {
    case 1:
        cout << "Ingreso\n\n\n";
        break;
    case 2:
        cout << "Modificar\n\n\n";
        break;
    case 3:
        cout << "Listar\n\n\n";
        break;
    case 4:
        cout << "Buscar\n\n\n";
        break;
    case 5:
        cout << "Eliminar\n\n\n";
        break;
    default:
        cout << "Solicitud desconocida\n\n\n";
        break;
    }


}


//Muestra el menú de opciones en pantalla
int MostrarMenu()
{
    string option;
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Mantenimiento de choferes" << endl;
    cout << "[2] Mantenimiento de clientes" << endl;
    cout << "[3] Envío de paquetes" << endl;
    cout << "[4] Cierre de envios" << endl;
    cout << "[5] Reportes" << endl;
    cout << "[6] Salir" << endl;
    cin >> option;

    if(ValidarSiEsNumero(option))
    {
        intOpcion=stoi(option);
    }
    return intOpcion;
}

//Muestra el menú de opciones del mantenimiento de clientes en pantalla
int MostrarMenuClientes()
{
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
    if(ValidarSiEsNumero(option))
    {
        intOpcion=stoi(option);
    }
    return intOpcion;
}
//Muestra el menú de opciones del mantenimiento de clientes en pantalla
int MostrarMenuChoferes()
{
    int intOpcion = 0;
    cout << "////////////////////////////////////////////" << endl;
    cout << "---------Pedro paquetes--------" << endl;
    cout << "[1] Ingresar un chofer" << endl;
    cout << "[2] Modificar un chofer" << endl;
    cout << "[3] Listar choferes" << endl;
    cout << "[4] Buscar chofer" << endl;
    cout << "[5] Eliminar un chofer" << endl;
    cout << "[6] Volver al menú principal" << endl;
    cin >> intOpcion;


    return intOpcion;
}

void lecturaClientes()
{
    globales global;

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
        cout << "\nIdentificación : " << id
             <<"\nNombre : "<< nombre
             <<"\nApellidos : "<<apes
             <<"\nDirección : "<<direccion
             <<"\nEmail : "<<email
             <<"\nTeléfono : "<< tel<< endl;
    }
    global.lectura.close();
}
bool busquedaCliente(string buscado)
{
    globales global;
    global.lectura.open(global.archivoClientes,ios::in);
    bool resultado=false;
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
    while(global.lectura >> id >> nombre >> apes >> direccion >> email >>tel )
    {
        if(id==buscado)
        {
            resultado=true;
            break;
        }
    }
    global.lectura.close();

    return resultado;
}

Cliente RetornarbusquedaCliente(string buscado)
{
    globales global;
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
    while(global.lectura >> id >> nombre >> apes >> direccion>> email >>tel )
    {
        if(id==buscado)
        {
            cliente.SetIdentificacion(id);
            cliente.SetNombre(nombre);
            cliente.SetApellidos(apes);
            cliente.SetDireccion(direccion);
            cliente.SetEmail(email);
            cliente.SetTelefono(tel);
            break;
        }
    }
    global.lectura.close();

    return cliente;
}

bool ingresoCliente(Cliente c)
{
    bool resultado=false;

    globales global;

    global.escritura.open(global.archivoClientes,ios::app);


    if(global.escritura.fail())
    {
        cout <<"no se pudo crear el archivo";
        exit(1);
    }
    global.escritura
            << c.GetIdentificacion()<<' '
            <<c.GetNombre()<<' '
            <<c.GetApellidos()<<' '
            <<c.GetDireccion()<< ' '
            <<c.GetEmail()<<' '
            <<c.GetTelefono()<<' ';

    global.escritura.flush();
    global.escritura.close();
    resultado=true;


    return resultado;
}

//Obtiene la opción elegida por el usuario en el menú de clientes
void EscucharOpcionesClientes()
{
    int solicitud=-1;
    //realizar mientras lo que ingresa el usuario es  un número o y que el número sea diferente a 4
    do
    {
        solicitud=MostrarMenuClientes();
        ProcesamientoDeDatosSubmenuClientes(solicitud);
    }
    while(solicitud != 6);
}

//Obtiene la opción elegida por el usuario en el menú de clientes
void EscucharOpcionesChoferes()
{
    int solicitud=-1;
    //realizar mientras lo que ingresa el usuario es  un número o y que el número sea diferente a 4
    do
    {
        solicitud=MostrarMenuChoferes();
        ProcesamientoDeDatosSubmenuChoferes(solicitud);
    }
    while(solicitud != 6);
}

//procesa los datos según la opción elegida por el usuario
void ProcesamientoDeDatos(int eleccion)
{

    switch (eleccion)
    {
    case 1:
        cout << "Mantenimiento de choferes\n\n\n";
        EscucharOpcionesChoferes();
        break;
    case 2:
        cout << "Mantenimiento de clientes\n\n\n";
        EscucharOpcionesClientes();
        break;
    case 3:
        cout << "Envío de paquetes\n\n\n";
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
//Obtiene la opción elegida por el usuario
void EscucharOpciones()
{
    int solicitud=-1;
    //realizar mientras lo que ingresa el usuario es  un número o y que el número sea diferente a 4
    do
    {
        solicitud=MostrarMenu();
        ProcesamientoDeDatos(solicitud);
    }
    while(solicitud != 6);
}
//obtiene la  fecha del  sistema.
//Este tipo auto se me hace  muy  similar a  la palabra  reservada "var" en C#, donde
//el compilador decide el mejor   tipo para la variable .
string FechaDelSistema()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y");
    string str = oss.str();

    return str;
}

//trata de abrir el archivo en modo lectura y si no lo encuentra lo intenta crear
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
    }else{
        global.lectura.close();
    }

}
int main()
{
    setlocale(LC_ALL, "");//para los acentos

    inicializarArchivos();
    EscucharOpciones();
    return 0;

}
