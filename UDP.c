#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "UDP.H"

int socket_id; // identificatore del socket

unsigned long IP_to_bin(char ip_address[])
{
 unsigned long bin_address = inet_network(ip_address);
 
 return bin_address;
}

int UDP_init(unsigned short port_number)
{
 struct sockaddr_in add; // struttura per indirizzo

 // apertura socket UDP non bloccante
 if ((socket_id = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK,
                         IPPROTO_UDP)) < 0)
   return -1;
 // costruzione struttura indirizzo
 memset(&add, 0, sizeof(add)); // azzeramento struttura
 add.sin_family = AF_INET; // dominio indirizzi IP
 add.sin_addr.s_addr = 0; // indirizzo IP locale
 add.sin_port = htons(port_number); // numero di porta assegnato
 // associazione socket a numero di porta
 if (bind(socket_id, (struct sockaddr *)&add, sizeof(add)) < 0)
   {
    close(socket_id);
    return -1;
   } 
 return 0;    
}

int UDP_send(unsigned long ip_address, unsigned short port_number,
             unsigned char data[], int byte)
{
 struct sockaddr_in add; // struttura per indirizzo di destinazione
 int n;

 // costruzione struttura indirizzo
 memset(&add, 0, sizeof(add)); // azzeramento struttura
 add.sin_family = AF_INET; // dominio indirizzi IP
 add.sin_port = htons(port_number); // numero di porta UDP
 add.sin_addr.s_addr = htonl(ip_address); // indirizzo IP
 
 // trasmissione datagram
 if ((n = sendto(socket_id, (void *)data, byte, 0,
                (struct sockaddr*)&add, sizeof(add))) < 0)
   return -1;
 return n;    
}

int UDP_receive(unsigned long *ip_address, unsigned short *port_number,
                unsigned char data[], int size)
{
 struct sockaddr_in add; // struttura per indirizzo mittente
 size_t dim = sizeof(add);
 int n;
 
 // ricezione datagram (non bloccante)
 if ((n = recvfrom(socket_id, (void *)data, size, 0,
                   (struct sockaddr*)&add, &dim)) <= 0)
   return -1;   
 
 // estrazione indirizzo IP e numero di porta UDP
 *ip_address = (unsigned long)(ntohl(add.sin_addr.s_addr));
 *port_number = (unsigned short)(ntohs(add.sin_port));
 return n; 
}

void UDP_close(void)
{
 // chiusura socket
 close(socket_id);
 return;
}
