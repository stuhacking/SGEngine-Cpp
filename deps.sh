#! /bin/sh
# Download 3rd party dependencies.

# Google Test/Mock lib
if [ ! -d './External/googletest' ] ; then
    git clone https://github.com/google/googletest.git ./External/googletest
fi

# JSON Parser
#if [ ! -d './External/rapidjson' ] ; then
#    git clone https://github.com/miloyip/rapidjson.git ./External/rapidjson
#fi
