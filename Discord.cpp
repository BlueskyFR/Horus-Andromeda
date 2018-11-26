#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "discord_rpc.h"

static const char* APPLICATION_ID = "516386139452473355";
static int64_t StartTime;

void InitDiscord() {
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	/*handlers.ready = handleDiscordReady;
	handlers.errored = handleDiscordError;
	handlers.disconnected = handleDiscordDisconnected;
	handlers.joinGame = handleDiscordJoinGame;
	handlers.spectateGame = handleDiscordSpectateGame;
	handlers.joinRequest = handleDiscordJoinRequest;*/

	// Discord_Initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId)
	Discord_Initialize(APPLICATION_ID, &handlers, 1, "0");

}

void UpdatePresence() {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Encore en vie"; // State
	discordPresence.details = "Multijoueur"; // Mode
	discordPresence.startTimestamp = time(0);
	discordPresence.largeImageText = "C'est cool rich presence non ? :D";
	discordPresence.smallImageText = "Moi j'aime bien en tout cas :)";
	discordPresence.partyId = "0001"; // Id de la partie, on s'en fout
	discordPresence.partySize = 2; // Nb de joueurs actuel
	discordPresence.partyMax = 2; // Nb de joueurs max
	Discord_UpdatePresence(&discordPresence);
}