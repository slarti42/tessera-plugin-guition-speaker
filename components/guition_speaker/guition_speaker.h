#pragma once
#include <cmath>
#include <string>

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/components/audio/audio.h"
#include "esphome/components/number/number.h"
#include "esphome/components/speaker/speaker.h"
#include "esphome/components/smart_display/plugin_api.h"
#include "esphome/components/smart_display/plugin_sound.h"

namespace esphome::guition_speaker {

// The volume as ears hear it, as Tessera's own boards run theirs (features/audio-player.yaml): 5 % is just audible
// beside the screen at LOW_DB, 100 % is the amplifier's full scale; 0 % is silent. ESPHome's software volume runs from
// MIN_DB at 0 to 0 dB at 1.
constexpr float LOW_DB = -45.0f, MIN_DB = -49.0f;

class GuitionSpeaker : public Component, public tessera::Plugin {
 public:
  float get_setup_priority() const override { return setup_priority::DATA; }
  void setup() override {
    volume_->add_on_state_callback([this](float) { this->apply_volume(); });
  }
  void loop() override { sounds_.loop(); }
  // Once the screen is up: the bus starts in silence and keeps running, so the amplifier's pop falls in the start.
  void on_ready() override {
    apply_volume();
    output_->set_audio_stream_info(audio::AudioStreamInfo(16, 1, 48000));
    output_->start();
  }
  void before_update() override { sounds_.stop(); }
  bool settings(tessera::SettingsPage &page) override;

  void set_output(speaker::Speaker *s) { output_ = s; }
  void set_speaker(speaker::Speaker *s) { sounds_.set_speaker(s); }
  void set_volume(number::Number *n) { volume_ = n; }
  void set_chime(tessera::Sound s) { chime_ = s; }

  // 0 to 100, as the setting holds it (50 until it has a value).
  int percent() const {
    return volume_ == nullptr || std::isnan(volume_->state) ? 50 : static_cast<int>(lroundf(volume_->state));
  }
  void apply_volume() {
    const int p = percent();
    const float db = LOW_DB * (1.0f - p / 100.0f);
    output_->set_volume(p <= 0 ? 0.0f : (db - MIN_DB) / -MIN_DB);
  }
  void test() { sounds_.play(chime_); }

 protected:
  speaker::Speaker *output_{};
  number::Number *volume_{};
  tessera::Sound chime_;
  tessera::SoundPlayer sounds_;
};

}  // namespace esphome::guition_speaker
