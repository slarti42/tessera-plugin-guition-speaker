"""Guition speaker: the board's amplifier as the screen's speaker (the feature `speaker`, ts_speaker).

plugin.yaml makes the speaker itself, with ESPHome's own i2s_audio and resampler platforms. This component starts the
bus in silence once the screen is up, turns the volume of 0 to 100 % into the amplifier's software volume, and plays a
chime for a test (sounds/chime.wav, built in by smart_display.sound()). register_plugin() takes the id, version and the
screen's texts from the manifest and translations/ beside this folder.
"""
from pathlib import Path

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number, smart_display, speaker
from esphome.const import CONF_ID

DEPENDENCIES = ["smart_display", "speaker", "number"]

CONF_OUTPUT = "output"
CONF_SPEAKER = "speaker"
CONF_VOLUME = "volume"
CHIME = Path(__file__).parent / "sounds" / "chime.wav"

guition_speaker_ns = cg.esphome_ns.namespace("guition_speaker")
GuitionSpeaker = guition_speaker_ns.class_("GuitionSpeaker", cg.Component)


def check_sound(config):
    smart_display.read_sound(CHIME)
    return config


CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(GuitionSpeaker),
            cv.Required(CONF_OUTPUT): cv.use_id(speaker.Speaker),
            cv.Required(CONF_SPEAKER): cv.use_id(speaker.Speaker),
            cv.Required(CONF_VOLUME): cv.use_id(number.Number),
        }
    ).extend(cv.COMPONENT_SCHEMA),
    check_sound,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await smart_display.register_plugin(var, __file__)
    cg.add(var.set_output(await cg.get_variable(config[CONF_OUTPUT])))
    cg.add(var.set_speaker(await cg.get_variable(config[CONF_SPEAKER])))
    cg.add(var.set_volume(await cg.get_variable(config[CONF_VOLUME])))
    cg.add(var.set_chime(smart_display.sound(config[CONF_ID], "chime", CHIME)))
