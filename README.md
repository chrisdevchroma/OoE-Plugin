# OoE-Plugin

## Info:
A plugin that translates the PS Vita game "Mahouka Koukou no Rettousei: Out of Order"/"魔法科高校の劣等生 Out of Order" to English.<br/>
Or in simpler terms, injects English text into the game using offset addresses.

## How to install:
- Download plugin [kuio](https://github.com/Rinnegatamante/kuio)
- Copy plugin file "kuio.skprx" to "ur0:/tai" or any other plugin directory
- Copy plugin file "OoE-Plugin.suprx" to "urx0:/data" or any other plugin directory
- Edit the main tai `confg.txt` file (if in doubt, use `ur0:tai/config.txt`)
- Add line under the `*KERNEL` section:<br/>
`ur0:tai/kuio.skprx`
- Add lines:<br/>
`*PCSG00456`<br/>
`uX0:data/OoE-Plugin.suprx`
- Copy bin file `translated.bin` to `ux0:data/OoE` (if folder does not exist, create it.)
- Turn off the console and turn it back on to reload taiHEN's `config.txt` from a clean state.

## How to build:
```
git clone https://github.com/Rinnegatamante/kuio
cd kuio
mkdir build && cd build
cmake ..
make install

mkdir build && cd build
cmake ..
make
```

## Thanks to:
><b>xyz</b> - For helping with the basics of C.<br/>

><b>Rinnegatamante</b> - For kuio and helping with the basics of C.<br/>

><b>Davee</b><br/>
