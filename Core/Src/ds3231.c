#include "main.h"
#include "ds3231.h"
#include "ssd1306.h"
#include "stdio.h"

static uint8_t D2B(uint8_t decimal)
{
  return (((decimal / 10) << 4) | (decimal % 10));
}

static uint8_t B2D(uint8_t bcd)
{
  return (bcd >> 4) * 10 + (bcd & 0x0F);
}



void ds3231_zaman_oku(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, zaman_t *zaman)
{
	uint8_t temp[8];
	temp[0] = DS3231_SECONDS_REG;			//0x00 Adresinden başlanarak ilgili saklayıcılara toplu okuma yapılacak.

	HAL_I2C_Master_Transmit(hi2c, DevAddress, &temp[0], 1, 500);	//İlk önce okumaya başlanacak saklayıcı adresi gönderilir.
	HAL_I2C_Master_Receive(hi2c, DevAddress, &temp[1], 7, 500);		//Verilen adresten itibaren 7 bayt okunacak.

	zaman->saniye = B2D(temp[1]);	//Modülden okunan ham veriler yazılan fonksiyonlara gönderilip işlenir.
	zaman->dakika = B2D(temp[2]);   //Modülden okunan ham veriler yazılan fonksiyonlara gönderilip işlenir.
	zaman->saat   = B2D(temp[3]);   //Modülden okunan ham veriler yazılan fonksiyonlara gönderilip işlenir.
	zaman->gun    = B2D(temp[4]);   //Modülden okunan ham veriler yazılan fonksiyonlara gönderilip işlenir.
	zaman->ay_gun = B2D(temp[5]);   //Modülden okunan ham veriler yazılan fonksiyonlara gönderilip işlenir.
	zaman->ay     = B2D(temp[6]);   //Modülden okunan ham veriler yazılan fonksiyonlara gönderilip işlenir.
	zaman->yil    = B2D(temp[7]);   //Modülden okunan ham veriler yazılan fonksiyonlara gönderilip işlenir.
}




void ds3231_zaman_ayarla(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, saat_ayarlama_t zaman)
{
	uint8_t temp[8];				//8 baytlık yerel değişken tanımlanır.

	temp[0] = DS3231_SECONDS_REG;	//0x00 Adresinden başlanarak ilgili saklayıcılara toplu yazma yapılacak.
	temp[1] = D2B(zaman.saniye);	//Fonksiyona girilen ham veriler yazılan fonksiyonlara gönderilip işlenir.
	temp[2] = D2B(zaman.dakika);    //Fonksiyona girilen ham veriler yazılan fonksiyonlara gönderilip işlenir.
	temp[3] = D2B(zaman.saat);      //Fonksiyona girilen ham veriler yazılan fonksiyonlara gönderilip işlenir.
	//TODO: tarih ayarlanmasi eklenecek
	temp[4] = zaman.gun_ay;         //Fonksiyona girilen ham veriler yazılan fonksiyonlara gönderilip işlenir.
	temp[5] = zaman.ay;             //Fonksiyona girilen ham veriler yazılan fonksiyonlara gönderilip işlenir.
	temp[6] = zaman.gun;            //Fonksiyona girilen ham veriler yazılan fonksiyonlara gönderilip işlenir.
	temp[7] = zaman.yil;            //Fonksiyona girilen ham veriler yazılan fonksiyonlara gönderilip işlenir.

	/*RTC modülünün bağlandığı i2c portunun meşguliyeti beklenir.*/
	while( ( HAL_I2C_GetState(hi2c) == HAL_I2C_STATE_BUSY ) || ( HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY ) );

	/*Fonksiyon parametresi zaman gönderilir*/
	HAL_I2C_Master_Transmit(hi2c, DevAddress, temp, 8, 500);
}




void menu_ac(uint8_t menu, uint8_t secili)
{
	switch(menu)
	{
		case ANA_SAYFA:
			anasayfa_ac(secili);		//Saatte anasayfa seçili ise anasayfa açılır.
			break;
		case NABIZ:
			nabiz_menu_ac(secili);		//Saatte nabız menüsü seçili ise anasayfa açılır.
			break;
		case ADIM:						//Saatte adım menüsü seçili ise anasayfa açılır.
			adim_menu_ac(secili);
			break;
		case TELEFON:					//Saatte telefon menüsü seçili ise anasayfa açılır.
			telefon_menu_ac(secili);
			break;
		case SICAKLIK:					//Saatte sıcaklık menüsü seçili ise anasayfa açılır.
			sicaklik_menu_ac();
			break;
		case SAAT:						//Saatte saat menüsü seçili ise anasayfa açılır.
			saat_goster();
			break;
		case SAAT_AYAR:					//Saatte saat ayarla menüsü seçili ise anasayfa açılır.
			saat_ayar_goster();
			break;
		default:
			break;
	}
}

void saat_ayar_goster()
{
	/*
	 * Saat ayarlama ekranında kullanıcı tarafından değiştirilen tarihin
	 * anlık olarak kullanıcıya gösterilmesini sağlayan fonksiyon
	 */
	sprintf(zaman_ayarlama.c_saat  , "%02d", zaman_ayarlama.saat  );	//Değiştirilen saatin tutulduğu kısım.
	sprintf(zaman_ayarlama.c_dakika, "%02d", zaman_ayarlama.dakika);    //Değiştirilen dakikanın tutulduğu kısım.
	sprintf(zaman_ayarlama.c_saniye, "%02d", zaman_ayarlama.saniye);    //Değiştirilen saniyenin tutulduğu kısım.

	ssd1306_Fill(Black);												//ekran temizlenir
	ssd1306_SetCursor(2, 0);											//İmleç başa alınır.
	ssd1306_WriteString(zaman_ayarlama.c_saat, Font_11x18, White);		//Saat.
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(zaman_ayarlama.c_dakika, Font_11x18, White);	//Dakika.
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(zaman_ayarlama.c_saniye, Font_11x18, White);	//Saniye.
	ssd1306_UpdateScreen();												//Doldurulan tampon ekrana gönderilir.
}

void sicaklik_menu_ac()
{
	ssd1306_Fill(Black);									//ekran temizlenir
	ssd1306_SetCursor(2, 0);								//İmleç başa alınır.
	ssd1306_WriteString("Sicaklik: 30", Font_11x18, White); //Örnek olarak sicaklik 30 derece gösterilir.
	ssd1306_SetCursor(2, 19);								//İmleç alt satıra alınır.
	ssd1306_WriteString("->Geri don", Font_11x18, White);	//Bu menüdeki tek seçenek geri dön.
	ssd1306_UpdateScreen();
}

void telefon_menu_ac(uint8_t secili)
{
	switch(secili)
	{
	case 1:
		ssd1306_Fill(Black); 									//Ekran temizlenir.
		ssd1306_SetCursor(2, 0);								//İmleç başa alınır.
		ssd1306_WriteString("->Tlf Bagla", Font_11x18, White);
		ssd1306_SetCursor(2, 19);								//İmleç alt satıra alınır.
		ssd1306_WriteString("Tlf Bag.Kes", Font_11x18, White);
		ssd1306_SetCursor(2, 38);								//İmleç alt satıra alınır.
		ssd1306_WriteString("Geri Don", Font_11x18, White);
		ssd1306_UpdateScreen();									//Ekran Güncelle.
		break;
	case 2:
		ssd1306_Fill(Black);                                    //Ekran temizlenir
		ssd1306_SetCursor(2, 0);                                //İmleç başa alınır.
		ssd1306_WriteString("Tlf Bagla", Font_11x18, White);
		ssd1306_SetCursor(2, 19);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("->Tlf Bag.Kes", Font_11x18, White);
		ssd1306_SetCursor(2, 38);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("Geri Don", Font_11x18, White);
		ssd1306_UpdateScreen();									//Ekran Güncelle.
		break;
	case 3:
		ssd1306_Fill(Black);                                    //Ekran temizlenir
		ssd1306_SetCursor(2, 0);                                //İmleç başa alınır.
		ssd1306_WriteString("Tlf Bagla", Font_11x18, White);
		ssd1306_SetCursor(2, 19);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("Tlf Bag.Kes", Font_11x18, White);
		ssd1306_SetCursor(2, 38);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("->Geri Don", Font_11x18, White);
		ssd1306_UpdateScreen();									//Ekran Güncelle.
		break;
	}

}

void adim_menu_ac(uint8_t secili)
{
	ssd1306_Fill(Black);                                        //ekran temizlenir
	ssd1306_SetCursor(2, 0);                                    //İmleç başa alınır.
	ssd1306_WriteString("Adim Sayisi: 90", Font_11x18, White);  //Örnek olarak adim sayisi 90 gösterilir.
	ssd1306_SetCursor(2, 19);                                   //İmleç alt satıra alınır.
	ssd1306_WriteString("->Geri don", Font_11x18, White);       //Bu menüdeki tek seçenek geri dön.
	ssd1306_UpdateScreen();										//Ekran Güncelle.
}

void nabiz_menu_ac(uint8_t secili)
{
	ssd1306_Fill(Black);                                        //ekran temizlenir
	ssd1306_SetCursor(2, 0);                                    //İmleç başa alınır.
	ssd1306_WriteString("Nabiz : 90", Font_11x18, White);       //Örnek olarak nabız sayisi 90 gösterilir.
	ssd1306_SetCursor(2, 19);                                   //İmleç alt satıra alınır.
	ssd1306_WriteString("->Geri don", Font_11x18, White);       //Bu menüdeki tek seçenek geri dön.
	ssd1306_UpdateScreen();                                     //Ekran Güncelle.
}

void anasayfa_ac(uint8_t secili)
{
	ssd1306_Fill(Black);										//Ekran temizlenir
	switch(secili)
	{
	case 1:
		ssd1306_SetCursor(2, 0);								//İmleç başa alınır.
		ssd1306_WriteString("->Nabiz", Font_11x18, White);
		ssd1306_SetCursor(2, 19);								//İmleç alt satıra alınır.
		ssd1306_WriteString("Adim", Font_11x18, White);
		ssd1306_SetCursor(2, 38);								//İmleç alt satıra alınır.
		ssd1306_WriteString("Telefon", Font_11x18, White);
		ssd1306_UpdateScreen();									//Ekran Güncelle.
		break;
	case 2:
		ssd1306_SetCursor(2, 0);                                //İmleç başa alınır.
		ssd1306_WriteString("Nabiz", Font_11x18, White);
		ssd1306_SetCursor(2, 19);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("->Adim", Font_11x18, White);
		ssd1306_SetCursor(2, 38);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("Telefon", Font_11x18, White);
		ssd1306_UpdateScreen();                                 //Ekran Güncelle.
		break;
	case 3:
		ssd1306_SetCursor(2, 0);                                //İmleç başa alınır.
		ssd1306_WriteString("Nabiz", Font_11x18, White);
		ssd1306_SetCursor(2, 19);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("Adim", Font_11x18, White);
		ssd1306_SetCursor(2, 38);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("->Telefon", Font_11x18, White);
		ssd1306_UpdateScreen();                                 //Ekran Güncelle.
		break;
	case 4:
		ssd1306_SetCursor(2, 0);                                //İmleç başa alınır.
		ssd1306_WriteString("Adim", Font_11x18, White);
		ssd1306_SetCursor(2, 19);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("Telefon", Font_11x18, White);
		ssd1306_SetCursor(2, 38);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("->Sicaklik", Font_11x18, White);
		ssd1306_UpdateScreen();                                 //Ekran Güncelle.
		break;
	case 5:
		ssd1306_SetCursor(2, 0);                                //İmleç başa alınır.
		ssd1306_WriteString("Telefon", Font_11x18, White);
		ssd1306_SetCursor(2, 19);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("Sicaklik", Font_11x18, White);
		ssd1306_SetCursor(2, 38);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("->Saat Yuzu", Font_11x18, White);
		ssd1306_UpdateScreen();                                 //Ekran Güncelle.
		break;
	case 6:
		ssd1306_SetCursor(2, 0);                                //İmleç başa alınır.
		ssd1306_WriteString("Sicaklik", Font_11x18, White);
		ssd1306_SetCursor(2, 19);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("Saat Yuzu", Font_11x18, White);
		ssd1306_SetCursor(2, 38);                               //İmleç alt satıra alınır.
		ssd1306_WriteString("->Saat Ayarla", Font_11x18, White);
		ssd1306_UpdateScreen();                                 //Ekran Güncelle.
		break;
	default:
		break;
	}

}


void saat_goster()
{
	sprintf(saat, "%02d", zaman.saat);					//zaman.saat saat değişkenin içine kopyalanır.
	sprintf(dakika, "%02d", zaman.dakika);				//zaman.dakila dakika değişkenin içine kopyalanır.
	sprintf(saniye, "%02d", zaman.saniye);              //zaman.saniye saniye değişkenin içine kopyalanır.

	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);                            //İmleç başa alınır.
	ssd1306_WriteString(saat, Font_11x18, White);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(dakika, Font_11x18, White);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(saniye, Font_11x18, White);
	ssd1306_UpdateScreen();                             //Ekran Güncelle.
}













