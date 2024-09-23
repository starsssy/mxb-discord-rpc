#pragma once

namespace RPC
{
	// Public members
	inline int lap_num = 0;
	inline int game_state = 1; // m_iType in bike or race event  /* 1 = testing; 2 = race; 4 = straight rhythm */
	inline int draw_state = -1; // _iState in the Draw function   /* _iState: 0 = on track; 1 = spectate; 2 = replay. */
	inline bool sim_paused = true; // RunStart and RunStop
	inline bool on_track = false; // RunInit and RunDeinit
	inline bool shutdown_called = false;
	inline char bike_name[100] = "Bike";
	inline char track_name[100] = "Track";
	inline unsigned long long start_unix_time = 0;
	inline unsigned long long last_spectating_unix_time = 0; // Set when the SpectateVehicles function is called - Used for checking if were actually still spectating

	// Functions
	void Create();
	void Destroy();
	void Update();

	void Thread();
}