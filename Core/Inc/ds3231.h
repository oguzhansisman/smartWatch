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

#define ANA_SAYFA_MAX_SATIR					6
#define TELEFON_MAX_SATIR					3

typedef struct
{
	uint8_t satir;
	uint8_t secili;
	uint8_t menu;
}lcd_t;

enum
{
	ANA_SAYFA,
	NABIZ,
	ADIM,
	TELEFON,
	SICAKLIK,
	SAAT
};

typedef struct
{
    uint8_t yil;
    uint8_t ay;
    uint8_t gun;
    uint8_t ay_gun;
    uint8_t saat;
    uint8_t dakika;
    uint8_t saniye;
}ds3231_cfg_t;

typedef struct
{
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
    uint32_t clock_tick_1_ms;
    uint8_t  _500Hz_bayrak;
    uint8_t  _200Hz_bayrak;
    uint8_t  _100Hz_bayrak;
    uint8_t  _50Hz_bayrak;
    uint8_t  _2Hz_bayrak;
    uint8_t  _1Hz_bayrak;
    uint8_t  zaman_asimi;
}task_clock_t;


task_clock_t sistem_zamani;
zaman_t zaman;
ds3231_cfg_t ds3231_cfg;
lcd_t lcd;
uint8_t timer_durum;


char string[20];
char saat[20];
char dakika[20];
char saniye[20];
char tire;
char deneme[20];
uint32_t buton_deneme;
void ds3231_zaman_ayarla(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, ds3231_cfg_t zaman);

void ds3231_zaman_oku(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, zaman_t *zaman);

void menu_ac(uint8_t menu, uint8_t secili);

void anasayfa_ac(uint8_t secili);
void telefon_menu_ac(uint8_t secili);
void adim_menu_ac(uint8_t secili);
void nabiz_menu_ac(uint8_t secili);
void sicaklik_menu_ac();
void saat_goster();

#endif
