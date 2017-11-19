# foo_mediacontrol
Adds the ability for foobar2000 to interact with the Windows 10 media control overlay.

### Screenshot
---------
![Screenshot](https://i.imgur.com/nDhw6XN.png)

### Installing
---------
Open your `Components` screen in foobar2000 and drop `Release.zip` on it.

### Compilation
---------
#### Windows:

Compilation requires Windows 10 SDK version 10.0.10240.0 or higher.
 - Open the provided solution file (foobar2000/foo_mediacontrol/foo_mediacontrol.sln) in Visual Studio.
 - Change the target to "Release" and platform to "x86".
 - Build the solution (Default: Ctrl+Shift+B).
 - Move the resulting foo_discord.dll as well as discord-rpc to your foobar2000 components folder.
 - (Re)Start foobar2000.

### License
----
[BSD-2-Clause](https://github.com/NaamloosDT/foo_discord/blob/master/LICENSE)
