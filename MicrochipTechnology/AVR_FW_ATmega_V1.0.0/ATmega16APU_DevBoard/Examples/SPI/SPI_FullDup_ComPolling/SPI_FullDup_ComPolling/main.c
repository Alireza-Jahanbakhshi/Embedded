/*
 * SPI_FullDup_ComPolling.c
 *
 * Created: 2/26/2025 11:35:55 PM
 * Author : PA
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

// SPI Pin Definitions for ATmega16
#define SPI_PORT PORTB
#define SPI_DDR  DDRB
#define SS       PB4    // Slave Select
#define MOSI     PB5    // Master Out Slave In
#define MISO     PB6    // Master In Slave Out
#define SCK      PB7    // Serial Clock

// Function Prototypes
void SPI_MasterInit(void);
void SPI_SlaveInit(void);
uint8_t SPI_MasterTransmit(uint8_t data);
uint8_t SPI_SlaveReceive(void);

// Main Function
int main(void)
{
    // Choose either Master or Slave mode by uncommenting appropriate init
    SPI_MasterInit();    // For Master device
    //SPI_SlaveInit();   // For Slave device (uncomment for slave)

    // Example usage for Master
    while (1) 
    {
        // Master sends data and receives simultaneously
        uint8_t receivedData = SPI_MasterTransmit(0x55); // Send 0x55, receive from slave
        _delay_ms(100);  // Small delay between transmissions
        
        // Use receivedData as needed
    }

    // Example usage for Slave (uncomment for slave device)
    /*
    while (1) 
    {
        uint8_t receivedData = SPI_SlaveReceive();
        // Process receivedData as needed
    }
    */
    return 0;
}

// SPI Master Initialization
void SPI_MasterInit(void)
{
    // Set MOSI, SCK, and SS as output, MISO as input
    SPI_DDR |= (1 << MOSI) | (1 << SCK) | (1 << SS);
    SPI_DDR &= ~(1 << MISO);
    
    // Enable SPI, Master mode, clock rate fck/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    
    // Set SS high (inactive)
    SPI_PORT |= (1 << SS);
}

// SPI Slave Initialization
void SPI_SlaveInit(void)
{
    // Set MISO as output, others as input
    SPI_DDR |= (1 << MISO);
    SPI_DDR &= ~((1 << MOSI) | (1 << SCK) | (1 << SS));
    
    // Enable SPI in Slave mode
    SPCR = (1 << SPE);
}

// SPI Master Transmit and Receive
uint8_t SPI_MasterTransmit(uint8_t data)
{
    // Pull SS low to select slave
    SPI_PORT &= ~(1 << SS);
    
    // Start transmission
    SPDR = data;
    
    // Wait for transmission complete
    while (!(SPSR & (1 << SPIF)));
    
    // Pull SS high to deselect slave
    SPI_PORT |= (1 << SS);
    
    // Return received data
    return SPDR;
}

// SPI Slave Receive
uint8_t SPI_SlaveReceive(void)
{
    // Wait for reception complete
    while (!(SPSR & (1 << SPIF)));
    
    // Return received data
    return SPDR;
}
