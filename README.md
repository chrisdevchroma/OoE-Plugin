# OoE-Plugin

## Info:
A plugin that translates the PS Vita game "Mahouka Koukou no Rettousei: Out of Order"/"魔法科高校の劣等生 Out of Order" to English.<br/>
Or in simpler terms, injects English text into the game using offset addresses.

## How to install:
- Copy plugin file "OoE-Plugin.suprx" to "urx0:/data", or any other plugin directory
- Edit the main tai `confg.txt` file (if in doubt, use `ur0:tai/config.txt`) and add lines:<br/>
`*PCSG00456`<br/>
`uX0:DIR_WHERE_PLUGIN_IS/OoE-Plugin.suprx`
- Copy bin file `translation.bin` to `ux0:data/OoE` (if folder does not exist, create it.)
- Restart the console to reload taiHEN's `config.txt` from a clean state.

## How to build:
```
mkdir build && cd build
cmake ..
make
```

## Thanks to:
><b>xyz</b> - For helping me with my basic knowledge of C and telling me how to properly do things.<br/>

><b>Rinnegatamante</b> - For showing what was up with weird behavior of pointers and objects not being properly allocated.
The plugin would have still been shitty and broken if not told this.<br/>

><b>[hz86](https://github.com/hz86)</b> - For the [original code](https://github.com/hz86/mask_of_truth) to make this plugin work with NoNpDrm.

><b>Jetbrains</b> - For making CLion
