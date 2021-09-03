#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

char Secim;
string FirmaKodu, OkuFirmaKodu;
int siramax, sira, OkuSira;
double Borc, Alacak, Kalan, OkuBorc, OkuAlacak, OkuKalan;
void tercih();
void baslik(), tablo();

void sil() {
	int gecici = 0;
	do {
		system("cls");
		baslik();
		cout << "-VERI SILME ISLEMINE HOSGELDINIZ-\n\n";
		tablo();

		cout << "\n\nSilmek istediginiz kayitin sira numarasini giriniz -> ";
		cin >> sira;
		ifstream dosyaoku("veriler.txt", ios::in);
		ofstream dosyayaz("veriler1.txt", ios::app);
		while (!dosyaoku.eof()) {
			dosyaoku >> OkuSira >> OkuFirmaKodu >> OkuBorc >> OkuAlacak >> OkuKalan;
			if (OkuSira == sira) {
				cout << "\nKayit basariyla silindi." << endl;
				gecici = 1;
			}
			else {
				dosyayaz << endl << OkuSira << " " << OkuFirmaKodu << " " << OkuBorc << " " << OkuAlacak << " " << OkuKalan;
			}
		}
		if (gecici == 0)
			cout << "Dosyada eslesen kayit bulunamadi." << endl;
		dosyaoku.close();
		dosyayaz.close();
		remove("veriler.txt");
		rename("veriler1.txt", "veriler.txt");
		cout << "\nTekrar islem yapmak icin -> 'E / e' \nBir onceki menu icin -> '0' \n";
		cin >> Secim;
	} while ((Secim == 'e') || (Secim == 'E'));
	if (Secim == '0')
		tercih();
}

void guncelle() {

	int gecici = 0;
	do {
		system("cls");
		baslik();
		cout << "-VERI GUNCELLEME ISLEMINE HOSGELDINIZ-\n\n";
		tablo();
		cout << "\n\nGuncellemek istediginiz kayitin sira numarasini giriniz -> ";
		cin >> sira;
		ifstream dosyaoku("veriler.txt", ios::in);
		ofstream dosyayaz("veriler1.txt", ios::app);
		while (!dosyaoku.eof()) {
			dosyaoku >> OkuSira >> OkuFirmaKodu >> OkuBorc >> OkuAlacak >> OkuKalan;
			if (OkuSira == sira) {
				cout << "Guncel firma kodunu girin= ";   cin >> FirmaKodu;
				if (FirmaKodu.length() == 6) {
					cout << "Guncel toplam borcu girin= ";   cin >> Borc;
					cout << "Guncel toplam alacak ucreti girin= ";   cin >> Alacak;
					dosyayaz << endl << sira << " " << FirmaKodu << " " << Borc << " " << Alacak << " " << Alacak - Borc; // dosyaya kayýt ekleme
					cout << "\nVerileriniz basariyla guncellendi." << endl;
				}
				else {
					cout << "Ýslem yapilmadi. Ürün kodu 6 haneli girilmedi.";
					dosyayaz << endl << OkuSira << " " << OkuFirmaKodu << " " << OkuBorc << " " << OkuAlacak << " " << OkuKalan;
				}
				gecici = 1;
			}
			else
				dosyayaz << endl << OkuSira << " " << OkuFirmaKodu << " " << OkuBorc << " " << OkuAlacak << " " << OkuKalan;
		}
		if (gecici == 0)
			cout << "Dosyada eslesen sira numarasi bulunamadi." << endl;
		dosyaoku.close();
		dosyayaz.close();
		remove("veriler.txt");
		rename("veriler1.txt", "veriler.txt");
		cout << "\nTekrar islem yapmak icin -> 'E / e' \nBir onceki menu icin -> '0' \n";
		cin >> Secim;
	} while ((Secim == 'e') || (Secim == 'E'));
	if (Secim == '0')
		tercih();
}

void baslik() {
	cout << "******* MUHASEBE OTOMASYONU *******\n";
	cout << "(Vadeli Satis Muhasebesi)\n\n";
}
void veriYaz() {
	ifstream SiraAl("veriler.txt", ios::in);
	if (!SiraAl) {
		siramax = 1;
		SiraAl.close();
		ofstream dosya1("veriler.txt", ios::app);
		dosya1 << endl << siramax << " " << FirmaKodu << " " << Borc << " " << Alacak << " " << Alacak - Borc;
		dosya1.close();
	}
	else {
		cout << "Lutfen toplam borcu girin= ";   cin >> Borc;
		cout << "Lutfen toplam alacak ucreti girin= ";   cin >> Alacak;
		cout << "\nVerileriniz basariyla kaydedildi. Tablonuz;\n";
		while (!SiraAl.eof()) // Dosyadaki max kayýt numarasýna ulaþma
			SiraAl >> siramax >> OkuFirmaKodu >> OkuBorc >> OkuAlacak >> OkuKalan;
		SiraAl.close();
		ofstream dosya("veriler.txt", ios::app);
		dosya << endl << siramax + 1 << " " << FirmaKodu << " " << Borc << " " << Alacak << " " << Alacak - Borc; // dosyaya kayýt ekleme
		dosya.close(); // dosya kapama
	}
}

void veriOku() {
	ifstream dosyaoku("veriler.txt", ios::in);
	while (!dosyaoku.eof()) { //dosya sonuna kadar veri okuma
		dosyaoku >> sira >> FirmaKodu >> Borc >> Alacak >> Kalan;
		cout << endl << std::left << setw(10) << sira << setw(10) << FirmaKodu << setw(10) << Borc << setw(10) << Alacak << setw(10) << Kalan;// okunan veriyi yazdirma
	}
	dosyaoku.close();
}

void tablo() {
	cout << "\n------------------------------------------------------\n";
	cout << std::left << setw(10) << "Sira" << setw(10) << "Kod" << setw(10) << "Borç" << setw(10) << "Alacak" << setw(10) << "Kalan";
	cout << "\n------------------------------------------------------\n";
	veriOku();
	cout << "\n------------------------------------------------------\n";
}

void listele() {
	do {
		system("cls");
		baslik();
		cout << "-VERI LISTELEME ISLEMINE HOSGELDINIZ-\n\n";
		tablo();
		cout << "\nTekrar islem yapmak icin -> 'E / e' \nBir onceki menu icin -> '0' \n";
		cin >> Secim;
	} while ((Secim == 'e') || (Secim == 'E'));
	if (Secim == '0')
		tercih();
}

void tablo2() {
	cout << "\n------------------------------------------------------\n";
	cout << std::left << setw(10) << "Sira" << setw(10) << "Kod" << setw(10) << "Borç" << setw(10) << "Alacak" << setw(10) << "Kalan";
	cout << "\n------------------------------------------------------\n";
}

void veriler() {
	do {
		system("cls");
		baslik();
		cout << "-VERI YAZMA ISLEMINE HOSGELDINIZ-\n\n";
		cout << "Lütfen 6 haneli ürün kodu girin : ";   cin >> FirmaKodu;
		if (FirmaKodu.length() == 6) {
			veriYaz();
			tablo();
		}
		else {
			cout << "Verileriniz kaydedilmedi. Ürün kodu 6 haneli girilmedi.";
		}
		cout << "\nTekrar islem yapmak icin -> 'E / e' \nBir onceki menu icin -> '0' \n";
		cin >> Secim;
	} while ((Secim == 'e') || (Secim == 'E'));
	if (Secim == '0')
		tercih();
}

void arama() {
	int gecici = 0;
	do {
		system("cls");
		baslik();
		cout << "-VERI ARAMA ISLEMINE HOSGELDINIZ-\n\n";
		ifstream kayitOku("veriler.txt", ios::in);
		if (!kayitOku) {
			cout << "Dosya bulunamadý.";
			Sleep(1000);
			kayitOku.close();
			tercih();
		}
		else {
			cout << "Aramak istediðiniz firma kodunu giriniz= "; cin >> FirmaKodu;
			tablo2();
			while (!kayitOku.eof()) {
				kayitOku >> OkuSira >> OkuFirmaKodu >> OkuBorc >> OkuAlacak >> OkuKalan;
				if (OkuFirmaKodu == FirmaKodu) {
					cout << std::left << setw(10) << OkuSira << setw(10) << OkuFirmaKodu << setw(10) << OkuBorc << setw(10) << OkuAlacak << setw(10) << OkuKalan << endl;
					gecici = 1;
				}
			}
			if (gecici == 0)
				cout << "Kayit bulunamadi.\n";
		}cout << "\n------------------------------------------------------\n";
		kayitOku.close();
		cout << "\nTekrar islem yapmak icin -> 'E / e' \nBir onceki menu icin -> '0' \n";
		cin >> Secim;
	} while ((Secim == 'e') || (Secim == 'E'));
	if (Secim == '0')
		tercih();
}

void tercih() {
	int sec;
	system("cls");
	baslik();
	cout << "1-> Veri Kayýt\n2-> Veri Arama\n3-> Veri Listeleme\n4-> Veri Guncelleme\n5-> Veri Silme";
	cout << "\n\nYapmak istediðiniz iþlemi seçiniz : ";	cin >> sec;
	switch (sec)
	{
	case 1:
		veriler();
		break;
	case 2:
		arama();
		break;
	case 3:
		listele();
		break;
	case 4:
		guncelle();
		break;
	case 5:
		sil();
		break;
	default:
		cout << "Geçersiz Seçim Yaptýnýz";
		Sleep(1000);
		tercih();
		break;
	}
}

int main() {
	setlocale(LC_ALL, "Turkish");
	tercih();

	system("pause");
}