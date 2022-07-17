# CarKeys - Keys control pawn

![image](https://pawn-wiki.ru/uploads/imgs/img_1635253141___-1.png)

### GivePlayerKeyVehicle(playerid, vehicleid)
> Give the key to the car (vehicleid) to the player (playerid)
> returns 1 with luck, returns 0 if the car does not exist

```C
new vehicle_infernus;
public OnGameModeInit()
{
    vehicle_infernus = CreateVehicle(411, 131.9713,-83.2864,1.4297,212.7320, 1, 1, 5000);
    return 1;
}

CMD:addkey(playerid, p[])
{
        GivePlayerKeyVehicle(playerid, vehicle_infernus);
        SendClientMessage(playerid, 0x44FF44FF, " Now you have the keys to Infernus!");
        return 1;
}
```
### GivePlayerKeyVehicles(playerid, vehicles[], vhsize = sizeof vehicles)
> Giving car keys (vehicles) to a player (playerid)
> Always returns 1

```C
new vehicle_infernus;
public OnGameModeInit()
{
    vehicle_infernus = CreateVehicle(411, 131.9713,-83.2864,1.4297,212.7320, 1, 1, 5000);
    return 1;
}

CMD:addkey(playerid, p[])
{
        GivePlayerKeyVehicle(playerid, vehicle_infernus);
        SendClientMessage(playerid, 0x44FF44FF, " Now you have the keys to Infernus!");
        return 1;
}
```
### RemovePlayerKeyVehicle(playerid, vehicleid)
> Take away the car keys (vehicleid) from the player (playerid)
> Always returns 1

```C
CMD:removekey(playerid, p[])
{
        RemovePlayerKeyVehicle(playerid, vehicle_infernus);
        SendClientMessage(playerid, 0x44FF44FF, " Now you don't have the keys to Infernus!");
        return 1;
}
```

### RemovePlayerKeyVehicles(playerid, vehicles[], vhsize = sizeof vehicles)
> Pick up the keys from the player (playerid) from cars (vehicles)
> Always returns 1

```C
new LSPD_cars[5];
public OnGameModeInit()
{
    LSPD_cars[0] = CreateVehicle(411, 131.9713,-83.2864,1.4297,212.7320, 1, 1, 5000);
    LSPD_cars[1] = CreateVehicle(411, 131.9715,-83.2864,1.4297,212.7320, 1, 1, 5000);
    LSPD_cars[2] = CreateVehicle(411, 131.9717,-83.2864,1.4297,212.7320, 1, 1, 5000);
    LSPD_cars[3] = CreateVehicle(411, 131.9719,-83.2864,1.4297,212.7320, 1, 1, 5000);
    LSPD_cars[4] = CreateVehicle(411, 131.9721,-83.2864,1.4297,212.7320, 1, 1, 5000);
    return 1;
}

CMD:addkeys(playerid, p[])
{
        GivePlayerKeyVehicles(playerid, LSPD_cars);
        SendClientMessage(playerid, 0x44FF44FF, " Now you have the keys to the LSPD cars!");
        return 1;
}
```

### RemovePlayersKeyVehicle(vehicleid)
> Take away the keys from all players from the car (vehicleid)
> Always returns 1

```C
CMD:remove_lspd(playerid, p[])
{
        RemovePlayerKeyVehicles(playerid, LSPD_cars);
        SendClientMessage(playerid, 0x44FF44FF, " You threw away all the keys to the LSPD cars!");
        return 1;
}
```
### GetPlayerKeysVehicles(playerid, vehiclesid[], sizekeys = sizeof(vehiclesid))
> Get a list of cars (vehiclesid) from which the player has keys (playerid)
> Always returns 1

### IsPlayerKeyVehicle(playerid, vehicleid)
> Does the player (playerid) have the keys to the car (vehicleid)
> Returns 0 if there are no keys, 1 if there are 

```C
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
        if(!IsPlayerKeyVehicle(playerid, vehicleid) && ispassenger == 0)
        {
                RemovePlayerFromVehicle(playerid);
                SendClientMessage(playerid, 0xFF4444FF, "You don't have keys to transport!");
        }
        return 1;
}
```

### RemoveAllPlayerKeysVehicle(playerid)
> Take away all keys from the player (playerid)
> Always returns 1

```C
CMD:addkeys(playerid, p[])
{
        RemoveAllPlayerKeysVehicle(playerid);
        SendClientMessage(playerid, 0x44FF44FF, " You threw away all the car keys!");
        return 1;
}
```


### DestroyVehicle(vehicleid)
> Automatically takes the keys from all players

### CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren = 0)
> When respawn_delay = -1, the car is destroyed, the keys are taken from all players