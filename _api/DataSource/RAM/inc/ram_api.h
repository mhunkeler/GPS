/******************************************************************************

  @file     RAM_api.h

  @brief    API Library to use RAM module

  @author   Ramiro Alarcon Lasagno

  @date     26/10/2023

  @version  v0.0.1

 ******************************************************************************/

#ifndef _RAM_API_H_
#define _RAM_API_H_

// Funciones de inicialización
void RAM_Init(void);
#setFile temp/EMICinits.c
	RAM_Init(); // Funcion que se ejecuta en el main
  //Aqui se agregan las funciones iniciales y las variables iniciales se crean
#unSetFile

void CircularBuffer_Init(void);

// Funciones de escritura y lectura en la cola circular
void CircularBuffer_Write(char *text, uint8_t length);
uint8_t CircularBuffer_Read(char *buffer, uint8_t length);

// Función para resetear la cola circular
void CircularBuffer_Reset(void);

// Definiciones para el tamaño del buffer y la dirección de inicio en la RAM
#define BUFFER_SIZE 1024
#define RAM_START_ADDRESS 0x0000

#endif