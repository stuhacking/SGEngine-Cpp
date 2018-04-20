#! /usr/bin/env perl
# Download SGEngine Dependencies.
require 5;
use strict;
use warnings;

# External dependencies (name will form the path so use filesystem friendly names.)
my @deps_ = (
    {name => 'soil',       version => 'master', url => 'https://github.com/stuhacking/soil.git'},
    {name => 'googletest', version => 'master', url => 'https://github.com/google/googletest.git'},
    {name => 'rapidjson',  version => 'master', url => 'https://github.com/miloyip/rapidjson.git'}
);

# Directory to place external dependencies.
my $ext_dir = "libs";

# Check target location for a dependency
# Dependency should be a hash of {name, url, version}.
sub check_and_download ($) {
    my ($dep) = @_;

    die "Unrecognized dependency structure."
        unless (defined $dep->{name} && defined $dep->{url} && defined $dep->{version});

    my $name = $dep->{name};
    my $url = $dep->{url};
    my $version = $dep->{version};

    my $path = "./$ext_dir/$name";

    if (-d "$path/.git") {
        print STDERR "$path already downloaded.\n";
        return;
    }

    if (-d "$path") {
        print STDERR "$path already exists but does not appear to be a git project.\n";
        return;
    }

    # Ok to download.
    `git clone --depth 1 -b $version $url $path`;
}

sub main () {
    for my $dep (@deps_) {
        check_and_download($dep);
    }
}

main();
exit 0;
