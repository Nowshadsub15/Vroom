#include <raylib.h>
#include <raymath.h>


int main(){
    InitWindow(1000, 800, "Vroom") ;
    SetTargetFPS(60) ;
    while(!WindowShouldClose()){
        BeginDrawing() ;

        ClearBackground(WHITE) ;

        EndDrawing() ;
    }
    CloseWindow() ;
    return 0;
}