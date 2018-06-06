#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

using namespace std;

int open_socket();
void bind_to_port(int,int);

int main(){
	const int PORT = 7200;

	char* advice[] = {"Deberias ir al gym.\n", "Deberias programar mas.\n", "A lo mejor un corte de pelo...\n", "Sal que te de el aire!\n", "No seas un lammer!"};

	int listener = open_socket();				//Le da el valor que devolvi� s en la funcion open_socket

	if(listener == -1){							//Comprobacion de error en el listener
		cout << "Error en el listener \n";
		return 0;
	}

	bind_to_port(listener, PORT);				//Enlazamos al puerto

	if(listen (listener, 10) == -1){				//Limitamos el numero de clientes a 10.
		cout << "No se pueden conectar mas clientes.\n";
		return 0;
	}

	cout << "Enlazado al puerto.\n";			//Si no ha habido ningun error ni se ha sobrepasado el numero de clientes.

	while(1){
		struct sockaddr_storage cliente; 		//Estructura que nos permite guardar toda la info del cliente que se esta conectando.
		unsigned int addres_size = sizeof(cliente);//Necesitamos conocer el tama�o del cliente.
		cout << "Esperando al cliente.\n";
		int connect = accept(listener, (struct sockaddr*)&cliente, &addres_size);//Estamos a la espera de que se conecte un cliente para aceptar, la funcion accept necesita (el listener que lo coge del main, la estructura con la info del cliente, y el tama�o de esta.)
		if(connect == -1){						//Comprobaci�n de errores.
			cout << "No se puede conectar al segundo socket.\n";
		}

		cout << "Atendiendo al cliente.\n"; 	//Si no ha habido errores.

		char* msg = advice[rand() %5];			//Aleatoriza el mensaje
		send(connect, msg, strlen(msg), 0);		//Envia el mensaje (usa la funcion connect, el mensaje,la longitud de este, y deja el protocolo a eleccion del pc.)
		msg = NULL;
		close(connect);							//Cierra la conexion.
	}
}

int open_socket(){
	int s = socket(PF_INET, SOCK_STREAM,0);		//NOSE, tipo stream, deja el protocolo a eleccion del pc
	if(s == -1){								//Comprobacion de error
		cout << "Error al abrir el socket\n";
	return s;
	}
}

void bind_to_port(int socket, int port){		 //Funci�n que toma los datos de listener y el puerto en la linea 17.
	struct sockaddr_in name;					 //Estructura de nombre "name".
		name.sin_family = PF_INET;				//Para que sepa de que tipo de dominio se trata (?).
		name.sin_port = ((in_port_t)htons(port));//Aqui toma el puerto que declaramos en la linea 9 y se lo hemos pasado en la 15.
		name.sin_addr.s_addr = htonl(INADDR_ANY);

	int reuse = 1;
	if(setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int)) == -1){ //Nos sirve para reutilizar el socket una vez fianlizada la conexion.
		cout << "No es posible reutilizar el socket\n";
	}

	int c = bind(socket, (struct sockaddr*)&name, sizeof(name));//Le pasamos el socket que es el listener que le pasamos antes a la funcion como parametro desde el main, pasamos la direccion de memoria del struct, y el tama�o del struct.
	if(c == -1){												//Comprobacion de errores al enalzar al puerto.
		cout << "No se puede enlazar al puerto, la direccion ya esta en uso.";
	}
}
