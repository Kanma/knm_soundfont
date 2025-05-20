/*
 * SPDX-FileCopyrightText: 2025 Philip Abbet <philip.abbet@gmail.com>
 *
 * SPDX-FileContributor: Philip Abbet <philip.abbet@gmail.com>
 *
 * SPDX-License-Identifier: MIT
*/

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#define KNM_SOUNDFONT_IMPLEMENTATION
#include <knm_soundfont.hpp>

using namespace knm::sf;


#ifndef DATA_DIR
    #define DATA_DIR ""
#endif


void checkWaveData(const float* buffer, size_t size)
{
    // Those values are coming from the script that generated the audio file
    float ref[] = {
        -1.0, -0.98, -0.96, -0.94, -0.92, -0.9, -0.88, -0.86, -0.84, -0.8200000000000001, -0.8,
        -0.78, -0.76, -0.74, -0.72, -0.7, -0.6799999999999999, -0.6599999999999999, -0.64, -0.62,
        -0.6, -0.5800000000000001, -0.56, -0.54, -0.52, -0.5, -0.48, -0.45999999999999996,
        -0.43999999999999995, -0.42000000000000004, -0.4, -0.38, -0.36, -0.33999999999999997,
        -0.31999999999999995, -0.30000000000000004, -0.28, -0.26, -0.24, -0.21999999999999997,
        -0.19999999999999996, -0.18000000000000005, -0.16000000000000003, -0.14, -0.12,
        -0.09999999999999998, -0.07999999999999996, -0.06000000000000005, -0.040000000000000036,
        -0.020000000000000018, 0.0, 0.020000000000000018, 0.040000000000000036, 0.06000000000000005,
        0.08000000000000007, 0.10000000000000009, 0.1200000000000001, 0.1399999999999999,
        0.15999999999999992, 0.17999999999999994, 0.19999999999999996, 0.21999999999999997,
        0.24, 0.26, 0.28, 0.30000000000000004, 0.32000000000000006, 0.3400000000000001,
        0.3600000000000001, 0.3799999999999999, 0.3999999999999999, 0.41999999999999993,
        0.43999999999999995, 0.45999999999999996, 0.48, 0.5, 0.52, 0.54, 0.56, 0.5800000000000001,
        0.6000000000000001, 0.6200000000000001, 0.6399999999999999, 0.6599999999999999,
        0.6799999999999999, 0.7, 0.72, 0.74, 0.76, 0.78, 0.8, 0.8200000000000001,
        0.8400000000000001, 0.8600000000000001, 0.8799999999999999, 0.8999999999999999,
        0.9199999999999999, 0.94, 0.96, 0.98, 1.0
    };

    for (int i = 0; i < size; ++i)
        REQUIRE(buffer[i] == Approx(ref[i]).margin(0.005));

    for (int i = size; i < size + 46; ++i)
        REQUIRE(buffer[i] == Approx(0.0f));
}


void checkSamples(SoundFont& soundfont)
{
    REQUIRE(soundfont.nbSamples() == 3);

    auto samples = soundfont.getSamples();

    REQUIRE(samples[0].name == "440L");
    REQUIRE(samples[0].start == 0);
    REQUIRE(samples[0].end == 101);
    REQUIRE(samples[0].loop_start == 0);
    REQUIRE(samples[0].loop_end == 100);
    REQUIRE(samples[0].sample_rate == 44100);
    REQUIRE(samples[0].original_pitch == 69);
    REQUIRE(samples[0].pitch_correction == 0);
    REQUIRE(samples[0].sample_type == SAMPLE_TYPE_LEFT);
    REQUIRE(samples[0].sample_link == 1);

    checkWaveData(soundfont.getBuffer() + samples[0].start, samples[0].end - samples[0].start);

    REQUIRE(samples[1].name == "440R");
    REQUIRE(samples[1].start == 147);
    REQUIRE(samples[1].end == 248);
    REQUIRE(samples[1].loop_start == 147);
    REQUIRE(samples[1].loop_end == 247);
    REQUIRE(samples[1].sample_rate == 44100);
    REQUIRE(samples[1].original_pitch == 69);
    REQUIRE(samples[1].pitch_correction == 0);
    REQUIRE(samples[1].sample_type == SAMPLE_TYPE_RIGHT);
    REQUIRE(samples[1].sample_link == 0);

    checkWaveData(soundfont.getBuffer() + samples[1].start, samples[1].end - samples[1].start);

    REQUIRE(samples[2].name == "440M");
    REQUIRE(samples[2].start == 294);
    REQUIRE(samples[2].end == 395);
    REQUIRE(samples[2].loop_start == 294);
    REQUIRE(samples[2].loop_end == 394);
    REQUIRE(samples[2].sample_rate == 44100);
    REQUIRE(samples[2].original_pitch == 69);
    REQUIRE(samples[2].pitch_correction == 0);
    REQUIRE(samples[2].sample_type == SAMPLE_TYPE_MONO);

   checkWaveData(soundfont.getBuffer() + samples[2].start, samples[2].end - samples[2].start);
}


void checkPresets(SoundFont& soundfont)
{
    REQUIRE(soundfont.nbPresets() == 2);

    auto presets = soundfont.getPresets();

    REQUIRE(presets.find(preset_id_t({0, 0})) != presets.end());
    REQUIRE(presets.find(preset_id_t({0, 1})) != presets.end());

    auto preset = soundfont.getPreset(0, 0);
    REQUIRE(preset->name == "Stereo");
    REQUIRE(preset->zones.size() == 1);

    auto& zone = preset->zones[0];

    REQUIRE(zone.keys_range.lo == 0);
    REQUIRE(zone.keys_range.hi == 127);
    REQUIRE(zone.velocities_range.lo == 0);
    REQUIRE(zone.velocities_range.hi == 127);
    REQUIRE(zone.generators.size() == 1);
    REQUIRE(zone.modulators.size() == 0);

    REQUIRE(zone.generators.find(GEN_TYPE_INSTRUMENT) != zone.generators.end());
    REQUIRE(zone.generators.at(GEN_TYPE_INSTRUMENT).uvalue == 0);

    preset = soundfont.getPreset(0, 1);
    REQUIRE(preset->name == "Mono");
    REQUIRE(preset->zones.size() == 1);

    auto& zone2 = preset->zones[0];

    REQUIRE(zone2.keys_range.lo == 0);
    REQUIRE(zone2.keys_range.hi == 127);
    REQUIRE(zone2.velocities_range.lo == 0);
    REQUIRE(zone2.velocities_range.hi == 127);
    REQUIRE(zone2.generators.size() == 1);
    REQUIRE(zone2.modulators.size() == 0);

    REQUIRE(zone2.generators.find(GEN_TYPE_INSTRUMENT) != zone2.generators.end());
    REQUIRE(zone2.generators.at(GEN_TYPE_INSTRUMENT).uvalue == 1);
}


void checkDefaultGenerators(const generator_map_t& generators)
{
    REQUIRE(generators.at(GEN_TYPE_INITIAL_FILTER_CUTOFF_FREQUENCY).uvalue == 13500);
    REQUIRE(generators.at(GEN_TYPE_DELAY_MODULATION_LFO).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_DELAY_VIBRATO_LFO).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_DELAY_MODULATION_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_ATTACK_MODULATION_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_HOLD_MODULATION_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_DECAY_MODULATION_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_RELEASE_MODULATION_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_DELAY_VOLUME_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_ATTACK_VOLUME_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_HOLD_VOLUME_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_DECAY_VOLUME_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_RELEASE_VOLUME_ENVELOPE).ivalue == -12000);
    REQUIRE(generators.at(GEN_TYPE_KEY_NUMBER).ivalue == -1);
    REQUIRE(generators.at(GEN_TYPE_VELOCITY).ivalue == -1);
    REQUIRE(generators.at(GEN_TYPE_SCALE_TUNING).uvalue == 100);
    REQUIRE(generators.at(GEN_TYPE_OVERRIDING_ROOT_KEY).ivalue == -1);
}


void checkInstruments(SoundFont& soundfont)
{
    REQUIRE(soundfont.nbInstruments() == 2);

    auto instruments = soundfont.getInstruments();

    REQUIRE(instruments[0].name == "440 Stereo");
    REQUIRE(instruments[0].zones.size() == 2);

    auto zone = &instruments[0].zones[0];

    REQUIRE(zone->keys_range.lo == 0);
    REQUIRE(zone->keys_range.hi == 127);
    REQUIRE(zone->velocities_range.lo == 0);
    REQUIRE(zone->velocities_range.hi == 127);
    REQUIRE(zone->generators.size() == 20);
    REQUIRE(zone->modulators.size() == 10);

    REQUIRE(zone->generators.find(GEN_TYPE_SAMPLE_ID) != zone->generators.end());
    REQUIRE(zone->generators.at(GEN_TYPE_SAMPLE_ID).uvalue == 0);

    checkDefaultGenerators(zone->generators);

    zone = &instruments[0].zones[1];

    REQUIRE(zone->keys_range.lo == 0);
    REQUIRE(zone->keys_range.hi == 127);
    REQUIRE(zone->velocities_range.lo == 0);
    REQUIRE(zone->velocities_range.hi == 127);
    REQUIRE(zone->generators.size() == 20);
    REQUIRE(zone->modulators.size() == 10);

    REQUIRE(zone->generators.find(GEN_TYPE_SAMPLE_ID) != zone->generators.end());
    REQUIRE(zone->generators.at(GEN_TYPE_SAMPLE_ID).uvalue == 1);

    checkDefaultGenerators(zone->generators);

    REQUIRE(instruments[1].name == "440 Mono");
    REQUIRE(instruments[1].zones.size() == 1);

    zone = &instruments[1].zones[0];

    REQUIRE(zone->keys_range.lo == 0);
    REQUIRE(zone->keys_range.hi == 127);
    REQUIRE(zone->velocities_range.lo == 0);
    REQUIRE(zone->velocities_range.hi == 127);
    REQUIRE(zone->generators.size() == 20);
    REQUIRE(zone->modulators.size() == 10);

    REQUIRE(zone->generators.find(GEN_TYPE_SAMPLE_ID) != zone->generators.end());
    REQUIRE(zone->generators.at(GEN_TYPE_SAMPLE_ID).uvalue == 2);

    checkDefaultGenerators(zone->generators);
}


void check16bits(SoundFont& soundfont)
{
    auto information = soundfont.getInformation();
    REQUIRE(information.name == "knm::soundfont test data (16bits)");
    REQUIRE(information.major_version == 2);
    REQUIRE(information.minor_version == 1);
    REQUIRE(information.engineers == "Kanma");
    REQUIRE(information.target_engine == "EMU8000");
    REQUIRE(information.creation_tool == "Polyphone");

    checkSamples(soundfont);
    checkPresets(soundfont);
    checkInstruments(soundfont);
}


void check24bits(SoundFont& soundfont)
{
    auto information = soundfont.getInformation();
    REQUIRE(information.name == "knm::soundfont test data (24bits)");
    REQUIRE(information.major_version == 2);
    REQUIRE(information.minor_version == 4);
    REQUIRE(information.engineers == "Kanma");
    REQUIRE(information.target_engine == "EMU8000");
    REQUIRE(information.creation_tool == "Polyphone");

    checkSamples(soundfont);
    checkPresets(soundfont);
    checkInstruments(soundfont);
}


TEST_CASE("Load 16-bits SoundFont file")
{
    SoundFont soundfont;

    REQUIRE(soundfont.load(DATA_DIR "440_16bits.sf2"));

    check16bits(soundfont);
}


TEST_CASE("Load 24-bits SoundFont file")
{
    SoundFont soundfont;

    REQUIRE(soundfont.load(DATA_DIR "440_24bits.sf2"));

    check24bits(soundfont);
}


TEST_CASE("Load 16-bits SoundFont file from memory")
{
    std::ifstream stream(DATA_DIR "440_16bits.sf2", std::ios::binary);
    stream.seekg(0, std::ios::end);
    size_t size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    char* buffer = new char[size];
    stream.read(buffer, size);

    SoundFont soundfont;

    REQUIRE(soundfont.load(buffer, size));

    delete[] buffer;

    check16bits(soundfont);
}


TEST_CASE("Load 24-bits SoundFont file from memory")
{
    std::ifstream stream(DATA_DIR "440_24bits.sf2", std::ios::binary);
    stream.seekg(0, std::ios::end);
    size_t size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    char* buffer = new char[size];
    stream.read(buffer, size);

    SoundFont soundfont;

    REQUIRE(soundfont.load(buffer, size));

    delete[] buffer;

    check24bits(soundfont);
}


TEST_CASE("Retrieve stereo key info")
{
    SoundFont soundfont;

    REQUIRE(soundfont.load(DATA_DIR "440_16bits.sf2"));

    key_info_t key_info;
    REQUIRE(soundfont.getKeyInfo(0, 0, 69, 100, key_info));

    REQUIRE(key_info.stereo);

    REQUIRE(key_info.left.sample->name == "440L");
    REQUIRE(key_info.left.generators.size() == 20);
    REQUIRE(key_info.left.modulators.size() == 10);

    REQUIRE(key_info.right.sample->name == "440R");
    REQUIRE(key_info.right.generators.size() == 20);
    REQUIRE(key_info.right.modulators.size() == 10);
}


TEST_CASE("Retrieve mono key info")
{
    SoundFont soundfont;

    REQUIRE(soundfont.load(DATA_DIR "440_16bits.sf2"));

    key_info_t key_info;
    REQUIRE(soundfont.getKeyInfo(0, 1, 69, 100, key_info));

    REQUIRE(!key_info.stereo);

    REQUIRE(key_info.left.sample->name == "440M");
    REQUIRE(key_info.left.generators.size() == 20);
    REQUIRE(key_info.left.modulators.size() == 10);

    REQUIRE(!key_info.right.sample);
    REQUIRE(key_info.right.generators.size() == 0);
    REQUIRE(key_info.right.modulators.size() == 0);
}


int main(int argc, char** argv)
{
    // Executes the tests
    int result = Catch::Session().run(argc, argv);

    return result;
}
