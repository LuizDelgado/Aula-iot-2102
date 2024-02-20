import paho.mqtt.client as mqtt
import time

#Variaveis de login no broker
broker = "test.mosquitto.org"  # endereço do broker MQTT
port = 1883 #Port de comunicação que é padrão dependendo do tipo (1883 - Publico --- 7500 - Privado)


def on_connect(client, userdata, flgs, rc):
    if(rc==0):
        print('A conexão com o servidor foi bem sucedida')
    else:
        print('A conexão não foi estabelecida. \nCódigo de erro:', rc)

#Criação do cliente
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1)

#Conecta o cliente ao sevidor broker
client.connect(broker, port=port)

#Verifica se a conexão como broker foi bem sucedida e só é utilizada quando o cliente se ancora ao servidor para envio constante de informação
client.on_connect = on_connect


mensagens = ["LIGA_LED_VERMELHO", "DESLIGA_LED_VERMELHO"]

#Aqui se escolhe o topico, a mensagem e utiliza o comando .publish 
topic = "aula_iot_3ano"
message = mensagens[1]
client.publish(topic, message) #Função utilizada para utilizar o cliente como o "publicador" de informações no tópico e mensagem que foi escolhido

#Mantém o looping de conexão com o Broker MQTT
# client.loop_forever()

# Desconecte-se do broker MQTT
client.disconnect()
