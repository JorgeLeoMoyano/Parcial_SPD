//===[Definición de pines]==
#define LED_A 12
#define LED_B 13
#define LED_C 7
#define LED_D 8
#define LED_E 9
#define LED_F 11
#define LED_G 10
#define DECENAS A4
#define UNIDADES A5
#define BOTON_SUBIR 4
#define BOTON_BAJAR 3
#define BOTON_REINICIAR 2

//===[Variables para el estado y números]==//
int numeroUnidades = 0;
int numeroDecenas = 0;
int estado_actual_boton_subir = 1;
int estado_actual_boton_bajar = 1;

void setup()
{
  //==[Configurar pines de salida y entrada]==
  configurarPinesSalidaYEntrada();
}

void loop()
{
  //==[Llama a la función para mostrar el número en el display]==
  mostrarNumeroEnDisplay(numeroDecenas, numeroUnidades);

  //==[Lectura de estados de los botones]==
  int estadoBotonSubir = digitalRead(BOTON_SUBIR);
  int estadoBotonBajar = digitalRead(BOTON_BAJAR);
  int estadoBotonReiniciar = digitalRead(BOTON_REINICIAR);

  //==[Manejo de los botones]==
  manejarBotones();
}

//==[Función para manejar los botones]==
void manejarBotones()
{
  int estadoBotonSubir = digitalRead(BOTON_SUBIR);
  int estadoBotonBajar = digitalRead(BOTON_BAJAR);
  int estadoBotonReiniciar = digitalRead(BOTON_REINICIAR);

  if (estadoBotonSubir == 0 && estado_actual_boton_subir != estadoBotonSubir)
  {
    //==[Incrementa las unidades o decenas según corresponda]==
    if (numeroUnidades == 9)
    {
      numeroUnidades = 0;
      numeroDecenas += 1;
    }
    else
    {
      numeroUnidades += 1;
    }
    estado_actual_boton_subir = estadoBotonSubir;
  }
  else if (estadoBotonBajar == 0 && estado_actual_boton_bajar != estadoBotonBajar)
  {
    //==[Decrementa las unidades o decenas según corresponda]==
    if (numeroUnidades == 0)
    {
      numeroUnidades = 9;
      numeroDecenas -= 1;
    }
    else
    {
      numeroUnidades -= 1;
    }

    if (numeroDecenas < 0)
    {
      numeroDecenas = 9;
    }
  }
  else if (estadoBotonReiniciar == 0)
  {
    //==[Reinicia ambos números]==
    numeroDecenas = 0;
    numeroUnidades = 0;
  }
  else
  {
    // Restaura los estados de los botones
    estado_actual_boton_subir = 1;
    estado_actual_boton_bajar = 1;
  }
}

//==[Función para configurar pines de salida]==
void configurarPinesSalidaYEntrada()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_F, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(DECENAS, OUTPUT);
  pinMode(UNIDADES, OUTPUT);
  Serial.begin(9600);
  pinMode(BOTON_SUBIR, INPUT_PULLUP);
  pinMode(BOTON_BAJAR, INPUT_PULLUP);
  pinMode(BOTON_REINICIAR, INPUT_PULLUP);
  estado_actual_boton_subir = 1;
  estado_actual_boton_bajar = 1;
}

//==[Función para mostrar números en el display]==
void mostrarNumeroEnDisplay(int decenasValue, int unidadesValue)
{
  //==[Configura el display para mostrar los números]==
  configurarDisplay(0, 0, 0, 0, 0, 0, 0);
  delay(80);
  digitalWrite(DECENAS, LOW);
  digitalWrite(UNIDADES, HIGH);
  dibujarNumeros(decenasValue);
  delay(10);
  digitalWrite(DECENAS, HIGH);
  digitalWrite(UNIDADES, LOW);
  dibujarNumeros(unidadesValue);
  delay(10);
}

//==[Función para configurar el display de 7 segmentos]==
void configurarDisplay(int a, int b, int c, int d, int e, int f, int g)
{
  digitalWrite(LED_A, a);
  digitalWrite(LED_B, b);
  digitalWrite(LED_C, c);
  digitalWrite(LED_D, d);
  digitalWrite(LED_E, e);
  digitalWrite(LED_F, f);
  digitalWrite(LED_G, g);
}

//==[Función para dibujar números en el display de 7 segmentos]==
void dibujarNumeros(int numeroBuscado)
{
  switch (numeroBuscado)
  {
  case 0:
    configurarDisplay(1, 1, 1, 1, 1, 1, 0);
    break;
  case 1:
    configurarDisplay(0, 1, 1, 0, 0, 0, 0);
    break;
  case 2:
    configurarDisplay(1, 1, 0, 1, 1, 0, 1);
    break;
  case 3:
    configurarDisplay(1, 1, 1, 1, 0, 0, 1);
    break;
  case 4:
    configurarDisplay(0, 1, 1, 0, 0, 1, 1);
    break;
  case 5:
    configurarDisplay(1, 0, 1, 1, 0, 1, 1);
    break;
  case 6:
    configurarDisplay(1, 0, 1, 1, 1, 1, 1);
    break;
  case 7:
    configurarDisplay(1, 1, 1, 0, 0, 0, 0);
    break;
  case 8:
    configurarDisplay(1, 1, 1, 1, 1, 1, 1);
    break;
  case 9:
    configurarDisplay(1, 1, 1, 1, 0, 1, 1);
    break;
  }
}
