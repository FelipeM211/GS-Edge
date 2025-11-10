# Monitor de Bem-Estar no Trabalho – ESP32 + HC-SR04 + DHT22 + MQTT

## 📘 Descrição do Projeto
Este projeto simula um **sistema IoT de monitoramento ambiental e segurança ocupacional**, alinhado ao tema **“O Futuro do Trabalho”**.  
Ele utiliza sensores para medir **distância, temperatura e umidade**, acionando alertas visuais e enviando dados em tempo real via **MQTT**, demonstrando como a tecnologia pode melhorar o **bem-estar no ambiente de trabalho**.

---

## 🎯 Objetivo
Criar uma aplicação com ESP32 que monitora condições de proximidade e conforto térmico, alertando sobre riscos e publicando as informações em um servidor MQTT acessível por dashboards IoT.

---

## 🧩 Componentes Utilizados (disponíveis no Wokwi)
| Componente | Função | Pino ESP32 |
|-------------|--------|------------|
| HC-SR04 (ultrassônico) | Medir distância | Trig → 5, Echo → 18 |
| DHT22 | Medir temperatura e umidade | Data → 15 |
| LED vermelho | Alerta de proximidade | 12 |
| LED azul | Alerta de calor | 14 |
| LED verde | Funcionamento normal | 27 |

---

## ⚙️ Funcionamento
- Mede a **distância** de objetos próximos com o **HC-SR04**.  
- Lê **temperatura e umidade** com o **DHT22**.  
- Envia os dados via **MQTT** para o broker público `test.mosquitto.org`.  
- Mostra todas as leituras no **Serial Monitor** a cada 2 segundos.  
- Ações automáticas:
  - **LED vermelho acende** se a distância < 10 cm.  
  - **LED azul pisca** se a temperatura > 30 °C.  
  - **LED verde permanece ligado** durante o funcionamento normal.  

---

## 🌐 Comunicação IoT
- **Protocolo:** MQTT  
- **Servidor:** `test.mosquitto.org`  
- **Porta:** `1883`  
- **Tópico:** `trabalho/futuro/bemestar`  
- **Formato da mensagem publicada (JSON):**
  json
  {
    "distancia": 7.2,
    "temperatura": 28.5,
    "umidade": 61.3
  }
🔌 Esquema de Ligação (resumo)
HC-SR04 → VCC (3.3V), GND, Trig (5), Echo (18)

DHT22 → VCC (3.3V), GND, Data (15)

LEDs:

Vermelho → 12

Azul → 14

Verde → 27
(todos com o cátodo no GND)

🧠 Justificativa e Contexto
O projeto se insere no contexto do Futuro do Trabalho como uma proposta de monitoramento ambiental inteligente, que:

Ajuda a manter ambientes de trabalho seguros e confortáveis;

Promove o bem-estar físico e a produtividade dos profissionais;

Demonstra o uso de IoT como ferramenta para melhoria das condições humanas no trabalho.

▶️ Execução no Wokwi
Acesse https://wokwi.com.

Crie um novo projeto ESP32.

Cole o código completo fornecido.

Substitua o arquivo diagram.json pelo JSON indicado.

Clique em Start Simulation.

Abra o Serial Monitor para ver os valores e status dos LEDs.

🧰 Dependências
Biblioteca DHT sensor library

Biblioteca PubSubClient

Biblioteca WiFi.h (nativa do ESP32)

📡 Possível Expansão
Dashboard IoT para visualização dos dados.

Envio via HTTP para API ou banco de dados.

Sistema de feedback automatizado (notificações ou relatórios).

🔗 Link do Wokwi
https://wokwi.com/projects/447252664581370881
