#define LED_YELLOW 4
#define LED_PLAYER_RED 3
#define LED_PLAYER_BLUE 5

#define BTN_PLAYER_RED 2
#define BTN_PLAYER_BLUE 6

#define TIME_BLINK 300

unsigned long rand_time;

bool is_game_started = false;
bool is_game_finished = false;

void setup() {
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_PLAYER_BLUE, OUTPUT);
  pinMode(LED_PLAYER_RED, OUTPUT);

  pinMode(BTN_PLAYER_BLUE, INPUT_PULLUP);
  pinMode(BTN_PLAYER_RED, INPUT_PULLUP);

  blink_times(LED_YELLOW, 3);

  randomSeed(analogRead(0));
  generate_random();
}

void loop() {
  if (is_game_finished) {
    if (is_game_started) {
      delay(3000);
    }
    lights_off();
    blink_times(LED_YELLOW, 3);
    is_game_finished = false;
    is_game_started = false;
    generate_random();
    return;
  }

  if (!is_game_started && (millis() < rand_time)) {
    if (!digitalRead(BTN_PLAYER_BLUE)) {
      long_blink(LED_PLAYER_RED);      
      blink_times(LED_PLAYER_RED, 2);
      delay(1000);
      is_game_finished = true;
      return;
    }
    if (!digitalRead(BTN_PLAYER_RED)) {
      long_blink(LED_PLAYER_BLUE);       
      blink_times(LED_PLAYER_BLUE, 2);
      delay(1000);
      is_game_finished = true;
      return;
    }
  }

  if (!is_game_started && (millis() >= rand_time)) {
    digitalWrite(LED_YELLOW, HIGH);
    is_game_started = true;
  }

  if (is_game_started && !digitalRead(BTN_PLAYER_BLUE)) {
    is_game_finished = true;
    digitalWrite(LED_PLAYER_BLUE, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    return;
  }

  if (is_game_started && !digitalRead(BTN_PLAYER_RED)) {
    is_game_finished = true;
    digitalWrite(LED_PLAYER_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    return;
  }
}

void lights_off() {
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_PLAYER_BLUE, LOW);
  digitalWrite(LED_PLAYER_RED, LOW);
}

void blink_times(uint8_t pin, unsigned int times) {
  for (int i = 0; i < times; i++) {
    blink(pin);
  }
}

void blink(uint8_t pin) {
  digitalWrite(pin, HIGH);
  delay(TIME_BLINK);
  digitalWrite(pin, LOW);
  delay(TIME_BLINK);
}

void long_blink(uint8_t pin) {
  digitalWrite(pin, HIGH);
  delay(TIME_BLINK * 2);
  digitalWrite(pin, LOW);
  delay(TIME_BLINK);  
}

void generate_random() {
  rand_time = random(800, 3500) + millis();
}