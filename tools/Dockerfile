FROM ubuntu:xenial

ENV  GNARGSCOMMON 'rtc_include_tests=false rtc_enable_protobuf=false use_custom_libcxx=false use_ozone=true rtc_include_pulse_audio=false' 

# armv7

ENV GYP_GENERATOR_OUTPUT rpi-armv7  
ENV GNARGS 'is_debug=false rtc_use_h264=true ffmpeg_branding="Chrome" is_clang=false target_cpu="arm" treat_warnings_as_errors=false' 
ENV CROSS arm-linux-gnueabihf- 
ENV SYSROOT /webrtc/src/build/linux/debian_stretch_arm-sysroot
ENV GYP_DEFINES "target_arch=arm"

RUN apt-get update
RUN apt-get update && apt-get install -y --no-install-recommends git g++ autoconf automake libtool xz-utils libasound-dev ca-certificates python


# # get toolchain
# - git clone --depth 1 https://chromium.googlesource.com/chromium/tools/depot_tools.git && export PATH=$PATH:$(pwd)/depot_tools
RUN git clone --depth 1 https://chromium.googlesource.com/chromium/tools/depot_tools.git 
ENV PATH $PATH:/depot_tools

# - if [ "$CROSS" == "arm-linux-gnueabihf-" ]; then git clone --depth 1 https://github.com/raspberrypi/tools.git rpi_tools && export PATH=$PATH:$(pwd)/rpi_tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin; fi

RUN git clone --depth 1 https://github.com/raspberrypi/tools.git rpi_tools
ENV PATH $PATH:/rpi_tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
RUN echo $PATH 







# # get WebRTC
# - mkdir webrtc
# - pushd webrtc
# - travis_wait 30 fetch --no-history --nohooks webrtc
# # patch webrtc to not download chromium-webrtc-resources
# - sed -i -e "s|'src/resources'],|'src/resources'],'condition':'rtc_include_tests==true',|" src/DEPS
# - travis_wait 30  ync
# - popd

#fixme: move up
#ENV SYSROOT /webrtc/src/build/linux/debian_stretch_arm-sysroot
RUN apt-get install -y curl wget bzip2 vim

RUN mkdir /webrtc && \
    cd /webrtc && \
    fetch --nohooks webrtc 

RUN cd /webrtc/src/ && git checkout branch-heads/62 
    #sed -i -e "s|'src/resources'],|'src/resources'],'condition':'rtc_include_tests==true',|" DEPS

RUN cd /webrtc && gclient sync -r src@branch-heads/62


# # # get, build and install live555 & alsa
# # - make WEBRTCROOT=./webrtc live555 alsa-lib

WORKDIR /build

COPY Makefile /build/Makefile

RUN apt-get install -y make
RUN make WEBRTCROOT=/webrtc live555 alsa-lib

RUN apt-get install -y vim 


# COPY . /build

# RUN cd /webrtc/src && git checkout -- DEPS && git checkout branch-heads/62
# #RUN cd /webrtc/src && git log 
# RUN cd /webrtc && sed -i -e "s|'src/resources'],|'src/resources'],'condition':'rtc_include_tests==true',|" src/DEPS
# RUN cd /webrtc && gclient sync

# RUN git clone https://github.com/unrelatedlabs/webrtc-clone /webrtc-clone && \
#     cd /webrtc-clone && git checkout 5d2bb36b95c2a89c4bdddb1ed613f9bcf8aa764e


# # build WebRTC
# - pushd webrtc
# - pushd src
# - gn gen ${GYP_GENERATOR_OUTPUT}/out/Release --args="${GNARGSCOMMON} ${GNARGS}"
# - ninja -C ${GYP_GENERATOR_OUTPUT}/out/Release jsoncpp rtc_json webrtc
# - popd
# - popd

#RUN cd /webrtc/src/ && git checkout 0f1c15d

#RUN cd /webrtc && gclient sync -r src@0f1c15d


#RUN cd /webrtc && gclient sync

#COPY patches/audio_mixer_impl.cc  /webrtc/src/modules/audio_mixer/audio_mixer_impl.cc

RUN cd /webrtc/src && \
    sed -i -e 's|"examples",||' BUILD.gn  && \
    gn gen ${GYP_GENERATOR_OUTPUT}/out/Release --args="${GNARGSCOMMON} ${GNARGS}" && \
    ninja -C ${GYP_GENERATOR_OUTPUT}/out/Release jsoncpp rtc_json webrtc 

#     cd .. && sed -i -e "s|'src/resources'],|'src/resources'],'condition':'rtc_include_tests==true',|" src/DEPS && \


# # build
# - make WEBRTCROOT=./webrtc all tgz
# RUN make WEBRTCROOT=/webrtc all tgz

# # clean up
# - rm -rf webrtc rpi_tools depot_tools
