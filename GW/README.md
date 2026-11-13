# Firmware GW — Projekte+

Firmware Tasmota **16.0.0** para o gateway Zigbee da Projekte+ (ESP32 + coordenador EFR32/EZSP). Versão atual: **0.2.1**.

Esta versão **não tem senhas**: não tem rede Wi-Fi, usuário nem senha MQTT, nem chaves Zigbee. Essas configurações ficam no próprio gateway.

## Link fixo

Este link sempre aponta para a versão mais recente:

```
https://raw.githubusercontent.com/jesuspity/Firmware-ProjektePlus-/main/GW/tasmota32-projekte-gw.bin
```

O firmware já vem com esse endereço como `OtaUrl` padrão.

| Arquivo | Para que serve |
|---|---|
| `tasmota32-projekte-gw.bin` | Atualização OTA (versão mais recente) |
| `tasmota32-projekte-gw.factory.bin` | Gravação completa pela serial, para gateway novo |
| `SHA256SUMS` | Conferência de integridade |
| `versions/` | Versões anteriores, para voltar atrás |

## Versão atual: 0.2.1

- Código igual à v0.2: correção do erro `ZbState Code 81` (tarefa de recepção Zigbee `ZbRx`). Detalhes em [CHANGELOG.md](CHANGELOG.md).
- Só muda o endereço OTA padrão, a versão do firmware e os padrões de fábrica abaixo.
- Padrões de fábrica, válidos para dispositivo novo ou após reset (um dispositivo já configurado mantém os seus): `STORE_ID` = `LojaXXX`; `DEVICE_ID` = `XXXX_GWXX_XXXX`, usado como Topic, DeviceName e FriendlyName; `EMPRESA_ID` = `Disp_Sem_Config`, usado no FullTopic (`Disp_Sem_Config/LojaXXX/%topic%/%prefix%/`) e no GroupTopic2.
- O endereço do broker MQTT (`mqtt.projekteplus.com`) continua como padrão. Usuário e senha não.
- Ambiente de compilação: `tasmota32-projekte-gw-publico`.

SHA-256 de `tasmota32-projekte-gw.bin`:

```
c3a0fdfe717bd6423f2c6befe247b34bdd58f72d3bfb0eff446821583d2cbcc8
```

## Atualização OTA

No console do gateway:

```
OtaUrl https://raw.githubusercontent.com/jesuspity/Firmware-ProjektePlus-/main/GW/tasmota32-projekte-gw.bin
Upgrade 1
```

Se o `OtaUrl` já estiver com esse endereço, basta `Upgrade 1`. O gateway mantém o Wi-Fi, o MQTT e a rede Zigbee já gravados.

## Primeira instalação (serial)

Para um gateway novo, grave a imagem completa no endereço `0x0`, com um adaptador USB-serial:

```bash
pip install esptool
esptool --chip esp32 --port /dev/cu.usbserial-XXXX --baud 460800 write-flash 0x0 tasmota32-projekte-gw.factory.bin
```

Depois de gravar, o gateway abre uma rede Wi-Fi própria para configuração (`tasmota-XXXX`). Pelo navegador, configure Wi-Fi e MQTT (Configuration > Configure WiFi e Configure MQTT).

## Histórico

Veja [CHANGELOG.md](CHANGELOG.md).
