#include <unistd.h>
#include <arpa/inet.h>//Inet_addr
#include <iostream>
#include <string.h>//Para strings
#include <stdlib.h>
#include <cerrno>//Para los errores

using namespace std;

int open_socket();

int main(){
    int bufsize;
	  string msg;
	  char *buffer = new char [msg.size() + 1];
    const int port = 7200;
    int listener = open_socket();
    bool salir = false;

    struct sockaddr_in server;
      server.sin_family = PF_INET;
      server.sin_port = ((in_port_t)htons(port));
      server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int conectar = connect(listener,(struct sockaddr*)&server, sizeof(server));
    if (conectar < 0){
      cout << "Error al conectar" << endl;
    }else{
      cout << "Conexion establecida." << endl;
    }
    recv(listener, buffer, bufsize, 0);

    while(1){
      cout << "\nCliente: ";

        getline(cin,msg);//Lo almacena en el string msg.
  		  copy(msg.begin(),msg.end(),buffer);//Copia el contenido del string msg al array char buffer.
  		  bufsize = strlen(buffer);
  		  send(conectar, buffer, bufsize,0);
        delete[] buffer;//Limpia el array buffer.

      cout << "Servidor: ";

        recv(listener, buffer, bufsize, 0);
        cout << buffer << " ";
        delete[] buffer;//Limpia el array buffer.

    }

  close(conectar);
cout << "\nConexion finalizada."<<endl;
}


int open_socket(){
  int socketcliente = socket(PF_INET, SOCK_STREAM,0);
  if(socketcliente == -1){								//Comprobacion de error
		cout << "Error al abrir el socket. " << strerror(errno) << endl;
	}
}
