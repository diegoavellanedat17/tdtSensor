/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs 

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs  - 1.45
        Device            :  PIC18F45K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <stdlib.h>
#include <pic18f45k22.h>

/*
                         Main application
 */
//Funcion para inicializar el ADC
void ADC_init(){
    ANSELA=0b00000011;
    TRISA=0b00000011;
    ANSELB=0b00001110;
    TRISB=0b00000111;
    ADCON1bits.PVCFG=0;
    ADCON1bits.NVCFG=0;
    ADCON2bits.ADCS=0b111;//Frecuencia conversion
    ADCON2bits.ADFM=1; //Justificado a la derecha
    ADCON0bits.ADON=1;
     __delay_ms(100);
    
}
//Funcion para leer el ADC y retornar los 10 bits de la converscion
unsigned int ADC_Read(unsigned char canal){
ADCON0bits.CHS &= 0x000;
ADCON0bits.CHS |=canal;
__delay_ms(2);
 ADCON0bits.GO_nDONE=1;//lanza la converscion 
 while(ADCON0bits.GO_nDONE);//Esperamos la conversion
 return ((ADRESH<<8)+ADRESL);


}
//Funcion que promedia los valores del ADC

int ADC_promediado(unsigned char canal){
    //inicializa el valor de ADC
    int sum=0;
    int av=0;
   

    for(uint16_t i=0; i <10; i++){
    
        sum=ADC_Read(canal)+sum;
        
    }
    av=sum/10;
    return av;
  
}
//funcion para cambiar la frecuencia de toma de datos 
int freq_datos(){
    int cuenta=0;
    int conteo;
      if(PORTBbits.RB0==1){
      
             cuenta=1; 
             if(cuenta==0)
                LATDbits.LATD3=1;
                LATDbits.LATD4=0;
                LATDbits.LATD5=0;
             __delay_ms(400);
             
          
      }
    
    return(cuenta);
    
}


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    //Inicializando el pulsador de la entrada
    TRISBbits.RB0=1;
    //COlocando El ADC
    TRISBbits.RB2=1;
    // Definiendolo como digital
    ANSELBbits.ANSB0=0;
    //Colocando como analogico
    ANSELBbits.ANSB2=0;
    
    // Inicializando los 4 LEDS de salida
    TRISDbits.RD4=0;
    TRISDbits.RD5=0;
    TRISDbits.RD6=0;
    TRISDbits.RD7=0;
    // Enable ESP8266 or Lopy
    TRISAbits.RA6=0;
    
    
    //Definiendo que empiezan en estado bajo
    LATDbits.LATD4=0;
    LATDbits.LATD5=0;
    LATDbits.LATD6=0;
    LATDbits.LATD7=0;
    LATAbits.LATA6=0;
    //Inicializar el ADC
    ADC_init();
    //variable para almacenar en el ADC
    unsigned int adc;
    TMR0_Initialize();
    int cuenta =0;
    int conteo=0;
    int freq[]={3,6,90,180,270,360,720,1080,1440,1800,2160,2520,3600,4320,6480,8640};
    int i=0;
    int valFreq=freq[0];

    while (1)
    {
        
 
        
        if(PORTBbits.RB0==1){
            conteo=1;
            __delay_ms(300);
        }
        if(conteo==1){
            valFreq=freq[i];
            i=i+1;
            conteo=0;
            if(i==3){
                i=0;
            }
            if(valFreq==freq[0]){
                LATDbits.LATD4=0;
                LATDbits.LATD5=0;
                LATDbits.LATD6=0; 
                LATDbits.LATD7=0;
                LATAbits.LATA6=1;
                __delay_ms(500);
                
            }
            if(valFreq==freq[1]){
                printf("1\n");
                LATDbits.LATD4=0;
                LATDbits.LATD5=0;
                LATDbits.LATD6=0; 
                LATDbits.LATD7=1;
                LATAbits.LATA6=0; 
                __delay_ms(500);
                LATDbits.LATD4=0;
                LATDbits.LATD5=0;
                LATDbits.LATD6=0; 
                LATDbits.LATD7=0;
                LATAbits.LATA6=0; 
            }
            if(valFreq==freq[2]){
                printf("0\n");
                LATDbits.LATD4=0;
                LATDbits.LATD5=0;
                LATDbits.LATD6=1; 
                LATDbits.LATD7=0;
                LATAbits.LATA6=0; 
                __delay_ms(500);
                LATDbits.LATD4=0;
                LATDbits.LATD5=0;
                LATDbits.LATD6=0; 
                LATDbits.LATD7=0;
                LATAbits.LATA6=0; 
                
            }
        }
   
        
        if(INTCONbits.TMR0IF ==1){
            //printf("cuenta %d \n",cuenta);
            cuenta=cuenta+1;
            TMR0_Initialize();
            if(cuenta==valFreq){
                LATAbits.LATA6=1;
                cuenta =0;
                __delay_ms(10000);
                //printf("\n el dato es: ");
                adc=ADC_promediado(8);
                //adc=ADC_Read();
                printf("%d \n",adc);
                printf("%d \n",adc);
                __delay_ms(10000);
                 //printf("y esto es cada %d ciclos",valFreq);
                LATAbits.LATA6=0;
            }
         
        }
        
  
        
        

        // Add your application code
    
}
}
/**
 End of File
*/