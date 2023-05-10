const int pins_led[] = {5, 18, 17, 19};
const int pins_button[] = {34, 35, 32, 33};
String salvarSequencia = "";
String listaVerifica = "";
int sequencia[4] = {};
int button = 25;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(pins_led[i], OUTPUT);
    pinMode(pins_button[i], INPUT_PULLUP);
  }
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

void loop() {
  if (digitalRead(button) == HIGH) {
    game();
  }
}

void randomLed() {
  for (int i = 0; i < 4; i++) {
    sequencia[i] = random(0, 4);
  }
  ascendeLed();
}

void ascendeLed() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins_led[sequencia[i]], HIGH);
    delay(500);
    digitalWrite(pins_led[sequencia[i]], LOW);
    delay(500);
  }
  salvarSequencia = ""; // Limpa a sequência salva anteriormente
  for (int i = 0; i < 4; i++) {
    salvarSequencia += String(pins_led[sequencia[i]]);
  }
}

void game() {
  randomLed();
  verifica();
}

void AdicionandoListaButton() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(pins_button[i]) == HIGH) {
      listaVerifica += String(pins_led[i]);
      digitalWrite(pins_led[i], HIGH);
      delay(500);
      digitalWrite(pins_led[i], LOW);
      Serial.println(listaVerifica);
      while (digitalRead(pins_button[i]) == HIGH);
      break;
    }
  }
}

void verifica() {
  listaVerifica = "";
  while (true) {
    AdicionandoListaButton();
    if (listaVerifica.length() >= salvarSequencia.length()) {
      break;
    }
  }
  if (listaVerifica != salvarSequencia) {
    Serial.println("Fim do jogo. Você perdeu! Aperte o botão a direita para reiniciar o game.");
  } else {
    Serial.println("Você acertou, next...");
    delay(2000);
    game();
  }
}




