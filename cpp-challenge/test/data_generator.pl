#!/usr/bin/perl
use warnings;
use strict;

use constant NUM_OF_INPUT => 1000;

# File handler (intput)
my $filename = "input_data.txt";
open(my $fh, '>', $filename) or die $!;
print $fh "go\n";;
print $fh "go\n";;

# Array with alphabet
my $str = "";
my @array = qw /a b c d e f g h i j k l m n o p q w s t u v w x y z 1 2 3 4 5 6 7 8 9 0/;

# Hash to check result
my %hash;

# Random generate string with alphabet
for (my $i=0; $i<int(NUM_OF_INPUT); $i++) {
    for (my $j=0; $j<int(rand(32)); $j++) {
        $str .= $array[rand @array];
    }
    print $fh $str."\n";
    $hash{$str}++;
    $str = "";
}

print $fh "end\n";

# Loop up
for my $key (keys %hash)
{
    print $fh $key."\n";
}
print $fh "\n";

close($fh);

# File handler (outtput)
$filename = "output_data.pl";
open($fh, '>', $filename) or die $!;
select($fh);
print<<EOF;
our %data_source_hash= ( 
EOF
for my $key (keys %hash)
{
    print $fh "'$key' => $hash{$key}, \n";
}
print<<EOF;
);
EOF
