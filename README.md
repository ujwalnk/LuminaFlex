# ![](icon.ico) LuminaFlex

LuminaFlex is a C++ application that uses Windows GDI API and low-level bitmap handling to automatically adjust the screen brightness when switching between light and dark-themed applications.

The app maintains the average luminance of the screen constant by adjusting the overall brightness. This provides a comfortable viewing experience and reduces eye strain.

The app is designed to work in the background and requires minimal user intervention. Once installed, it automatically adjusts the screen brightness as needed, without requiring the user to manually adjust the settings.

# Quick Start
- Unzip the downloadable, into your preferred destination.
- Run the `LuminaFlex.exe` file, let it work until it displays a message on the screen
- Close and open the same file
- Modify the `.config` file when necessary

# Config file
```txt
<deltaValue> - maximum deviation from the user set value 
<interval> - time interval for scanning the display & changing the brightness
<maxLuminance> - Maximum luminance of the display
<minLuminance> - Minimum luminance of the display
<gammaRamp> - If the display doesn't support brightness control, use this, with caution it can cause damage to the display
```

# Gammaramp
- The gamma ramp will be reset on application exit
- It can also be reset by running using the `resetGamma.bat` file on the command prompt

# Contributing
LuminaFlex is open-source and contributions are welcome. If you encounter any issues or have suggestions for improvements, feel free to submit a pull request or open an issue.

> Don't forget to add the `-lgdi32` command while running the linker

# License
The app is licensed under the MIT License.
