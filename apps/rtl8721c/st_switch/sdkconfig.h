
#ifndef _SDKCONFIG_H_
#define _SDKCONFIG_H_

#define CONFIG_STDK_MQTT_RECV_CYCLE		100
#ifdef CONFIG_SAMSUNG_BUILD_ENG
#define CONFIG_STDK_IOT_CORE_LOG_LEVEL_INFO
#define CONFIG_STDK_IOT_CORE_LOG_LEVEL_WARN
#define CONFIG_STDK_IOT_CORE_LOG_LEVEL_ERROR
#else
#define CONFIG_STDK_IOT_CORE_LOG_LEVEL_ERROR
#define CONFIG_STDK_IOT_CORE_LOG_LEVEL_WARN
#endif
#define CONFIG_STDK_IOT_CORE_CRYPTO_SUPPORT_ED25519
#define CONFIG_STDK_IOT_CORE_SECURITY_BACKEND_SOFTWARE

#define CONFIG_STDK_IOT_CORE_NETWORK_TLS 1


#define CONFIG_STDK_MQTT_CLEAN_SESSION 1
#define CONFIG_MQTT_RECV_BUFFER 2048
#define CONFIG_STDK_MQTT_PING_TIMEOUT 3000
#define CONFIG_DEFAULT_MQTT_SECURITY 0
#define CONFIG_STDK_MQTT_RECV_BUFFER 2048
#define CONFIG_STDK_MQTT_CLIENT_ID "stdk_sample"
//#define CONFIG_MQTT_USERNAME "espressif"
#define CONFIG_DEFAULT_MQTT_PUB_QOS 1
#define CONFIG_STDK_MQTT_DYNAMIC_BUFFER 1
#define CONFIG_STDK_MQTT_NO_TLS 1
#define CONFIG_MQTT_PORT 1883
#define CONFIG_MQTT_BROKER "mosquitto.org"
#define CONFIG_STDK_MQTT_PASSWORD "admin"
#define CONFIG_MQTT_PUBLISH_INTERVAL 0
#define CONFIG_STDK_MQTT_SEND_BUFFER 2048
//#define CONFIG_MQTT_PUB_TOPIC "/espressif/pub"
#define CONFIG_STDK_DEFAULT_MQTT_SESSION 1
#define CONFIG_STDK_MQTT_SEND_CYCLE 30000
#define CONFIG_DEFAULT_MQTT_VERSION 3
#define CONFIG_DEFAULT_MQTT_SUB_QOS 1
#define CONFIG_MQTT_KEEP_ALIVE 30
#define CONFIG_STDK_MQTT_PUBLISH_RETRY 3
#define CONFIG_MQTT_USING_IBM 1
#define CONFIG_STDK_DEFAULT_MQTT_VERSION 3
#define CONFIG_STDK_MQTT_RECV_CYCLE 100
#define CONFIG_MQTT_SEND_CYCLE 30000
#define CONFIG_MQTT_SEND_BUFFER 2048
#define CONFIG_STDK_MQTT_V3_1 1
#define CONFIG_STDK_DEFAULT_MQTT_SECURITY 0
#define CONFIG_DEFAULT_MQTT_SESSION 1
//#define CONFIG_MQTT_CLIENT_ID "espressif_sample"
#define CONFIG_STDK_MQTT_USERNAME "stdk"
#define CONFIG_MQTT_PAYLOAD_BUFFER 1460
#define CONFIG_MQTT_PING_TIMEOUT 3000
#define CONFIG_MQTT_RECV_CYCLE 100
#define CONFIG_MQTT_PASSWORD "admin"
//#define CONFIG_MQTT_SUB_TOPIC "/espressif/sub"
#define CONFIG_STDK_MQTT_KEEP_ALIVE 30




#define CONFIG_MBEDTLS_XTEA_C 1
#define CONFIG_MBEDTLS_KEY_EXCHANGE_RSA 1
#define CONFIG_MBEDTLS_AES_C 1
#define CONFIG_MBEDTLS_RSA_BITLEN_MIN 2048
#define CONFIG_MBEDTLS_SSL_PROTO_TLS1 1
#define CONFIG_MBEDTLS_ECDH_C 1
#define CONFIG_MBEDTLS_PEM_WRITE_C 1
#define CONFIG_MBEDTLS_SSL_OUT_CONTENT_LEN 4096
#define CONFIG_STDK_IOT_CORE_USE_MBEDTLS 1
#define CONFIG_SSL_USING_MBEDTLS 1
#define CONFIG_MBEDTLS_ECP_DP_CURVE25519_ENABLED 1
#define CONFIG_MBEDTLS_ECP_C 1
#define CONFIG_MBEDTLS_RC4_DISABLED 1
#define CONFIG_MBEDTLS_X509_CRL_PARSE_C 1
#define CONFIG_LIBSODIUM_USE_MBEDTLS_SHA 1
#define CONFIG_MBEDTLS_RSA_BITLEN_2048 1
#define CONFIG_MBEDTLS_SSL_PROTO_TLS1_1 1
#define CONFIG_MBEDTLS_X509_CSR_PARSE_C 1
#define CONFIG_MBEDTLS_PEM_PARSE_C 1
#define CONFIG_MBEDTLS_SSL_PROTO_TLS1_2 1
#define CONFIG_MBEDTLS_TLS_ENABLED 1
#define CONFIG_MBEDTLS_TLS_CLIENT 1
#define CONFIG_MBEDTLS_ECP_DP_SECP256R1_ENABLED 1
#define CONFIG_MBEDTLS_HAVE_TIME 1
#define CONFIG_MBEDTLS_TLS_CLIENT_ONLY 1
#define CONFIG_MBEDTLS_SSL_IN_CONTENT_LEN 6144
#define CONFIG_STDK_MQTT_USE_SSL

#endif
