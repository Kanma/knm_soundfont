# knm::soundfont

[![Documentation Status](https://readthedocs.org/projects/knmsoundfont/badge/?version=latest)](https://knmsoundfont.readthedocs.io/en/latest/)

A C++ library to parse SoundFont (2.x) files.

**knm::soundfont** is a single-file, header-only C++ library, without any dependency.

To know how to use the information in a SoundFont file, please refer to the
[SoundFont v2.01 specification](https://www.synthfont.com/SFSPEC21.PDF).

**Notes:**

1. No synthesis is performed, the objective is only to parse a SoundFont file
and provide a simple interface to retrieve informations from it (to maybe
implement a synthetizer).

2. Some sanity checks aren't implemented yet (there are numerous conditions
that should lead to the SoundFont file to be declared invalid, but for now
it is assumed that the file is valid).

Everything is defined in the `knm::sf` namespace (`knm` for my username, *Kanma*,
and `sf` for *SoundFont*).


## Usage

1. Copy the ```knm_soundfont.hpp```file in a convenient place for your project

2. In *one* C++ file, add the following code to create the implementation:

```cpp
    #define KNM_SOUNDFONT_IMPLEMENTATION
    #include <knm_soundfont.hpp>
```

In other files, just use ```#include <knm_soundfont.hpp>```


Here is an example using the library to retrieve the data about key 60 (C4)
at velocity 20 in bank 0, preset 0:

```cpp
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
```


## License

knm::soundfont is made available under the MIT License.

Copyright (c) 2025 Philip Abbet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
