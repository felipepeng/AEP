#include <raylib.h>
#include <stdlib.h>

// Constantes
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FONT_SIZE 30
int yInstrucoes=200; 
int xAcoesHud=120;
int xVida=25;

 // Variáveis Globais
int vida=100;
int vidaBoss[3]= {150, 200, 300};
int mana=4;
int op2=0;
int ataqBoss;
int x=0;


// Cores
Color selecionado = MAROON;
Color padrao = WHITE;

// Função para desenhar o Menu
void DrawMenu(int op) {
    DrawText("Início"    , 500, 300, FONT_SIZE, (op == 1) ? selecionado : padrao);
    DrawText("Instruções", 500, 340, FONT_SIZE, (op == 2) ? selecionado : padrao);
    DrawText("Sair"      , 500, 380, FONT_SIZE, (op == 3) ? selecionado : padrao);
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
    DrawText("BOSS 1", 500, 300, 30, (op == 1) ? selecionado : padrao);
    DrawText("BOSS 2", 500, 340, 30, (op == 2) ? selecionado : padrao);
    DrawText("BOSS 3", 500, 380, 30, (op == 3) ? selecionado : padrao);
}

// Função para desenhar o Boss1
void DrawBoss1 (Texture2D bg1,Texture2D richas, Texture2D chay) {
    DrawText("BOSS 1", 1100, 30, 45, PINK); 
    DrawTexture(bg1, 0, 0, WHITE); // Background Boss 1
    DrawTexture(richas, 150, 275, WHITE); // desenhar personagem
    DrawTexture(chay, 700, 260, WHITE); // desenhar Boss
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
    DrawText("Ataque", xAcoesHud    , 590, FONT_SIZE, (op == 1) ? YELLOW : padrao); //1
    DrawText("Defesa", xAcoesHud+300, 590, FONT_SIZE, (op == 2) ? YELLOW : padrao); //2
    DrawText("Ações" , xAcoesHud+600, 590, FONT_SIZE, (op == 3) ? YELLOW : padrao); //3
        break;
    case 1: // Ataques
    DrawText("Espadada",     xAcoesHud    , 590, FONT_SIZE, (op == 1) ? YELLOW : padrao); 
    DrawText("Bola de fogo", xAcoesHud+340, 590, FONT_SIZE, (op == 2) ? YELLOW : padrao); 
    DrawText("Hackear" ,     xAcoesHud+690, 590, FONT_SIZE, (op == 3) ? YELLOW : padrao); 
        break;
    case 2: // Ações
    DrawText("Defesa",          xAcoesHud    , 590, FONT_SIZE, (op == 1) ? YELLOW : padrao); 
    DrawText("Defesa Perfeita", xAcoesHud+290, 590, FONT_SIZE, (op == 2) ? YELLOW : padrao); 
    DrawText("???????",         xAcoesHud+680, 590, FONT_SIZE, (op == 3) ? YELLOW : padrao); 
        break;
    case 3: // Ações
    DrawText("Meditar", xAcoesHud    , 590, FONT_SIZE, (op == 1) ? YELLOW : padrao); 
    DrawText("???????", xAcoesHud+300, 590, FONT_SIZE, (op == 2) ? YELLOW : padrao); 
    DrawText("???????", xAcoesHud+600, 590, FONT_SIZE, (op == 3) ? YELLOW : padrao); 
        break;
    default:
        break;
    } 
}


// MAIN------------------------------------------------------------------------------------------
int main() {
    // Inicialização
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Joguinho Show");
    InitAudioDevice();

    // Adicionar elementos
    Music music;
    Sound select;
    Texture2D coracao;
    Texture2D bg1;
    Texture2D richas;
    Texture2D chay;

    // Carregar elementos
    music = LoadMusicStream("./music.mp3");
    select = LoadSound("./click.wav");
    bg1 = LoadTexture("./Imagens/Mine3.png");
    richas = LoadTexture("./Imagens/Richas2.png");
    chay = LoadTexture("./Imagens/Chay.png");

    // Tocar música
    PlayMusicStream(music);

    // Variáveis Locais
    int op = 1;

    bool enterPressionado = false; // Computar apenas uma vez o Enter

    bool continuar = false; // Após turno Boss
    bool seuTurno = false; // Seu turno
    // Varíaveis controladoras de tela
    bool desenharMenu = true;  // Menu
    bool desenharInstrucoes = false; // Instruções
    bool desenharBosses = false; // Bosses
    bool desenharBoss1 = false; // Boss 1
    
    // Laço de repetição
    while (!WindowShouldClose()) {
        // Tocar música
        UpdateMusicStream(music);

        // Controles do menu
        if(desenharMenu || desenharBosses){  // Menu e Bosses
            if (IsKeyPressed(KEY_UP)) {
            op -= 1;
            PlaySound(select);
            }
            if (IsKeyPressed(KEY_DOWN)) {
                op += 1;
                PlaySound(select);
            }
        } else if(desenharBoss1 && seuTurno){
            if (IsKeyPressed(KEY_LEFT)) {
            op -= 1;
            PlaySound(select);
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                op += 1;
                PlaySound(select);
            }
        }
        // Controle de limite
        if (op < 1) op = 3;
            if (op > 3) op = 1;  

//--------- Testes 
            if(IsKeyPressed(KEY_FOUR)) vida-=25;
            if(IsKeyPressed(KEY_FIVE)) seuTurno = !seuTurno;
            if(IsKeyPressed(KEY_SIX)) mana+=5;
        

        //CONTROLE DAS TELAS
        // Controle de tela do Menu
        if (desenharMenu) {
            if (op == 1 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Bosses
                desenharMenu = false; // Sai do Menu
                desenharBosses = true; // Ativa o desenho de Seleção de Bosses
                PlaySound(select);
                enterPressionado = true; // Marca que Enter foi pressionado
            } else
            
            if (op == 2 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Instruções
                desenharMenu = false; // Sai do Menu
                desenharInstrucoes = true; // Ativa o desenho da tela de Instruções
                PlaySound(select);
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
                PlaySound(select);
            }
        }  
        // Controle de tela Bosses
        if (desenharBosses) { 
            if (IsKeyPressed(KEY_BACKSPACE)) { // Voltar a tela
                desenharBosses = false; // Sai da seleção de bosses
                desenharMenu = true; // Volta ao menu
                PlaySound(select);
                op=1;
            }

        
             if (op == 1 && IsKeyPressed(KEY_ENTER) && !enterPressionado) { // Entrar Boss 1
                desenharBosses = false; // Sai da seleção de Bosses
                desenharBoss1 = true; // Ativa a Boss Fight 1
                PlaySound(select);
                enterPressionado = true; // Marca que Enter foi pressionado
                seuTurno = true;      // Iniciar turno
            }
        }  

        if (desenharBoss1 && op2==0) {
            if (IsKeyPressed(KEY_BACKSPACE)) { // Voltar a tela
                desenharBoss1 = false; // Sai da Boss Fight 1
                desenharBosses = true; // Volta a seleção de Bosses
                PlaySound(select);
                op=1;
            }
        }
        
        
    // Abrir desenho=================================================================================================
        BeginDrawing();
        ClearBackground(BLACK);

    // CONTROLADOR DAS TELAS
        // Menu
        if(desenharMenu){
            DrawMenu(op);
        }
        // Instruções
        if(desenharInstrucoes){
            DrawInstrucoes(op);
        }
        // Bosses
        if (desenharBosses) {
         DrawBosses(op);
        }
        // Boss 1
        if (desenharBoss1) {
            DrawBoss1(bg1, richas, chay); // Desenha o Boss

            // Ataques do Boss
            if(seuTurno==false){
                ataqBoss=rand()%3;
                if(x<=2){
                    x++;
                    if(x==1){
                        switch (ataqBoss)
                        {
                            case 0: // Ataque Padrão
                            vida-=5+rand()%11;
                                break;

                            case 1: // Ataque Empoderado
                            vida-=10+rand()%11;
                                break;
                            
                            case 2: // Ataque Empoderado
                            vidaBoss[0]+=10+rand()%11;
                                break;

                            default:
                                break;
                        }
                    }
                }

                
                
                if(IsKeyPressed(KEY_ENTER) && !enterPressionado){
                seuTurno=true;
                enterPressionado = true; // Marca que Enter foi pressionado
                }

                
            }
        }

        // (Boss1, Boss2, Boss3)
        if(desenharBoss1){  //Adicionar Boss2 e Boss3 (depois)
            DrawHud ();               // HUD
            DrawText(TextFormat("%d", vida), xVida+100, 20, 30, YELLOW);   // Barra de vida (Sua)
            DrawText("VIDA:", xVida, 20, 30, YELLOW);
      
            //Desenha Vida Boss (Temporário)
            DrawText(TextFormat("%d", vidaBoss[0]), 1070, 20, 30, YELLOW); 
            DrawText("Vida Boss:", 900, 20, 30, YELLOW);

            //Desenha Mana (Temporário)
            DrawText(TextFormat("%d", mana), 490, 20, 30, YELLOW); 
            DrawText("MANA:", 390, 20, 30, YELLOW);

            if(seuTurno){
                DrawHudActions(op);   // Ações do HUD
            }
        
            // CONTROLE DAS AÇÕES---------------------------------------------------------------------------------------    
            if(seuTurno && IsKeyPressed(KEY_ENTER) && !enterPressionado && op2==0){  // Principal
                PlaySound(select);
                switch (op)
                {
                case 1:
                    op2=1; 
                    break;
                case 2:
                    op2=2;
                    break;
                case 3:
                    op2=3;
                    break;
                default:
                    break;
                }
                enterPressionado = true; // Marca que Enter foi pressionado
            }

            if(seuTurno && IsKeyPressed(KEY_ENTER) && !enterPressionado && op2==1){  // Ataques
                PlaySound(select);
                switch (op)
                {
                case 1: // Espadada 
                    vidaBoss[0]-=5 + rand()%11;
                    seuTurno=false;
                    break;
                case 2: // Bola de fogo
                    if(mana>=1){
                        vidaBoss[0]-=8 + rand()%11;
                        mana-=1;
                        seuTurno=false; 
                    } 
                    break;
                case 3: // Hackear
                    if(mana>=2){
                        vidaBoss[0]-=8 + rand()%18;
                        mana-=2;
                        seuTurno=false;
                    } 
                    break;
                default:
                    break;
                }
                x=0;
                enterPressionado = true; // Marca que Enter foi pressionado
            }

            // Volta para o HUD principal ao apertar Backspace
            if(IsKeyPressed(KEY_BACKSPACE) && op2!=0){
                op2=0;
                PlaySound(select);
            }
        }




        // Limpe enterPressionado quando a tecla Enter for liberada
        if (IsKeyReleased(KEY_ENTER)) {
            enterPressionado = false;
        }

        // Desenha o número da opção atual para depuração (op)
        DrawText(TextFormat("%d", op), 100, 100, 40, BLUE);

        // Fechar desenho
        EndDrawing();
    }

    // Fechamento do código
    StopMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}