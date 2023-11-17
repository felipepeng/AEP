#include <raylib.h>
#include <stdlib.h>

// Constantes
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FONT_SIZE 30
int yInstrucoes=200; 
int xAcoesHud=200;
int xVida=25;

// Variáveis Globais
int vida=100;
int vidaBoss[3]= {150, 200, 300};
int qntVidaBoss[3]= {150, 200, 300}; 
int mana=4;
int op2=0;
int ataqBoss;
int x=0, y=0;
int ataqueBoss;
int curaBoss;
int seuAtaque=0;
int mostrar=0;

int nBoss=0;
int iVida=0, iMana=0, iVidaBoss=0;

int suaDefesa=0;
int nDefesa=0;
bool defesaPerfeita=false;

bool fimFalas=false;
bool lutando=false;

// Adicionar elementos8
Music music;
Sound selectSound;
Texture2D bgMenu;
Texture2D bg1;
Texture2D bg2;
Texture2D richas;
Texture2D chay;
Texture2D CubePeng;
Texture2D MatrixPeng;
Texture2D blaze;

// Cores
Color selecionado = MAROON;
Color padrao = WHITE;

// Função para desenhar o Menu
void DrawMenu(int op, Texture2D bgMenu) {
    DrawTexture(bgMenu, 0, 0 , RAYWHITE);
    DrawTextureEx(CubePeng, (Vector2){730, 220}, 0, 1.0f, RAYWHITE);
  //DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);
    DrawText("Início"    , 215, 243, FONT_SIZE, (op == 1) ? selecionado : BLACK);
    DrawText("Instruções", 173, 345, FONT_SIZE, (op == 2) ? selecionado : BLACK);
    DrawText("Sair"      , 220, 452, FONT_SIZE, (op == 3) ? selecionado : BLACK);
}

// Função para desenhar as Instruções
void DrawInstrucoes(int op) {
    DrawText("COMANDOS:"                           , 320, yInstrucoes-50 , 40       , PINK);
    DrawText("SETAS: seleciona as ações."          , 320, yInstrucoes    , FONT_SIZE, padrao);
    DrawText("ENTER: confirma uma ação."           , 320, yInstrucoes+40 , FONT_SIZE, padrao);
    DrawText("BACKSPACE: retorna ao menu anterior.", 320, yInstrucoes+80 , FONT_SIZE, padrao);
    DrawText("ESC: fecha o jogo."                  , 320, yInstrucoes+120, FONT_SIZE, padrao);
}

// Função para desenhar a seleção de Bosses
void DrawBosses(int op) {
    DrawTexture(bgMenu, 0, 0 , RAYWHITE);
    DrawText("BOSS 1", 200, 243, 30, (op == 1) ? selecionado : BLACK);
    DrawText("BOSS 2", 200, 345, 30, (op == 2) ? selecionado : BLACK);
    DrawText("BOSS 3", 200, 452, 30, (op == 3) ? selecionado : BLACK);
    
    if(op==1){
        DrawTextureEx(chay, (Vector2){780, 220}, 0, 1.3f, RAYWHITE);
    }else
    if(op==2){
        DrawTextureEx(MatrixPeng, (Vector2){628, 200}, 0, 1.3f, RAYWHITE);
    }else
    if(op==3){
        DrawTextureEx(CubePeng, (Vector2){810, 280}, 0, 0.5f, RAYWHITE);
    }
    
}

// Função para desenhar o Boss1
void DrawBoss1 (Texture2D bg1,Texture2D richas, Texture2D chay) {
    DrawText("BOSS 1", 1100, 30, 45, PINK); 
    DrawTexture(bg1, 0, 0, WHITE); // Background Boss 1
    DrawTexture(richas, 150, 275, WHITE); // desenhar personagem
    DrawTexture(chay, 700, 260, WHITE); // desenhar Boss
}


// Função para desenhar Vida, Mana e vida do Boss
void DrawStatus(){
    
    //Desenha o HUD Superior
    DrawRectangle(0, 0, 1280, 60, DARKPURPLE);
    DrawRectangle(5, 5, 1270, 50, WHITE);
    
    
    //Desenha Barras de: Vida, Mana, VidaBoss
    for(int i=0; i<10; i++){
        //VIDA
        if(i<iVida)DrawRectangle(xVida+12*i, 20, 10, 20, RED);
        DrawRectangleLines(xVida+12*i, 20, 10, 20, MAROON);
        
        //MANA
        if(i<iMana)DrawRectangle(270+12*i, 20, 10, 20, BLUE);
        DrawRectangleLines(270+12*i, 20, 10, 20, DARKBLUE);
        
        //VIDA BOSS
        if(i<iVidaBoss)DrawRectangle(1000+15*i, 20, 15, 20, RED);
    }
    
    //Sua Vida
    DrawText(TextFormat("%d/100", vida), 148, 20, 20, BLACK);
    
    //Sua Mana
    DrawText(TextFormat("%d/10", mana), 394, 20, 20, BLACK);
    
    //Vida Boss1
    DrawRectangleLines(1000, 20, 150, 20, BLACK);
    DrawText(TextFormat("%d/%d", vidaBoss[nBoss], qntVidaBoss[nBoss]), 1158, 20, 20, BLACK);
    DrawText(TextFormat("Boss %d", nBoss+1) , 920, 20, 20, BLACK);

}

//função para desenhar o HUD 
void DrawHud () {
    // Retângulo do HUD
    DrawRectangle(0, 500, 1280, 220, WHITE);
    DrawRectangle(5, 505, 1270, 210, DARKPURPLE); // Cor interna
}

void DrawHudActions (int op) {
    // Ações do HUD
    switch (op2)
    {
    case 0:
    DrawText("Ataque", 120    , 590, FONT_SIZE, (op == 1) ? YELLOW : padrao); //1
    DrawText("Defesa", 120+300, 590, FONT_SIZE, (op == 2) ? YELLOW : padrao); //2
    DrawText("Ações" , 120+600, 590, FONT_SIZE, (op == 3) ? YELLOW : padrao); //3
    DrawText("Fugir" , 120+900, 590, FONT_SIZE, (op == 4) ? YELLOW : padrao); //4
        break;
    case 1: // ataqueBosss
    DrawText("Espadada",     xAcoesHud    , 590, FONT_SIZE, (op == 1) ? YELLOW : padrao); 
    DrawText("Bola de fogo", xAcoesHud+290, 590, FONT_SIZE, (op == 2) ? YELLOW : padrao); 
    DrawText("Hackear" ,     xAcoesHud+640, 590, FONT_SIZE, (op == 3) ? YELLOW : padrao); 
        break;
    case 2: // Ações
    DrawText("Defesa",          xAcoesHud    , 590, FONT_SIZE, (op == 1) ? YELLOW : padrao); 
    DrawText("Defesa Perfeita", xAcoesHud+260, 590, FONT_SIZE, (op == 2) ? YELLOW : padrao); 
    DrawText("???????",         xAcoesHud+650, 590, FONT_SIZE, (op == 3) ? YELLOW : padrao); 
        break;
    case 3: // Ações
    DrawText("Meditar", xAcoesHud    , 590, FONT_SIZE, (op == 1) ? YELLOW : padrao); 
    DrawText("???????", xAcoesHud+300, 590, FONT_SIZE, (op == 2) ? YELLOW : padrao); 
    DrawText("???????", xAcoesHud+600, 590, FONT_SIZE, (op == 3) ? YELLOW : padrao); 
        break;
    default:
        break;
    } 
    
    // Descrições
    if(op2==1){ // Ataques
        switch(op){
        case 1: //Espadada
        DrawText("Custo de Mana: 0", 15, 690, 20, LIGHTGRAY);
        DrawText("Ataca com a espada causando 5-20 de dano.", 380, 690, 20, LIGHTGRAY);
            break;
        case 2: //Bola de Fogo
        DrawText("Custo de Mana: 1", 15, 690, 20, LIGHTGRAY);
        DrawText("Atira uma bola flamejante causando 8-25 de dano.", 380, 690, 20, LIGHTGRAY);
            break;
        case 3: //Hackear
        DrawText("Custo de Mana: 2", 15, 690, 20, LIGHTGRAY);
        DrawText("Hackeia o inimigo causando 12-30 de dano.", 400, 690, 20, LIGHTGRAY);
            break;
        }
    }
    
    if(op2==2){ // Defesas
        switch(op){
        case 1: //Defesa Simples
        DrawText("Custo de Mana: 0", 15, 690, 20, LIGHTGRAY);
        DrawText("Defende 5-20 de dano do próximo ataque.", 400, 690, 20, LIGHTGRAY);
            break;
        case 2: //Defesa Perfeita
        DrawText("Custo de Mana: 1", 15, 690, 20, LIGHTGRAY);
        DrawText("Defende 100% de dano do próximo ataque.", 400, 690, 20, LIGHTGRAY);
            break;
        case 3: //???????????????
        DrawText("Custo de Mana: ?", 15, 690, 20, LIGHTGRAY);
        DrawText("????????????????????????????????????????????????", 300, 690, 20, LIGHTGRAY);
            break;
        }
    }
    
    if(op2==3){ // Ações
        switch(op){
        case 1: //Meditar
        DrawText("Custo de Mana: 0", 15, 690, 20, LIGHTGRAY);
        DrawText("Restaura +4 de Mana.", 460, 690, 20, LIGHTGRAY);
            break;
        case 2: //???????????????
        DrawText("Custo de Mana: ?", 15, 690, 20, LIGHTGRAY);
        DrawText("????????????????????????????????????????????????", 300, 690, 20, LIGHTGRAY);
            break;
        case 3: //???????????????
        DrawText("Custo de Mana: ?", 15, 690, 20, LIGHTGRAY);
        DrawText("????????????????????????????????????????????????", 300, 690, 20, LIGHTGRAY);
            break;
        }
    }
        
} //Void DrawHudActions

void DrawWinScreen(){
    DrawRectangle(180, 120, 920, 320, DARKPURPLE);
    DrawRectangle(190, 130, 900, 300, WHITE);
    
    if(vida>0 && vidaBoss[nBoss]<=0){
        DrawText("PARABENS, VOCÊ VENCEU! :D", 400, 150, 33, BLACK);
    }
    else if(vida<=0 && vidaBoss[nBoss]>0){
        DrawText("INFELISMENTE, VOCÊ PERDEU! ;-;", 400, 150, 33, BLACK);
    }else if(vida<=0 && vidaBoss[nBoss]<=0){
        DrawText("PARABENS, VOCÊ EMPATOU!", 400, 150, 33, BLACK);
    }
    
    
    DrawText("Pressione Enter para voltar para a seleção de Bosses...", 300, 390, 25, GRAY);
}


// MAIN------------------------------------------------------------------------------------------
int main() {
    // Inicialização
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Joguinho Show");
    InitAudioDevice();

    // Carregar elementos
    music = LoadMusicStream("./music.mp3");
    selectSound = LoadSound("./click.wav");
    bgMenu = LoadTexture("./Imagens/background.png");
    bg1 = LoadTexture("./Imagens/Mine3.png");
    bg2 = LoadTexture("./Imagens/nether3.png");
    richas = LoadTexture("./Imagens/Richas2.png");
    chay = LoadTexture("./Imagens/Chay.png");
    CubePeng = LoadTexture("./Imagens/CubePeng.png");
    MatrixPeng = LoadTexture("./Imagens/PengMatrix.png");
    blaze = LoadTexture("./Imagens/blaze.png");

    // Tocar música
    PlayMusicStream(music);

    // Variáveis Locais
    int op = 1;

    bool enterPressionado = false; // Computar apenas uma vez o Enter

    bool seuTurno = false; // Seu turno
    // Varíaveis controladoras de tela
    bool desenharMenu = true;  // Menu
    bool desenharInstrucoes = false; // Instruções
    bool desenharBosses = false; // Seleção de Bosses
    bool desenharBoss1 = false; // Boss 1
    bool desenharBoss2 = false; // Boss2
    bool desenharBoss3 = false; // Boss2
    
    // Laço de repetição
    while (!WindowShouldClose()) {
        // Tocar música
        UpdateMusicStream(music);

        // Controles do menu (OP)
        if(desenharMenu || desenharBosses){  // Menu e Bosses
            if (IsKeyPressed(KEY_UP)) {
            op -= 1;
            PlaySound(selectSound);
            }
            if (IsKeyPressed(KEY_DOWN)) {
                op += 1;
                PlaySound(selectSound);
            }
        } else 
            if((desenharBoss1 || desenharBoss2 || desenharBoss3) && seuTurno && lutando){
                if (IsKeyPressed(KEY_LEFT)) {
                op -= 1;
                PlaySound(selectSound);
                }
                if (IsKeyPressed(KEY_RIGHT)) {
                    op += 1;
                    PlaySound(selectSound);
                }
                // Volta para o HUD principal ao apertar Backspace
                if(IsKeyPressed(KEY_BACKSPACE) && op2!=0){
                    if(op2==1){
                        op=1;
                    }else
                    if(op2==2){
                        op=2;
                    }else
                    if(op2==3){
                        op=3;
                    }
                    op2=0;
                    PlaySound(selectSound);
                }
            }
        // Controle de limite (OP)
        if(op2==0 && (desenharBoss1 || desenharBoss2 || desenharBoss3)){  
            if (op < 1) op = 4;
            if (op > 4) op = 1; 
        }
        else{
            if (op < 1) op = 3;
            if (op > 3) op = 1; 
        }
         

//--------- Testes 
        if(IsKeyPressed(KEY_FOUR)) vida-=10;
        if(IsKeyPressed(KEY_FIVE)) lutando = !lutando;
        if(IsKeyPressed(KEY_SIX)) mana+=5;
            
    //Controle Vida, Mana, VidaBoss
        //VIDA
        if(vida>=100){
            iVida=10;
        }else
        if(vida<100 && vida>=90){
            iVida=9;
        }else
        if(vida<90 && vida>=80){
            iVida=8;
        }else
        if(vida<80 && vida>=70){
            iVida=7;
        }else
        if(vida<70 && vida>=60){
            iVida=6;
        }else
        if(vida<60 && vida>=50){
            iVida=5;
        }else
        if(vida<50 && vida>=40){
            iVida=4;
        }else
        if(vida<40 && vida>=30){
            iVida=3;
        }else    
        if(vida<30 && vida>=20){
            iVida=2;
        }else
        if(vida<20 && vida>0){
            iVida=1;
        }else
        if(vida<=0){
            iVida=0;
        }
        
        //MANA
        if (mana >= 10) {
            iMana = 10;
        } else 
        if (mana < 10 && mana >= 9) {
            iMana = 9;
        } else 
        if (mana < 9 && mana >= 8) {
            iMana = 8;
        } else 
        if (mana < 8 && mana >= 7) {
            iMana = 7;
        } else 
        if (mana < 7 && mana >= 6) {
            iMana = 6;
        } else 
        if (mana < 6 && mana >= 5) {
            iMana = 5;
        } else 
        if (mana < 5 && mana >= 4) {
            iMana = 4;
        } else 
        if (mana < 4 && mana >= 3) {
            iMana = 3;
        } else 
        if (mana < 3 && mana >= 2) {
            iMana = 2;
        } else 
        if (mana < 2 && mana > 0) {
            iMana = 1;
        } else 
        if (mana <= 0) {
            iMana = 0;
        }
        
        //VIDA BOSS
        if (vidaBoss[nBoss] >= 150) {
            iVidaBoss = 10;
        } else if (vidaBoss[nBoss] < 150 && vidaBoss[nBoss] >= 135) {
            iVidaBoss = 9;
        } else if (vidaBoss[nBoss] < 135 && vidaBoss[nBoss] >= 120) {
            iVidaBoss = 8;
        } else if (vidaBoss[nBoss] < 120 && vidaBoss[nBoss] >= 105) {
            iVidaBoss = 7;
        } else if (vidaBoss[nBoss] < 105 && vidaBoss[nBoss] >= 90) {
            iVidaBoss = 6;
        } else if (vidaBoss[nBoss] < 90 && vidaBoss[nBoss] >= 75) {
            iVidaBoss = 5;
        } else if (vidaBoss[nBoss] < 75 && vidaBoss[nBoss] >= 60) {
            iVidaBoss = 4;
        } else if (vidaBoss[nBoss] < 60 && vidaBoss[nBoss] >= 45) {
            iVidaBoss = 3;
        } else if (vidaBoss[nBoss] < 45 && vidaBoss[nBoss] >= 30) {
            iVidaBoss = 2;
        } else if (vidaBoss[nBoss] < 30 && vidaBoss[nBoss] > 0) {
            iVidaBoss = 1;
        } else if (vidaBoss[nBoss] <= 0) {
            iVidaBoss = 0;
        }


        //CONTROLE DAS TELAS
        // Controle de tela do Menu
        if (desenharMenu) {
            if (op == 1 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Bosses
                desenharMenu = false; // Sai do Menu
                desenharBosses = true; // Ativa o desenho de Seleção de Bosses
                PlaySound(selectSound);
                enterPressionado = true; // Marca que Enter foi pressionado
            } else
            
            if (op == 2 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Instruções
                desenharMenu = false; // Sai do Menu
                desenharInstrucoes = true; // Ativa o desenho da tela de Instruções
                PlaySound(selectSound);
                enterPressionado = true; // Marca que Enter foi pressionado
            } else

            if (op == 3 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Instruções
                CloseWindow();
            }
}
        // Controle de tela Instrucoes
        if (desenharInstrucoes) { 
            if (IsKeyPressed(KEY_BACKSPACE)) { // Voltar a tela
                desenharInstrucoes = false; // Sai das Instruções
                desenharMenu = true; // Volta ao Menu
                PlaySound(selectSound);
            }
        }  
        // Controle de tela Bosses
        if (desenharBosses) { 
            if (IsKeyPressed(KEY_BACKSPACE)) { // Voltar a tela
                desenharBosses = false; // Sai da seleção de bosses
                desenharMenu = true; // Volta ao menu
                PlaySound(selectSound);
                op=1;
            }

        
            if (op == 1 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Boss 1
                desenharBosses = false; // Sai da seleção de Bosses
                desenharBoss1 = true; // Ativa a Boss Fight 1
                PlaySound(selectSound);
                enterPressionado = true; // Marca que Enter foi pressionado
                seuTurno = true;      // Iniciar turno
                lutando= true;  // Inicia estado de luta
                op=1;
            }
            
            if (op == 2 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Boss 1
                desenharBosses = false; // Sai da seleção de Bosses
                desenharBoss2 = true; // Ativa a Boss Fight 2
                PlaySound(selectSound);
                enterPressionado = true; // Marca que Enter foi pressionado
                seuTurno = true;      // Iniciar turno
                lutando= true;  // Inicia estado de luta
                op=1;
            }
            
            if (op == 3 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Boss 1
                desenharBosses = false; // Sai da seleção de Bosses
                desenharBoss3 = true; // Ativa a Boss Fight 3
                PlaySound(selectSound);
                enterPressionado = true; // Marca que Enter foi pressionado
                seuTurno = true;      // Iniciar turno
                lutando= true;  // Inicia estado de luta
                op=1;
            }
        }  

        
    // Abrir desenho=================================================================================================
        BeginDrawing();
        ClearBackground(BLACK);

    // CONTROLADOR DAS TELAS
        // Menu
        if(desenharMenu){
            DrawMenu(op, bgMenu);
        }
        // Instruções
        if(desenharInstrucoes){
            DrawInstrucoes(op);
        }
        // Seleção de Bosses
        if (desenharBosses) {
         DrawBosses(op);
        }
        // Boss 1
        if (desenharBoss1) {
            DrawBoss1(bg1, richas, chay); // Desenha o Boss 1
            nBoss=0;
        }
        // Boss 2
        if (desenharBoss2) {
            DrawBoss1(bg2, richas, blaze); // Desenha o Boss 2
            nBoss=1;
        }
        // Boss 3
        if (desenharBoss3) {
            DrawBoss1(bg1, richas, CubePeng); // Desenha o Boss 3
            nBoss=2;
        }

        // (Boss1, Boss2, Boss3)
        if(desenharBoss1 || desenharBoss2 || desenharBoss3){  
            DrawHud ();               // HUD
            DrawStatus();

            if(seuTurno){
                DrawHudActions(op);   // Ações do HUD
                ataqueBoss=0;   // Reseta o dano de ataque do Boss
                if(y==0){
                    mana+=1;
                    y+=1;
                }
            }
            
            // ataqueBosss do Boss 
            if(seuTurno==false){
                if(x==0){
                    ataqBoss=rand()%3;
                    switch (ataqBoss)
                    {
                        case 0: // ataqueBoss Padrão
                        ataqueBoss= 5+rand()%11;
                        break;

                        case 1: // ataqueBoss Empoderado
                        ataqueBoss= 10+rand()%11;
                        break;
                            
                        case 2: // HEAL
                        curaBoss= 1+rand()%10;
                        vidaBoss[0]+=curaBoss;
                        break;
                        default:
                        break;
                    }
                        
                    if(!defesaPerfeita && ataqBoss!=2){ // Ajustes nas Defesas
                        if(ataqueBoss>=suaDefesa){
                            vida-=ataqueBoss -suaDefesa;        
                        } else{
                            nDefesa=ataqueBoss;
                        }
                    }
                        
                    if(ataqBoss==2){
                        nDefesa=0;
                    }
                    
                    y=0; //Controlador Player
                    x++;
                }
            }
            

            // Sinaliza ações ****  (Talvez trocar este+Controle de Telas para o Boss1)
            if(seuTurno==false){
                if(mostrar==0){   // Seu Ataque
                    DrawText(TextFormat("O seu ataque deu %d de dano.", seuAtaque), 300, 590, 40, YELLOW);
                    DrawText("Aperte ENTER...", 1102, 690, 20, RAYWHITE);
                }else
                if(mostrar==1){   // Ataque do Boss
                    if(ataqBoss==2){
                        DrawText(TextFormat("O Boss curou %d de vida.", curaBoss), 370, 590, 40, YELLOW);
                    } else(DrawText(TextFormat("O ataque do Boss deu %d de dano.", ataqueBoss), 280, 590, 40, YELLOW));
                    DrawText("Aperte ENTER...", 1102, 690, 20, RAYWHITE);
                }else
                if(mostrar==2){   // Sua Defesa
                    if(defesaPerfeita){
                        DrawText(TextFormat("Você Defendeu %d de dano do ataque.", ataqueBoss), 238, 590, 40, YELLOW);
                    }else (DrawText(TextFormat("Você Defendeu %d de dano do ataque.", nDefesa), 238, 590, 40, YELLOW));
                    DrawText("Aperte ENTER...", 1102, 690, 20, RAYWHITE);
                }
                
                //Controle de Telas
                if(IsKeyPressed(KEY_ENTER) && !enterPressionado && mostrar==0){   // Seu Ataque
                    mostrar=1;
                    enterPressionado = true; // Marca que Enter foi pressionado
                }
                    
                if(IsKeyPressed(KEY_ENTER) && !enterPressionado && mostrar==1){   // Ataque do Boss
                    if(defesaPerfeita || suaDefesa>0){
                        mostrar=2;
                    }else{
                        seuAtaque=0;
                        defesaPerfeita=false;
                        suaDefesa=0;
                        seuTurno=true;
                        fimFalas=true;
                    }
                    enterPressionado = true; // Marca que Enter foi pressionado
                }   
                
                if(IsKeyPressed(KEY_ENTER) && !enterPressionado && mostrar==2){   // Ataque do Boss
                    seuAtaque=0;
                    defesaPerfeita=false;
                    suaDefesa=0;
                    enterPressionado = true; // Marca que Enter foi pressionado
                    seuTurno=true;
                    fimFalas=true;
                }   
                
                // Desativa estado de luta ao morrer
                if((desenharBoss1 || desenharBoss2 || desenharBoss3) && (vida<=0 || vidaBoss[nBoss]<=0) && fimFalas){  
                    lutando=false;
                }
            } // Seu Turno==false
        
            // CONTROLE DAS AÇÕES---------------------------------------------------------------------------------------    
            if(seuTurno && lutando){
                
                if(IsKeyPressed(KEY_ENTER) && !enterPressionado && op2==0){  // HUD Principal
                    PlaySound(selectSound);
                    switch (op)
                    {
                        case 1:
                            op2=1;  //Ataques 
                            break;
                        case 2:
                            op2=2;  //Defesas
                            break;
                        case 3:
                            op2=3;  //Ações
                            break;
                        case 4:     //Correr
                            if(desenharBoss1){
                                desenharBoss1 = false; // Sai da Boss Fight 1
                            }else if(desenharBoss2){
                                desenharBoss2 = false; // Sai da Boss Fight 2
                            }else if (desenharBoss3){
                                desenharBoss3 = false; // Sai da Boss Fight 3
                            }
                            desenharBosses = true; // Volta a seleção de Bosses
                            op=1;
                            break;
                        default:
                            break;
                    }
                    op=1;
                    enterPressionado = true; // Marca que Enter foi pressionado
                }
                // Ataque, Defesa, Ações
                if(IsKeyPressed(KEY_ENTER) && !enterPressionado){
                    
                    if(op2==1){  // HUD Ataques
                        PlaySound(selectSound);
                        switch (op)
                        {
                            case 1: // Espadada 
                                seuAtaque= 5 + rand()%16;  //(5-20)
                                seuTurno=false;
                                break;
                            case 2: // Bola de fogo
                                if(mana>=1){
                                    seuAtaque= 8 + rand()%18;  //(8-25)
                                    mana-=1;
                                    seuTurno=false;
                                } 
                                break;
                            case 3: // Hackear
                                if(mana>=2){
                                    seuAtaque= 12 + rand()%19;  //(12-30)
                                    mana-=2;
                                    seuTurno=false;
                                } 
                                break;
                            default:
                                break;
                        }
                        mostrar=0;
                        vidaBoss[0]-=seuAtaque;
                        x=0; //Controlador Boss
                        enterPressionado = true; // Marca que Enter foi pressionado
                    }
                    
                    if(op2==2){  // HUD Defesas 
                        PlaySound(selectSound);
                        switch (op)
                        {
                            case 1: // Defesa Normal 
                                suaDefesa=5+ rand()%16;
                                seuTurno=false;                    
                                break;
                            case 2: // Defesa Perfeita
                                if(mana>=1){
                                    defesaPerfeita=true;  
                                    mana-=1;
                                    seuTurno=false;
                                } 
                                break;
                            default:
                                break;
                        }
                        mostrar=1;
                        nDefesa=suaDefesa;
                        x=0; //Controlador Boss
                        enterPressionado = true; // Marca que Enter foi pressionado
                    }
                    
                    if(op2==3){  // HUD Ações 
                        PlaySound(selectSound);
                        switch (op)
                        {
                            case 1: // Meditar
                            mana+=4;
                            seuTurno=false;                    
                            break;
                            default:
                            break;
                        }
                        mostrar=1;
                        x=0; //Controlador Boss
                        enterPressionado = true; // Marca que Enter foi pressionado
                    }     
                }
                fimFalas=false;
            } // Seu Turno && Lutando
            
        } //Desenhar Bosses

        //Não Lutando e em BossFight
        if(!lutando && (desenharBoss1 || desenharBoss2 || desenharBoss3)){ // Add Boss2 e Boss3
            DrawWinScreen(); //Desenhar Win Screen
            op2=0;
            op=1;
            
            if(IsKeyPressed(KEY_ENTER) && !enterPressionado){
                if(desenharBoss1){
                    desenharBoss1=false;
                }else if(desenharBoss2){
                    desenharBoss2=false;
                }else if(desenharBoss3){
                    desenharBoss3=false;
                }
                desenharBosses=true;
            }
        }



        // Limpe enterPressionado quando a tecla Enter for liberada
        if (IsKeyReleased(KEY_ENTER)) {
            enterPressionado = false;
        }

      // Desenha o número da opção atual para depuração (op)
        //DrawText(TextFormat(" op: %d", op), 100, 100, 40, BLUE);  ***
        //DrawText(TextFormat("Vida: %d", vida), 100, 200, 40, BLUE);  

        // Fechar desenho
        EndDrawing();
    }

    // Fechamento do código
    StopMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
