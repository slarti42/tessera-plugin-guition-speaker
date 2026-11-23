# Guition speaker


The Guition 3,5-inch screen (JC3248W535C) has an amplifier for a small loudspeaker on its board, but Tessera does
not use it. This plugin makes it the screen's speaker, so plugins that play sounds work on this screen too: the
**Alarm clock**, **Timers** and **Tap sound**.

## Before you add it

- **A loudspeaker** on the board's speaker connector: a small one of 4 or 8 ohms.


## Set up

1. In Tessera, open Plugins, choose **Add with a link** and paste
   `https://github.com/slarti42/tessera-plugin-guition-speaker`.
2. Tick the Guition 3.5-inch screen and apply. The screen builds once.
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
