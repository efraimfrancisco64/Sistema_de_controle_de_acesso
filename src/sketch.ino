#include <Arduino.h>
#include <Keypad.h>

// Definição do tamanho do teclado e pinos
#define ROWS_NUM 4
#define COLS_NUM 4
#define LED_VERDE 25
#define LED_VERMELHO 26
#define BUZZER 27
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

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
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
      Serial.println("Sistema desbloqueado");
    }
    else
    {
      Serial.println("Sistema bloqueado. Aguarde 30 segundos.");
      delay(5000);
      return;
    }
  }
  // Verifica se uma tecla foi pressionada
  if (tecla)
  {
    Serial.print("Tecla: ");
    Serial.println(tecla);

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
      Serial.println("Acesso Permitido");
      digitalWrite(LED_VERDE, HIGH);
      delay(200);
      digitalWrite(LED_VERDE, LOW);
      tentativas = 0; // Reset tentativas após sucesso
    }
    else if (PIN_DIGITADO != PIN_CORRETO)
    {
      Serial.println("Acesso Negado");
      digitalWrite(LED_VERMELHO, HIGH);
      delay(200);
      digitalWrite(LED_VERMELHO, LOW);
      tentativas++;
      if (tentativas >= 3)
      {
        bloqueio = true;
        tempoBloqueio = millis();
        Serial.println("Sistema bloqueado por 30 segundos devido a 3 tentativas incorretas.");
      }
    }
    PIN_DIGITADO = "";
  }
  // Verifica se a tecla pressionada é '*' para limpar o PIN digitado
  else if (tecla == '*')
  {
    Serial.println("Digite o PIN novamente");
    PIN_DIGITADO = "";
  }
}