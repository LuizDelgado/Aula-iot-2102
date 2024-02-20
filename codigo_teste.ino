//Inclusão das bibliotecas
#include <WiFi.h> // inclui a biblioteca do wifi no programa
WiFiClient esp_32_luizinho; // cria o objeto esp_32_n2auco
#include <PubSubClient.h> //inclui a biblioteca do protocolo MQTT
PubSubClient MQTT(esp_32_luizinho); //cria o objeto MQTT usando as definições do cliente wifi esp_32_n2auco para conexão


//Credenciais de acesso ao wifi
const char* ssid = "Luzenho";// nome da rede wifi a conectar
const char* senha = "123456789";//senha da rede wifi a conectar

//------------------------- Credenciais do MQTT ----------------------
const char* endereco_broker = "test.mosquitto.org"; //endereço do broker a conectar
#define client_id "esp32_luizinho" //nome do cliente, obrigatoriamente deve ser UNICO
int porta = 1883; //porta de conexão com o broker a ser utilizada


void setup() {
  
  Serial.begin(115200);//inicia o serial monitor
  inicia_wifi(); //chama a rotina inicia wifi
  inicia_mqtt(); //chama a rotina inicia mqtt
  
  //Definição de saídas
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(27,OUTPUT);
  
  //Sinaleira indicando inicio do código
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  delay(500);
  digitalWrite(12,LOW);
  digitalWrite(27,HIGH);
  delay(500);
  digitalWrite(27,LOW);
  
}

void loop() {
  reconecta_wifi(); //chama a rotina de reconexão do wifi
  reconecta_mqtt(); //chama a rotina de reconexão do mqtt
  MQTT.loop(); // keep alive da função do mqtt
}

void inicia_wifi()
{

  delay(10);//fica um curto tempo em espera
  Serial.println();//pula uma linha em branco
  Serial.println("--------- Iniciando conexao WiFi -----------");
  Serial.print("Tentando conectar na rede: ");Serial.println(ssid);
  Serial.println("Aguarde...");

  reconecta_wifi();//chama a rotina de reconexão do wifi
  
}


void reconecta_wifi()
{

  if(WiFi.status() == WL_CONNECTED)//verifica se está conectado a rede
          return;//se estiver sai da função reconecta wifi

  while(WiFi.status() != WL_CONNECTED)//esnquanto não estiver conectado
  {
    digitalWrite(2,LOW); //apaga o led azul da placa indicando que está sem conexao wifi
    WiFi.begin(ssid,senha);//tenta fazer a conexão
    
    for(byte xis = 0; xis<50; xis++)
      {
        delay(100);
        Serial.print(".");
      }
  }
  digitalWrite(2,HIGH); //acende o led azul da placa indicando que está conectado no wifi
  Serial.println();//pula uma linha
  Serial.println("Conectado com sucesso a rede WiFi !!!");
  Serial.print("IP obtido: ");
  Serial.println(WiFi.localIP());//mostra o ip obtido pelo micrccontrolador
  Serial.print("Endereco MAC: "); 
  Serial.println(WiFi.macAddress());//mostra o endereço mac da placa de rede
          
}


void inicia_mqtt()
{
  Serial.println("-------------------- iniciando MQTT -------------------");

  reconecta_mqtt(); //chama a rotina reconecta mqtt
}

void reconecta_mqtt()
{
  
  while(!MQTT.connected()) //enquanto estiver desconectado
  {

    reconecta_wifi(); //chama a rotina de reconexão do wifi
    
    Serial.print("Tentando conectar ao broker: ");Serial.println(endereco_broker);
    MQTT.setServer(endereco_broker, porta); //tenta conectar ao broker através da porta informada
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
    Serial.println("Aguarde ...");
    delay(2000); //espera 2 segundos

    if(MQTT.connect(client_id))//se conectou
    {
      Serial.println("Conectado ao broker com sucesso !!!");
      MQTT.subscribe("aula_iot_3ano");
      //MQTT.publish(topic, msg);
    }
    else//senão conectou
    {
      Serial.println("Falha de conexao com o broker");
      Serial.println("Havera uma nova tentativa de conexao em 2 segundos");
      delay(2000);//espera 2 segundos
    }

  }
  
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
  
    /* obtem a string do payload recebido */
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
 
    Serial.print(".");
    Serial.println(msg);

    if (msg == "LIGA_LED_VERMELHO"){

        digitalWrite(13, HIGH);
      }

    else if (msg == "DESLIGA_LED_VERMELHO"){
        digitalWrite(13, LOW);
      
    
    }
}