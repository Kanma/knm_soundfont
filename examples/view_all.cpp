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
#include <cstring>

using namespace knm::sf;


int main(int argc, char** argv)
{
    // Simple command-line parameters handling
    if ((argc != 2) || (strncmp(argv[1], "--help", 6) == 0) || (strncmp(argv[1], "-h", 2) == 0))
    {
        std::cout << "Usage: view_all <filename>" << std::endl;
        std::cout << std::endl;
        std::cout << "Display ALL the data extracted from the SoundFont file (v2.x)" << std::endl;
        return 0;
    }

    // Load the SoundFont file
    SoundFont soundfont;

    if (!soundfont.load(argv[1]))
    {
        std::cerr << "Failed to load SoundFont file: " << argv[1] << std::endl;
        return 1;
    }

    // Display all the data
    std::cout << soundfont << std::endl;

    return 0;
}
