# Auto Glow

Auto Glow is a C++ application that uses Windows GDI API and low bitmap handling to automatically adjust the screen brightness when switching between light and dark-themed applications.

The app maintains the average luminance of the screen constant by adjusting the overall brightness. This provides a comfortable viewing experience and reduces eye strain.

The app is designed to work in the background and requires minimal user intervention. Once installed, it automatically adjusts the screen brightness as needed, without requiring the user to manually adjust the settings.

# Contributing
Auto Glow is open-source and contributions are welcome. If you encounter any issues or have suggestions for improvements, feel free to submit a pull request or open an issue.

> Don't forget to add the `-lgdi32` command while running the linker

# License
The app is licensed under the MIT License, which means that it is free to use, modify, and distribute.