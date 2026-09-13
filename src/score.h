#ifndef SCORE_H
#define SCORE_H

#include <raylib.h>

typedef struct
{
    float starting_x;
    float total_shifted_x;
    float max_distance_reached;
    int current_score;
    int high_score;
} ScoreSystem;

ScoreSystem score_init(float start_x);
void score_reset_current(ScoreSystem *score, float start_x);
void score_update(ScoreSystem *score, float car_x);
void score_shift(ScoreSystem *score, float shift_x);
void score_draw(ScoreSystem *score, Font font);

// File handling functions
int score_load_high_score(void);
void score_save_high_score(int score_val);

#endif