
// These define's must be placed at the beginning before #include "TimerInterrupt_Generic.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG           0
#define _TIMERINTERRUPT_LOGLEVEL_       0

#include "ESP32TimerInterrupt.h"

// Init ESP32 timer 1
ESP32Timer ITimer1(1);

#define TIMER_INTERVAL_MS             15
#define DEBOUNCE_TIME                 30
#define LED_PIN                       4
#define BUTTON_PIN                    15

volatile unsigned long  lastDebounceTime  = 0;
volatile bool           buttonPressed     = false;
volatile bool           alreadyTriggered  = false;
volatile bool           LampState    = false;
volatile bool           SwitchReset  = true;


void IRAM_ATTR Falling();
void IRAM_ATTR Rising();
void IRAM_ATTR ButtonCheck();
void IRAM_ATTR ToggleLED();


void IRAM_ATTR Rising() {
  unsigned long currentTime  = millis();
  unsigned long TimeDiff;

  TimeDiff = currentTime - lastDebounceTime;

  if (digitalRead(BUTTON_PIN) && (TimeDiff > DEBOUNCE_TIME) ) {
    buttonPressed = false;
    lastDebounceTime = currentTime;
  }
}

void IRAM_ATTR Falling() {
  unsigned long currentTime  = millis();

  if ( !digitalRead(BUTTON_PIN) && (currentTime > lastDebounceTime + DEBOUNCE_TIME)) {
    lastDebounceTime = currentTime;
    buttonPressed = true;
  }
}


void IRAM_ATTR HWCheckButton(void)
{
  if (!alreadyTriggered && buttonPressed)
  {
    alreadyTriggered = true;
    ButtonCheck();
  }
  else if (!buttonPressed)
  {
    // Reset flag when button released to avoid triggered repeatedly
    alreadyTriggered = false;
    ButtonCheck();
  }
}


void IRAM_ATTR ButtonCheck()
{
  boolean SwitchState = (digitalRead(BUTTON_PIN));

  if (!SwitchState && SwitchReset)
  {
    ToggleLED();
    SwitchReset = false;
  }
  else if (SwitchState)
    SwitchReset = true;
}


void IRAM_ATTR ToggleLED()
{
  LampState = !LampState;
  digitalWrite(LED_PIN, LampState);
}


void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), Falling, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), Rising, RISING);

  Serial.begin(115200);
  while (!Serial);

  Serial.print(F("\nStarting ISR_Timer_Switch on ")); Serial.println(ARDUINO_BOARD);
  Serial.println(ESP32_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));
  // Interval in microsecs (us),  ms ==> multiply by 1000
  // Be sure to place this HW Timer well ahead blocking calls, because it needs to be initialized.
  if (ITimer1.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, HWCheckButton)) {
    Serial.print(F("Starting  ITimer1 OK,  from restart - millis() = "));
    Serial.println(millis());
  } else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));
}


void loop()
{
  vTaskDelete(nullptr);
}
