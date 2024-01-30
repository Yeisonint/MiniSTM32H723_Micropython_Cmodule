#include "py/mphal.h"
#include "lcd.h"
#include "spi.h"

static int32_t __lcd_init(void);
static int32_t __lcd_gettick(void);
static int32_t __lcd_writereg(uint8_t reg,uint8_t* pdata,uint32_t length);
static int32_t __lcd_readreg(uint8_t reg,uint8_t* pdata);
static int32_t __lcd_senddata(uint8_t* pdata,uint32_t length);
static int32_t __lcd_recvdata(uint8_t* pdata,uint32_t length);

#define LCD_BACKLIGHT_ON     HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_RESET)
#define LCD_BACKLIGHT_OFF    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET)
#define LCD_CS_SET           HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET)
#define LCD_CS_RESET         HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET)
#define LCD_RS_SET           HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET)
#define LCD_RS_RESET         HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET)

SPI_HandleTypeDef hspi4;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
ST7735_IO_t st7735_pIO = {
	NULL,
	NULL,
	NULL,
	__lcd_writereg,
	__lcd_readreg,
	__lcd_senddata,
	__lcd_recvdata,
	__lcd_gettick
};
#pragma GCC diagnostic pop

// extern const spi_t spi_obj[6];
ST7735_Object_t st7735_pObj;
uint32_t st7735_id;

// #define SPI_OBJ_PTR &spi_obj[3]


int32_t lcd_init(void){
    int32_t ret;
    ret = __lcd_init();
    // Background pin
    // mp_hal_pin_output(LCD_BACKLIGHT_PIN);
    // mp_hal_pin_output(LCD_RS_PIN);
    // mp_hal_pin_output(LCD_CS_PIN);
    // mp_hal_pin_config_speed(LCD_RS_PIN, MP_HAL_PIN_SPEED_VERY_HIGH);
    // mp_hal_pin_config_speed(LCD_CS_PIN, MP_HAL_PIN_SPEED_VERY_HIGH);
    LCD_BACKLIGHT_OFF;

    // Config LCD
    ST7735Ctx.Orientation = ST7735_ORIENTATION_LANDSCAPE_ROT180;
	ST7735Ctx.Panel = HannStar_Panel;
	ST7735Ctx.Type = ST7735_0_9_inch_screen;
    mp_print_str(MP_PYTHON_PRINTER, "LCD configuration\n");
	
    // Register and init
	ST7735_RegisterBusIO(&st7735_pObj,&st7735_pIO);
	ret = ST7735_LCD_Driver.Init(&st7735_pObj,ST7735_FORMAT_RBG565,&ST7735Ctx);
    mp_print_str(MP_PYTHON_PRINTER, "LCD init\n");
	ST7735_LCD_Driver.ReadID(&st7735_pObj,&st7735_id);
    mp_print_str(MP_PYTHON_PRINTER, "LCD read id\n");

    return ret;
}

void LCD_Test(void){
	extern unsigned char WeActStudiologo_160_80[];
	ST7735_LCD_Driver.DrawBitmap(&st7735_pObj,0,0,WeActStudiologo_160_80);
}

static int32_t __lcd_init(void){
    int32_t res;
    spi_init0();
    // Manually set SPI parameters
    // SPI_HandleTypeDef *spi = spi_obj[3].spi;
    hspi4.Instance = SPI4;
    // SPI_InitTypeDef *init = &spi->Init;

    hspi4.Init.Mode = SPI_MODE_MASTER;
    hspi4.Init.Direction = SPI_DIRECTION_1LINE;
    hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi4.Init.NSS = SPI_NSS_SOFT;
    hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi4.Init.CRCPolynomial = 0x0;
    hspi4.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    hspi4.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    hspi4.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    hspi4.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    hspi4.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
    hspi4.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    hspi4.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    hspi4.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    hspi4.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
    hspi4.Init.IOSwap = SPI_IO_SWAP_DISABLE;

    // init clock and GPIOs
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI4;
    PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        mp_print_str(MP_PYTHON_PRINTER, "Error on PeriphClkInitStruct\n");
    __HAL_RCC_SPI4_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /**SPI4 GPIO Configuration
    PE12     ------> SPI4_SCK
    PE14     ------> SPI4_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_14; // 
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI4;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /**SPI4 GPIO Configuration
    PE10     ------> LCD_BACKLIGHT
    PE11     ------> LCD_CS
    PE13     ------> LCD_RS
    */
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_10, GPIO_PIN_RESET);
    /*Configure GPIO pins : PEPin PEPin */
    GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    res = HAL_SPI_Init(&hspi4);
    if (res!=0)
        mp_print_str(MP_PYTHON_PRINTER, "Error on HAL_SPI_Init\n");
    return res;
}

static int32_t __lcd_gettick(void)
{
	return HAL_GetTick();
}

static int32_t __lcd_writereg(uint8_t reg, uint8_t* pdata, uint32_t length)
{
    int32_t res;
    // spi_obj, size_t len, const uint8_t *src, uint8_t *dest, uint32_t timeout
    LCD_CS_RESET;
    LCD_RS_RESET;
    res = HAL_SPI_Transmit(&hspi4,&reg,1,100);
    // spi_transfer(SPI_OBJ_PTR, 1, &reg, NULL,100);
    LCD_RS_SET;
    res += HAL_SPI_Receive(&hspi4,pdata,length,500);
    // spi_transfer(SPI_OBJ_PTR, length, pdata, NULL,100);
    LCD_CS_SET;
    if (res!=0)
        mp_print_str(MP_PYTHON_PRINTER, "Error on writereg\n");
    return res;
}

static int32_t __lcd_readreg(uint8_t reg,uint8_t* pdata)
{
    int32_t res;
    LCD_CS_RESET;
    LCD_RS_RESET;
    // spi_transfer(SPI_OBJ_PTR, 1, &reg, NULL,100);
    res = HAL_SPI_Transmit(&hspi4,&reg,1,100);
    LCD_RS_SET;
    // spi_transfer(SPI_OBJ_PTR, 1, NULL, pdata, 500);
    res += HAL_SPI_Receive(&hspi4,pdata,1,500);
    LCD_CS_SET;
    if (res!=0)
        mp_print_str(MP_PYTHON_PRINTER, "Error on readreg\n");
    return res;
}

static int32_t __lcd_senddata(uint8_t* pdata,uint32_t length)
{
	// HAL_SPI_Transmit(SPI_Drv,pdata,length,100);
    int32_t res;
    LCD_CS_RESET;
    // spi_transfer(SPI_OBJ_PTR, length, pdata, NULL,100);
    res = HAL_SPI_Transmit(&hspi4,pdata,length,100);
    LCD_CS_SET;
    if (res!=0)
        mp_print_str(MP_PYTHON_PRINTER, "Error on senddata\n");
    return res;
}

static int32_t __lcd_recvdata(uint8_t* pdata,uint32_t length)
{
    int32_t res;
	// HAL_SPI_Receive(SPI_Drv,pdata,length,500);
    LCD_CS_RESET;
    // spi_transfer(SPI_OBJ_PTR, length, NULL, pdata, 500);
    res = HAL_SPI_Receive(&hspi4,pdata,length,500);
    LCD_CS_SET;
    if (res!=0)
        mp_print_str(MP_PYTHON_PRINTER, "Error on recvdata\n");
    return res;
}
