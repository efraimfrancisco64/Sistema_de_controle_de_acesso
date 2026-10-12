## README.md

```markdown
# 🔐 Access Control System — ESP32

Sistema de controle de acesso baseado em PIN, desenvolvido com **ESP32** e simulado no **Wokwi**.

## Como funciona

- O utilizador insere um PIN de 4 dígitos através de um **Keypad 4x4**
- Ao pressionar `#`, o sistema valida o PIN:
  - ✅ **PIN correto** → LED verde acende + 2 bips
  - ❌ **PIN incorreto** → LED vermelho acende + 1 bip
- A tecla `*` limpa a entrada

## Componentes

| Componente | Função |
|---|---|
| ESP32 DevKit | Microcontrolador |
| Keypad 4x4 | Entrada de PIN |
| LED Verde | Feedback de sucesso |
| LED Vermelho | Feedback de erro |
| Buzzer Passivo | Feedback sonoro |

## Tecnologias

- **Framework:** Arduino (ESP32)
- **Simulação:** [Wokwi](https://wokwi.com)
- **IDE:** VSCode + PlatformIO
- **Bibliotecas:** Keypad (Mark Stanley)

## Estrutura

```
├── src/
│   └── sketch.ino          ← Código principal
├── platformio.ini          ← Configuração do projeto
├── wokwi.toml              ← Configuração do Wokwi
└── diagram.json            ← Circuito
```

## Como rodar

1. Clonar o repositório
2. Abrir no VSCode com a extensão **PlatformIO**
3. `Ctrl+Shift+P` → **PlatformIO: Build**
4. `Ctrl+Shift+P` → **Wokwi: Start Simulator**
5. Inserir o PIN e pressionar `#`