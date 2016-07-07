#include "Server.h"



int build_server(char* ip, int port){
	
	
  
    struct sockaddr_in dest; /* socket info about the machine connecting to us */
    struct sockaddr_in serv; /* socket info about our server */
    int mysocket;            /* socket used to listen for incoming connections */
    socklen_t socksize = sizeof(struct sockaddr_in);

    memset(&serv, 0, sizeof(serv));           /* zero the struct before filling the fields */
    serv.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
    serv.sin_addr.s_addr = inet_addr(ip); /* set our address to any interface */
    serv.sin_port = htons(port);           /* set the server port number */    

    mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
    /* bind serv information to mysocket */
    bind_socket(mysocket, serv);

    /* start listening, allowing a queue of up to 1 pending connection */
    listen(mysocket, 1);
    int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  
    while(consocket)
    {
        send_to(consocket, "Hello World !\n");
        infinity_receive(consocket);
        close(consocket);
        consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
    }

    close(mysocket);
    return EXIT_SUCCESS;
}

void infinity_receive(int socket){
	char receive_msg[20];
    int n = recv(socket , receive_msg , 20 , 0);
    printf("client msg: %s", receive_msg);
}

void send_to(int socket, char* msg){	
	//printf("Incoming connection from %s - sending welcome\n", inet_ntoa(dest.sin_addr));
    send(socket, msg, strlen(msg), 0);
}

void bind_socket(int socket, struct sockaddr_in server){
	int r = bind(socket, (struct sockaddr *)&server, sizeof(struct sockaddr));
	if(r != 0){
		printf("Error Bind socket\n");
		exit(1);
	}
	printf("Server Up\n");
}



// void *connection_handler(void *socket_desc)
// {
//     //Get the socket descriptor
//     int sock = *(int*)socket_desc;
//     int read_size;
//     char *message , client_message[2000];
     
//     //exemple send message
//     //write(sock , message , strlen(message));
     
//     //Receive a message from client
//     while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
//     {
        
//         printf("%s\n", client_message );
//         //Send the message back to client
//         //write(sock , client_message , strlen(client_message));
//         if(strcmp("BONJ", client_message) != 0){
//             message = "WHO";            
//         } else if(strcmp("pass", client_message) != 0){
            
//         }

//         write(sock , message , strlen(message));
//     }
     
//     if(read_size == 0)
//     {
//         puts("Client disconnected");
//         fflush(stdout);
//     }
//     else if(read_size == -1)
//     {
//         perror("recv failed");
//     }
         
//     //Free the socket pointer
//     free(socket_desc);
     
//     return 0;
// }


// int* new_client(int new_socket){
// 	pthread_t sniffer_thread;

// 	int *new_sock = malloc(4);
//     *new_sock = new_socket;

// 	if( pthread_create( &sniffer_thread , NULL ,  connection_handler , &new_sock) < 0)
// 	{
// 	    perror("could not create thread");
// 	    return 1;
// 	}
	 
// 	//Now join the thread , so that we dont terminate before the thread
// 	//pthread_join( sniffer_thread , NULL);
// 	puts("Handler assigned");
// 	return *new_sock;
// }




// int* instanciate_socket(){
// 	int socket_open;
// 	/* Ouverture d'un socket afin de recevoir des demandes de connection */
// 	int sock_des = (socket_open = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
// 	if( sock_des == -1)
// 	{
// 		printf("Error instanciate socket\n");
// 	}
// 	return *sock_des;
// }



// void* connection_handler(void *socket_desc)
// {
//     //Get the socket descriptor
//     int sock = *(int*)socket_desc;
//     int read_size;
//     char *message , client_message[2000];
     
//     //exemple send message
//     //write(sock , message , strlen(message));
     
//     //Receive a message from client
//     while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
//     {
        
//         printf("%s\n", client_message );
//         //Send the message back to client
//         //write(sock , client_message , strlen(client_message));
//         if(strcmp("BONJ", client_message) != 0){
//             message = "WHO";            
//         } else if(strcmp("pass", client_message) != 0){
            
//         }

//         write(sock , message , strlen(message));
//     }
     
//     if(read_size == 0)
//     {
//         puts("Client disconnected");
//         fflush(stdout);
//     }
//     else if(read_size == -1)
//     {
//         perror("recv failed");
//     }
         
//     //Free the socket pointer
//     free(socket_desc);
     
//     return 0;
// }







// int* standby_accept_connection(int socket_desc){
// 	server_struct *client;
// 	int new_socket;
// 	listen(socket_desc , 3);
// 	int c = sizeof(client);
// 	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
//     {
//     	new_client(new_socket);
//     }
//     if (new_socket<0)
//     {
//         perror("accept failed");
//         return 1;
//     }
//     return *new_socket;
// }


// void send_message(int socket, char* message){
// 	write(socket , message , strlen(message));
// }