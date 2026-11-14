# Guition speaker

> Needs a small change on the board first: out of the box the speaker output is not connected (below, "Before you
> add it"). Not together with Guition relays: both use the same three pins.

The Guition 4-inch screen (ESP32-S3-4848S040) has an amplifier for a small loudspeaker on its board, but Tessera does
not use it. This plugin makes it the screen's speaker, so plugins that play sounds work on this screen too: the
**Alarm clock**, **Timers** and **Tap sound**.

## Before you add it

- **The board.** The amplifier (an NS4168) shares its three pins with the relay connector (L1, L2, L3). On most boards
  small 0-ohm resistors beside the amplifier send those pins to the relay connector, not to the amplifier. Check your
  board: the speaker output needs those resistors moved or the pads bridged, as described in the Home Assistant
  community thread on this screen. Without it the plugin builds and runs, and you hear nothing.
- **A loudspeaker** on the board's speaker connector: a small one of 4 or 8 ohms.
- **No relays.** A screen with this plugin cannot have Guition relays: both use GPIO1, GPIO2 and GPIO40, and the build
  refuses a pin used twice.

## Set up

1. In Tessera, open Plugins, choose **Add with a link** and paste
   `https://github.com/woldhek/tessera-plugin-guition-speaker`.
2. Tick the Guition 4-inch screen and apply. The screen builds once.
3. Open the plugin's details on the screen's Plugins tab, **Settings**, and press **Run** beside **Test the speaker**:
   you hear a short chime. Set **Speaker volume** to taste.
4. Add a plugin that plays sounds, such as **Alarm clock**: its sound part is now offered on this screen.

## Settings

The same two are on the screen's own settings page (hold the top bar, Settings, Plugins, Guition speaker) and are
entities of the screen in Home Assistant.

- **Speaker volume**: 0 to 100 %, 50 at first. It runs evenly in decibels as ears hear it; 0 is silent. Every sound on
  this speaker follows it.
- **Test the speaker**: plays a short chime.

## Good to know

- The pins, as the board's schematic and the Home Assistant community found them: BCLK on GPIO1, LRCLK on GPIO2 and
  the data on GPIO40.
- The plugin brings the feature `speaker` (`ts_speaker`) for other plugins. It brings no media player: Home
  Assistant's announcements and music do not play on this screen.
- The amplifier has no volume of its own, so the sound is turned down in software; at 100 % it plays at full scale.
- The bus runs in silence from the start, as on Tessera's own boards with a speaker, so the amplifier's pop when it
  starts comes once, at the start, and not before every sound.
- Checked with the plugins repository's `check.py` and a compile against the headers of Tessera's release and dev
  branch. Not yet run on a real screen.
