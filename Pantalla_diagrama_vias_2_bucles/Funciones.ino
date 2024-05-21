void Accesorio(char *ac) {
  short n, s, m;
  sscanf(ac, "%d %d %d", &n, &s, &m);


  if (n == 1) {
    switch (s) {
      case 0:
        break;
      case 1:  // EFECTO_SOLDADOR:
        accesorios[3] = m;        
        break;
      case 2:  //LUCES_EXTERIORES:
        accesorios[1] = m;
        break;
      case 3:  // LUCES_CASAS:
        accesorios[2] = m;
        break;
    }
  }
  if (n == 2) {
    switch (s) {
      case 0:
        accesorios[3] = m;
        break;
      case 1:  // EFECTO_SOLDADOR:
        accesorios[0] = m;
        break;
      case 2:  //LUCES_EXTERIORES:
        accesorios[1] = m;
        break;
      case 3:  // LUCES_CASAS:
        accesorios[2] = m;
        break;
    }
  }
  screen = true;
}

void Desvio(char *d) {
  int n, s;
  sscanf(d, "%d %d", &n, &s);
  Serial.print(F("Activado desvio: "));
  Serial.print(n);
  Serial.print(F(" estado: "));
  Serial.println(s);
  switch (n) {
    case LUCES_EXTERIORES:
      accesorios[0] = s;
      screen = true;
      break;
    case LUCES_CASAS:
      accesorios[1] = s;
      screen = true;
      break;
    case LUCES_TALLER:
      accesorios[2] = s;
      screen = true;
      break;
    case LUCES_CARRETERA:
      accesorios[3] = s;
      screen = true;
      break;
    case EF_SOLDADOR_B1:
      accesorios[4] = s;
      screen = true;
      break;
    case EF_TELEVISOR_B1:
      accesorios[5] = s;
      screen = true;
      break;
    //////////////////
    case B1_PRINCIPAL:
      desvios[0] = s;
      screen = true;
      break;
    case B1_COCHERAS:
      desvios[1] = s;
      screen = true;
      break;

  }
}

void Locomotora(char *l) {
  int r, n, s, m;
  sscanf(l, "%d %d %d %d", &r, &n, &s, &m);

  /* Serial.print(F("Registro: "));  Serial.print(r);
    Serial.print(F(" DCC: "));      Serial.print(n);
    Serial.print(F(" Velocidad: ")); Serial.print(s);
    Serial.print(F(" S.marcha: ")); Serial.println(m);*/
  tft.fillRect(185, 80, 140, 70, TFT_DARKGREY);  // Pantalla locomotora);
  tft.setCursor(185, 85);
  tft.print(F("Reg: "));
  tft.print(r);
  tft.setCursor(185, 105);
  tft.print(F("DCC: "));
  tft.print(n);
  tft.setCursor(185, 125);
  tft.print(F("Vel: "));
  tft.print(s);
  tft.setCursor(185, 145);
  tft.print(F("Dir: "));
  if (m == 1) tft.print(F("Avance"));
  else tft.print(F("Atras"));
}

void locomotoraEX(char *lex){
  // Comando `l' Comando de DCCEX -> <l DCC REG SPEED FUNCTION>
  // La velocidad va desde 0 a 255.
  // Desde 0 a 128 va en un sentido avance y de 128 a 255 va en retroceso
  int r, n, s, m;
  
  sscanf(lex, "%d %d %d %d", &r, &n, &s, &m); // DCC REG SPEED FUNCTION
  uint8_t avance = 1;
  uint8_t valor = s;
    if (s >= 1){
      s = s-1;
    } else s = 0;
    if (valor >= 128){ //  Si la velocidad es mayor de 128 el estado es retroceso
      avance = 0;
      if (s >= 128) s = s - 128;
    }
    if (s >= 126) s = 126; // Velocidad no puede ser mayor de 126

  /* // DEBUG
    Serial.print(F("Registro: "));  Serial.print(r);
    Serial.print(F(" DCC: "));      Serial.print(n);
    Serial.print(F(" Velocidad: ")); Serial.print(s);
    Serial.print(F(" S.marcha: ")); Serial.println(m);
  */
  tft.fillRect(185, 80, 140, 70, TFT_DARKGREY);  // Pantalla locomotora);
  tft.setCursor(185, 85);
  tft.print(F("Reg: "));
  tft.print(n);
  tft.setCursor(185, 105);
  tft.print(F("DCC: "));
  tft.print(r);
  tft.setCursor(185, 125);
  tft.print(F("Vel: "));
  tft.print(s);
  tft.setCursor(185, 145);
  tft.print(F("Dir: "));
  if (avance == 1) tft.print(F("Avance"));
  else tft.print(F("Atras"));
}

void CheckSensores(char *s, bool low, bool serial){
  int8_t n; // Número de id del sensor
  sscanf(s, "%d0", &n);
  if (low) { 
    sensores[n] = true;
    if (!serial){
      Serial.print(F("<q"));
      Serial.print(n);
      Serial.println(F(">"));  
    }
  } else {
    sensores[n] = false;
    if (!serial){
      Serial.print(F("<Q"));
      Serial.print(n);
      Serial.println(F(">"));  
    }
  }
  screen = true; 
}
