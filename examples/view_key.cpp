/*
 * SPDX-FileCopyrightText: 2025 Philip Abbet <philip.abbet@gmail.com>
 *
 * SPDX-FileContributor: Philip Abbet <philip.abbet@gmail.com>
 *
 * SPDX-License-Identifier: MIT
*/

#define KNM_SOUNDFONT_IMPLEMENTATION
#include <knm_soundfont.hpp>

#include <iostream>

using namespace knm::sf;


int main(int argc, char** argv)
{
    // Simple command-line parameters handling
    if (argc != 6)
    {
        std::cout << "Usage: view_key <filename> <bank> <preset> <key> <velocity>" << std::endl;
        std::cout << std::endl;
        std::cout << "Display the data extracted from the SoundFont file (v2.x) about a specific "
                  << "key+velocity in a given <bank:preset>" << std::endl;
        return 0;
    }

    uint16_t bank = uint16_t(atoi(argv[2]));
    uint16_t preset = uint16_t(atoi(argv[3]));
    uint16_t key = uint16_t(atoi(argv[4]));
    uint16_t velocity = uint16_t(atoi(argv[5]));

    // Load the SoundFont file
    SoundFont soundfont;

    if (!soundfont.load(argv[1]))
    {
        std::cerr << "Failed to load SoundFont file: " << argv[1] << std::endl;
        return 1;
    }

    // Retrieve the data about the key
    key_info_t info;
    if (!soundfont.getKeyInfo(bank, preset, key, velocity, info))
    {
        std::cerr << "Key not found in the SoundFont file" << std::endl;
        return 1;
    }

    // Display the data
    if (!info.stereo)
    {
        std::cout << "Sample (mono):" << std::endl;
        std::cout << *info.left.sample << std::endl;
        std::cout << "    Generators (" << info.left.generators.size() << ")" << std::endl;
        std::cout << info.left.generators << std::endl;
        std::cout << "    Modulators (" << info.left.modulators.size() << ")" << std::endl;
        std::cout << info.left.modulators << std::endl;
    }
    else
    {
        std::cout << "Left sample:" << std::endl;
        std::cout << *info.left.sample << std::endl;
        std::cout << "    Generators (" << info.left.generators.size() << ")" << std::endl;
        std::cout << info.left.generators << std::endl;
        std::cout << "    Modulators (" << info.left.modulators.size() << ")" << std::endl;
        std::cout << info.left.modulators << std::endl;
        std::cout << std::endl;

        std::cout << "Right sample:" << std::endl;
        std::cout << *info.right.sample << std::endl;
        std::cout << "    Generators (" << info.right.generators.size() << ")" << std::endl;
        std::cout << info.right.generators << std::endl;
        std::cout << "    Modulators (" << info.right.modulators.size() << ")" << std::endl;
        std::cout << info.right.modulators << std::endl;
    }

    return 0;
}
