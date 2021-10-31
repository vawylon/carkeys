#include <a_samp>
#include <foreach>

/*

	GivePlayerKeyVehicle(playerid, vehicleid)
        Выдать ключ от авто (vehicleid) игроку (playerid)
        возвращает 1 при удаче, возвращает 0 если авто не существует

    GivePlayerKeyVehicles(playerid, vehicles[], vhsize = sizeof vehicles)
                Выдать ключи от автомобилей (vehicles) игроку (playerid)
                Всегда возвращает 1

    RemovePlayerKeyVehicle(playerid, vehicleid)
        Отобрать ключи от автомобиля (vehicleid)  у игрока (playerid)
        Всегда возвращает 1

    RemovePlayerKeyVehicles(playerid, vehicles[], vhsize = sizeof vehicles)
       Забрать ключи у игрока (playerid) от автомобилей (vehicles)
       Всегда возвращает 1

    RemovePlayersKeyVehicle(vehicleid)
        Отобрать ключи у всех игроков от автомобиля (vehicleid)
        Всегда возвращает 1

    GetPlayerKeysVehicles(playerid, vehiclesid[], sizekeys = sizeof(vehiclesid))
                Получить список автомобилей (vehiclesid) от которых есть ключи у игрока (playerid)
                Всегда возвращает 1

    IsPlayerKeyVehicle(playerid, vehicleid)
        Есть ли ключи от автомобиля (vehicleid) у игрока (playerid)
        Возвращает 0 если нет ключей, 1 если есть

    RemoveAllPlayerKeysVehicle(playerid)
       Отобрать у игрока (playerid) все ключи
       Всегда возвращает 1


	DestroyVehicle(vehicleid)
		Автоматически забирает у всех игроков ключи

	CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren = 0)
		При respawn_delay = -1 автомобиль уничтожается, у всех игроков отбираются ключи

*/

new bool:isremovekey[MAX_VEHICLES];
native IsValidVehicle(vehicleid);

new Iterator:global_keys[MAX_PLAYERS]<MAX_VEHICLES>;
public OnGameModeInit()
{
	Iter_Init(global_keys);
#if defined kgm__OnGameModeInit
    return kgm__OnGameModeInit();
#endif
}
#if defined _ALS_OnGameModeInit
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    kgm__OnGameModeInit
#if defined kgm__OnGameModeInit
forward kgm__OnGameModeInit();
#endif


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
