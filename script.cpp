/*Copyright (c) 2026 Savannah
Original source: https://github.com/Savannah-Lily/
Licensed under the MIT License
See LICENSE for details*/
#include "inc/keyboard.h"
#include "Keys.h"
#include "natives.h"
#include <cmath>
#include <string>

const float DegToRad = std::acos(-1) / 180;

void FlingEntity(bool ForceRagdoll, bool ragdoll, float speed, float UpForce, Entity entity, int RagdollType)
{
	if (RagdollType > 3)
	{
		RagdollType = 0;
	}

	if (RagdollType < 0)
	{
		RagdollType = 0;
	}

	if (ForceRagdoll)
	{
		PED::SET_PED_CAN_RAGDOLL(entity, true);
	}

	if (ragdoll)
	{
		PED::SET_PED_TO_RAGDOLL(entity, 2500, 10000, RagdollType, false, false, false);
	}

	float heading = ENTITY::GET_ENTITY_HEADING_FROM_EULERS(entity);
	float rad = heading * DegToRad;
	float dirX = -sin(rad);
	float dirY = cos(rad);
	ENTITY::SET_ENTITY_VELOCITY(entity, dirX * speed, dirY * speed, UpForce);
}

void ShowSubtitle(const char* message, int duration)
{
	HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message);
	HUD::END_TEXT_COMMAND_PRINT(duration, true);
}

std::string Format(float value)
{
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "%.1f", value);
	return buffer;
}

float LaunchSpeed = 100.0f;
float LaunchUpForce = 50.0f;

void ScriptMain()
{
	while (true)
	{
		WAIT(0);
		if (IsKeyDown(Keys::F7))
		{
			Ped PlayerPed = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(PlayerPed, true))
			{
				Entity PlayerCar = PED::GET_VEHICLE_PED_IS_IN(PlayerPed, true);
				FlingEntity(false, false, LaunchSpeed, LaunchUpForce, PlayerCar, 0);
			}
			else
			{
				FlingEntity(true, true, LaunchSpeed, LaunchUpForce, PlayerPed, 0);
			}
		}

		if (IsKeyJustUp(Keys::F8))
		{
			Player player = PLAYER::PLAYER_ID();
			PLAYER::SET_PLAYER_INVINCIBLE(player, !PLAYER::GET_PLAYER_INVINCIBLE(player));
			bool state = PLAYER::GET_PLAYER_INVINCIBLE(player);
			std::string InvincibilityMessage = std::string("Invincibility set to: ") + (state ? "true" : "false");
			ShowSubtitle(InvincibilityMessage.c_str(), 5000);
		}

		if (IsKeyDown(Keys::Add))
		{
			LaunchSpeed += 0.05f;
			std::string LaunchSpeedMessage = "Launch speed changed to: " + Format(LaunchSpeed);
			ShowSubtitle(LaunchSpeedMessage.c_str(), 5000);
		}
		
		if (IsKeyDown(Keys::Subtract))
		{
			LaunchSpeed -= 0.05f;
			std::string LaunchSpeedMessage = "Launch speed changed to: " + Format(LaunchSpeed);
			ShowSubtitle(LaunchSpeedMessage.c_str(), 5000);
		}

		if (IsKeyDown(Keys::Multiply))
		{
			LaunchUpForce += 0.05f;
			std::string LaunchForceMessage = "Launch up force changed to: " + Format(LaunchUpForce);
			ShowSubtitle(LaunchForceMessage.c_str(), 5000);
		}

		if (IsKeyDown(Keys::Divide))
		{
			LaunchUpForce -= 0.05f;
			std::string LaunchForceMessage = "Launch up force changed to: " + Format(LaunchUpForce);
			ShowSubtitle(LaunchForceMessage.c_str(), 5000);
		}
	}
}