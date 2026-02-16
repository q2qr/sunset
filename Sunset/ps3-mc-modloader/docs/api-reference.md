# API Reference

- `ModLoader_Init()` initializes memory APIs and scans the mod directory.
- `ModLoader_Tick()` calls `onTick` for each active mod.
- `ModLoader_Shutdown()` unloads loaded mod PRX modules.
- `ReadMemory<T>() / WriteMemory<T>()` read and write process memory.
- `MCOffsets` exposes known Minecraft PS3 offsets.
