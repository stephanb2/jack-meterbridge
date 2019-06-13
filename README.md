# Jack Meterbridge

This is an attempt to maintain [JACK Meterbridge](http://plugin.org.uk/meterbridge/) from Steve Harris (2002)

Broadcast and Music Producers are advised to use [Ebumeter](http://kokkinizita.linuxaudio.org/linuxaudio/) by Fons Adriaensen, which offers loudness metering according to [EBU R-128](https://tech.ebu.ch/publications/r128). 

Check the [Awesome Broadcasting](https://github.com/ebu/awesome-broadcasting) list maintained by the EBU.

## Prerequisistes

Debian dependencies (aside from `build-essential`):
`libsdl-dev libsdl-image1.2-dev libjack-jackd2-dev`

TODO: `./configure` doesn't pick the dependency on `libsdl-image`

## Aims

* Bring PPM and VU ballistics in line with [Spifoski & Klar (2004) Levelling and Loudness. EBU technical Review - January 2004](https://tech.ebu.ch/docs/techreview/trev_297-spikofski_klar.pdf)
* Code cleanup
* Update Jack client ?

## License

This project is released under the GNU General Public License, version 3 (GPL-3.0)[https://opensource.org/licenses/GPL-3.0]
