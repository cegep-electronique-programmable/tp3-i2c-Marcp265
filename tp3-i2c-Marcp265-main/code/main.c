/**
 * Fait par : Marc Pilon
 * Date : 25/02/2025
 * Description : read et write avec I2C
 */

#include "mcc_generated_files/mcc.h"

#define ADDRESSE_I2C_ECRAN  40			//0x28
#define ADDRESSE_I2C_EEPROM 0x50        //1010 000

void Capture_CallBack(uint16_t capturedValue);

uint16_t capture;

/*
    D�but de l'application principale
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    // set the custom callback
    CCP2_SetCallBack(Capture_CallBack);
    
    uint8_t addrW[20]; //tab write
    
    addrW[0]= 0x00;
    addrW[1]= 0x01;
    addrW[2]= 0x3A;
    addrW[3]= 0x29;
    
    uint8_t addrR[20]; //tab read

    uint16_t capSec = ((capture/5)*8); //fosc/4
    
    uint8_t capTab[4];
    
    capTab[0] = 0x30; //dizaine
    capTab[1] = 0x31; //unit�
    capTab[2] = 0x2E; //point
    capTab[3] = 0x31; //dixi�me
    

    while (1)
    {
        printf("%d", capture);
        printf("%d", capSec);
        // Code qui �crit sur l'�cran
        while(I2C_Open(ADDRESSE_I2C_ECRAN) == I2C_BUSY);    //Passage de l'adresse
        I2C_SetBuffer(capTab, 4);                          //Passage des donn�es
        I2C_MasterOperation(0);                             //D�marrer une op�ration d'�criture
        while (I2C_Close() == I2C_BUSY);                   	//Attendre que l'op�ration soit compl�te    

        __delay_ms(1000);
        
        
        
        
         //Code qui lit 4 octets de la m�moire EEPROM
        
//        // �criture de deux octets de donn�es � la EEPROM
//        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);   //passage de l?adresse I2C
//        I2C_SetBuffer(addrW, 4);        //passage de l?adresse interne sur 2 octets plus 2 octets de donn�
//        I2C_MasterOperation(0);				//write
//        while (I2C_Close() == I2C_BUSY);
//        __delay_ms(1000);
//
//        
//        // Lecture de 2 octets de la EEPROM
//        while(I2C_Open(ADDRESSE_I2C_EEPROM) == I2C_BUSY);	//passage de l?adresse I2C
//        I2C_SetBuffer(addrW, 2);        //set position pour write
//        I2C_MasterOperation(0);         //write
//        I2C_SetBuffer(addrR, 2);        //passage du tampon et du nombre de //lectures � faire
//        I2C_MasterOperation(1);         //read
//        while (I2C_Close() == I2C_BUSY);
//        __delay_ms(1000);
//        
//        
//        //print sur l'�cran a partir du EEPROM
//        while(I2C_Open(ADDRESSE_I2C_ECRAN) == I2C_BUSY);    //Passage de l'adresse
//        I2C_SetBuffer(addrR, 2);                            //Passage des donn�es
//        I2C_MasterOperation(0);                             //write
//        while (I2C_Close() == I2C_BUSY);                   	//Attendre que l'op�ration soit compl�te    
//
//        __delay_ms(1000);
    }
}

void Capture_CallBack(uint16_t capturedValue)
    {
    //mettre la valeur captur� dans une variable et restart le timer
        capture = capturedValue;
        TMR1_Reload();
        
    }