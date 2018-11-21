#!python
import os

target = ARGUMENTS.get("target", "debug")
platform = ARGUMENTS.get("platform", "linux")
bits = ARGUMENTS.get("bits", 64)

final_lib_path = 'demo/bin/'

# This makes sure to keep the session environment variables on windows, 
# that way you can run scons in a vs 2017 prompt and it will find all the required tools
env = Environment()
if platform == "windows":
    env = Environment(ENV = os.environ)

def add_sources(sources, directory):
    for file in os.listdir(directory):
        if file.endswith('.cpp'):
            sources.append(directory + '/' + file)

if platform == "osx":
    env.Append(CCFLAGS = ['-g','-O3', '-arch', 'x86_64', '-std=c++14'])
    env.Append(LINKFLAGS = ['-arch', 'x86_64'])

    final_lib_path = final_lib_path + 'osx/'

elif platform == "linux":
    env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++14'])

    final_lib_path = final_lib_path + 'x11/'

elif platform == "windows":
    if target == "debug":
        env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '-MDd'])
    else:
        env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '-MD'])

    final_lib_path = final_lib_path + 'win' + str(bits) + '/'

env.Append(CPPPATH=['.', 'src/', "godot_headers/", 'godot-cpp/include/', 'godot-cpp/include/core/', '/usr/include/opencv2','/usr/local/include/aruco'])
env.Append(LIBPATH="godot-cpp/bin")
env.Append(LIBS=["godot-cpp" + "." + platform + "." + target + "." + str(bits)])
env.ParseConfig('pkg-config --libs aruco')

sources = []
add_sources(sources, "src")

library = env.SharedLibrary(target=final_lib_path + 'libgdexample', source=sources)
Default(library)
