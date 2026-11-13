# Changelog — Firmware GW

## 0.2.1 (2026-11-12)

- Link OTA fixo: `GW/tasmota32-projekte-gw.bin` neste repositório.
- Mesmo código da v0.2. Muda só o `OTA_URL` padrão e a versão (`16.0.0(Projekte+ GW v0.2.1)`).
- Build público: sem senhas de Wi-Fi nem de MQTT.

## 0.2 (2026-11-05)

- Correção do erro `ZbState Code 81` (ASH "ACK timeout"): tarefa de recepção Zigbee `ZbRx` com ACK imediato.
- Controle de fluxo nRdy, sequência após descarte de quadro e checagem de memória livre na `ZbRx`.
- OTA apontando para a release `projekte-gw-v0.2` do repositório `jesuspity/Tasmota-GW`.
- Bateria automática de 2 h aprovada no gateway de teste.
