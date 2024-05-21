
// Recibe datos RF433
void   Recibe433() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    for (i = 0; i < buflen; i++)
    {
      // Serial.print((char)buf[i]);
      b = (char)buf[i];


      if (b == '<') {                   // start of new command
        commandString[0] = 0;
      } else if (b == '>') {              // end of new command
        decodata(commandString, false); // 
      }    else if (strlen(commandString) <  MAX_COMMAND_LENGTH)  // if commandString still has space, append character just read from serial line
        sprintf(commandString, "%s%c", commandString, b); // otherwise, character is ignored (but continue to look for '<' or '>')
    }
    PrintData(commandString);
  }
}

// Recibe datos seriales
void Recibe_datos() {
  memset(commandString, 0, sizeof(commandString));
  while (Serial.available() > 0) {  // while there is data on the serial line
    c = Serial.read();
    if (c == '<')                    // start of new command
      commandString[0] = 0;
    else if (c == '>')               // end of new command
      decodata(commandString, true);
    else if (strlen(commandString) <  MAX_COMMAND_LENGTH)  // if commandString still has space, append character just read from serial line
      sprintf(commandString, "%s%c", commandString, c); // otherwise, character is ignored (but continue to look for '<' or '>')
    PrintData(commandString);
  }

}

// Imprime el comando recibido 
void PrintData(char *com){
    tft.fillRect(0, 280 , 479, 40, TFT_BLUE); // Monitor Serial);
    tft.setCursor(TXT_START_TEXT, 300);
    tft.print(commandString);
}

// Busca el primer caracter que corresponde al comando y lo envía a la 
// función correspondiente.
// char = comando DCC++
// serial = control para los datos seiales. Solo se usa en los sensores para
// evitar retroalimentación del comando.
void decodata(char *com, uint8_t serial) {
  switch (com[0]) {
    case 'p': // Encendido
      if (com[1] == "0") Serial.println(F(" DCC OFF"));
      else if (com[1] == "1") Serial.println(F("DCC ON"));
      break;
    case 'T': // Locomotora
      // Serial.println(F("LOCOMOTORA"));
      Locomotora(com + 1);
      break;
    case 'a': // Accesorios
      // Serial.println(F("ACCESORIO"));
      Accesorio(com + 1);
      break;
    case 'H': // Desvíos
      // Serial.println(F("DESVIO"));
      Desvio(com + 1);
      break;
    case 'Q': // Sensor estado alto
      CheckSensores(com + 1, false, serial);
      // Serial.println(F(" SENSOR ALTO"));
      break;
    case 'q': // Sensor estado bajo
      CheckSensores(com + 1, true, serial);
      // Serial.println(F(" SENSOR BAJO"));
      break;
  }
}
