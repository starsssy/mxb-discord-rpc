#pragma once

// All structs included in the example plugin files listed on the MX-Bikes download page
// https://mx-bikes.com/downloads/mxb_example.c
// https://www.kartracing-pro.com/downloads/input_int.c

// Main structs

typedef struct
{
	char m_szRiderName[100];
	char m_szBikeID[100];
	char m_szBikeName[100];
	int m_iNumberOfGears;
	int m_iMaxRPM;
	int m_iLimiter;
	int m_iShiftRPM;
	float m_fEngineOptTemperature;									/* degrees Celsius */
	float m_afEngineTemperatureAlarm[2];							/* degrees Celsius. Lower and upper limits */
	float m_fMaxFuel;												/* fuel tank capacity. liters */
	float m_afSuspMaxTravel[2];										/* maximum travel of the shocks. meters. 0 = front; 1 = rear. */
	float m_fSteerLock;												/* degrees */
	char m_szCategory[100];
	char m_szTrackID[100];
	char m_szTrackName[100];
	float m_fTrackLength;											/* centerline length. meters */
	int m_iType;													/* 1 = testing; 2 = race; 4 = straight rhythm */
} SPluginsBikeEvent_t;

typedef struct
{
	int m_iSession;													/* testing: 0 = waiting; 1 = in progress. Race: 0 = waiting; 1 = practice; 2 = pre-qualify; 3 = qualify; 4 = warmup; 5 = race1; 6 = race2; straight rhythm: 0 = waiting; 1 = practice; 2 = round; 3 = quarter-finals; 4 = semi-finals; 5 = final */
	int m_iConditions;												/* 0 = sunny; 1 = cloudy; 2 = rainy */
	float m_fAirTemperature;										/* degrees Celsius */
	char m_szSetupFileName[100];
} SPluginsBikeSession_t;

typedef struct
{
	int m_iRPM;														/* engine rpm */
	float m_fEngineTemperature;										/* degrees Celsius */
	float m_fWaterTemperature;										/* degrees Celsius */
	int m_iGear;													/* 0 = Neutral */
	float m_fFuel;													/* liters */
	float m_fSpeedometer;											/* meters/second */
	float m_fPosX,m_fPosY,m_fPosZ;									/* world position of a reference point attached to chassis ( not CG ) */
	float m_fVelocityX,m_fVelocityY,m_fVelocityZ;					/* velocity of CG in world coordinates. meters/second */
	float m_fAccelerationX,m_fAccelerationY,m_fAccelerationZ;		/* acceleration of CG local to chassis rotation, expressed in G ( 9.81 m/s2 ) and averaged over the latest 10ms */
	float m_aafRot[3][3];											/* rotation matrix of the chassis. It incorporates lean and wheeling */
	float m_fYaw,m_fPitch,m_fRoll;									/* degrees, -180 to 180 */
	float m_fYawVelocity,m_fPitchVelocity,m_fRollVelocity;			/* degress / second */
	float m_afSuspLength[2];										/* shocks length. meters. 0 = front; 1 = rear. */
	float m_afSuspVelocity[2];										/* shocks velocity. meters/second. 0 = front; 1 = rear */
	int m_iCrashed;													/* 1 = rider is detached from bike */
	float m_fSteer;													/* degrees. Negative = right  */
	float m_fThrottle;												/* 0 to 1 */
	float m_fFrontBrake;											/* 0 to 1 */
	float m_fRearBrake;												/* 0 to 1 */
	float m_fClutch;												/* 0 to 1. 0 = Fully engaged */
	float m_afWheelSpeed[2];										/* meters/second. 0 = front; 1 = rear */
	int m_aiWheelMaterial[2];										/* material index. 0 = not in contact */
	float m_afBrakePressure[2];										/* kPa */
	float m_fSteerTorque;											/* Nm */
} SPluginsBikeData_t;

typedef struct
{
	int m_iLapNum;													/* lap index */
	int m_iInvalid;
	int m_iLapTime;													/* milliseconds */
	int m_iBest;													/* 1 = best lap */
} SPluginsBikeLap_t;

typedef struct
{
	int m_iSplit;													/* split index */
	int m_iSplitTime;												/* milliseconds */
	int m_iBestDiff;												/* milliseconds. Difference with best lap */
} SPluginsBikeSplit_t;


// Drawing structs

typedef struct
{
	float m_aafPos[4][2];			/* 0,0 -> top left. 1,1 -> bottom right. counter-clockwise */
	int m_iSprite;					/* 1 based index in SpriteName buffer. 0 = fill with m_ulColor */
	unsigned long m_ulColor;		/* ABGR */
} SPluginQuad_t;

typedef struct
{
	char m_szString[100];
	float m_afPos[2];				/* 0,0 -> top left. 1,1 -> bottom right */
	int m_iFont;					/* 1 based index in FontName buffer */
	float m_fSize;
	int m_iJustify;					/* 0 = left; 1 = center; 2 = right */
	unsigned long m_ulColor;		/* ABGR */
} SPluginString_t;


// Track centerline structs

typedef struct
{
	int m_iType;					/* 0 = straight; 1 = curve */
	float m_fLength;				/* meters */
	float m_fRadius;				/* curve radius in meters. < 0 for left curves; 0 for straights */
	float m_fAngle;					/* start angle in degrees. 0 = north */
	float m_afStart[2];				/* start position in meters */
	float m_fHeight;				/* start height in meters */
} SPluginsTrackSegment_t;


// Race data structs

typedef struct
{
	int m_iType;										/* 1 = testing; 2 = race; 4 = straight rhythm; -1 = loaded replay */
	char m_szName[100];
	char m_szTrackName[100];
	float m_fTrackLength;								/* meters */
} SPluginsRaceEvent_t;

typedef struct
{
	int m_iRaceNum;										/* unique race number */
	char m_szName[100];
	char m_szBikeName[100];
	char m_szBikeShortName[100];
	char m_szCategory[100];
	int m_iUnactive;									/* if set to 1, the rider left the event and the following fields are not set */
	int m_iNumberOfGears;
	int m_iMaxRPM;
} SPluginsRaceAddEntry_t;

typedef struct
{
	int m_iRaceNum;										/* race number */
} SPluginsRaceRemoveEntry_t;

typedef struct
{
	int m_iSession;										/* testing: 0 = waiting; 1 = in progress. Race: 0 = waiting; 1 = practice; 2 = pre-qualify; 3 = qualify; 4 = warmup; 5 = race1; 6 = race2 */
	int m_iSessionState;								/* testing / waiting: always 0. practice / pre-qualify / warmup: 16 = in progress; 32 = completed. qualify / race1 / race2: 16 = in progress; 64 = sighting lap; 256 = pre-start; 512 = race over; 1024 = completed */
	int m_iSessionLength;								/* milliseconds. 0 = no limit */
	int m_iSessionNumLaps;
	int m_iConditions;									/* 0 = sunny; 1 = cloudy; 2 = rainy */
	float m_fAirTemperature;							/* degrees Celsius */
} SPluginsRaceSession_t;

typedef struct
{
	int m_iSession;										/* testing: 0 = waiting; 1 = in progress. Race: 0 = waiting; 1 = practice; 2 = pre-qualify; 3 = qualify; 4 = warmup; 5 = race1; 6 = race2 */
	int m_iSessionState;								/* testing / waiting: always 0. practice / pre-qualify / warmup: 16 = in progress; 32 = completed. qualify / race1 / race2: 16 = in progress; 64 = sighting lap; 256 = pre-start; 512 = race over; 1024 = completed */
	int m_iSessionLength;								/* milliseconds. 0 = no limit */
} SPluginsRaceSessionState_t;

typedef struct
{
	int m_iSession;										/* testing: 0 = waiting; 1 = in progress. Race: 0 = waiting; 1 = practice; 2 = pre-qualify; 3 = qualify; 4 = warmup; 5 = race1; 6 = race2 */
	int m_iRaceNum;										/* race number */
	int m_iLapNum;										/* lap index */
	int m_iInvalid;
	int m_iLapTime;										/* milliseconds */
	int m_aiSplit[2];									/* milliseconds */
	int m_iBest;										/* 1 = personal best lap; 2 = overall best lap */
} SPluginsRaceLap_t;

typedef struct
{
	int m_iSession;										/* testing: 0 = waiting; 1 = in progress. Race: 0 = waiting; 1 = practice; 2 = pre-qualify; 3 = qualify; 4 = warmup; 5 = race1; 6 = race2 */
	int m_iRaceNum;										/* race number */
	int m_iLapNum;										/* lap index */
	int m_iSplit;										/* split index */
	int m_iSplitTime;									/* milliseconds */
} SPluginsRaceSplit_t;

typedef struct
{
	int m_iSession;
	int m_iRaceNum;
	int m_iTime;
} SPluginsRaceHoleshot_t;

typedef struct
{
	int m_iSession;										/* testing: 0 = waiting; 1 = in progress. Race: 0 = waiting; 1 = practice; 2 = pre-qualify; 3 = qualify; 4 = warmup; 5 = race1; 6 = race2 */
	int m_iRaceNum;										/* race number */
	int m_iCommunication;								/* 1 = change state; 2 = penalty */
	int m_iState;										/* 1 = DNS; 2 = retired; 3 = DSQ */
	int m_iReason;										/* Reason for DSQ. 0 = jump start; 1 = too many offences; 2 = director */
	int m_iOffence;										/* 1 = jump start; 2 = cutting */
	int m_iLap;											/* lap index */
	int m_iType;										/* always 0 = time penalty */
	int m_iTime;										/* milliseconds. Penalty time */
} SPluginsRaceCommunication_t;

typedef struct
{
	int m_iSession;										/* testing: 0 = waiting; 1 = in progress. Race: 0 = waiting; 1 = practice; 2 = pre-qualify; 3 = qualify; 4 = warmup; 5 = race1; 6 = race2 */
	int m_iSessionState;								/* testing / waiting: always 0. practice / pre-qualify / warmup: 16 = in progress; 32 = completed. qualify / race1 / race2: 16 = in progress; 64 = sighting lap; 256 = pre-start; 512 = race over; 1024 = completed */
	int m_iSessionTime;									/* milliseconds. Current session time */
	int m_iNumEntries;									/* number of entries */
} SPluginsRaceClassification_t;

typedef struct
{
	int m_iRaceNum;										/* race number */
	int m_iState;										/* 1 = DNS; 2 = retired; 3 = DSQ */
	int m_iBestLap;										/* milliseconds */
	int m_iBestLapNum;									/* best lap index */
	int m_iNumLaps;										/* number of laps */
	int m_iGap;											/* milliseconds */
	int m_iGapLaps;
	int m_iPenalty;										/* milliseconds */
	int m_iPit;											/* 0 = on track; 1 = in the pits */
} SPluginsRaceClassificationEntry_t;

typedef struct
{
	int m_iRaceNum;										/* race number */
	float m_fPosX,m_fPosY,m_fPosZ;						/* meters */
	float m_fYaw;										/* angle from north. degrees */
	float m_fTrackPos;									/* position on the centerline, from 0 to 1 */
	int m_iCrashed;
} SPluginsRaceTrackPosition_t;

typedef struct
{
	int m_iRaceNum;										/* race number */
	int m_iActive;										/* if set to 0, the vehicle is not active and the following fields are not set */
	int m_iRPM;											/* engine RPM */
	int m_iGear;										/* 0 = Neutral */
	float m_fSpeedometer;								/* meters/second */
	float m_fThrottle;									/* 0 to 1 */
	float m_fFrontBrake;								/* 0 to 1 */
	float m_fLean;										/* degrees. Negative = left */
} SPluginsRaceVehicleData_t;


// Replay structs

typedef struct
{
	int m_iRaceNum;
	char m_szName[100];
} SPluginsSpectateVehicle_t;


// Input structs

typedef struct
{
	char m_szName[100];
	char m_szUUID[37];						/* universally unique identifier */
	int m_iID;								/* internal unique ID */
	char m_iNumAxis;						/* number of axis */
	short m_aaiAxisRange[6][3];				/* min, max and center value of each axis */
	char m_iNumSliders;						/* number of sliders */
	short m_aiSliderRange[6];				/* max value of each slider */
	char m_iNumButtons;						/* number of buttons */
	char m_iNumPOV;							/* number of POVs */
	char m_iNumDials;						/* number of dials */
	char m_aiDialRange[8];					/* max value of dials */
} SControllerInfo_t;

typedef struct
{
	short m_aiAxis[6];
	short m_aiSlider[6];
	char m_aiButton[32];
	unsigned short m_aiPOV[2];
	char m_aiDial[8];
} SControllerData_t;