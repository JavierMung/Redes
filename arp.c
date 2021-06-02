

void estructuraARPsol(unsigned char*);

unsigned char tramaARPsol[60] = {0xff,0xff,0xff,0xff,0xff,0xff,0x0A,0x00,0x27,0x00,0x00,0x02,
	0x08,0x06,0x00,0x01,0x08,0x00,0x06,0x04,0x00,0x01,0x0A,0x00,0x27,0x00,0x00,0x02,0xc0,0xa8,0x00,0x01,
	0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xa8,0x00,0x02,'F','J','M','G'};


int main(int argc, int ** argv){

	int packet_socket, indice;
	packet_socket=socket(AF_SOCKET,SOCK_RAW,htons(ETH_P_ALL));
	if(packet_socket==-1){
		perror("nError al abrir el socket\n");
		exit(0);
	}else{
		printf("\nExitoal abrir el socket\n");
		indice=obtenerDatos(packet_socket);
		obtenerIPdestino();
		estructuraARPsol(tramaARPsol);
		printf("\nLa trama que se enviara es: \n");
		imprimirTrama(tramaARPsol,60);
		enviaTrama(packet_socket,indice,tramaARPsol);

	}

	close(packet_socket);
	return 1;
}

void estructuraARPsol(unsigned char * trama){
	memcpy(trama+6,MACorigen,6);
	memcpy(trama+22,MACorigen,4);
	memcpy(trama+28,IPorigen,4);
	memset(trama+32,0x00,6);
	memcpy(trama+38,IPdestino,4);
}

void enviaTrama(int ds, int index, unsigned char * paq){
	int tam;
	struct sockaddr_ll capaEnlace;
	memset(&capaEnlace,0x00,sizeof(capaEnlace));
	capaEnlace.sll_family = AF_PACKET;
	capaEnlace.sll_protocol = htons(ETH_P_ALL);
	capaEnlace.sll_ifindex = index;
	tam = sento(ds,paq,60,0,(struct sockaddr*)&capaEnlace,sizeof(capaEnlace));
	if(tam==-1){
		perror("\nError al enviar la trama\n");
	}else{
		printf("nExito al enviar la trama\n");
		
	}
}