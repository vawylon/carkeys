/*
GitHub
	GivePlayerKeyVehicle(playerid, vehicleid)
		Give the key to the car (vehicleid) to the player (playerid)
		returns 1 with luck, returns 0 if the car does not exist

	GivePlayerKeyVehicles(playerid, vehicles[], vhsize = sizeof vehicles)
		Giving car keys (vehicles) to a player (playerid)
		Always returns 1

	RemovePlayerKeyVehicle(playerid, vehicleid)
		Take away the car keys (vehicleid) from the player (playerid)
		Always returns 1

	RemovePlayerKeyVehicles(playerid, vehicles[], vhsize = sizeof vehicles)
		Pick up the keys from the player (playerid) from cars (vehicles)
		Always returns 1

	RemovePlayersKeyVehicle(vehicleid)
		Take away the keys from all players from the car (vehicleid)
		Always returns 1

	GetPlayerKeysVehicles(playerid, vehiclesid[], sizekeys = sizeof(vehiclesid))
		Get a list of cars (vehiclesid) from which the player has keys (playerid)
		Always returns 1

	IsPlayerKeyVehicle(playerid, vehicleid)
		Does the player (playerid) have the keys to the car (vehicleid)
		Returns 0 if there are no keys, 1 if there are

	RemoveAllPlayerKeysVehicle(playerid)
		Take away all keys from the player (playerid)
		Always returns 1


	DestroyVehicle(vehicleid)
		Automatically takes the keys from all players

	CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren = 0)
		When respawn_delay = -1, the car is destroyed, the keys are taken from all players

*/
#include <a_samp>
#include <foreach> // https://github.com/karimcambridge/SAMP-foreach/releases

static bool:isremovekey[MAX_VEHICLES];
#if !defined IsValidVehicle
        native IsValidVehicle(vehicleid);
#endif

static Iterator:global_keys[MAX_PLAYERS]<MAX_VEHICLES>;

stock InitCarKeys()
{
	Iter_Init(global_keys);
}


public OnVehicleSpawn(vehicleid)
{
	if(isremovekey[vehicleid] == true) DestroyVehicle(vehicleid);
#if defined kgm__OnVehicleSpawn
    return kgm__OnVehicleSpawn(vehicleid, killerid);
#endif
}
#if defined _ALS_OnVehicleSpawn
    #undef    OnVehicleSpawn
#else
    #define    _ALS_OnVehicleSpawn
#endif
#define    OnVehicleSpawn    kgm__OnVehicleSpawn
#if defined kgm__OnVehicleSpawn
forward kgm__OnVehicleSpawn(vehicleid, killerid);
#endif


stock GivePlayerKeyVehicle(playerid, vehicleid)
{
    if(!IsValidVehicle(vehicleid)) return 0;
	Iter_Add(global_keys[playerid], vehicleid);
	return 1;
}

stock GivePlayerKeyVehicles(playerid, vehicles[], vhsize = sizeof vehicles)
{
	for(new index; index<vhsize; index++)
	{
 		GivePlayerKeyVehicle(playerid, vehicles[index]);
	}
	return 1;
}

stock RemovePlayerKeyVehicle(playerid, vehicleid)
{
	Iter_Remove(global_keys[playerid], vehicleid);
	return 1;
}

stock RemovePlayerKeyVehicles(playerid, vehicles[], vhsize = sizeof vehicles)
{
	for(new i; i<vhsize; i++)
	{
	    RemovePlayerKeyVehicle(playerid, vehicles[i]);
	}
	return 1;
}

stock RemovePlayersKeyVehicle(vehicleid)
{
	foreach(Player, playerid)
	{
	    RemovePlayerKeyVehicle(i, vehicleid);
	}
	return 1;
}

stock GetPlayerKeysVehicles(playerid, vehiclesid[], sizekeys = sizeof(vehiclesid))
{
	new i;
	foreach(global_keys[playerid], key)
	{
	    if(i < sizekeys) vehiclesid[i] = key; else break;
		i++;
	}
	return 1;
}

stock RemoveAllPlayerKeysVehicle(playerid)
{
	Iter_Clear(global_keys[playerid]);
	return 1;
}

stock IsPlayerKeyVehicle(playerid, vehicleid)
{
	return Iter_Contains(global_keys[playerid], vehicleid);
}

stock keys_DestroyVehicle(vehicleid)
{
    isremovekey[vehicleid] = false;
    RemovePlayersKeyVehicle(vehicleid);
    return DestroyVehicle(vehicleid);
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
	#define DestroyVehicle keys_DestroyVehicle
	
	
stock keys_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren = 0)
{
	new vehicleid = CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren);
    if(respawn_delay == -1) isremovekey[vehicleid] = true;
    return vehicleid;
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
	#define CreateVehicle keys_CreateVehicle
