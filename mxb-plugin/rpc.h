#pragma once

namespace RPC
{
	// Public members
	inline int lap_num = 0;
	inline int game_state = 1; // m_iType in bike or race event  /* 1 = testing; 2 = race; 4 = straight rhythm */
	inline bool sim_paused = true; // RunStart and RunStop
	inline char bike_name[100] = "Bike";
	inline char track_name[100] = "Track";
	inline unsigned long long start_unix_time = 0;

	// Functions

	void Create();
	void Destroy();
	void Update();

	void Thread();
}