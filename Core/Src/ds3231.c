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
	temp[0] = DS3231_SECONDS_REG;

	HAL_I2C_Master_Transmit(hi2c, DevAddress, &temp[0], 1, 500);
	HAL_I2C_Master_Receive(hi2c, DevAddress, &temp[1], 7, 500);

	zaman->saniye = B2D(temp[1]);
	zaman->dakika = B2D(temp[2]);
	zaman->saat   = B2D(temp[3]);
	zaman->ay_gun = B2D(temp[4]);
	zaman->ay     = B2D(temp[5]);
	zaman->gun    = B2D(temp[6]);
	zaman->yil    = B2D(temp[7]);
}

void ds3231_zaman_ayarla(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, ds3231_cfg_t zaman)
{
	uint8_t temp[8];
	temp[0] = 0x00;
	temp[1] = D2B(zaman.saniye);
	temp[2] = D2B(zaman.dakika);
	temp[3] = D2B(zaman.saat);
	temp[4] = D2B(zaman.ay_gun);
	temp[5] = D2B(zaman.ay);
	temp[6] = zaman.gun;
	temp[7] = D2B(zaman.yil);

//	HAL_I2C_Master_Transmit(hi2c, DevAddress, temp, 8, 500);
	HAL_I2C_Master_Transmit_DMA(hi2c, DevAddress, temp, 8);
}




void menu_ac(uint8_t menu, uint8_t secili)
{
	switch(menu)
	{
		case ANA_SAYFA:
			anasayfa_ac(secili);
			break;
		case ADIM:
			printf("Bugün attıgınız adım sayisi 12\n");
			break;
		case TELEFON:
			printf("Telefona baglan");
			switch (secili)
			{
			case 1:
				printf("->Baglantiyi kes\n");
				printf("Baglan");
				break;
			case 2:
				printf("Baglantiyi kes\n");
				printf("->Baglan");
				break;
			default:
				break;
			}
			break;
		case SICAKLIK:
			printf("Anlik ortam sicakligi: 25");
			break;
		default:
			break;
	}
}



void anasayfa_ac(uint8_t secili)
{
	ssd1306_Fill(Black);
	switch(secili)
	{
	case 1:
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("->Nabiz", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("Adim", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("Telefon", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;
	case 2:
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Nabiz", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("->Adim", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("Telefon", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;
	case 3:
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Nabiz", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("Adim", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("->Telefon", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;
	case 4:
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Adim", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("Telefon", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("->Sicaklik", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;
	case 5:
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Telefon", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("Sicaklik", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("->Saat Yuzu", Font_11x18, White);
		ssd1306_UpdateScreen();
	case 6:
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Sicaklik", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("Saat Yuzu", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("->Saat Ayarla", Font_11x18, White);
		ssd1306_UpdateScreen();
	default:
		break;
	}

}


void saat_goster()
{
	sprintf(saat, "%02d", zaman.saat);
	sprintf(dakika, "%02d", zaman.dakika);
	sprintf(saniye, "%02d", zaman.saniye);

	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString(saat, Font_11x18, White);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(dakika, Font_11x18, White);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(saniye, Font_11x18, White);
	ssd1306_UpdateScreen();
}













