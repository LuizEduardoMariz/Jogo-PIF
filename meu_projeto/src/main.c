#include "mapa.h"
#include "personagem.h"
#include <raylib.h>
// ... inclua seus outros arquivos .h aqui (keyboard.h, screen.h, timer.h)

Jogador astronauta;

int main(void)
{
    // ... Código de inicialização ...

    while (!WindowShouldClose())
    {
        // ... Lógica do jogo (Update) ...

        BeginDrawing();

            ClearBackground(BLACK);

            DrawGameMap(); // Desenha o mapa

            // ... Desenho do Player, etc. ...

        EndDrawing();
    }

    // ... Código de finalização ...
    return 0;
}