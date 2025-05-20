Usage
=====

1. Copy the ``knm_soundfont.hpp`` file in a convenient place for your project

2. In *one* C++ file, add the following code to create the implementation:

.. code:: cpp

    #define KNM_SOUNDFONT_IMPLEMENTATION
    #include <knm_soundfont.hpp>

In other files, just use ``#include <knm_soundfont.hpp>``


Here is an example using the library to retrieve the data about key 60 (C4)
at velocity 20 in bank 0, preset 0:

.. code:: cpp

    #define KNM_SOUNDFONT_IMPLEMENTATION
    #include <knm_soundfont.hpp>

    #include <iostream>

    using namespace knm::sf;

    int main(int argc, char** argv)
    {
        uint16_t bank = 0;
        uint16_t preset = 0;
        uint16_t key = 60;
        uint16_t velocity = 20;

        // Load the SoundFont file
        SoundFont soundfont;

        if (!soundfont.load("/path/to/sounfont/file.sf2"))
        {
            std::cerr << "Failed to load SoundFont file" << std::endl;
            return 1;
        }

        // Retrieve the data about the key
        key_info_t info;
        if (!soundfont.getKeyInfo(bank, preset, key, velocity, info))
        {
            std::cerr << "Key not found in the SoundFont file" << std::endl;
            return 1;
        }

        // Do something with 'info'

        return 0;
    }
