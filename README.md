# Firmware-ProjektePlus-

Firmware Tasmota 16.0.0 usado pela Projekte+ nos gateways Zigbee (GW) e nos emissores e receptores IR (IR). Este repositório guarda só os builds públicos, sem senhas de Wi-Fi nem de MQTT.

- [GW/](GW/README.md): gateway Zigbee (ESP32), versão 0.2.1, com link OTA fixo.
- [IR/](IR/README.md): emissores e receptores IR (ESP8266, 4 MB), versão 16.0.0-P1.

## Arquivos principais do IR

- [IR/config/user_config_override.exemplo.h](IR/config/user_config_override.exemplo.h): configuração de fábrica do IR. As senhas de Wi-Fi e MQTT estão trocadas por placeholders.
- [IR/config/platformio_override.ini](IR/config/platformio_override.ini): ambientes de compilação `tasmota-ir-projekte`, `tasmota-ir-projekte-4M` e `tasmota-ir-projekte-4M-public`.
- [IR/build/build.sh](IR/build/build.sh): compila os ambientes, copia os binários e gera o SHA-256.
- [IR/espelho/sincronizar-ir.sh](IR/espelho/sincronizar-ir.sh): baixa o firmware deste repositório, confere o SHA-256 e copia para a pasta do espelho HTTP.

Esses arquivos são usados pela árvore de código do IR (Tasmota 16.0.0 com a camada da Projekte+). Essa árvore não está neste repositório. O `build.sh` espera a estrutura dela (pasta `projekte/` e `platformio_override.ini` na raiz).

## OTA

- **GW (ESP32):** o firmware já traz o link fixo como `OtaUrl` padrão. Para atualizar, basta `Upgrade 1`.
  ```
  OtaUrl https://raw.githubusercontent.com/jesuspity/Firmware-ProjektePlus-/main/GW/tasmota32-projekte-gw.bin
  ```
- **IR (ESP8266):** o ESP8266 só baixa OTA por HTTP, e o link do GitHub é HTTPS. O IR aponta para um espelho HTTP na rede local, montado com `IR/espelho/sincronizar-ir.sh`:
  ```
  OtaUrl http://<servidor-da-rede>:8080/tasmota-ir.bin.gz
  ```

## Regras

- Só entram builds públicos, sem senhas. Antes de publicar, confira que o `.bin` não tem senhas e que o SHA-256 bate com o `SHA256SUMS`.
- Os padrões de fábrica (`STORE_ID`, `DEVICE_ID` e `EMPRESA_ID`) valem só para dispositivo novo ou depois de `Reset 1`. Um OTA não altera a configuração gravada.
