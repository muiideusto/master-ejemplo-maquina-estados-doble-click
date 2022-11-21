#include "mbed.h"
 
#define botonPulsado 0
#define botonNoPulsado 1
#define tiempoMaximo 0.5
 
 

 
DigitalOut led(LED1);
DigitalIn boton(PC_13);
Timer temporizador;
enum estados {esperandoPulsacion,esperandoSoltarBoton, esperandoSegundaPulsacion,esperandoSoltarSegundaPulsacion};
estados estado;
 
 
void funcionEsperandoPulsacion()
{
    if(boton==botonPulsado) {
        temporizador.reset();
        temporizador.start();
        estado=esperandoSoltarBoton;
        printf("Boton pulsado\n");
    }
}
 
void funcionEsperandoSoltarBoton()
{
    if(boton==botonNoPulsado) {
        estado=esperandoSegundaPulsacion;
        printf("Boton soltado\n");
    }
}
 
void funcionEsperandoSegundaPulsacion()
{
    if(temporizador.read()>tiempoMaximo) {
        estado=esperandoPulsacion;
       printf("Temporizador expirado\n");
    } else if(boton==botonPulsado) {
        led=!led;
        estado=esperandoSoltarSegundaPulsacion;
        printf("Doble Click\n");
    }
}
 
void funcionEsperandoSoltarSegundaPulsacion()
{
    if(boton==botonNoPulsado) {
        estado=esperandoPulsacion;
        printf("Boton soltado Segunda pulsacion\n");
    }
}
 
int main()
{
    
    estado=esperandoPulsacion;
    while(1) {
        switch(estado) {
            case esperandoPulsacion:
                funcionEsperandoPulsacion();
                break;
            case esperandoSoltarBoton:
                funcionEsperandoSoltarBoton();
                break;
            case esperandoSegundaPulsacion:
                funcionEsperandoSegundaPulsacion();
                break;
            case esperandoSoltarSegundaPulsacion:
                funcionEsperandoSoltarSegundaPulsacion();
                break;
        }
    }
}