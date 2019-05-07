/* file nanme linkedlist.h */
#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER
#include "boolean.h"
#define Nil NULL
typedef char infotype;
typedef struct tElmntList *address;
typedef struct tElmntList{
	infotype Info;
	address Next;
}ElmList;

typedef struct {
	address First;
}List;

#define Info(P) (P)->Info
#define Next(P) (P)->Next
#define First(L) ((L).First)


/* Mengalokasikan sebuah memori */
address Alokasi (infotype X){ 
	address P;
	P = (address) malloc (sizeof (ElmList));
	if (P!=Nil){
		Info(P)=X ; Next(P)=Nil;
		return P;
	}else {
		return Nil;
	}
}

void Dealokasi (address P){
	free(P);
}

boolean IsEmpty (List L) { 
  return (First(L) == Nil);
}

void CreateEmpty (List * L) {
  First(*L) = Nil;
}

void InsertFirst (List * L, address P) { 
  Next(P) = First(*L);
  First(*L) = P;
}

void InsVFirst (List * L, infotype InfoE) { 
  address P;
  P = Alokasi(InfoE);
  if (P != Nil) {
    Next(P) = First(*L); 
    First(*L) = P;
  }
}

void InsertAfter (address P, address Prec){
  	Next(P) = Next(Prec);
  	Next(Prec) = P;
}

void InsertLast (List * L, address P) { 
  address Last; 
  if (IsEmpty(*L)) { 
    InsertFirst(L,P); 
  } else {
    Last = First(*L);
    while (Next(Last) != Nil) {
      Last = Next(Last);
    } 
    InsertAfter(P,Last);
	}
}

void InsVLast (List * L, infotype InfoE) { 
  address Alokasi(infotype X);
  address P;
  P = Alokasi(InfoE);
  if (P != Nil) { 
    InsertLast(L,P); 
  }
}

void DeleteFirst (List * L, address * P) { 
  *P = First(*L);
  First(*L) = Next(First(*L));
  Next(*P) = Nil;
}

void DeleteAfter (address Prec, address *P) { 
  *P = Next(Prec);
  Next(Prec) = Next(Next(Prec));
  Next(*P) = Nil;
}

void DeleteP (List * L, address P) { 
  address Prec; 
  if (P = First(*L)) { 
      DeleteFirst(L,&P); 
  } else {
      Prec = First(*L);
      while (Next(Prec) != P) {
         Prec = Next(Prec);
      } 
      DeleteAfter(Prec,&P);
  }
}

void DeleteLast (List * L, address * P) { 
  address Last, PrecLast; 
  Last = First(*L);
  PrecLast = Nil; 
  while (Next(Last) != Nil) {
  
    PrecLast = Last;
    Last = Next(Last);
  } 

  *P = Last;
  if (PrecLast == Nil) { 
    First(*L) = Nil;
  } else {
    Next(PrecLast) = Nil;
  }
}

void PrintInfo (List L){
	address P;
	if (IsEmpty(L)){ // Jika List Kosong Maka Menampilkan "List Kosong"
		printf ("List Kosong\n");
	}
	P = First(L);
	while (Next(P) != Nil){ // Untuk Print Isi dari List digunakan cara menjelajahi semua isi nya sampai elemen terakhir
		printf("%c ",Info(P));
		P = Next(P);
	} 
}

int CekKata(List *L1, List *L2, infotype x){
	address P1;
	P1 = First(*L1);
	address P2;
	P2 = First(*L2);
	int t = 0;
	while (Next(P1) != Nil){ 
		if(Info(P1) == x){
			Info(P2) = x;
			t=1;
		}
		P1 = Next(P1);
		P2= Next(P2);
	}
	return t;
}

/*** Operasi-Operasi Lain ***/
boolean IsEqual(List L1, List L2, int BanyakHuruf ){
	address P1 = First(L1);
	address P2 = First(L2);
	int t=0;
	while (Next(P1)!=Nil){
		if (IsEmpty(L1) || IsEmpty(L2)) {
			return false;  	
		} else {			
			if (Info(P1)!=Info(P2)) {
				return false;
			} else {
				t++;
			}
		}
		P1 = Next(P1);
		P2 = Next(P2);
	}
	
	if (BanyakHuruf == t){
		return true;
	} else {
		return false;
	}
}

#endif
