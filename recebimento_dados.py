import paho.mqtt.client as mqtt
import time
# Defina as informações do broker MQTT
broker = "test.mosquitto.org"  # endereço do broker MQTT
port = 1883  # porta do broker MQTT

# Crie um cliente MQTT
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1)

# Defina a função de callback para tratar mensagens recebidas
def on_message(client, userdata, mensagem):
    print(f"Mensagem recebida no tópico: {mensagem.topic} \nMensagem: {mensagem.payload.decode()}")



# Associe a função de callback ao cliente MQTT
client.on_message = on_message

# Conecte-se ao broker MQTT
client.connect(broker, port=port)

# Inscreva-se em um tópico
topic = "aula_iot_3ano"
client.subscribe(topic)

# Inicie o loop de recebimento de mensagens
client.loop_forever()
