/***************************************************************************

  @file     RAM_api.c

  @brief    API Library to use RAM module

  @author   Ramiro Alarcon Lasagno

  @date     26/10/2023

  @version  v0.0.1
  
 ******************************************************************************/

// Definiciones de constantes
#define BUFFER_SIZE 1024          // Define el tamaño del buffer
#define RAM_START_ADDRESS 0x0000  // Dirección inicial en la RAM

// Variables globales para los punteros de lectura y escritura
uint32_t write_pointer = RAM_START_ADDRESS;  // Puntero de escritura
uint32_t read_pointer = RAM_START_ADDRESS;   // Puntero de lectura

// Función de inicialización de la RAM y el buffer circular
void RAM_Init(void) {
    RAM_Driver_Init();  // Inicializa el driver de la RAM
    CircularBuffer_Init();  // Inicializa el buffer circular
}

// Función de inicialización del buffer circular
void CircularBuffer_Init(void) {
    write_pointer = RAM_START_ADDRESS;  // Restablece el puntero de escritura al inicio
    read_pointer = RAM_START_ADDRESS;   // Restablece el puntero de lectura al inicio
}

// Función para escribir en el buffer circular
void CircularBuffer_Write(char *text, uint8_t length) {
    // Verificar si hay espacio suficiente en el buffer
    uint32_t next_write_pointer = (write_pointer + length) % BUFFER_SIZE;
    if (next_write_pointer == read_pointer) {
        // Buffer lleno, no se puede escribir más
        return;
    }

    // Escribe los datos en la RAM
    for(uint8_t i = 0; i < length; i++) {
        RAM_Driver_writeData(write_pointer, &text[i], 1);
        write_pointer = (write_pointer + 1) % BUFFER_SIZE;
    }
}

// Función para leer del buffer circular
uint8_t CircularBuffer_Read(char *buffer, uint8_t length) {
    uint8_t bytesRead = 0;

    while (read_pointer != write_pointer && bytesRead < length) {
        RAM_Driver_readData(read_pointer, (uint8_t*)&buffer[bytesRead], 1);
        bytesRead++;
        read_pointer = (read_pointer + 1) % BUFFER_SIZE;
    }

    // Devuelve la cantidad de bytes leídos
    return bytesRead;
}

// Función para resetear el buffer circular
void CircularBuffer_Reset(void) {
    write_pointer = RAM_START_ADDRESS;  // Restablece el puntero de escritura al inicio
    read_pointer = RAM_START_ADDRESS;   // Restablece el puntero de lectura al inicio
}
 