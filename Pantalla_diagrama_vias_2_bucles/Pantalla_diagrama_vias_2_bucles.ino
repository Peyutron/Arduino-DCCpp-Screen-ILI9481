// Modulo Pantalla DCC Diagrama Bucles || 21-04-2024
//
// Pantalla con controlador ILI9481 sin Touch
////////////////////////////////////////////////////
// Distribucion de pines:
// A4 = Receptor RF -> MX-RM-5V

// SENS01		1	// B1 -> Sensor IR Norte Interior bucle
// SENS02		2	// B1 -> Sensor IR Sur   Interior bucle
// SENS03		3	// B1 -> Sensor Consumo E/S Sur
// SENS04		4	// B1 -> Sensor Consumo Interior bucle
// SENS05		5	// B1 -> Sensor Consumo E/S Norte
// SENS06		6 	// No Usado

#include <VirtualWire.h>
#include <listaAccesorios.h>  // Opcional
#include <listaDetectores.h>  // Opcional
#include "ScreenDefine.h"
#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>

#include <Fonts/FreeMonoBold12pt7b.h>

MCUFRIEND_kbv tft;

const int receive_pin = A4; // Pin recepción RF433


// Recepción de datos
uint8_t bserial = false;
char c;
char b;
char commandString[MAX_COMMAND_LENGTH + 1];


bool screen = true;
bool printdata = true;


uint8_t sensores[16] = {  true, true, true, true, true,
                          true, true, true, true, true,
                          true, true, true, true, true
                          };
                          
uint8_t desvios[MAX_DESVIOS]= {true, false};
uint8_t accesorios[MAX_DESVIOS]= {false, false};


void setup()
{
  Serial.begin(115200); // Velocidad serial
  delay(200);

// Configuración pantalla ILI9481 sin Touch
  tft.reset();
  uint16_t identifier = tft.readID();
  // if (identifier == 0xEFEF) identifier = 0x9481;
  Serial.println(identifier, HEX);
  tft.begin(identifier);
  delay(200);
  tft.setRotation(true);  // Rotación
  tft.fillScreen(TFT_BLACK);     // Fondo de pantalla
  tft.setTextColor(TFT_WHITE);   // Color del texto
  tft.setTextSize(1);       // Tamaño de la letra
  tft.setFont(&FreeMonoBold12pt7b);
  ClearScreen();
  Locomotora("1 8 100 0");

// Configuración RF433 MX-RM-5V ¡¡¡Siempre al final del setup()!!!
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true);  // Requerido para RD3100
  vw_setup(2000);             // Bits por segundo
  vw_rx_start();       // Start the receiver PLL running

}
// FIN SETUP

void loop()
{
  if (screen) {

    //  *** Diagrama de vías ***** //
    // MODULO B1
    // VIA NORTE BUCLE RETORNO 1 SENSOR 5
    Seccion(BN_X_START_B1_NORTE, 
            BN_Y_START, 
            BN_RECTA_LARGA_B1_NORTE, 
            ANCHO_RECTA, 
            sensores[SENS05]); 
    
    //  INTERIOR BUCLE RETORNO 1 SENSORES 1,2,4
    Bucle_1(sensores[SENS04]);  
    
    //  VIA SUR BUCLE RETORNO 1
    SalidaBucle1(sensores[SENS03]); 
    
    // MODULO B1 COCHERAS
    Seccion14(sensores[SENS06]);
    
    if (desvios[0]) DesvioCocherasPrincipal(COLOR_LIBRE, COLOR_OCUPADO);
    else DesvioCocherasPrincipal(COLOR_OCUPADO, COLOR_LIBRE);
    

    if (desvios[1]) DesvioCocheras(COLOR_LIBRE, COLOR_OCUPADO);
    else DesvioCocheras(COLOR_OCUPADO, COLOR_LIBRE);

    // MODULO B2
    // VIA NORTE MODULO 2
    Seccion(240, 
            BN_Y_START, 
            BN_RECTA_LARGA, 
            ANCHO_RECTA, 
            sensores[SENS07]); 
    Bucle_2(sensores[SENS07]);
    SalidaBucle2(sensores[SENS07]); //  VIA SUR BUCLE RETORNO 1


    PintaAccesorios(FLINE1, FLINE1_1, TXTL_EXTERIOR, accesorios[0]); // Efecto soldador
    PintaAccesorios(FLINE1, FLINE1_2, TXTL_CASAS, accesorios[1]); // Interruptor luces exteriores
    PintaAccesorios(FLINE1, FLINE1_3, TXTL_TALLER, accesorios[2]);    // Luces Taller
    PintaAccesorios(FLINE2, FLINE1_1, TXTL_CARRETERA, accesorios[3]); // Soldador
    PintaAccesorios(FLINE2, FLINE1_2, TXTL_SOLDADOR, accesorios[4]);  // TV taller
    PintaAccesorios(FLINE2, FLINE1_3, TXTL_TV_TALLER, accesorios[5]); // Soldador

    screen = false;
  }
  // Recibe los datos desde el módulo MX-RM-5V
  Recibe433();

  // Comunicación serial.
  Recibe_datos();


} // END LOOP

// Limpia la pantalla
void ClearScreen() {
  tft.fillRect(20, 3, LARGO_RECTA + 10, (tft.height()/2), TFT_DARKGREY);
  tft.setCursor(100, (tft.height()/2-5));
  tft.println(F("M1"));

  tft.fillRect(240, 3, LARGO_RECTA + 10, (tft.height()/2), TFT_DARKGREY);
  tft.setCursor(380, (tft.height()/2-5));
  tft.println(F("M2"));
  PrintData("");

}
 