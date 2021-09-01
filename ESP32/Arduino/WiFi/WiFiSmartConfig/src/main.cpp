/**
 *  SmartConfig
 *  ArduinoOTA 
 *  mDNS
 *  Só entra em modo smart config se não conseguir entrar nas redes salvas na memoria
 *  
 *
 **/

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Ticker.h>
#include <ESPmDNS.h>

#define LED 13
#define PORTA_SERIAL Serial

Ticker blinker;

void flipLed()
{
  int state = digitalRead(LED);         // get the current state of GPIO1 pin
  digitalWrite(LED, !state);            // set pin to the opposite state
}

void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  PORTA_SERIAL.begin(115200);
  PORTA_SERIAL.println("\r\n\n\nIniciando...");


  WiFi.mode(WIFI_AP_STA);

  WiFi.begin();

  PORTA_SERIAL.print("Esperando conexao WiFi.");

  // da ao ESP 10 segundos pra conectar ao roteador
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000)
  {
    PORTA_SERIAL.write('.');
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    // imprime o IP
    PORTA_SERIAL.println("conectado!");
    PORTA_SERIAL.print("Endereco IP: ");
    PORTA_SERIAL.println(WiFi.localIP());
    // blinker.detach();
    digitalWrite(LED, HIGH);
  }
  else
  {
    PORTA_SERIAL.println("\r\nNao foi possivel conectar, entrando em modo SmartConfig.");

    WiFi.beginSmartConfig();
    blinker.attach(0.1, flipLed);

    //Esperar pelo pacote SmartConfig do telefone
    PORTA_SERIAL.println("Esperando SmartConfig.");
    while (!WiFi.smartConfigDone())
    {
      delay(500);
      PORTA_SERIAL.print(".");
    }

    PORTA_SERIAL.println("");
    PORTA_SERIAL.println("SmartConfig recebido.");
    blinker.attach(0.3, flipLed);

    //Esperando para conectar ao AP
    PORTA_SERIAL.print("Esperando WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      PORTA_SERIAL.print(".");
    }
    PORTA_SERIAL.println();
    PORTA_SERIAL.println(WiFi.localIP());
  }


  if (!MDNS.begin("esp32"))
  {
    PORTA_SERIAL.println("Erro configurando MDNS!");
    PORTA_SERIAL.println("Reiniciando...");
    delay(5000);
    ESP.restart();
  }
  PORTA_SERIAL.println("mDNS Iniciado");
  MDNS.addService("http", "tcp", 80);

  // Porta padrão 3232
  ArduinoOTA.setPort(3232);

  // Hostname padrão esp32-[MAC]
  ArduinoOTA.setHostname("esp32");

  // Sem autenticação por padrão
  // ArduinoOTA.setPassword("admin");

  // A senha pode ser configurada para ser a soma md5 também
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "Programa";
      else // U_SPIFFS
        type = "FS";

      // NOTA: se estiver atualizando o SPIFFS aqui é o lugar de desmontar o sistema de arquivos usando SPIFFS.end()
      PORTA_SERIAL.println("Iniciando update " + type);
    })
    .onEnd([]() {
      PORTA_SERIAL.println("\nFim");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      PORTA_SERIAL.printf("Progresso: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      PORTA_SERIAL.printf("Erro[%u]: ", error);
      if (error == OTA_AUTH_ERROR)
        PORTA_SERIAL.println("Falha na autenticacao");
      else if (error == OTA_BEGIN_ERROR)
        PORTA_SERIAL.println("Falhou em iniciar");
      else if (error == OTA_CONNECT_ERROR)
        PORTA_SERIAL.println("Falhou em conectar");
      else if (error == OTA_RECEIVE_ERROR)
        PORTA_SERIAL.println("Falha no recebimento");
      else if (error == OTA_END_ERROR)
        PORTA_SERIAL.println("Falha na Finalizacao");
    });

  ArduinoOTA.begin();

}
  

void loop() {
  ArduinoOTA.handle();
}