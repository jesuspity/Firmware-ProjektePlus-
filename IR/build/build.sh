#!/usr/bin/env bash
# Compila o firmware Projekte+ IR e copia os binários para projekte/firmware/<versao>
# Uso: projekte/build.sh [versao]      ex.: projekte/build.sh v16.0.0-P2
set -euo pipefail
cd "$(dirname "$0")/.."
VER="${1:-v16.0.0-P1}"
OUT="projekte/firmware/$VER"

pio run -e tasmota-ir-projekte-4M   # recomendado (layout 4 MB, com senhas: privado)
pio run -e tasmota-ir-projekte-4M-public   # sem senhas: vai para o repositório público
pio run -e tasmota-ir-projekte      # layout 1 MB (legado)
pio run -e tasmota-minimal

mkdir -p "$OUT"
cp build_output/firmware/tasmota-ir-projekte-4M.bin \
   build_output/firmware/tasmota-ir-projekte-4M.bin.gz \
   build_output/firmware/tasmota-ir-projekte.bin \
   build_output/firmware/tasmota-ir-projekte.bin.gz \
   build_output/firmware/tasmota-minimal.bin.gz "$OUT/"
(cd "$OUT" && shasum -a 256 *.bin *.gz > SHA256SUMS)
ls -la "$OUT"

# Build público (sem senhas): é o que vai para o repositório público
mkdir -p "$OUT/publico"
cp build_output/firmware/tasmota-ir-projekte-4M-public.bin \
   build_output/firmware/tasmota-ir-projekte-4M-public.bin.gz "$OUT/publico/"
(cd "$OUT/publico" && shasum -a 256 *.bin *.gz > SHA256SUMS)
