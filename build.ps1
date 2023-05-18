#
# Building in win for win
#
# 1. Install Visual Studio Build Tools
#    Desktop Development with C++ is enough
# 2. Open x86 or x64 Native Tools Command Prompt for VS
#    Use start menu or visit install location
# 3. Change to the repo root dir
#    This is where this file build.ps1 resides
# 4. Run this power shell script
#    pwsh ./build.ps1
#

rm -Recurse bld
mkdir bld
cd bld

cl /O2 /Oy /LD ../src/*.c /link /OUT:phe.dll /EXPORT:calc_OT /EXPORT:test

cd ..
