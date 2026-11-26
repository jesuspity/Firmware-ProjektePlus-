// EXEMPLO PUBLICO (sem senhas): os valores de Wi-Fi e MQTT foram trocados por placeholders
// (SENHA_WIFI_1, SENHA_WIFI_2, USUARIO_MQTT, SENHA_MQTT).
// Para compilar com as senhas, copie para tasmota/user_config_override.h e troque os placeholders.
// No build publico (-DPROJEKTE_PUBLIC) os valores de senha ficam vazios de qualquer forma.

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

// ======================================================
// PROJEKTE+ IR EMISSOR - ESP8266
// Base: Tasmota v16.0.0 + perfil oficial FIRMWARE_IR
// Build: pio run -e tasmota-ir-projekte
// Revisão Projekte+: P1 (2026-11-12)
// ======================================================
//
// Padrões de fábrica (troque antes de compilar, se for o caso):
//   STORE_ID   -> loja/unidade        padrão: "LojaXXX"
//   DEVICE_ID  -> nome do dispositivo padrão: "XXXX_GWXX_XXXX" (ex.: "I007-GW01-FARM")
//   EMPRESA_ID -> grupo da empresa    padrão: "Disp_Sem_Config"
//
// IMPORTANTE: todos os valores abaixo são DEFAULTS. Eles só valem
// em dispositivo novo ou após "Reset 1". Um OTA não altera a
// configuração já gravada no dispositivo.
//
// O perfil FIRMWARE_IR (tasmota_configurations.h) é aplicado DEPOIS
// deste arquivo e já remove sensores, displays, energia, luzes
// endereçáveis, I2C/SPI etc. Aqui ficam só os ajustes Projekte+.
// ======================================================

// #define USE_PROJEKTE_DISCOVERY   // Driver xdrv_98 (HA climate) - desativado

// Build público (sem senhas): compile com -DPROJEKTE_PUBLIC.
// Sem a flag, as senhas abaixo ficam gravadas no firmware (texto puro).
#ifdef PROJEKTE_PUBLIC
  #define PRJ_CRED(valor) ""
#else
  #define PRJ_CRED(valor) valor
#endif


// ======================================================
// 1) IDENTIFICAÇÃO DO DISPOSITIVO
// ======================================================

#define STORE_ID   "LojaXXX"            // Loja/unidade usada no FullTopic MQTT
#define DEVICE_ID  "XXXX_GWXX_XXXX"     // Topic, DeviceName e FriendlyName I007-GW01-FARM
#define EMPRESA_ID "Disp_Sem_Config"    // Grupo da empresa (GroupTopic2); Disp_Sem_Config = sem empresa definida
#define UNIQUE_ID DEVICE_ID "_%06X"     // MqttClient único usando final do MAC

#undef  CODE_IMAGE_STR
#define CODE_IMAGE_STR "Projekte+"      // Aparece como 16.0.0(Projekte+)

#undef  FRIENDLY_NAME
#define FRIENDLY_NAME DEVICE_ID         // FriendlyName1; DeviceName vazio = usa este

// Sem OTA automático para o build oficial (que não tem TLS nem esta config)
#undef  OTA_URL
#define OTA_URL ""


// ======================================================
// 2) HARDWARE (antes no USER_BACKLOG: Template + Module 0)
// ======================================================
// GPIO0 = Button1 (32) | GPIO4 = IRsend (1056) | GPIO5 = IRrecv (1088)
// GPIO13 = LedLink (576)

#undef  USER_TEMPLATE
#define USER_TEMPLATE "{\"NAME\":\"IR-Projekte+\",\"GPIO\":[32,1,1,1,1056,1088,1,1,1,576,1,1,1,1],\"FLAG\":0,\"BASE\":18}"
#undef  MODULE
#define MODULE USER_MODULE
#undef  FALLBACK_MODULE
#define FALLBACK_MODULE USER_MODULE


// ======================================================
// 3) WI-FI
// ======================================================
// Fonte única: estes defines. (O backlog antigo gravava outra rede,
// "ADMINISTRATIVO", e conflitava; os dispositivos em campo usam estas.)

#undef  STA_SSID1
#define STA_SSID1 "Ganza_2G"
#undef  STA_PASS1
#define STA_PASS1 PRJ_CRED("SENHA_WIFI_1")
#undef  STA_SSID2
#define STA_SSID2 "projekte"
#undef  STA_PASS2
#define STA_PASS2 PRJ_CRED("SENHA_WIFI_2")


// ======================================================
// 4) MQTT + TLS
// ======================================================

#undef  MQTT_HOST
#define MQTT_HOST "mqtt.projekteplus.com"
#undef  MQTT_PORT
#define MQTT_PORT 8883
#undef  MQTT_USER
#define MQTT_USER PRJ_CRED("USUARIO_MQTT")
#undef  MQTT_PASS
#define MQTT_PASS PRJ_CRED("SENHA_MQTT")

#undef  MQTT_TOPIC
#define MQTT_TOPIC DEVICE_ID
#undef  MQTT_FULLTOPIC
#define MQTT_FULLTOPIC "PROJEKTEPLUS/" STORE_ID "/%topic%/%prefix%/"
#undef  MQTT_GRPTOPIC
#define MQTT_GRPTOPIC "tasmotas"        // GroupTopic1
#undef  MQTT_CLIENT_ID
#define MQTT_CLIENT_ID UNIQUE_ID

// O tasmota-minimal (passo intermediário de OTA) não tem lib_ssl
#if !defined(USE_MQTT_TLS) && !defined(FIRMWARE_MINIMAL)
#define USE_MQTT_TLS                    // TLS (+34k flash); valida pela CA Let's Encrypt embutida
#endif
#undef  MQTT_TLS_ENABLED
#define MQTT_TLS_ENABLED true           // SetOption103 1 (SetOption132 fica 0 = CA)


// ======================================================
// 5) DEFAULTS DE RUNTIME (antes no USER_BACKLOG)
// ======================================================

#undef  APP_TIMEZONE
#define APP_TIMEZONE -3                 // Timezone -3 (BRT)
#undef  TELE_PERIOD
#define TELE_PERIOD 300                 // TelePeriod 300
#undef  APP_DISABLE_POWERCYCLE
#define APP_DISABLE_POWERCYCLE true     // SetOption65 1 - sem reset por ciclos de energia
#undef  BOOT_LOOP_OFFSET
#define BOOT_LOOP_OFFSET 0              // SetOption36 0 - sem restauração em boot loop
#undef  IR_DATA_RADIX
#define IR_DATA_RADIX true              // SetOption29 1 - IrReceived em decimal
#undef  IR_ADD_RAW_DATA
#define IR_ADD_RAW_DATA true            // SetOption58 1 - inclui RawData
// SetOption38 6, SetOption44 25, SetOption4 0, SetOption147 0 = já são os padrões.


// ======================================================
// 6) RECURSOS MANTIDOS
// ======================================================
// Seções 6 e 7 não se aplicam ao tasmota-minimal (passo intermediário
// de OTA), que é compilado sem as bibliotecas IR/SSL.
#ifndef FIRMWARE_MINIMAL

#ifndef USE_IR_REMOTE
#define USE_IR_REMOTE
#endif
#ifndef USE_IR_REMOTE_FULL
#define USE_IR_REMOTE_FULL              // Todos os protocolos IRremoteESP8266
#endif

#undef  USE_DISCOVERY                   // mDNS (não usado)
#undef  USE_HOME_ASSISTANT              // Substituído pelo Tasmota Discovery
#ifndef USE_TASMOTA_DISCOVERY
#define USE_TASMOTA_DISCOVERY
#endif

#ifndef USE_RULES
#define USE_RULES
#endif
#undef  USE_EXPRESSION
#undef  SUPPORT_IF_STATEMENT
#undef  USE_SCRIPT                      // Script desligado (Rules ligado)

#ifndef USE_WEBSERVER
#define USE_WEBSERVER
#endif


// ======================================================
// 7) RECURSOS REMOVIDOS (além do perfil FIRMWARE_IR)
// ======================================================

// Integrações / protocolos não usados
#undef USE_DOMOTICZ
#undef USE_KNX
#undef USE_KNX_WEB_MENU
#undef USE_CUSTOM
#undef USE_ENHANCED_GUI_WIFI_SCAN
#undef USE_WEBSEND_RESPONSE
#undef USE_ARDUINO_OTA
#undef USE_PING
#undef USE_DEVICE_GROUPS
#undef USE_DEVICE_GROUPS_SEND

// Timers e cálculo de nascer/pôr do sol (Timers desligados = sunrise inútil)
#undef USE_TIMERS
#undef USE_TIMERS_WEB
#undef USE_SUNRISE
#undef USE_SCRIPT_SUB_COMMAND
#undef USE_SCRIPT_WEB_DISPLAY

// Luzes / dimmers - o hardware só tem LedLink (que não depende disto)
#undef USE_LIGHT
#undef USE_LIGHT_PALETTE
#undef USE_LIGHT_VIRTUAL_CT
#undef USE_WS2812

// Filesystem
#undef USE_UFILESYS
#undef USE_SDCARD
#undef GUI_TRASH_FILE
#undef GUI_EDIT_FILE

// Barramentos e sensores (o FIRMWARE_IR já remove a maioria)
#undef USE_I2C
#undef USE_SPI
#undef USE_DS18x20
#undef USE_DHT
#undef USE_ENERGY_SENSOR
#undef USE_RC_SWITCH
#undef USE_TUYA_MCU
#undef USE_SHUTTER
#undef USE_MODBUS_BRIDGE
#undef USE_MODBUS_BRIDGE_TCP
#undef USE_TASMOTA_CLIENT
#undef USE_DISPLAY

#endif  // FIRMWARE_MINIMAL


// ======================================================
// 8) USER_BACKLOG - só o que não tem #define nativo
// ======================================================
// Executa uma vez no primeiro boot / após Reset 1.

#undef USER_BACKLOG
#define USER_BACKLOG \
  "GroupTopic2 " EMPRESA_ID "; " \
  "GroupTopic3 " STORE_ID "; " \
  "GroupTopic4 IR; " \
  "GroupTopic5 " STORE_ID "_IR"

#endif  // _USER_CONFIG_OVERRIDE_H_
