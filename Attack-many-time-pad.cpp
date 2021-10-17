#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
typedef struct MSG {
	char BanMa[400]; // luu ban ma he 16 theo dang ky tu vao day
	unsigned char BanMaHe_10[400]; // cac ky tu theo he 16 trong ban ma dc chuyen ve ma ascii cua chung va luu vao day
	int len = 0; // dem cac ky tu cua ban ma he 10 khi chuyen 2 ky tu tu he 16 // ban ma thu 10 co 83 ky tu
	unsigned char banXor[10][300];
}Tn;
Tn msg[11];
// msg[10].len = 83 la do dai cua ban ro thu 11 can tim
int soBanMa=0;
char banRo_MSG_11 [100]; // luu cac ky tu tim duoc vao day
char ganHoanThanh [100];
int check[83]={32};
int maxFre[83]={0};
void docFile (char fileName[]){ 
	FILE *f = fopen (fileName,"r");
	int i=0;
	while (fgets (msg[i].BanMa,400,f) != NULL){
//		printf ("Doc thanh cong ban ma thu %d:\n",i+1);
//		puts (msg[i].BanMa);
		soBanMa = ++i;
	}
	fclose (f);
}
int convert (unsigned char s){
	switch (s){
		case 'a': 
			return 10;
			break;
		case 'b': 
			return 11;
			break;
		case 'c': 
			return 12;
			break;
		case 'd': 
			return 13;
			break;
		case 'e': 
			return 14;
			break;
		case 'f': 
			return 15;
			break;
		default :
			return s-'0';
			break;
	}		
}
void Dec (int i, int j,unsigned char str1,unsigned char str2){
	msg[i].BanMaHe_10[msg[i].len] = convert(str1)*16 + convert(str2);
//	printf ("Vi tri %-3d cua ban ma thu %-3d: He Dec la: %-3d\n",msg[i].k,i,msg[i].BanMaHe_10[msg[i].k]);
	msg[i].len+=1;
}

void ChuyenSangHe_10 (){
	for (int i = 0; i<11; i++){ // vong lap chay cac ban ma
		for (int j = 0; j < strlen (msg[i].BanMa); j+=2){ // vong lap chay tung ky tu cua ban ma
			Dec (i,j,msg[i].BanMa[j],msg[i].BanMa[j+1]);
		}
	}
}
void InBanRo (){
	for (int i = 0; i < msg[10].len; i++){
//		printf ("Ky tu thu %-2d: %c\n",i,banRo_MSG_11[i]);
	}
	puts (banRo_MSG_11);
}
void doanSpace (int f[],int key, char banRo_MSG_11[]){
	if (key != 10){
		for (int i = 0; i < msg[10].len; i++){
			if (f[i] >= 6 && f[i]>=maxFre[i]){ // tan so xuat cang cao thi do chinh xac cang lon 
				banRo_MSG_11[i] = ' '^msg[key].banXor[10][i];
				maxFre[i] = f[i]; // cap nhat tan so
			}
			if (key == 9){
				ganHoanThanh[i] = banRo_MSG_11[i];
			}
		}
	//	InBanRo ();
	}
	
}

void Xor (int key){ // coi ban ma thu i chuyen vao lam key
	int fre [msg[10].len]={0};
	for (int i = 0; i < soBanMa; i++){
//		printf ("Ban %d lam key\n",key);
		for (int  j=0; j < msg[10].len; j++){
			msg[key].banXor[i][j] = msg[key].BanMaHe_10[j]^msg[i].BanMaHe_10[j];
			if (msg[key].banXor[i][j] >= 'a' && msg[key].banXor[i][j] <= 'z' || msg[key].banXor[i][j] >= 'A' && msg[key].banXor[i][j] <= 'Z'){
				fre[j]++;
			}
//			printf ("Dem xor voi ban %-2d vi tri %-2d duoc: %-3c\n",i,j,msg[key].banXor[i][j]);
		}
	}
	for (int i=0; i<83;i++){
//		printf ("Vi Tri %-2d xuat hien: %-2d lan\n",i,fre[i]);
	}
	doanSpace (fre,key,banRo_MSG_11);
//	getch ();
//	system ("cls");
}

void doanSpaceBan10 (int f[],int key){
//	puts (ganHoanThanh);
//	printf ("Da in ban ro gan hoan thanh.\n");
	int k;
	for (k = 0; k < msg[10].len; k++){ // chay cac gia tri trong tan so
//		printf ("K = %d\nFre = %d\n",k,f[k]);
		if (f[k] >= 7){
//			printf ("Dieu kien lon hon 7\n\n");
			ganHoanThanh[k] = ' ';
		}
		if (f[k] == 1){
//			printf ("Dieu kien lon == 1\n\n");
			for (int i = 0; i < soBanMa; i++){
				if (msg[key].banXor[i][k] >= 'a' && msg[key].banXor[i][k] <= 'z' || msg[key].banXor[i][k] >= 'A' && msg[key].banXor[i][k] <= 'Z'){
					ganHoanThanh[k] = msg[key].banXor[i][k]^' ';
				}
			}
		}
	}
	printf ("Ban ro thu 11 sau khi giai ma la: \n");
	puts (ganHoanThanh);
}
void XorBan10 (int key){
//	printf ("Ban %d\n",key);
	int fre [msg[10].len]={0};
	for (int i = 0; i < soBanMa; i++){
		for (int  j=0; j < msg[10].len; j++){
			msg[key].banXor[i][j] = msg[key].BanMaHe_10[j]^msg[i].BanMaHe_10[j];
			if (msg[key].banXor[i][j] >= 'a' && msg[key].banXor[i][j] <= 'z' || msg[key].banXor[i][j] >= 'A' && msg[key].banXor[i][j] <= 'Z'){
				fre[j]++;
			}
//			printf ("Ban %d dem xor ban %-2d duoc: %-3d\n",key,i,msg[key].banXor[i][j]);
		}
	}
	for (int i=0; i<83;i++){
//		printf ("Vi tri thu %-2d: %-2d lan\n",i+1,fre[i]);
	}
	doanSpaceBan10 (fre,key);
}
void demTungBanRoLamKey (){
	for (int  i = 0; i < soBanMa-1; i++){ // goi tu ban 0 den ban 9
//		printf ("%d\n",i);
		Xor (i); // dem di xor
	}
}

int main (){
	for (int i = 0 ; i < 83; i++){
		banRo_MSG_11[i] = ' ';
	}
	docFile ("banma1.txt");
	ChuyenSangHe_10 ();
	demTungBanRoLamKey ();
	XorBan10 (10); // ban thu 10 ta dem xor rieng vi no khong giong voi nhung ban khac
}

