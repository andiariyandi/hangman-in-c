/* file name: 01_SourceCode_14116133_AndiAriyandi_RC.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ADT */
#include "boolean.h"
#include "linkedlist.h"

#define maks 1000 /* konstanta maksimum */

void showHangman(int); /* Menanmpilkan HangMan */

void NamaKategori(int); /* Menampilkan Kategori */

char LokasiFile[maks]; /* Cadangan lokasi file */

FILE *BukaKamusPilihan (int); /* Membuka Kamus */

char *AmbilKata(int ); /* Mengambil kata dengan acakan dari kamus */
void tampilLogo();
void pembukaan();

/* Pengacak Kata */
char MesinAcak(int maks_kata) { 
	srand(time(NULL));
	int Acak = (rand() % (maks_kata ));
	return Acak;
}

/* Program Utama */
int main (){
	pembukaan();
	getchar(); 
	system("cls"); 
// -------------------------------------------------------------------------------------------- 	
	char *nama[maks] = {0};
	int kategori = 1;
	int JumlahKata = 5;
	tampilLogo();
	printf("Selamat datang di Permainan HangMan!\n");
	printf("Nama	: ");
	scanf("%s", &nama);

	printf("Ok %s, Ayo bermain! \n", nama);
	printf("--------------------------------------------\n\n");
	printf(" <Tekan sembarang untuk melanjutkan> ");	
	getchar(); 
	printf(" ");
	getchar();
	system("cls"); 	
// --------------------------------------------------------------------------------------------	
 	int j;
 	address PPagar, PKata, PTebak;
	List LKata, LPagar, LTebak;	
while (kategori<3) {
//Meminta kata dari kamus sesuai kategori
 	char *tebakKata = AmbilKata(kategori); //
// Menghitung panjang kata 
 	int Jmlhchar= strlen(tebakKata);
	int tCekKata = Jmlhchar;	
// Memasukkan kedalam List 		
	CreateEmpty(&LKata);
	CreateEmpty(&LPagar);
	CreateEmpty(&LTebak);
	char pagar = '#';
	for( j = 0; j <= Jmlhchar ; j++) {
		PKata=Alokasi(tebakKata[j]);
		InsertLast(&LKata,PKata);
		// Menutupi kata dengan "#" (name: LPagar)	
		PPagar=Alokasi(pagar);
		InsertLast(&LPagar, PPagar);
	}
 	int kesempatan = 4; // Memberi batasan untuk menebak, looping berhenti jika kesempatan = 0
 	int  cekTebakHuruf = 0; 
 	char tebakHuruf;

 	system("cls");
 	NamaKategori(kategori);
 	printf("\nTebak kata: "); PrintInfo(LPagar); printf(" <%d huruf>\n", Jmlhchar); 
 	printf("Kesempatan menebakan: %d\n" , kesempatan);
 	printf("Sembarang Alphabet (a-z) untuk hint, Numeric (0-9) untuk tebak langsung...  ");
 	scanf("%c", &tebakHuruf);
 	while( (!IsEqual(LKata, LPagar, Jmlhchar)) && (kesempatan > 0) ){
		scanf("%c", &tebakHuruf);
 		tebakHuruf = toupper(tebakHuruf);		
 		if (tebakHuruf != '\n') {
 			if (isalpha(tebakHuruf)) {	
				cekTebakHuruf = CekKata(&LKata, &LPagar, tebakHuruf);
				kesempatan--;
 				if (cekTebakHuruf == 0) {		
  					showHangman(kesempatan);
  					printf("\n\n<!> Salah, huruf %c Tidak ada !\n", tebakHuruf);
				}else {
 					cekTebakHuruf = 0;
 					showHangman(kesempatan);
  					printf("\n\n Benar, huruf %c  Ada !\n", tebakHuruf);	
				}
 				printf("\nTebak kata: "); PrintInfo(LPagar); printf(" <%d huruf>\n", Jmlhchar);
 				printf("Kesempatan menebakan: %d\n" ,kesempatan);
 				if ( (!IsEqual(LKata, LPagar, Jmlhchar)) && (kesempatan > 0) ) {
  					printf("Masukkan tebakan anda: ");	
				}
 			}else{
 				printf("LANGSUNG Masukkan tebakan anda: ");
 				break;
			}
 		}
 	}
 		// --------------------------------------------------------------------------------------------			
 	while( tCekKata > 0 && kesempatan > 0){
		scanf("%c", &tebakHuruf);
 		tebakHuruf = toupper(tebakHuruf);		
 		if (tebakHuruf != '\n') {
			cekTebakHuruf = CekKata(&LKata, &LPagar, tebakHuruf);
			tCekKata--;
 			}
 		}
 	printf("\n--------------------------------------------\n");
 		
 /* Showing the results, wether the player won or not  */	
	if ((IsEqual(LKata, LPagar, Jmlhchar))) {
		
   		printf("\nTERTEBAK!");
   		printf("\nKata yang harus ditebak: %s\n", tebakKata);
   		printf("\n--------------------------------------------\n");
   		getchar();
   		JumlahKata--;
   		if(JumlahKata==0){
      		if(kategori<2){
      			JumlahKata = 5;
      			kategori++;
			}else{
				showHangman(4);
			
				printf("\nSELAMAT KAMU TELAH MENYELAMATKAN SESEORANG :)\n");
				printf("\n------- You Win -------\n");
				break; //Keluar dari looping
			}
		}else{
					//Tidak melakukan apa-apa
		}
 	} else {
 		showHangman(0);
 		printf("\nTIDAK TERTEBAK\n");
 		if(kesempatan==0){
 			printf("\nKESEMPATAN ANDA HABIS!\n");
		}
      	printf("Kata yang harus ditebak: %s\nTebakan Kamu: ", tebakKata); PrintInfo(LPagar);
      	printf("\nMAAF KALI INI KAMU TIDAK DAPAT MENYELAMATKANNYA, :'( \n");
      	printf("\n------- Game Over -------\n");
      	break; //Keluar dari looping
 	}	
}
//	Hasil
	printf("\nPemain	: %s ", nama);
    NamaKategori(kategori);
	return 0;
}

/* Menanmpilkan HangMan */
void showHangman(int choice){
    switch(choice){
    	case 0:
    	
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||   %cO/",'\\');
		printf("\n\t||    | ");
		printf("\n\t||   / %c",'\\');
		printf("\n\t||      ");
		printf("\n");
	break;
     	case 1:
	    system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||   %cO/",'\\');
		printf("\n\t||    | ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n");
	break;
   		case 2:
        system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||   %cO/",'\\');
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n");
	break;
  		case 3:
        system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n");
	break;
	    case 4:
    	
		printf("\n\t   %cO/",'\\');
		printf("\n\t    | ");
		printf("\n\t   / %c",'\\');
		printf("\n\t      ");
		printf("\n");
	break;
    }
    return;
 }
 /* Menampilkan Kategori */
void NamaKategori(int nomor){
	switch(nomor){
		case 1:
		printf("\nKategori : 1. Binatang \n");
	break;
		case 2:
     	printf("\nKategori : 2. Bunga \n");
    break;     
	}
	return;
}

/* Membuka Kamus */
FILE *BukaKamusPilihan (int pilih){
	FILE *kamus;
	switch(pilih){
		case 1:
		kamus = fopen("KamusKata_Kategori1.txt", "r");
	break;
     	case 2:
     	kamus = fopen("KamusKata_Kategori2.txt", "r");
    break; 
	}
	return kamus;
}

/* Mengambil kata dengan acakan dari kamus */
char *AmbilKata(int kt) {
	char baca[maks];  
	int ujung;
	FILE *file;  /* Deklarasikan file pointer */
	file = BukaKamusPilihan(kt);/* Membuka File  */
    ujung = fread(baca, 1, maks, file);/* Memebaca file */
    baca[ujung] = '\0';	
/* menjadikan tanda "|" sebagai pemisah antar kata di KamusKata */
    char *tanda = strtok(baca, "|");
    char *kata[maks] = {0};
    int JmlKata = 0;
/* Menyalin semua karakter menjadi kata hingga ada tanda "|", kemudian berulang */
    while(tanda != NULL){
		kata[JmlKata] = malloc(strlen(tanda)+1); 
      	strcpy(kata[JmlKata],tanda);
      	tanda = strtok(NULL, "|");
      	JmlKata++;
    }
    fclose(file);/* Menutup File */
    int Nkata = MesinAcak(JmlKata);/* Mendapatkan Acakan */  
/* Membebaskan semua memori untuk string */
	for(JmlKata = 0; JmlKata < maks; JmlKata++){
        if( JmlKata != Nkata) {
        	free(kata[JmlKata]);
        }
    }
    return kata[Nkata];
}

 /* Menampilkan Logo */
void tampilLogo() {
      printf("--------------------------------------------\n");
      printf("| H  H   A   N   N  GGGG M   M   A   N   N |\n");
      printf("| H  H  A A  NN  N G     MM MM  A A  NN  N |\n");
      printf("| HHHH AAAAA N N N G  GG M M M AAAAA N N N |\n");
      printf("| H  H A   A N  NN G   G M   M A   A N  NN |\n");
      printf("| H  H A   A N   N  GGG  M   M A   A N   N |\n");
      printf("--------------------------------------------\n\n");
} 
/* Menampilkan Pembukaan */
void pembukaan(){
	printf("---\n");
	printf("\t\tPermainan HangMan dengan Impelentasi Bahasa C \n");
	printf("Kelompok HangMAn - RC \n");
	printf("1. 14116133 Andi Ariyandi \n");
	printf("2. 14116148 Alvijar A Pahlevi \n");
	printf("3. 14116153 Rutlima Sinaga \n\n");
	printf("Pentujuk & Aturan Main : \n");
	printf("<1> Akan ada jumlah huruf yang terlihat dari kata yang akan ditebak.\n");
	printf("<2> Kata yang akan ditebak sesuai dengan kategor. \n");
	printf("<3> Hanya mememiliki 4 kali kesempatan menebak.\n");
	printf("<4> Jika yakin, dapat menebaknya langsung dengan inputkan Kata, atau dapat input secara per huruf.\n");
	printf("<5> Akan ada beberapa kata yang bisa ditebak, bila dapat menyelesaikan 2 kategori maka permainan dimenangkan.\n");
	printf("<6> Jika salah menebak kata, maka permainan selesai dan kalah\n\n <Tekan sembarang untuk melanjutkan>");
}
