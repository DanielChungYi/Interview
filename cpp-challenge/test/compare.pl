#!/usr/bin/perl

require "./output_data.pl";

for my $key (keys %data_source_hash)
{
    print $key."\n";
    print $data_source_hash{$key}."\n";
}
print "\n";

my $filename = 'log.txt';

open(FH, '<', $filename) or die $!;

while(<FH>){
    my ($key, $times) = ( $_ =~ /Enter a word for lookup:SUCCESS: '(\w+)' was present (\d+) times in the initial word list/);
    if ($key == "" | $times == "") { last; }
    if ($data_source_hash{$key} != $times) {
        print STDERR "Error matching in $key\n";
    }
    else {
        print "Matching $key with $time\n";
    }
}


close(FH);

print "====================\n";
print "test success\n";
