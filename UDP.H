// converte un indirizzo IP nella notazione ASCII decimale usuale (esempio:
// "192.168.1.1") in un valore numerico a 32 bit
unsigned long IP_to_bin(char ip_address[]);

// inizializza il socket impostando il numero di porta locale
// restituisce -1 in caso di errore, 0 in caso di successo
int UDP_init(unsigned short port_number);

// trasmette al socket identificato dall’indirizzo IP e dal numero di porta UDP un
// numero byte di dati contenuti nel buffer data
// restituisce -1 in caso di errore, altrimenti il numero di byte trasmessi
int UDP_send(unsigned long ip_address, unsigned short port_number,
             unsigned char data[], int byte);

// riceve un datagram nel buffer data di dimensione size
// restituisce -1 in caso di errore o di dati non disponibili,
// il numero di byte ricevuti in caso di successo
// indirizzo IP e numero di porta UDP del mittente sono restituiti come parametri
int UDP_receive(unsigned long *ip_address, unsigned short *port_number,
                unsigned char data[], int size);

// chiude il socket
void UDP_close(void);
