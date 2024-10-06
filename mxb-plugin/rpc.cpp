#include "includes.h"

namespace RPC
{
	// Private members
	discord::Core* instance = nullptr;

	// Callbacks
	void UpdateCallback(discord::Result result)
	{
		switch (result)
		{
		case discord::Result::Ok:
			//DbgMsg("[+] Updated activity\n");
			break;

			/* Doesnt work */
		//case discord::Result::NotRunning:
		//	// Destroy instance if discord is closed, thread will attempt to create a new one
		//	RPC::Destroy();
		//	DbgMsg("[ERR] Discord application closed, instance destroyed\n");
		//	break;

		default:
			DbgMsg("[ERR] Failed to update activity\n");
			break;
		}
	}

	void ClearCallback(discord::Result result)
	{
		switch (result)
		{
		case discord::Result::Ok:
			DbgMsg("[+] Cleared activity\n");
			break;

			/* Doesnt work */
		//case discord::Result::NotRunning:
		//	// Destroy instance if discord is closed, thread will attempt to create a new one
		//	RPC::Destroy();
		//	DbgMsg("[ERR] Discord application closed, instance destroyed\n");
		//	break;

		default:
			DbgMsg("[ERR] Failed to clear activity\n");
			break;
		}
	}

	// Receives logs from discord sdk
	void LogHookCallback(discord::LogLevel level, const char* message)
	{
		static const char* levels[5] =
		{
			"0",
			"Error",
			"Warn",
			"Info",
			"Debug",
		};

		DbgMsg("[DSC] Level: %s [ %s ]\n", levels[(int)level], message);
	}


	// Functions
	void Thread()
	{
		while (!shutdown_called)
		{
			if (!instance)
			{
				RPC::Create();

				// Sleep for a second so we dont attempt to spam create if unavailable at the moment
				if (!instance)
					Sleep(1000);
			}
			else
			{
				RPC::Update();

				// More than 4/s unnecessary
				Sleep(250);
			}
		}
	}

	void Create()
	{
		if (discord::Result result = discord::Core::Create(1286928297288011817, DiscordCreateFlags_Default, &instance); result != discord::Result::Ok)
		{
			DbgMsg("[ERR] Failed to create core instance (Result: %i)\n", result);
			return;
		}

		DbgMsg("[+] New Core instance created\n");

		instance->SetLogHook(discord::LogLevel::Error, LogHookCallback);
	}

	void Destroy()
	{
		if (instance)
		{
			// Only clear if were destroying through shutdown
			if (shutdown_called)
				instance->ActivityManager().ClearActivity(ClearCallback);

			instance->~Core();

			instance = nullptr;
		}
	}

	void Update()
	{
		if (!instance)
		{
			DbgMsg("[ERR] Update called with invalid instance\n");
			return;
		}

		// Runs all pending SDK callbacks https://discord.com/developers/docs/developer-tools/game-sdk#runcallbacks
		instance->RunCallbacks();

		static auto state_to_string = [](int state) -> const char*
		{
			return state == 1 ? "Testing" : "Racing"; // 1 = testing, 2 = race, 4 = straight rhythm (Pretty much a race)
		};

		discord::Activity activity = {};

		activity.SetType(discord::ActivityType::Playing); // Could put this to watching during replay/spectating
		activity.SetName("MX Bikes");

		auto& timestamps = activity.GetTimestamps();
		timestamps.SetStart(start_unix_time);
		timestamps.SetEnd(0);

		auto& assets = activity.GetAssets();
		assets.SetLargeImage("rpc-icon");
		assets.SetLargeText("MX Bikes");

		if (time(0) - last_spectating_unix_time <= 1 && draw_state > 0/* spec or replay */) // Could use an std::chrono clock for this
		{
			if (draw_state == 1)
			{
				activity.SetState("Spectating");
				activity.SetDetails(track_name);
			}
			else
			{
				activity.SetState("Watching Replay");
				activity.SetDetails(tfm::format("%s on %s", track_name, bike_name).c_str());
			}
		}
		else if (!on_track)
		{
			activity.SetState("In Menus");
			activity.SetDetails("");
		}
		else
		{
			activity.SetState(sim_paused ? "Paused" : tfm::format("%s (Lap %i)", state_to_string(game_state), lap_num + 1).c_str());
			activity.SetDetails(tfm::format("%s on %s", track_name, bike_name).c_str());
		}

		instance->ActivityManager().UpdateActivity(activity, UpdateCallback);
	}
}