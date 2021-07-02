# Minecraft Bedrock Server Exposer (Windows 10+)
<img alt="Lines of code" src="https://img.shields.io/tokei/lines/github/hari01584/libWin10MinecraftTunnel?style=flat-square">
<img alt="GitHub Repo stars" src="https://img.shields.io/github/stars/hari01584/libWin10MinecraftTunnel?style=social">
<img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/hari01584/libWin10MinecraftTunnel?style=flat-square">

aka libWin10MinecraftTunnel (tho not necessarily a library but a simple script :D)
> Just a simple script to expose global minecraft servers to your lan tab, Basically it could allow non microsoft/xbox login play in minecraft if target offline server has *Online Mode* turned off (Or you can say server allows cracked/non authenticated clients)! Handy tool when you quickly wana expose your server and ask your friends to play and there's authenticity in you, Or if you want to create a GUI which acts as lobby to invite people and play with them! :D

This is Java Ported Library of [this repository](https://github.com/hari01584/libMcServerProxy) which was used to do the same thing but for Android Bedrock versions of minecraft. It works 

## Usage / How To
Umn download the latest running executable from [releases](https://github.com/hari01584/libWin10MinecraftTunnel/releases/latest) or you can alternatively build the script from source as well (See how_to_build.txt)

Execute the executable in this format:
> bedrockProxy.exe [Target Server IPv4 Address] [Target Server Port]

Where *Target Server IPv4 Address* referes to ipv4 server address, please note that *domain name like (play.cubicgames.com) will not work here and will give error on starting*, Its better you use webtools like [mcserverstatus](https://mcsrvstat.us/) to ping your target server and get its ipv4 equivalent address :)!

After executing it in the order if no error comes then open your Minecraft Bedrock and go to the LAN tab of your game, If nothing goes wrong(which hopefully will not go wrong) then you will see your target server in LAN tab, if you can't see then it might be possible that the server you are trying is wrong/incorrect or no minecraft server is hosted on the ip, Double check input parameters (especially port)!
##### AntiVirus False Positive
I don't know but you might get antivirus warnings using this module, not sure why but even my windows defender was flagging this as Severe Virus sometimes, and it was random (like different filename of executable or extension), Currently this build doesn't give any virus warnings but it might be possible that your antivirus might flag it as virus! So add this as in quarantine if it happens (it is safe anyways :))

## Bindings
As i was rushing to finish this, I could'nt prepare it as binding compatible or anything, So if you like to use this script in other languages (python, nodejs etc etc) then you are free to invoke the script with parameters, Or even better! Make your own bindings and do PRs to update this repo! :)

## License
GPLv3

    Copyright (C) 2021 Harishankar Kumar
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.


**Free Software, Hell Yeah!**
