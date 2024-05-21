// Cambia el color de las rutas / Dibuja el plano
// Secciones 1, 4, 6, 7, 8, 9, 10, 11

void Seccion(int posx, int posy, int H1, int W1, uint8_t estado) {
  tft.fillRect(posx, posy, H1, W1, GetColor(estado)); // VIA NORTE BUCLE RETORNO 1
}

// MODULO 1
void Bucle_1(uint8_t estado) { // INTERIOR BUCLE RETORNO 1

    tft.fillRect(BN_X_START, BN_Y_START, BN_RECTA_CORTA, ANCHO_RECTA, GetColor(estado)); // INFERIOR

    for (int i = 0; i < 8; i++) tft.drawLine(30 + i, 50, 60 + i, BN_Y_START, GetColor(estado)); // Linea inclinada con 8px de ancho
    
    tft.fillRect(30, 50, ANCHO_RECTA, 40, GetColor(estado));  // LATERAL IZQUIERDO
    
    for (int i = 0; i < 8; i++) tft.drawLine(30 + i, 90, 55 + i, 110, GetColor(estado)); // Linea inclinada con 8px de ancho
    
    tft.fillRect(55, 104, BN_RECTA_CORTA, ANCHO_RECTA, GetColor(estado)); // INFERIOR
    
    for (int i = 0; i < 8; i++) tft.drawLine(140 + i, 110, 160 + i, 90, GetColor(estado)); // Linea inclinada con 8px de ancho
}

void SalidaBucle1(uint8_t estado) { //  SALIDA BUCLE RETORNO 1 SUR
  
  tft.fillRect(160, 70, ANCHO_RECTA, 20, GetColor(estado));

  for (int i = 0; i < 8; i++) tft.drawLine(160 + i, 70, 180 + i, 50, GetColor(estado)); // Linea inclinada con 8px de ancho

  tft.fillRect(180, 50, 60, ANCHO_RECTA, GetColor(estado)); // VIA SUR
}

void Seccion14(uint8_t estado) { // BUCLE RETORNO

  tft.fillRect(60, 60, 60, ANCHO_APEAD, GetColor(estado)); // Taller 2
  tft.fillRect(60, 75, 70, ANCHO_APEAD, GetColor(estado)); // Taller 
}

void DesvioCocherasPrincipal(uint16_t color1, uint16_t color2) { // B1_COCHERAS_CON_PRINCIPAL    
    
    tft.fillRect(140 , 30, LARGO_DESVIO, ANCHO_RECTA, color2);
    
    for (int i = 0; i < 10; i++) tft.drawLine(140 + i, 60, 155 + i, 38, color1); // Linea inclinada con 8px de ancho
}

void DesvioCocheras(uint16_t color1, uint16_t color2) { // B1_COCHERAS
    
  tft.fillRect(120 , 60, LARGO_DESVIO, ANCHO_APEAD, color2);
  for (int i = 0; i < 10; i++) tft.drawLine(120 + i, 80 , 140 + i, 60, color1); // Linea inclinada con 8px de ancho
}


// MODULO 2
void Bucle_2(uint8_t estado) {  // INTERIOR BUCLE 2

  for (int i = 0; i < 8; i++) tft.drawLine(410 + i, BN_Y_START, 440 + i, 50, GetColor(estado)); // Linea inclinada con 8px de ancho
  tft.fillRect(440, 50, ANCHO_RECTA, 40, GetColor(estado)); // LATERAL DERECHO
  for (int i = 0; i < 8; i++) tft.drawLine(420 + i, 110, 440 + i, 90, GetColor(estado)); // Linea inclinada con 8px de ancho
  tft.fillRect(330, 104, BN_RECTA_CORTA, ANCHO_RECTA, GetColor(estado)); // INFERIOR
  for (int i = 0; i < 8; i++) tft.drawLine(330 + i, 110, 310 + i, 90, GetColor(estado)); // Linea inclinada con 8px de ancho
}  
  
void SalidaBucle2(uint8_t estado) { //  SALIDA BUCLE RETORNO 1 SUR

  tft.fillRect(310, 70, ANCHO_RECTA, 20, GetColor(estado));
    
  for (int i = 0; i < 8; i++) tft.drawLine(310 + i, 70, 290 + i, 50, GetColor(estado)); // Linea inclinada con 8px de ancho
    
  tft.fillRect(240, 50, 60, ANCHO_RECTA, GetColor(estado)); // VIA SUR
}

// Accesorios
void PintaAccesorios(int curX, int curY, String text, uint8_t estado) {

  int r = 4;
  tft.setCursor(curX, curY);
  tft.println(text);
  tft.drawCircle((curX - 10), (curY - 5), 4, TFT_WHITE);
  if (estado) {
    tft.fillCircle((curX - 10), (curY - 5), (r - 1), TFT_GREEN);
  } else {
    tft.fillCircle((curX - 10), (curY - 5), (r - 1), TFT_RED);
  }
}

uint16_t GetColor(uint8_t estado){
  if (estado) return COLOR_PISTA;
  else return COLOR_OCUPADO;
}