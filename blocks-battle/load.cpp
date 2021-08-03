#include "pch.h"
#include "load.h"

Load::Load(int btnx, int btny, int wid, int len, const char* text) :Button(btnx, btny, wid, len, text) {}

void Load::pressfuc()
{
	if (!press) return;
	Game::initial(2);
	Game::play();
}

void Load::save()
{
	FILE* save = fopen("save.txt", "w");
	if (save == NULL) return;
	for (int k = 0; k < BRICKLINE; k++)
	{
		for (int i = 0; i < BRICKROW; i++)
			fprintf_s(save, "%d ", Brick::map[k][i]);
		fputs("\n", save);
	}
	fprintf_s(save, "%d\n", Stage::stage);
	fprintf_s(save, "%d\n", Color::type);
	if (Color::type == CUSTOMIZE)
		for (int k = 0; k < BRICKLINE; k++)
		{
			for (int i = 0; i < BRICKROW; i++)
				fprintf(save, "%x ", Brick::color[k][i]);
			fputs("\n", save);
		}
	fprintf(save, "%d\n", Top::score);
	fprintf(save, "%d\n", Heart::value);
	fprintf(save, "%d\n", ((clock() - Time::t) / CLOCKS_PER_SEC + Time::t_save));
	fprintf(save, "%f %f %f %f", Ball::ball->x, Ball::ball->y, Ball::ball->x_move, Ball::ball->y_move);
	fclose(save);
}

bool Load::read()
{
	FILE* save = fopen("save.txt", "r");
	if (save == NULL) return false;

	for (int k = 0; k < BRICKLINE; k++)
		for (int i = 0; i < BRICKROW; i++)
			fscanf_s(save, "%d", &Brick::map[k][i]);

	fscanf_s(save, "%d", &Stage::stage);
	fscanf_s(save, "%d", &Color::type);
	if (Color::type == CUSTOMIZE)
		for (int k = 0; k < BRICKLINE; k++)
			for (int i = 0; i < BRICKROW; i++)
				fscanf_s(save, "%x", &Brick::color[k][i]);

	fscanf_s(save, "%d", &Top::score);
	fscanf_s(save, "%d", &Heart::value);
	fscanf_s(save, "%d", &Time::t_save);
	fscanf_s(save, "%lf %lf %lf %lf", &Ball::ball->x, &Ball::ball->y, &Ball::ball->x_move, &Ball::ball->y_move);

	fclose(save);
	return true;
}
