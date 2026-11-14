#include "guition_speaker.h"

namespace esphome::guition_speaker {

// The plugin's page on the screen's settings (hold the top bar, Settings, Plugins): the volume and the chime, which work
// while Home Assistant is away too.
bool GuitionSpeaker::settings(tessera::SettingsPage &page) {
  page.icon = "\U000F057E";
  page.number(text("volume"), 0, 100, 5, "%", [this] { return percent(); }, [this](int v) {
    auto call = volume_->make_call();
    call.set_value(v);
    call.perform();
  });
  page.action(text("test"), "\U000F009E", [this] { test(); });
  return true;
}

}  // namespace esphome::guition_speaker
