#ifndef __DS3231_H
#define __DS3231_H

#include "stdint.h"

#define DS3231_SECONDS_REG 	                0x00
#define DS3231_MINUTES_REG 	                0x01
#define DS3231_HOUR_REG		                0x02
#define DS3231_DAY_REG		                0x03
#define DS3231_DATE_REG		                0x04
#define DS3231_MONTH_REG		            0x05
#define DS3231_YEAR_REG 		            0x06
#define DS3231_ALARM_1_SECONDS_REG 		    0x07
#define DS3231_ALARM_1_MINUTES_REG 		    0x08
#define DS3231_ALARM_1_HOUR_REG 		    0x09
#define DS3231_ALARM_1_DAY_REG 		    	0x0A
#define DS3231_SLAVE_ADDR					0xD0



#define ANA_SAYFA_MAX_SATIR					6
#define TELEFON_MAX_SATIR					3

typedef struct
{
	uint8_t secili;		//Mevcut menüde hangi seçeneğin seçili olduğu tutulur.
	uint8_t menu;	 	//Hangi menüde olduğu tutulur.
}lcd_t;


typedef struct
{
	/* Saat ayarlanırken zaman bilgilerinin tutulduğu yapı */

	uint8_t saat    ;		//Ayalanacak saat tutulur.
	uint8_t dakika  ;	  	//Ayalanacak dakika tutulur.
	uint8_t saniye  ;     	//Ayalanacak saniye tutulur.
	uint8_t gun_ay  ;     	//Ayalanacak gun_ay tutulur.
	uint8_t ay      ;     	//Ayalanacak ay tutulur.
	uint8_t gun     ;     	//Ayalanacak gun tutulur.
	uint8_t yil     ;     	//Ayalanacak yil tutulur.
	char c_saat[5]  ;		//Ayar yapılırken ekrana yazılacak saat tutulur
	char c_dakika[5];       //Ayar yapılırken ekrana yazılacak dakika tutulur
	char c_saniye[5];       //Ayar yapılırken ekrana yazılacak saniye tutulur
	uint8_t saat_ayar_digit;//Hangi basamağın ayarlanacağı tutulur.
}saat_ayarlama_t;

enum
{
	/* Menü isimlerinin tutulduğu enum */
	ANA_SAYFA,
	NABIZ,
	ADIM,
	TELEFON,
	SICAKLIK,
	SAAT,
	SAAT_AYAR
};

typedef struct
{
	/* RTC modülünden okunan verilerin tutulduğu yapı*/

    uint8_t yil;
    uint8_t ay;
    uint8_t gun;
    uint8_t ay_gun;
    uint8_t saat;
    uint8_t dakika;
    uint8_t saniye;
}zaman_t;

typedef struct
{
	/* sistem zamanı için oluşturulmuş yapı */

    uint32_t clock_tick_1_ms;		//Her 1 milisaniyede bir artırılacak değişken
    uint8_t  _500Hz_bayrak;			//500Hz temsil eden bayrak
    uint8_t  _200Hz_bayrak;         //200Hz temsil eden bayrak
    uint8_t  _100Hz_bayrak;         //100Hz temsil eden bayrak
    uint8_t  _50Hz_bayrak;          //50Hz  temsil eden bayrak
    uint8_t  _2Hz_bayrak;           //2Hz   temsil eden bayrak
    uint8_t  _1Hz_bayrak;           //1Hz   temsil eden bayrak
    uint8_t  zaman_asimi;			//Zaman aşımı tespit edebilmek için tutulan değişken
}task_clock_t;

enum
{
	/*Saat ayar ekranında adımları saymak için kullanılan enumlar */

	SAAT_ONDALIK,
	SAAT_BIRLIK,
	DAKIKA_ONDALIK,
	DAKIKA_BIRLIK,
	SANIYE_ONDALIK,
	SANIYE_BIRLIK,
	SET_SAAT
};

enum
{
	/* Gun ayarı için tutulan enumlar*/

	PAZARTESI = 1,
	SALI,
	CARSAMBA,
	PERSEMBE,
	CUMA,
	CUMARTESI,
	PAZAR
};

task_clock_t sistem_zamani;			//Task yapılarında kullanılacak global değişken
zaman_t zaman;						//Mevcut zamanı tutmada kullanılacak global değişken
lcd_t lcd;							//Ekran işlemlerinde kullanılacak global değişken
saat_ayarlama_t zaman_ayarlama;		//Saat ayarlama işlemlerinde kullanılacak global değişken
uint8_t timer_durum;				//Buton debouncing önlemek için kullanılan timer değişkeni

/*Saat yüzünde ekrana bastırılmak için kullanılan karakter dizileri*/
char saat[5];
char dakika[5];
char saniye[5];

/* Oluşturulan fonksiyonların prototipleri */
void ds3231_zaman_ayarla(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, saat_ayarlama_t zaman);
void ds3231_zaman_oku(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, zaman_t *zaman);
void saat_ayar_goster();
void menu_ac(uint8_t menu, uint8_t secili);
void anasayfa_ac(uint8_t secili);
void telefon_menu_ac(uint8_t secili);
void adim_menu_ac(uint8_t secili);
void nabiz_menu_ac(uint8_t secili);
void sicaklik_menu_ac();
void saat_goster();

#endif
