knm::soundfont
==============

A C++ library to parse SoundFont (2.x) files.

**knm::soundfont** is a single-file, header-only C++ library, without any dependency.

To know how to use the information in a SoundFont file, please refer to the
SoundFont v2.01 specification (https://www.synthfont.com/SFSPEC21.PDF).

**Notes:**

1. No synthesis is performed, the objective is only to parse a SoundFont file
and provide a simple interface to retrieve informations from it (to maybe
implement a synthetizer).

2. Some sanity checks aren't implemented yet (there are numerous conditions
that should lead to the SoundFont file to be declared invalid, but for now
it is assumed that the file is valid).

Everything is defined in the ``knm::sf`` namespace (``knm`` for my username, *Kanma*,
and ``sf`` for *SoundFont*).


.. toctree::
   :maxdepth: 2
   :caption: Documentation
   
   usage
   license


.. toctree::
   :maxdepth: 2
   :caption: API
   
   api_soundfont
   api_keyinfo
   api_sampleinfo
   api_sample
   api_information
   api_generators
   api_modulators
