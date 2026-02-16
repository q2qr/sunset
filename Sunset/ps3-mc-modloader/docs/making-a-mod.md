# Making a Mod

1. Include `sdk/ModLoader.h`.
2. Implement `onLoad`, `onUnload`, and optional `onTick`.
3. Export `extern "C" Mod ModInfo`.
4. Build as `.sprx` and place it in the `mods` folder used by the loader.
