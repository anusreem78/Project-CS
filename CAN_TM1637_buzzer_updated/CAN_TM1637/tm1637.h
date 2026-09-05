#define PORT8 P8
#define PORT1 P1
#define SDA_PIN 3
#define CLK_PIN 4
#define Autoincre_mode 0x40

void R_MAIN_UserInit(void);

void TM1637_Demo(void);
void TM1637_Init(void);
void TM1637_DisplayDecimal(int v, int displaySeparator);
void TM1637_SetBrightness(char brightness);
void TM1637_Start(void);
void TM1637_Stop(void);
void TM1637_ReadResult(void);
void TM1637_WriteByte(unsigned char b);
void TM1637_DelayUsec(int );
void TM1637_ClkHigh(void);
void TM1637_ClkLow(void);
void TM1637_DataHigh(void);
void TM1637_DataLow(void);





