#include "includes.h"

#pragma region Startup/Shutdown

MXB_EXPORT int Startup(char *_szSavePath)
{
	/*
	return value is requested rate
	0 = 100hz; 1 = 50hz; 2 = 20hz; 3 = 10hz; -1 = disable
	*/

	DbgMsg("[FN] " __FUNCDNAME__ "\n");

	RPC::start_unix_time = time(0);

	std::thread rpc_thread(RPC::Thread);
	rpc_thread.detach();

	return 3;
}

/* called when software is closed */
MXB_EXPORT void Shutdown()
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");

	RPC::shutdown_called = true;
	RPC::Destroy();
}

#pragma endregion

#pragma region GetMod Functions

MXB_EXPORT char *GetModID()
{
#ifdef CONSOLE
	// Called early so alloc here
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Debug");
#endif

	DbgMsg("[FN] " __FUNCDNAME__ "\n");
	return (char*)"mxbikes";
}

MXB_EXPORT int GetModDataVersion()
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");
	return 8;
}

MXB_EXPORT int GetInterfaceVersion()
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");
	return 9;
}

#pragma endregion

#pragma region Main Functions

/* called when event is initialized. This function is optional */
MXB_EXPORT void EventInit(void *_pData,int _iDataSize)
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");

	SPluginsBikeEvent_t *psEventData = (SPluginsBikeEvent_t*)_pData;
	if (!psEventData)
		return;

	strcpy_s(RPC::bike_name, psEventData->m_szBikeName);
	strcpy_s(RPC::track_name, psEventData->m_szTrackName);

	RPC::game_state = psEventData->m_iType;
}

/* called when bike goes to track. This function is optional */
MXB_EXPORT void RunInit(void *_pData,int _iDataSize)
{
	SPluginsBikeSession_t *psSessionData = (SPluginsBikeSession_t*)_pData;
	if (!psSessionData)
		return;

	RPC::on_track = true;
}

/* called when bike leaves the track. This function is optional */
MXB_EXPORT void RunDeinit()
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");

	RPC::lap_num = 0;
	RPC::on_track = false;
}

/* called when simulation is started / resumed. This function is optional */
MXB_EXPORT void RunStart()
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");

	RPC::sim_paused = false;
}

/* called when simulation is paused. This function is optional */
MXB_EXPORT void RunStop()
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");

	RPC::sim_paused = true;
}

/* This function is optional */
MXB_EXPORT void RaceLap(void *_pData,int _iDataSize)
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");

	SPluginsRaceLap_t *psRaceLap = (SPluginsRaceLap_t*)_pData;
	if (!psRaceLap)
		return;

	RPC::lap_num = psRaceLap->m_iLapNum;
}

/* This function is optional */
MXB_EXPORT void RaceSplit(void *_pData,int _iDataSize)
{
	DbgMsg("[FN] " __FUNCDNAME__ "\n");

	SPluginsRaceSplit_t *psRaceSplit = (SPluginsRaceSplit_t*)_pData;
	if (!psRaceSplit)
		return;

	RPC::lap_num = psRaceSplit->m_iLapNum;
}

#pragma endregion