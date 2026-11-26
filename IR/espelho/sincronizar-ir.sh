#!/usr/bin/env bash
# Espelha o firmware IR público (GitHub) numa pasta servida por HTTP na rede local.
# O ESP8266 só baixa OTA por HTTP; o OtaUrl do dispositivo aponta para este espelho.
# Uso: sincronizar-ir.sh <pasta_do_espelho>
#   ex.: sincronizar-ir.sh ~/espelho-ir
DEST="${1:?uso: $0 <pasta_do_espelho>}"
BASE="https://raw.githubusercontent.com/jesuspity/Firmware-ProjektePlus-/main/IR"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
mkdir -p "$DEST" || exit 1
for f in SHA256SUMS tasmota-ir.bin.gz tasmota-ir.bin; do
  curl -fsSL --retry 3 "$BASE/$f" -o "$TMP/$f" || { echo "falha ao baixar $f"; exit 1; }
done
(cd "$TMP" && shasum -a 256 -c SHA256SUMS) || { echo "SHA-256 não confere: nada foi copiado"; exit 1; }
cp "$TMP/SHA256SUMS" "$TMP/tasmota-ir.bin.gz" "$TMP/tasmota-ir.bin" "$DEST/"
echo "Espelho atualizado: $DEST"
ls -la "$DEST"
