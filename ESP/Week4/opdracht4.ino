// These define's must be placed at the beginning before #include "TimerInterrupt_Generic.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG           0
#define _TIMERINTERRUPT_LOGLEVEL_       0

#include "ESP32TimerInterrupt.h"

// Init ESP32 timer 1
ESP32Timer ITimer1(1);

#define TIMER_INTERVAL_MS             18
#define DEBOUNCE_TIME                 30
#define LED_PIN                       4
#define BUTTON1_PIN                   19
#define BUTTON2_PIN                   15 

volatile unsigned long  lastDebounceTime_button1  = 0;
volatile unsigned long  lastDebounceTime_button2  = 0;
volatile bool           SwitchReset_button1  = true;
volatile bool           SwitchReset_button2  = true;

volatile bool           buttonPressed_button1     = false;
volatile bool           alreadyTriggered_button1  = false;
volatile bool           buttonPressed_button2     = false;
volatile bool           alreadyTriggered_button2  = false;

volatile bool           LampState    = false;

void IRAM_ATTR Falling_button1();
void IRAM_ATTR Rising_button1();
void IRAM_ATTR Falling_button2(); //falling en rising button voor knop 2 aanmaken
void IRAM_ATTR Rising_button2();
void IRAM_ATTR ButtonCheck();
void IRAM_ATTR ToggleLED();


void IRAM_ATTR Rising_button1() {
  unsigned long currentTime  = millis();
  unsigned long TimeDiff;

  TimeDiff = currentTime - lastDebounceTime_button1;

  if (digitalRead(BUTTON1_PIN) && (TimeDiff > DEBOUNCE_TIME) ) {
    buttonPressed_button1 = false;
    lastDebounceTime_button1 = currentTime;
  }
}

void IRAM_ATTR Falling_button1() {
  unsigned long currentTime  = millis();

  if ( !digitalRead(BUTTON1_PIN) && (currentTime > lastDebounceTime_button1 + DEBOUNCE_TIME)) {
    lastDebounceTime_button1 = currentTime;
    buttonPressed_button1 = true;
  }
}

//create herer Rising and Falling ISR for button2


void IRAM_ATTR Rising_button2() { //aanmaken rising button voor knop 2
  unsigned long currentTime  = millis();
  unsigned long TimeDiff;

  TimeDiff = currentTime - lastDebounceTime_button2;

  if (digitalRead(BUTTON2_PIN) && (TimeDiff > DEBOUNCE_TIME) ) {
    buttonPressed_button2 = false;
    lastDebounceTime_button2 = currentTime;
  }
}

void IRAM_ATTR Falling_button2() { //aanmaken falling button voor knop 2
  unsigned long currentTime  = millis();

  if ( !digitalRead(BUTTON2_PIN) && (currentTime > lastDebounceTime_button2 + DEBOUNCE_TIME)) {
    lastDebounceTime_button2 = currentTime;
    buttonPressed_button2 = true;
  }
}




void IRAM_ATTR HWCheckButton(void)
{
  if ((!alreadyTriggered_button1 && buttonPressed_button1)|| (!alreadyTriggered_button2 && buttonPressed_button2))
  {
    if(buttonPressed_button1)
        alreadyTriggered_button1 = true;
    else
        alreadyTriggered_button2 = true;
   ButtonCheck();
  }
  else if (!buttonPressed_button1 || !buttonPressed_button2 )
  {
    // Reset flag when button released to avoid triggered repeatedly
    if(buttonPressed_button1)
        alreadyTriggered_button1 = false;
    else
        alreadyTriggered_button2 = false;
    ButtonCheck();
  }
}


void IRAM_ATTR ButtonCheck()
{
  boolean SwitchState_button1 = (digitalRead(BUTTON1_PIN));
  boolean SwitchState_button2 = (digitalRead(BUTTON2_PIN));

  if (!SwitchState_button1 && SwitchReset_button1)
  {
    ToggleLED();
    SwitchReset_button1 = false;
  }
  else if (SwitchState_button1)
    SwitchReset_button1 = true;

  if (!SwitchState_button2 && SwitchReset_button2)
  {
    ToggleLED();
    SwitchReset_button2 = false;
  }
  else if (SwitchState_button2)
    SwitchReset_button2 = true;
}


void IRAM_ATTR ToggleLED()
{
  LampState = !LampState;
  digitalWrite(LED_PIN, LampState);
}


void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), Falling_button1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), Rising_button1, RISING);
  // copy and change lens above to attch interrupt to button2
  attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), Falling_button1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), Rising_button1, RISING);

  
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
