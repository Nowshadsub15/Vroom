#include "terrain.h"
#include <math.h>
#include <string.h>

bool IsPointBelowLine(Vector2 a, Vector2 b, Vector2 point, Vector2 *collisionPoint) {
        float t = (point.x - a.x) / (b.x - a.x);
        if (t < 0.0f || t > 1.0f)
            return false;
        collisionPoint->x = point.x;
        collisionPoint->y = a.y + t * (b.y - a.y);
        return (point.y > collisionPoint->y);
}

float catmull_rom(float p0, float p1, float p2, float p3, float t){
    float t2 = t * t;
    float t3 = t2 * t;
    return 0.5f * (
        (2.0f * p1) +
        (-p0 + p2) * t +
        (2.0f*p0 - 5.0f*p1 + 4.0f*p2 - p3) * t2 +
        (-p0 + 3.0f*p1 - 3.0f*p2 + p3) * t3
    );
}

void terrain_generate(Vector2 terrain[],int window_height,float anchors[])
{
    int min_h = window_height*0.35 ;
    int max_h = window_height*0.95 ;
    int num_anchors = TERRAIN_COUNT / CONTROL_STEP + 3;
    //float anchors[num_anchors] ;
    int pos = GetRandomValue(min_h+60,max_h-60) ;
    anchors[0] = pos ;
    anchors[1] = pos ;
    anchors[2] = pos ;
    anchors[3] = pos ;
    anchors[4] = pos ;
    anchors[5] = pos ;
    anchors[6] = pos ;
    anchors[7] = pos ;
    anchors[8] = pos + GetRandomValue(-20,20) ;
    for(int i = 9 ; i < num_anchors ; i++){
        int step ;
        if(i%7){
            step = GetRandomValue(-220,220) ;
            pos += step ;
        }
        else{
            step = GetRandomValue(-150,150) ;
            pos += step ;
        }
        if(pos < min_h) pos = min_h ;
        else if(pos > max_h) pos = max_h ;
        if(pos == anchors[i-1]){
            if(step == 0 && pos == min_h) step = -50 ;
            else if(step == 0 && pos == max_h) step = 50 ;
            if(pos == min_h || pos == max_h) pos -= step ;
            else pos += 25 ;
        }
        anchors[i] = pos ;
    }
    for(int i = 0 ; i < TERRAIN_COUNT ; i++){
        int anchor_index = i / CONTROL_STEP ;
        float t = (i%CONTROL_STEP) / (float)CONTROL_STEP ;
        float p0 = anchors[anchor_index] ;
        float p1 = anchors[anchor_index+1] ;
        float p2 = anchors[anchor_index+2] ;
        float p3 = anchors[anchor_index+3] ;
        float y = catmull_rom(p0,p1,p2,p3,t) ;
        if(y<min_h) y = min_h ;
        if(y>max_h) y= max_h ;
        terrain[i].x = i*TERRAIN_LENGTH ;
        terrain[i].y = y ;
    }
}

void terrain_shift(Vector2 terrain[], int shift_count, float anchors[])
{
    int num_anchors = TERRAIN_COUNT / CONTROL_STEP + 3 ;
    int anchor_shift = shift_count / CONTROL_STEP ;
    int keep_anchors = num_anchors - anchor_shift ;
    memmove(anchors, anchors+anchor_shift, sizeof(float)*keep_anchors) ;
    int window_height = GetScreenHeight() ;
    int min_h = window_height*0.35 ;
    int max_h = window_height*0.95 ;
    int pos = anchors[keep_anchors - 1] ;
    for(int i = keep_anchors ; i < num_anchors ; i++){
        int step ;
        if(i%7){
            step = GetRandomValue(-220,220) ;
            pos += step ;
        }
        else{
            step = GetRandomValue(-150,150) ;
            pos += step ;
        }
        if(pos < min_h) pos = min_h ;
        else if(pos > max_h) pos = max_h ;
        if(pos == anchors[i-1]){
            if(step == 0 && pos == min_h) step = -50 ;
            else if(step == 0 && pos == max_h) step = 50 ;
            if(pos == min_h || pos == max_h) pos -= step ;
            else pos += 25 ;
        }
        anchors[i] = pos ;
    }
    for(int i = 0 ; i < TERRAIN_COUNT ; i++){
        int anchor_index = i / CONTROL_STEP ;
        float t = (i%CONTROL_STEP) / (float)CONTROL_STEP ;
        float p0 = anchors[anchor_index] ;
        float p1 = anchors[anchor_index+1] ;
        float p2 = anchors[anchor_index+2] ;
        float p3 = anchors[anchor_index+3] ;
        float y = catmull_rom(p0,p1,p2,p3,t) ;
        if(y<min_h) y = min_h ;
        if(y>max_h) y= max_h ;
        terrain[i].x = i*TERRAIN_LENGTH ;
        terrain[i].y = y ;
    }
}