#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);
const int sensorHumidade = A0;
const int nivelAgua = A1;
const int ldr = A2;
const int botao = 2;
const int buzzer = 6;
const int servoPin = 5;
const int ledAviso = 7;
Servo bomba;
volatile int estadoLCD = 0;// 0=desligado, 1=boas-vindas, 2=humidade, 3=nivel
int ultimoEstadoLCD = -1; // guarda último estado para comparar
// Variaveis Buzzer
unsigned long ultimoBeep = 0;
const long intervaloBeep = 500;
bool buzzerLigado = false;
// Variveis LED de aviso a piscar
unsigned long ultimoPiscar = 0;
const long intervaloPiscar = 500;
bool ledLigado = false;
// Atualização do LCD
unsigned long ultimoUpdateLCD = 0;
const long intervaloLCD = 1000;

// ######Funções
void regarPlanta() { bomba.write(90); }
void desligarBomba() { bomba.write(0); }
// Ler sensores
int lerHumidade() { return analogRead(sensorHumidade); }
int lerNivel() { return analogRead(nivelAgua); }
int lerLuz() { return analogRead(ldr); }

// Beep do buzzer via millis
void beepBuzzer() 
{
  unsigned long agora = millis();
  if (agora - ultimoBeep >= intervaloBeep)
  {
    ultimoBeep = agora;
    if (buzzerLigado) 
    { 
      noTone(buzzer); 
      buzzerLigado = false; 
    } 
    else
    { 
      tone(buzzer, 1000); 
      buzzerLigado = true; 
    }
  }
}

// LED de aviso a piscar
void piscarLED()
{
  unsigned long agora = millis();
  if (agora - ultimoPiscar >= intervaloPiscar)
  {
    ultimoPiscar = agora;
    ledLigado = !ledLigado;
    digitalWrite(ledAviso, ledLigado);
  }
}

// Função do botão
void trocarLCD() 
{
  estadoLCD++;
  if (estadoLCD > 3) 
    estadoLCD = 0; 
}

void setup() 
{
  Serial.begin(9600);

  lcd.init();
  lcd.noBacklight(); // começa desligado

  pinMode(botao, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(ledAviso, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(botao), trocarLCD, FALLING);

  bomba.attach(servoPin);
  desligarBomba();
}
void atualizarLCD(int humidade, int nivel) 
{
  // Ligar/desligar conforme estado
  if (estadoLCD != ultimoEstadoLCD)
  {
    ultimoEstadoLCD = estadoLCD;
    lcd.clear();
    if (estadoLCD == 0)
      lcd.noBacklight();// desligar LCD
    else
      lcd.backlight();// ligar LCD
  }
  unsigned long agora = millis();
  if (estadoLCD > 0 && agora - ultimoUpdateLCD >= intervaloLCD)
  {
    ultimoUpdateLCD = agora;
    lcd.clear();
    if (estadoLCD == 1) 
    {
      lcd.setCursor(0,0);
      lcd.print("Bem-vindo!");
      lcd.setCursor(0,1);
      lcd.print("Sistema ativo");
    }
    else if (estadoLCD == 2)
    {
      lcd.setCursor(0,0);
      lcd.print("Humidade:");
      lcd.setCursor(0,1);
      lcd.print(humidade);
    }
    else if (estadoLCD == 3)
    {
      lcd.setCursor(0,0);
      lcd.print("Nivel agua:");
      lcd.setCursor(0,1);
      lcd.print(nivel);
    }
  }
}
// Função da bomba de agua
void controlarBomba(int humidade, int nivel) 
{
  if (humidade < 400 && nivel > 200)
    regarPlanta();
  else
    desligarBomba();
}

// ###Função do alerta
void alertaAgua(int nivel, int luz) 
{
  if (nivel < 200)
  {
    if (luz >= 300)
    { // dia
      digitalWrite(ledAviso, LOW);
      beepBuzzer();
    }
    else 
    {// noite
      noTone(buzzer);
      piscarLED();
    }
  } 
  else 
  { // água ok
    noTone(buzzer);
    digitalWrite(ledAviso, LOW);
  }
}

void loop()
{
  int humidade = lerHumidade();
  int nivel = lerNivel();
  int luz = lerLuz();
  // Serial monitor debugging
  Serial.print("Humidade: "); Serial.print(humidade);
  Serial.print(" | Nivel: "); Serial.print(nivel);
  Serial.print(" | Luz: "); Serial.println(luz);
  // Gerir mudança no lcd
  atualizarLCD(humidade, nivel);
  controlarBomba(humidade, nivel);
  alertaAgua(nivel, luz);
  delay(50); // loop rápido, millis controla tudo
}
