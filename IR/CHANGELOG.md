# Changelog — Firmware IR

## 16.0.0-P1 — revisão de 2026-11-13 (padrões de fábrica)

- Mesma versão (16.0.0-P1). Build público regerado.
- Padrões de fábrica: `STORE_ID` = `LojaXXX`, `DEVICE_ID` = `XXXX_GWXX_XXXX` e o novo `EMPRESA_ID` = `Disp_Sem_Config` (grupo MQTT `GroupTopic2`, antes com o texto fixo `Indiana`).
- Valem só para dispositivo novo ou depois de `Reset 1`. Um OTA não altera a configuração gravada.

## 16.0.0-P1 (2026-11-12)

- Base: Tasmota v16.0.0, perfil FIRMWARE_IR.
- Layout de flash de 4 MB, com OTA direto pelo `tasmota-ir.bin.gz`.
- Todos os protocolos IR, MQTT com TLS, Tasmota Discovery e Rules.
- Build público: sem senhas de Wi-Fi nem de MQTT.
