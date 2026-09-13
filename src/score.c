#include "score.h"
#include <stdio.h>

#define FILENAME "highestscore.txt"

int score_load_high_score(void)
{
    FILE *file = fopen(FILENAME, "r");
    int saved_score = 0;

    if (file == NULL)
    {

        file = fopen(FILENAME, "w");
        if (file != NULL)
        {
            fprintf(file, "%d", 0);
            fclose(file);
        }
        return 0;
    }

    if (fscanf(file, "%d", &saved_score) != 1)
    {
        saved_score = 0;
    }

    fclose(file);
    return saved_score;
}

void score_save_high_score(int score_val)
{
    FILE *file = fopen(FILENAME, "w");
    if (file != NULL)
    {
        fprintf(file, "%d", score_val);
        fclose(file);
    }
}

ScoreSystem score_init(float start_x)
{
    ScoreSystem score = {0};
    score.starting_x = start_x;
    score.total_shifted_x = 0.0f;
    score.max_distance_reached = 0.0f;
    score.current_score = 0;

    score.high_score = score_load_high_score();

    return score;
}

void score_reset_current(ScoreSystem *score, float start_x)
{
    score->starting_x = start_x;
    score->total_shifted_x = 0.0f;
    score->max_distance_reached = 0.0f;
    score->current_score = 0;
    score->high_score = score_load_high_score();
}

void score_update(ScoreSystem *score, float car_x)
{

    float actual_x = car_x + score->total_shifted_x;
    float current_distance = actual_x - score->starting_x;

    float distance_in_meters = current_distance / 100.0f;

    if (distance_in_meters > score->max_distance_reached)
    {
        score->max_distance_reached = distance_in_meters;
    }

    score->current_score = (int)score->max_distance_reached;

    if (score->current_score > score->high_score)
    {
        score->high_score = score->current_score;

        score_save_high_score(score->high_score);
    }
}

void score_shift(ScoreSystem *score, float shift_x)
{
    score->total_shifted_x += shift_x;
}

void score_draw(ScoreSystem *score, Font font)
{
    char high_str[64];
    char curr_str[64];

    snprintf(high_str, sizeof(high_str), "HIGH SCORE : %d m", score->high_score);
    snprintf(curr_str, sizeof(curr_str), "SCORE      : %d m", score->current_score);

    DrawTextEx(font, high_str, (Vector2){40, 30}, 40, 0, YELLOW);
    DrawTextEx(font, curr_str, (Vector2){40, 80}, 40, 0, WHITE);
}