#include <Arduino.h>
#include <Keypad.h>

#define ROWS_NUM 4
#define COLS_NUM 4
#define LED_VERDE 25
#define LED_VERMELHO 26
#define BUZZER 27
const String PIN_CORRETO = "1234";
String PIN_DIGITADO = "";

char Key[ROWS_NUM][COLS_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte pinROWS[ROWS_NUM] = {19, 18, 5, 17};
byte pinCOLS[COLS_NUM] = {16, 4, 0, 2};

Keypad keypad = Keypad(makeKeymap(Key), pinROWS, pinCOLS, ROWS_NUM, COLS_NUM);

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Teclado Ligado com sucesso");

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
}

void loop()
{
  char tecla = keypad.getKey();
  if (tecla)
  {
    Serial.print("Tecla: ");
    Serial.println(tecla);

    if (tecla >= '0' && tecla <= '9')
    {
      PIN_DIGITADO += tecla;
    }
  }
  if (tecla == '#')
  {
    if (PIN_DIGITADO == PIN_CORRETO)
    {
      Serial.println("Acesso Permitido");
      digitalWrite(LED_VERDE, HIGH);
      delay(200);
      digitalWrite(LED_VERDE, LOW);
    }
    else if (PIN_DIGITADO != PIN_CORRETO)
    {
      Serial.println("Acesso Negado");
      digitalWrite(LED_VERMELHO, HIGH);
      delay(200);
      digitalWrite(LED_VERMELHO, LOW);
    }
  }
  else if (tecla == '*')
  {
    Serial.println("Digite o PIN novamente");
  }
}