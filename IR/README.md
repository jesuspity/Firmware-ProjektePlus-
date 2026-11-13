# Firmware IR — Projekte+

Firmware Tasmota **16.0.0** para os emissores e receptores IR da Projekte+ (ESP8266, flash de 4 MB).

Esta versão **não tem senhas**. Wi-Fi e MQTT são configurados no próprio dispositivo depois da gravação.

## Link fixo

Este link sempre aponta para a versão mais recente:

```
https://raw.githubusercontent.com/jesuspity/Firmware-ProjektePlus-/main/IR/tasmota-ir.bin.gz
```

| Arquivo | Para que serve |
|---|---|
| `tasmota-ir.bin.gz` | Atualização OTA (versão mais recente) |
| `tasmota-ir.bin` | Gravação pela serial, na primeira instalação |
| `SHA256SUMS` | Conferência de integridade |
| `versions/` | Versões anteriores, para voltar atrás |

## Versão atual: 16.0.0-P1

- Layout de 4 MB: a atualização OTA cabe direto, sem passo intermediário.
- Todos os protocolos IR (IRremoteESP8266), inclusive ar-condicionado.
- MQTT com TLS (porta 8883).
- Tasmota Discovery e Rules.
- Sem senhas. Os nomes das redes Wi-Fi de referência (SSID) continuam no código; as senhas não.
- Padrões de fábrica: `STORE_ID` = `LojaXXX`, `DEVICE_ID` = `XXXX_GWXX_XXXX` e grupo `EMPRESA_ID` = `Disp_Sem_Config`. Valem para dispositivo novo ou depois de `Reset 1`; um OTA não altera a configuração já gravada.

SHA-256 de `tasmota-ir.bin.gz`:

```
0d62ffe8eff25cf85ecf11ccbd7bf577d886f507559c5c25a49f8c1582753d97
```

## Primeira instalação (serial)

Precisa de um adaptador USB-serial com nível de 3,3 V e do [esptool](https://github.com/espressif/esptool):

```bash
pip install esptool
esptool --port /dev/cu.usbserial-XXXX --baud 115200 write-flash 0x0 tasmota-ir.bin
```

Para um chip novo, ou para começar do zero, apague antes:

```bash
esptool --port /dev/cu.usbserial-XXXX erase-flash
```

Depois de gravar, o dispositivo abre uma rede Wi-Fi própria para configuração (`tasmota-XXXX`). Pelo navegador, configure:

- Wi-Fi: Configuration > Configure WiFi
- MQTT: Configuration > Configure MQTT (host, porta, usuário e senha)
- Nome: Configuration > Configure Module, ou os comandos `Topic`, `FullTopic` e `FriendlyName`

## Atualização OTA

O ESP8266 só baixa atualização por **HTTP**. O link do GitHub é HTTPS, então não funciona como `OtaUrl` direto. Espelhe o arquivo `tasmota-ir.bin.gz` numa máquina da sua rede local, sirva por HTTP e aponte o dispositivo para ele:

```
OtaUrl http://<servidor-da-rede>:8080/tasmota-ir.bin.gz
Upgrade 1
```

Para conferir o endereço configurado, envie `OtaUrl` sem valor.

## Histórico

Veja [CHANGELOG.md](CHANGELOG.md).
