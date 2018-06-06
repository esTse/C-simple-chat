#include <unistd.h>
#include <arpa/inet.h>//Para internet
#include <iostream>
#include <string.h>//Para strings
#include <stdlib.h>
#include <cerrno>//Para los errores

using namespace std;

int open_socket();
void bind_to_port(int,int);

int main(){
	int bufsize = 1024;
	string msg;
	char *buffer = new char [msg.size() + 1];
	const int PORT = 7200;
	int listener = open_socket();
	bind_to_port(listener, PORT);				//Enlazamos al puerto

	if(listen (listener, 10) == -1){				//Limitamos el numero de clientes a 10.
		cout << "No se pueden conectar mas clientes. "<< strerror(errno) << endl;;
		return 0;
	}

	cout << "Conexion establecida.\n";			//Si no ha habido ningun error ni se ha sobrepasado el numero de clientes.
	struct sockaddr_storage cliente; 		//Estructura que nos permite guardar toda la info del cliente que se esta conectando.
	unsigned int addres_size = sizeof(cliente);//Necesitamos conocer el tama�o del cliente.
	int aceptar = accept(listener, (struct sockaddr*)&cliente, &addres_size);//Estamos a la espera de que se conecte un cliente para aceptar, la funcion accept necesita (el listener que lo coge del main, la estructura con la info del cliente, y el tama�o de esta.)
	send(aceptar, buffer, bufsize,0);

	while(1){
  	cout << "\nServidor: ";

			getline(cin,msg);//Lo almacena en el string msg.
			copy(msg.begin(),msg.end(),buffer);//Copia el contenido del string msg al array char buffer.
			bufsize = strlen(buffer);
			send(aceptar, buffer, bufsize,0);
			delete[] buffer;//Limpia el array buffer.

		cout << "Cliente: ";

			recv(listener, buffer, bufsize, 0);
			cout << buffer << " ";
			delete[] buffer;//Limpia el array buffer.

	}

close(aceptar);
return 0;
}

int open_socket(){
	int socket1 = socket(PF_INET, SOCK_STREAM,0);		//NOSE, tipo stream, deja el protocolo a eleccion del pc
	if(socket1 == -1){								//Comprobacion de error
		cout << "Error al abrir el socket. " << strerror(errno) << endl;
		exit(EXIT_FAILURE);
	}
}

void bind_to_port(int socket, int port){		 //Funci�n que toma los datos de listener y el puerto en la linea 17.
	struct sockaddr_in name;					 //Estructura de nombre "name".
		name.sin_family = PF_INET;				//Para que sepa de que tipo de dominio se trata (?).
		name.sin_port = ((in_port_t)htons(port));//Aqui toma el puerto que declaramos en la linea 9 y se lo hemos pasado en la 15.
		name.sin_addr.s_addr = htonl(INADDR_ANY);

	int enlace = bind(socket, (struct sockaddr*)&name, sizeof(name));//Le pasamos el socket que es el listener que le pasamos antes a la funcion como parametro desde el main, pasamos la direccion de memoria del struct, y el tama�o del struct.
	if(enlace == -1){												//Comprobacion de errores al enalzar al puerto.
		cout << "No se puede enlazar al puerto, la direccion ya esta en uso. "<< strerror(errno) << endl;
		exit(EXIT_FAILURE);
	}
}
