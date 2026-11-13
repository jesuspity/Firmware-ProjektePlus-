# Changelog — Firmware GW

## 0.2.1 (2026-11-12, recompilado em 2026-11-13)

- Link OTA fixo: `GW/tasmota32-projekte-gw.bin` neste repositório.
- Mesmo código da v0.2. Muda o `OTA_URL` padrão, a versão (`16.0.0(Projekte+ GW v0.2.1)`) e os padrões de fábrica abaixo.
- Padrões de fábrica, válidos para dispositivo novo ou após reset: `STORE_ID` = `LojaXXX`, `DEVICE_ID` = `XXXX_GWXX_XXXX` (Topic, DeviceName e FriendlyName) e `EMPRESA_ID` = `Disp_Sem_Config` (FullTopic `Disp_Sem_Config/LojaXXX/%topic%/%prefix%/` e GroupTopic2).
- Build público: sem senhas de Wi-Fi nem de MQTT.

## 0.2 (2026-11-05)

- Correção do erro `ZbState Code 81` (ASH "ACK timeout"): tarefa de recepção Zigbee `ZbRx` com ACK imediato.
- Controle de fluxo nRdy, sequência após descarte de quadro e checagem de memória livre na `ZbRx`.
- OTA apontando para a release `projekte-gw-v0.2` do repositório `jesuspity/Tasmota-GW`.
- Bateria automática de 2 h aprovada no gateway de teste.
