#include "FTScore.h"

FTScore::FTScore(const YEGameContext& _game_context):
	YEGameObject("Football Score", _game_context),
	_goal_sound_component(new YEAudioComponent(false)),
	_soundFilename("C:\\Game Assets\\goal_stadium_cheerin_.wav")
{
	// Score markers 3D game objects
	_score_marker_player = new FTScoreMarker(_game_context);
	_score_marker_ai = new FTScoreMarker(_game_context);

	addComponent(_goal_sound_component);

	_goal_widget_ui = new FTGoalWidgetUI(_game_context);
}

FTScore::~FTScore()
{
}

void FTScore::start()
{
	_score_marker_player->start();
	_score_marker_player->_isPositiveOffset = false;
	_score_marker_player->SetInitialPosition(1.7f);
	_score_marker_player->SetMarkerOffset(0.34333f);
	_score_marker_player->PlaceMarkerAt(0);

	_score_marker_ai->start();
	_score_marker_ai->_isPositiveOffset = true;
	_score_marker_ai->SetInitialPosition(-1.6f);
	_score_marker_ai->SetMarkerOffset(0.35333f);
	_score_marker_ai->PlaceMarkerAt(0);

	_goal_sound_component->start();
	_goal_sound_component->LoadSound("Goal SFX", _soundFilename);
	_goal_sound_component->SetVolume(1.0f);
	_goal_sound_component->SetPriority(1);

	_goal_widget_ui->start();
	_goal_widget_ui->OnWidgetUIHide = std::bind(&FTScore::ResetGameplay, this);
}

void FTScore::shutdown()
{
}

void FTScore::update(float _deltaTime)
{
	if (_active)
		_goal_widget_ui->update(_deltaTime);
}

void FTScore::IncrementScore(const char* player)
{
	if (_active)
	{
		if (strcmp(player, "Net Player") == 0)
		{
			_score_marker_ai->PlaceMarkerAt(++_aiScore);

			PlayGoalSound();

			_goal_widget_ui->Show();

			ResetBall();
		}
		else if (strcmp(player, "Net PlayerAI") == 0)
		{
			_score_marker_player->PlaceMarkerAt(++_playerScore);

			PlayGoalSound();

			_goal_widget_ui->Show();

			ResetBall();
		}
	}
}

void FTScore::PlayGoalSound()
{
	_goal_sound_component->PlaySound("Goal SFX");
}
