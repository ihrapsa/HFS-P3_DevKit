`STLinkReflash_for_STM32.exe` - is for STM32 based ST-LinkV2 devices  

`STLinkReflash_for_clones.exe` - is for chinese clones (mine was a Geehy APM32 ST-Link V2)

I modified the stock STLinkReflash.exe binary based on these instructions:
https://gist.github.com/jamesy0ung/919ef51fea4631e9dfe0bd26dc85c8f0

1. Download STLinkReflash (Version 190812 tested)
2. Modify the following offsets in `STLinkReflash.exe`
  ```
  2566 3C > 38
  2567 40 > C0
  26B2 3C > 38
  26B3 4A > C0
  ```
3. Run `STLinkReflash.exe` and accept, selecting option 1.
4. Fun and profit!