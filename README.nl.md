# Guition-speaker

> Vraagt eerst een kleine aanpassing op het bord: standaard is de speakeruitgang niet aangesloten (hieronder, "Voordat
> je hem toevoegt"). Niet samen met Guition relays: beide gebruiken dezelfde drie pinnen.

Het Guition 4-inch-scherm (ESP32-S3-4848S040) heeft een versterker voor een kleine luidspreker op het bord, maar
Tessera gebruikt hem niet. Deze plugin maakt er de speaker van het scherm van, zodat plugins met geluid ook op dit
scherm werken: de **Wekker** (Alarm clock), **Timers** en **Tap sound**.

## Voordat je hem toevoegt

- **Het bord.** De versterker (een NS4168) deelt zijn drie pinnen met de relaisconnector (L1, L2, L3). Op de meeste
  borden sturen kleine weerstandjes van 0 ohm naast de versterker die pinnen naar de relaisconnector, niet naar de
  versterker. Kijk op je eigen bord: voor de speakeruitgang moeten die weerstandjes verplaatst of de pads doorverbonden
  worden, zoals beschreven in de draad over dit scherm op de Home Assistant-community. Zonder dat bouwt en draait de
  plugin, en hoor je niets.
- **Een luidspreker** op de speakerconnector van het bord: een kleine van 4 of 8 ohm.
- **Geen relais.** Een scherm met deze plugin kan geen Guition relays hebben: beide gebruiken GPIO1, GPIO2 en GPIO40,
  en de build weigert een pin die twee keer gebruikt wordt.

## Instellen

1. Open in Tessera Plugins, kies **Add with a link** en plak
   `https://github.com/woldhek/tessera-plugin-guition-speaker`.
2. Vink het Guition 4-inch-scherm aan en pas toe. Het scherm bouwt één keer.
3. Open de details van de plugin op het tabblad Plugins van het scherm, **Settings**, en druk op **Run** naast
   **Speaker testen**: je hoort een kort belletje. Zet **Speakervolume** naar smaak.
4. Voeg een plugin met geluid toe, zoals de **Wekker**: zijn geluidsonderdeel wordt nu op dit scherm aangeboden.

## Instellingen

Dezelfde twee staan op de eigen instellingenpagina van het scherm (houd de bovenbalk vast, Settings, Plugins,
Guition-speaker) en zijn entiteiten van het scherm in Home Assistant.

- **Speakervolume**: 0 tot 100 %, eerst 50. Het loopt gelijkmatig in decibel, zoals oren het horen; 0 is stil. Elk
  geluid op deze speaker volgt het.
- **Speaker testen**: speelt een kort belletje.

## Goed om te weten

- De pinnen, zoals het schema van het bord en de Home Assistant-community ze vonden: BCLK op GPIO1, LRCLK op GPIO2 en
  de data op GPIO40.
- De plugin brengt de feature `speaker` (`ts_speaker`) voor andere plugins. Hij brengt geen mediaspeler: aankondigingen
  en muziek van Home Assistant spelen niet op dit scherm.
- De versterker heeft geen eigen volume, dus het geluid wordt in software zachter gezet; op 100 % speelt hij op vol
  bereik.
- De bus loopt vanaf de start in stilte, zoals op Tessera's eigen borden met een speaker, zodat de plop van de
  versterker bij het starten één keer komt, bij de start, en niet voor elk geluid.
- Gecontroleerd met `check.py` van de plugins-repository en een compile tegen de headers van Tessera's release en dev.
  Nog niet op een echt scherm gedraaid.
