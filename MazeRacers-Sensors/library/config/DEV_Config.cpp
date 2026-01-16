#include "DEV_Config.h"

uint slice_num;

void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{
    gpio_put(Pin, Value);
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
    return gpio_get(Pin);
}

void DEV_SPI_WriteByte(UBYTE Value)
{
    spi_write_blocking(SPI_PORT, &Value, 1);
}

void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len)
{
    spi_write_blocking(SPI_PORT, pData, Len);
}

void DEV_Delay_ms(UDOUBLE xms)
{
    sleep_ms(xms);
}

void DEV_Delay_us(UDOUBLE xus)
{
    sleep_us(xus);
}

void DEV_I2C_WriteByte(uint8_t addr, uint8_t reg, uint8_t Value)
{
    uint8_t data[2] = {reg, Value};
    i2c_write_blocking(I2C_PORT, addr, data, 2, false);
}

void DEV_I2C_Write_nByte(uint8_t addr, uint8_t *pData, uint32_t Len)
{
    i2c_write_blocking(I2C_PORT, addr, pData, Len, false);
}

uint8_t DEV_I2C_ReadByte(uint8_t addr, uint8_t reg)
{
    uint8_t buf;
    i2c_write_blocking(I2C_PORT, addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, addr, &buf, 1, false);
    return buf;
}

void DEV_SET_PWM(uint8_t Value)
{
    if(Value < 0 || Value > 100){
        printf("DEV_SET_PWM() failed \r\n");
    }
    else{
        pwm_set_chan_level(slice_num, PWM_CHAN_B, Value);
    }
}

UBYTE DEV_Module_Init(void)
{
    stdio_init_all();
    DEV_Delay_ms(500);

    i2c_init(I2C_PORT, DEFAULT_KHZ);
    gpio_set_function(LCD_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(LCD_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(LCD_SDA_PIN);
    gpio_pull_up(LCD_SCL_PIN);

    return 0;
}

void DEV_Module_Exit(void)
{
}

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{
    gpio_init(Pin);
    if(Mode == 0 || Mode == GPIO_IN){
        gpio_set_dir(Pin, GPIO_IN);
    }
    else{
        gpio_set_dir(Pin, GPIO_OUT);
    }
}

void DEV_KEY_Config(UWORD Pin)
{
    gpio_init(Pin);
    gpio_pull_down(Pin);
    gpio_set_dir(Pin, GPIO_IN);
}
