#! /usr/bin/env perl
# Download SGEngine Dependencies.
require 5;
use strict;
use warnings;

# External dependencies (key will be used in path.)
my %deps = (
    googletest => 'https://github.com/google/googletest.git',
    rapidjson => 'https://github.com/miloyip/rapidjson.git'
    );

# Directory to place external dependencies.
my $ext_dir = "External";

sub main () {
    for my $dep (keys %deps) {
        my $path = "./$ext_dir/$dep";
        my $url = $deps{$dep};

        if (! -d "$path/.git") {
            `git clone $url $path`;
        } else {
            print STDERR "$dep already downloaded.\n";
        }
    }
}

main();
exit 0;
