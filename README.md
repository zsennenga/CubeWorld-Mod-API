CubeWorld-Mod-API
=================

This is a Mod API for the game Cube World. It uses DLL injection and memory editing to get Cube World to load 
plugin DLLs and then execute user code at specified "events" (such as npcInteract, playerJump, and so on).

Plugins interact with entities, such as "Player" that mirror assembly values and allow plugin developers to modify
properties of the game world without having to work with asm.
