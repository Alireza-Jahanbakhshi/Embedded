/*
 * I2C_TwoBoards_ComPolling.c
 *
 * Created: 2/26/2025 11:39:16 PM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <util/delay.h>

// I2C (TWI) Definitions
#define I2C_SLAVE_ADDRESS 0x20 // Slave address (adjust as needed)
#define SDA PC1
#define SCL PC0

void I2C_Init(void)
{
    TWSR = 0;           // No prescaler
    TWBR = 32;          // Set bitrate for 100kHz at 8MHz (adjust for your clock)
    TWCR = (1 << TWEN); // Enable TWI
}

void I2C_Start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

void I2C_Stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO))
        ;
}

void I2C_Write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

uint8_t I2C_Read_ACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}

uint8_t I2C_Read_NACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}

int main(void)
{
    // Master configuration
    I2C_Init();

    while (1)
    {
        I2C_Start();                             // Send start condition
        I2C_Write((I2C_SLAVE_ADDRESS << 1) | 0); // Write to slave
        I2C_Write(0x55);                         // Send data (e.g., 0x55)
        I2C_Stop();                              // Send stop condition
        _delay_ms(100);                          // Wait before next transmission
    }

    // For Slave (uncomment and use on second board)
    /*
    I2C_Init();
    while(1) {
        if(TWCR & (1<<TWINT)) {        // Check if TWI interrupt flag is set
            uint8_t data = TWDR;       // Read received data
            // Process data as needed
        }
    }
    */
    return 0;
}
