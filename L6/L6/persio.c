#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char persio[100];
	int cont=0;
	printf("Vc acha que persio é gay ?\n");
	scanf(" %[^\n]", persio);
	while(strcmp(persio, "sim")!=0){
		if(cont>1){
			printf("PORRA TU EH IMBECIL EH ?\n");
			printf("EH PERSIO CARALHO\n\n\n\n\n");
		}
		else{
			printf("VC acha que PERSIO é gay ? VEJA BEM, EH PERSIO\n");
			printf("CUIDADO, PENSE DIREITINHO\n\n\n\n\n");
		}
		scanf(" %[^\n]", persio);
		cont++;
	}
	printf("Finalmente!!!! OLHA PRA TRAS, ELE DEVE TA ATRAS DE TU!\n\n\n\n");
}