import os
from os.path import join
from dotenv import load_dotenv

# Import env from SCons
Import("env")

# Use the current working directory
dotenv_path = join(env["PROJECT_DIR"], '.env')
load_dotenv(dotenv_path)

# Read environment variables
wifi_ssid = os.getenv('WIFI_SSID')
wifi_password = os.getenv('WIFI_PASSWORD')

mqtt_server = os.getenv('MQTT_SERVER')
mqtt_topic = os.getenv('MQTT_TOPIC')
mqtt_user = os.getenv('MQTT_USER')
mqtt_password = os.getenv('MQTT_PASSWORD')

# Add Build Flags
if wifi_ssid and wifi_password and mqtt_server and mqtt_topic and mqtt_user and mqtt_password:
    print(f'Using WIFI_SSID={wifi_ssid} and WIFI_PASSWORD={wifi_password}')
    print(f'Using MQTT_SERVER={mqtt_server} and MQTT_TOPIC={mqtt_topic}')
    env.Append(
        BUILD_FLAGS=[
            f'-DWIFI_SSID=\\"{wifi_ssid}\\"',
            f'-DWIFI_PASSWORD=\\"{wifi_password}\\"',
            f'-DMQTT_SERVER=\\"{mqtt_server}\\"',
            f'-DMQTT_TOPIC=\\"{mqtt_topic}\\"',
            f'-DMQTT_USER=\\"{mqtt_user}\\"',
            f'-DMQTT_PASSWORD=\\"{mqtt_password}\\"'
        ]
    )
else:
    print('WIFI_SSID or WIFI_PASSWORD or MQTT SETTINGS is not set in .env file')