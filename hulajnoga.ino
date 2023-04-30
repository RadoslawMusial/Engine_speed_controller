#define SIGNAL A0
#define ANALOG_CUTOFF 50
#define ADC_SAMPLE_CNT 25

void PWM_init()
{
    TCCR2A = _BV(COM2A1) |  _BV(COM2A0) | _BV(COM2B1) | _BV(COM2B0) | _BV(WGM21) | _BV(WGM20); // inverted PWM mode
    TCCR2B = _BV(CS21);
    //OCR2A = 255;
    OCR2B = 255;  
}

void setup() {
    pinMode(3, OUTPUT);    
    PWM_init(); 
}

void loop() {
  static bool NoThrottle = false;
  static uint16_t ADC_val;
  static unsigned int ADC_samples;
  
  /************** SAMPLING ***************/
  for(int i = 0; i < ADC_SAMPLE_CNT; ++i)
  {
    ADC_samples += analogRead(SIGNAL); 
  }
  ADC_val = ADC_samples / ADC_SAMPLE_CNT;  
  ADC_samples = 0;
  /***************************************/

  /*********** RIDE AND STOP *************/
  if(ADC_val > ANALOG_CUTOFF)
  {
    if(NoThrottle == true);
    {
      PWM_init();
    }
    OCR2B = ADC_val/4;
  }
  else
  {
    NoThrottle = true;
    OCR2B = 0; 
    digitalWrite(3, HIGH);
  }  
  /***************************************/                   
}
