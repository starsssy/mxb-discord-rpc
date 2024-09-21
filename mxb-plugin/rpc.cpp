#include "includes.h"

namespace RPC
{
	// Private members
	discord::Core* instance = nullptr;


	// Callbacks
	void UpdateCallback(discord::Result result)
	{
		if (result != discord::Result::Ok)
			DbgMsg("[ERR] Failed to update activity\n");

		else
			DbgMsg("[+] Updated activity\n");
	}

	void ClearCallback(discord::Result result)
	{
		if (result != discord::Result::Ok)
			DbgMsg("[ERR] Failed to clear activity\n");

		else
			DbgMsg("[+] Cleared activity\n");
	}


	// Functions
	void Thread()
	{
		// Called until instance is valid
		while (!instance)
		{
			RPC::Create();

			// Sleep for a second so we dont attempt to spam create if unavailable at the moment
			if (!instance)
				Sleep(1000);
		}

		while (true)
		{
			RPC::Update();

			// More than 4/s unnecessary
			Sleep(250);
		}
	}

	void Create()
	{
		if (discord::Core::Create(1286928297288011817, DiscordCreateFlags_NoRequireDiscord, &instance) != discord::Result::Ok)
		{
			DbgMsg("[ERR] Failed to create core instance\n");
			return;
		}

		start_unix_time = time(0);
	}

	void Destroy()
	{
		instance->ActivityManager().ClearActivity(ClearCallback);
		instance->~Core();
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
			return state == 1 ? "Testing" : "Race"; // 1 = testing, 2 = race, 4 = straight rhythm (Pretty much a race)
		};

		discord::Activity activity = {};

		activity.SetType(discord::ActivityType::Playing);
		activity.SetName("MX Bikes");

		auto& timestamps = activity.GetTimestamps();
		timestamps.SetStart(start_unix_time);
		timestamps.SetEnd(0);

		auto& assets = activity.GetAssets();
		assets.SetLargeImage("rpc-icon");
		assets.SetLargeText("MX Bikes");

		if (sim_paused)
		{
			activity.SetState("In Menus");
			activity.SetDetails("");
		}
		else
		{
			activity.SetState(tfm::format("%s (Lap %i)", state_to_string(game_state), lap_num + 1).c_str());
			activity.SetDetails(tfm::format("%s on %s", track_name, bike_name).c_str());
		}

		instance->ActivityManager().UpdateActivity(activity, UpdateCallback);
	}
}