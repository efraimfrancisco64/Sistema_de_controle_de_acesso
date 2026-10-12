#include <Arduino.h>
#include <Keypad.h>

#define ROWS_NUM 4
#define COLS_NUM 4

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
}

void loop()
{
  char Key = keypad.getKey();
  if (Key)
  {
    Serial.print("Tecla pressionada: ");
    Serial.println(Key);
  }
}