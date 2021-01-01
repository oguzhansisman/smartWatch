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
	zaman->gun    = B2D(temp[4]);
	zaman->ay_gun = B2D(temp[5]);
	zaman->ay     = B2D(temp[6]);
	zaman->yil    = B2D(temp[7]);
}

void ds3231_zaman_ayarla(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, saat_ayarlama_t zaman)
{
	uint8_t temp[8];
	temp[0] = 0x00;
	temp[1] = D2B(zaman.saniye);
	temp[2] = D2B(zaman.dakika);
	temp[3] = D2B(zaman.saat);
	//TODO: tarih ayarlanmasi eklenecek
	temp[4] = PAZARTESI;
	temp[5] = 19;
	temp[6] = 4;
	temp[7] = 20;

	while( ( HAL_I2C_GetState(hi2c) == HAL_I2C_STATE_BUSY ) || ( HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY ) );
	HAL_I2C_Master_Transmit(hi2c, DevAddress, temp, 8, 500);
//	HAL_I2C_Master_Transmit_DMA(hi2c, DevAddress, temp, 8);

}




void menu_ac(uint8_t menu, uint8_t secili)
{
	switch(menu)
	{
		case ANA_SAYFA:
			anasayfa_ac(secili);
			break;
		case NABIZ:
			nabiz_menu_ac(secili);
			break;
		case ADIM:
			adim_menu_ac(secili);
			break;
		case TELEFON:
			telefon_menu_ac(secili);
			break;
		case SICAKLIK:
			sicaklik_menu_ac();
			break;
		case SAAT:
			saat_goster();
			break;
		case SAAT_AYAR:
			saat_ayar_goster();
			break;
		default:
			break;
	}
}

void saat_ayar_goster()
{
	sprintf(zaman_ayarlama.c_saat  , "%02d", zaman_ayarlama.saat  );
	sprintf(zaman_ayarlama.c_dakika, "%02d", zaman_ayarlama.dakika);
	sprintf(zaman_ayarlama.c_saniye, "%02d", zaman_ayarlama.saniye);

	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString(zaman_ayarlama.c_saat, Font_11x18, White);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(zaman_ayarlama.c_dakika, Font_11x18, White);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(zaman_ayarlama.c_saniye, Font_11x18, White);
	ssd1306_UpdateScreen();
}

void sicaklik_menu_ac()
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("Sicaklik: 30", Font_11x18, White);
	ssd1306_SetCursor(2, 19);
	ssd1306_WriteString("->Geri don", Font_11x18, White);
	ssd1306_UpdateScreen();
}

void telefon_menu_ac(uint8_t secili)
{
	switch(secili)
	{
	case 1:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("->Tlf Bagla", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("Tlf Bag.Kes", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("Geri Don", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;
	case 2:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Tlf Bagla", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("->Tlf Bag.Kes", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("Geri Don", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;
	case 3:
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Tlf Bagla", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("Tlf Bag.Kes", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("->Geri Don", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;
	}

}

void adim_menu_ac(uint8_t secili)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("Adim Sayisi: 90", Font_11x18, White);
	ssd1306_SetCursor(2, 19);
	ssd1306_WriteString("->Geri don", Font_11x18, White);
	ssd1306_UpdateScreen();
}

void nabiz_menu_ac(uint8_t secili)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("Nabiz : 90", Font_11x18, White);
	ssd1306_SetCursor(2, 19);
	ssd1306_WriteString("->Geri don", Font_11x18, White);
	ssd1306_UpdateScreen();
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
		break;
	case 6:
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Sicaklik", Font_11x18, White);
		ssd1306_SetCursor(2, 19);
		ssd1306_WriteString("Saat Yuzu", Font_11x18, White);
		ssd1306_SetCursor(2, 38);
		ssd1306_WriteString("->Saat Ayarla", Font_11x18, White);
		ssd1306_UpdateScreen();
		break;
	default:
		break;
	}

}


void saat_goster()
{

	sprintf(saat, "%02d", zaman.saat);
	sprintf(dakika, "%02d", zaman.dakika);
	sprintf(saniye, "%02d", zaman.saniye);

	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString(saat, Font_11x18, White);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(dakika, Font_11x18, White);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_WriteString(saniye, Font_11x18, White);
	ssd1306_UpdateScreen();
}













