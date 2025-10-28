// Define os pinos conectados aos LEDs
int redPin = 10;
int yellowPin = 11;
int greenPin = 12;

// Define o tempo (em milissegundos) que cada luz ficará acesa
const unsigned long redInterval = 6000;    // 6 segundos no vermelho
const unsigned long yellowInterval = 2000; // 2 segundos no amarelo
const unsigned long greenInterval = 4000;  // 4 segundos no verde

// Variável para armazenar o último momento em que o estado foi trocado
unsigned long lastTimeRead = 0;

/*
Define o estado atual do semáforo:
0 = Vermelho
1 = Verde
2 = Amarelo
*/
unsigned int currentState = 0; // Começa com vermelho

// Ponteiro para armazenar qual é o intervalo atual
unsigned long *currentInterval = &redInterval;

// Função de configuração — executada uma única vez ao iniciar o Arduino
void setup()
{
  // Define os pinos dos LEDs como saídas
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

// Função principal — executada repetidamente em loop
void loop()
{
  // Pega o tempo atual desde que o Arduino foi ligado (em milissegundos)
  unsigned long currentMillis = millis();

  // Estado 0 → luz vermelha acesa
  if (currentState == 0)
  {
    digitalWrite(redPin, HIGH);   // Liga o vermelho
    digitalWrite(yellowPin, LOW); // Desliga o amarelo
    digitalWrite(greenPin, LOW);  // Desliga o verde

    // Verifica se já passou o tempo do vermelho
    if (currentMillis - lastTimeRead >= *currentInterval)
    {
      lastTimeRead = currentMillis; // Atualiza o tempo da última troca
      currentState = 1;             // Muda para o estado 1 (verde)
      currentInterval = &greenInterval;
    }
  }

  // Estado 1 → luz verde acesa
  else if (currentState == 1)
  {
    digitalWrite(redPin, LOW);    // Desliga o vermelho
    digitalWrite(yellowPin, LOW); // Desliga o amarelo
    digitalWrite(greenPin, HIGH); // Liga o verde

    // Verifica se já passou o tempo do verde
    if (currentMillis - lastTimeRead >= *currentInterval)
    {
      lastTimeRead = currentMillis; // Atualiza o tempo da última troca
      currentState = 2;             // Muda para o estado 2 (amarelo)
      currentInterval = &yellowInterval;
    }
  }

  // Estado 2 → luz amarela acesa
  else if (currentState == 2)
  {
    digitalWrite(redPin, LOW);     // Desliga o vermelho
    digitalWrite(yellowPin, HIGH); // Liga o amarelo
    digitalWrite(greenPin, LOW);   // Desliga o verde

    // Verifica se já passou o tempo do amarelo
    if (currentMillis - lastTimeRead >= *currentInterval)
    {
      lastTimeRead = currentMillis; // Atualiza o tempo da última troca
      currentState = 0;             // Volta para o estado 0 (vermelho)
      currentInterval = &redInterval;
    }
  }
}
