/******************************************************
* ARDU GAME
* DEV: SkyList
* NAME: Matheus Pantoja Filgueira
* DATE: 10/06/2018
* 
* Using arduino(UNO) + lcd(16x2) + push button 
* for create a simples game, runner with handler for 
* points and animations 
********************************************************/

#include <LiquidCrystal.h>
#define BOTAO 7 //PORTA ONDE O PUSH BUTTON ESTA CONECTADO

LiquidCrystal lcd(2,4,8,9,10,11); //PORTAS DE CONTROLE PARA O LCD

bool playerPos = true;  //DEFINE SE O PLAYER ESTA EM CIMA OU EM BAIXO
int pontos = 0; //PONTUAÇÃO DO PLAYER
int bState = 0; // ESTADO DO BOTÃO
int velocidade = 300; //VELOCIDADE INICIAL DO JOGO
int velocidadeFinal = 100; //DEFINE A VELOCIDADE FINAL DO JOGO
int posObstaculoL = 0;  //POSIÇÃO DO OBSTACULO NA LINHA(0 A 1)
int posObstaculoC = 0;  //POSIÇÃO DO OBSTACULO NA COLUNA(0 A 15)
int fimDeJogo = 0;  //DEFINE O FIM DO JOGO (0 FALSE, 1 TRUE)

void setup() {
  pinMode( BOTAO, INPUT );
  lcd.begin(16,2);
  telaApresentacao(); //ANIMAÇÃO DA TELA DE APRESENTAÇÃO
  telaJogo(); // DESENHA A TELA DE JOGO
}

void loop() {
  while(fimDeJogo == 0){
    jogo();
  }
  telaFimDeJogo();
}

void jogo(){
  gerarObstaculo();
  moverPlayer();
}

void telaApresentacao(){
  lcd.print("   |ARDU----|   ");
  lcd.setCursor(0,1);
  lcd.print("   |----GAME|   ");
  
  delay(2000);

  animacaoTransicao(30);
}

void telaFimDeJogo(){

  animacaoTransicao(40);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CONGRATULATIONS!");
  lcd.setCursor(0,1);
  lcd.print("POINTS:");
  lcd.setCursor(8,1);
  lcd.print(pontos);
  delay(3000);
  
  animacaoTransicao(30);

  for(int i = 16; i >= 4; i--){
    lcd.clear();
    lcd.setCursor(i,0);
    lcd.print("RESET");
    lcd.setCursor(i,1);
    lcd.print(" ARDUINO");
    delay(100);
  }
  delay(3000);

  for(int i = 16; i >= 0; i--){
    lcd.clear();
    lcd.setCursor(i,0);
    lcd.print("   GAME         ");
    lcd.setCursor(i,1);
    lcd.print("        OVER    ");
    delay(100);
  }
  delay(3000);
}

void animacaoTransicao( int atraso){
  limpaTela('=', atraso);
  limpaTela(' ', atraso);
}

void moverPlayer(){
  bState = digitalRead(BOTAO);
  if( bState == HIGH){
    playerPos=true;
  }else{
    playerPos = false;
  }

  if( playerPos ){
    preencherCelula( 0,0,'o' );
    preencherCelula( 0,1,' ' );
    if( posObstaculoC == 0 && posObstaculoL == 0 ){
      fimDeJogo = 1;
    }
  }
  if( !playerPos ){
    preencherCelula( 0,1,'o' );
    preencherCelula( 0,0,' ' );
    if( posObstaculoC == 0 && posObstaculoL == 1 ){
      fimDeJogo = 1;
    }
  }
  
}

void gerarObstaculo(){

  posObstaculoL = random(0,2);
  
  for( posObstaculoC = 8; posObstaculoC >= 0; posObstaculoC --){
    moverPlayer();
    preencherCelula(posObstaculoC, posObstaculoL, '-');
    delay(velocidade);
    preencherCelula(posObstaculoC, posObstaculoL, ' ');
  }
  atualizarPontos();
  atualizarVelocidade();
}

void atualizarVelocidade(){
  if(velocidade == velocidadeFinal){
    velocidade = velocidadeFinal;
  }
  else{
    velocidade = velocidade - 10;
  }
}

void atualizarPontos(){
  pontos++;
  lcd.setCursor(10,1);
  lcd.print(pontos);
}

void telaJogo(){
  preencherCelula(9,0, '|');
  lcd.print("POINTS");
  preencherCelula(9,1, '|');
  lcd.print("0");
  preencherCelula(0,1,'1');
}

void preencherCelula( int coluna, int linha, char icone ){
  lcd.setCursor( coluna, linha );
  lcd.write( icone );
}

void limpaTela( char icone, int atraso ){
  for(int l = 0; l < 2; l++ ){
    for(int c = 0; c < 16; c++){
      preencherCelula( c, l, icone);
      delay(atraso);
    }
  }
}


