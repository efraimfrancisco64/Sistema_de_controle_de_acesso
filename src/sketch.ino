#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Definição do tamanho do teclado e pinos
#define ROWS_NUM 4
#define COLS_NUM 4
#define LED_VERDE 25
#define LED_VERMELHO 26
#define BUZZER 27
#define RELAY 23
LiquidCrystal_I2C LCD(0x27, 16, 2); // Endereço I2C do LCD e tamanho (16 colunas, 2 linhas)

// Definição do PIN correto e variáveis de controle
const String PIN_CORRETO = "1234";
String PIN_DIGITADO = "";
int tentativas = 0;
bool bloqueio = false;
unsigned long tempoBloqueio = 0; // 10 segundos
// Definição do layout do teclado
char Key[ROWS_NUM][COLS_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
// Definição dos pinos do teclado
byte pinROWS[ROWS_NUM] = {19, 18, 5, 17};
byte pinCOLS[COLS_NUM] = {16, 4, 0, 2};
// Criação do objeto Keypad
Keypad keypad = Keypad(makeKeymap(Key), pinROWS, pinCOLS, ROWS_NUM, COLS_NUM);
// Função de configuração inicial
void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Teclado Ligado com sucesso");

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Digite o PIN:");
  LCD.setCursor(0, 1);
  LCD.print("> __________");
}
// Função principal do loop
void loop()
{
  char tecla = keypad.getKey();
  // Validar se o sistema está bloqueado e se o tempo de bloqueio expirou
  if (bloqueio == true)
  {
    if (millis() - tempoBloqueio >= 30000)
    {
      bloqueio = false;
      tentativas = 0;
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.println("Desbloqueado");
      delay(1000);
      tone(BUZZER, 1000, 300);
      noTone(BUZZER);
    }
    else
    {
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.println("Bloqueado");
      digitalWrite(RELAY, HIGH);
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.println("Aguarde por 30 segundos.");
      delay(100000);
      return;
    }
  }
  // Verifica se uma tecla foi pressionada
  if (tecla)
  {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.println(tecla);

    if (tecla >= '0' && tecla <= '9')
    {
      PIN_DIGITADO += tecla;
    }
  }
  // Verifica se a tecla pressionada é '#' para validar o PIN
  if (tecla == '#')
  {
    // Verifica se o PIN digitado é igual ao PIN correto para ser validado
    if (PIN_DIGITADO == PIN_CORRETO)
    {
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.println("Acesso Permitido");
      digitalWrite(LED_VERDE, HIGH);
      delay(200);
      digitalWrite(LED_VERDE, LOW);
      tentativas = 0; // Reset tentativas após sucesso
      tone(BUZZER, 1000, 100);
      delay(100);
      tone(BUZZER, 1000, 100);
      delay(100);
      noTone(BUZZER);
      digitalWrite(RELAY, LOW);  // Fecha o relay → "desbloqueia"
      delay(1000);               // Mantém aberto 1 segundo
      digitalWrite(RELAY, HIGH); // Abre o relay → "bloqueia" de novo
    }
    else if (PIN_DIGITADO != PIN_CORRETO)
    {
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.println("Acesso Negado");
      tone(BUZZER, 500, 300);
      delay(100);
      noTone(BUZZER);
      digitalWrite(LED_VERMELHO, HIGH);
      delay(200);
      digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(RELAY, HIGH);
      tentativas++;
      if (tentativas >= 3)
      {
        bloqueio = true;
        tempoBloqueio = millis();
        tone(BUZZER, 200, 1000);
        noTone(BUZZER);
        digitalWrite(RELAY, HIGH);
      }
    }
    PIN_DIGITADO = "";
  }
  // Verifica se a tecla pressionada é '*' para limpar o PIN digitado
  else if (tecla == '*')
  {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.println("Digite novamente");
    PIN_DIGITADO = "";
  }
}