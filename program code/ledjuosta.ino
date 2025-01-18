#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 13 //Valdysime per šį išvadą
#define ILGIS 50 //LED juostos diodų skaičius
#define LAUKTI 1000 //Laikas tarp programų
#define PRGREITIS 20 //Programos LED užsidegimo greitis
Adafruit_NeoPixel juosta = Adafruit_NeoPixel(ILGIS, PIN, NEO_GRB + NEO_KHZ800); 
//apsirašau savo LED juostą

void setup() 
{
  juosta.begin(); //atlieka pradinį visų diodų nustatymą į būseną išjungta
  juosta.show(); 
}

void loop() 
{
  subegantiSpalva(juosta.Color(255, 0, 0), PRGREITIS);
  delay(LAUKTI);
  subegantiSpalva(juosta.Color(0, 0, 0), PRGREITIS);
  delay(LAUKTI);
  subegantiSpalva(juosta.Color(0, 255, 0), PRGREITIS);
  delay(LAUKTI);
  subegantiSpalva(juosta.Color(0, 0, 0), PRGREITIS);
  delay(LAUKTI);
  subegantiSpalva(juosta.Color(0, 0, 255), PRGREITIS);
  delay(LAUKTI);
  subegantiSpalva(juosta.Color(0, 0, 0), PRGREITIS);
  delay(LAUKTI);

  blykseti(juosta.Color(255, 255, 255), PRGREITIS);
  delay(LAUKTI);

  vaivorykste(PRGREITIS);
  spalvuPerejimas(PRGREITIS);
}

//subega norimaspalva
void subegantiSpalva(uint32_t spalva, uint8_t laukti) 
{
  for (uint16_t i = 0; i < ILGIS; i++) //uint16_t - 16 bitų sveikasis skaicius
  {
    juosta.setPixelColor(i, spalva);
    juosta.show(); 
    delay(laukti); //kiek laukti iki sekančio diodo užšvietimo
  }
}

//uzdegti norima spalva sviesos dioda atsitiktineje juostos vietoje:
void blykseti(uint32_t spalva, uint8_t laukti) 
{
  uint16_t atsitiktinis;
  for (uint16_t i = 0; i < 300; i++)
  {
    int atsitiktinis = random(0, ILGIS);
    juosta.setPixelColor(atsitiktinis, spalva);
    juosta.show();
    delay(laukti);
    juosta.setPixelColor(atsitiktinis, juosta.Color(0, 0, 0));
    juosta.show();
    delay(laukti); 
    
  }
}

// Letas vauvorykstes spalvu perejimas:
void vaivorykste(uint8_t laukti) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { 
    for(i=0; i< juosta.numPixels(); i++) {
      juosta.setPixelColor(i, ciklas(((i * 256 / juosta.numPixels()) + j) & 255));
    }
    juosta.show();
    delay(laukti);
  }
}

//Spalvu perejimas kas trecia dioda:
void spalvuPerejimas(uint8_t laukti) {
  for (int j=0; j < 256; j++) {     //suka ratu visas 256 spalvas
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < juosta.numPixels(); i=i+3) {
        juosta.setPixelColor(i+q, ciklas( (i+j) % 255));    //ijungia kas trecia
      }
      juosta.show();

      delay(100);

      for (uint16_t i=0; i < juosta.numPixels(); i=i+3) {
        juosta.setPixelColor(i+q, 0);        //isjungia kas trecia
      }
    }
  }
}

uint32_t ciklas(byte cikloVieta) {
  cikloVieta = 255 - cikloVieta;
  if(cikloVieta < 85) {
    return juosta.Color(255 - cikloVieta * 3, 0, cikloVieta * 3);
  }
  if(cikloVieta < 170) {
    cikloVieta -= 85;
    return juosta.Color(0, cikloVieta * 3, 255 - cikloVieta * 3);
  }
  cikloVieta -= 170;
  return juosta.Color(cikloVieta * 3, 255 - cikloVieta * 3, 0);
}



















