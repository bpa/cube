#! /usr/local/bin/perl6

use v6;
grammar CubeFile {
    rule TOP {
        <descriptions> <solutions>
    }
    rule descriptions { ^^ Descriptions: \n <line>+ }
    rule solutions    { ^^ Solutions: \n <line>+ }
    rule description_line { ^^ (\w+) \, (\w) \, (\w+) \, (\w+) $$ }
    rule solution_line    { ^^ \w+ \, \w+ \, .* $$ }
    token comment { ^^ \# .* $$ }
    token line { ^^ .* $$ }
}

my $file = slurp "cfop.csv";
    say CubeFile.parse($file).perl;
#    for $csv.lines -> $line {
#        next if $line ~~ /^ <ws> \#/;
#        $line.chomp;
#        if $line ~~ /^ (\w+) :/ {
#            say $line;
#            #$parse = $parse_funcs{lc($1)} || sub { print "?\n" };
#            #next;
#        }
#        #$parse->($_);
#    }
#}
#else {
    #die "Can't open $file: $!\n";
#}

=begin END
#my $show = 0;

#my $review_phase, $review_group) = @*ARGS.uc;
#say $review_phase;
#say $reveiw_group;

grammar File {
    token TOP {
        <section>+
    }
    token 
    token comment 
}
#while ( my ( $phase, $groups ) = each %phase ) {
#    next if $review_phase && $phase ne $review_phase;
#    print "Phase: $phase\n" if $show;
#    while ( my ( $group, $solutions ) = each %$groups ) {
#        next if $review_group && $group ne $review_group;
#        if ($show) {
#            show_group($group, $solutions);
#            next;
#        }
#        foreach (@{$solutions->{'moves'}}) {
#            print "\n\n";
#            print $_->[0], "\n";
#            my $x        = <STDIN>;
#            my @solution = @{$_};
#            shift @solution;
#            print join( "\n", @solution ), "\n";
#        }
#    }
#}
#
#sub parse_solution {
#    my ( $phase, $group, @moves ) = split( /,/, $_[0] );
#    push @{ $phase{$phase}{$group}{'moves'} }, \@moves;
#}
#
#sub parse_description {
#    my ( $phase, $group, $view, @display) = split( /,/, $_[0] );
#    for (@display) {
#        tr/.X/▢■/;
#    }
#    push @{ $phase{$phase}{$group}{'display'} }, @display;
#    $phase{$phase}{$group}{'view'} = $view;
#}
#
#sub show_group {
#    my ( $group, $solutions ) = @_;
#    if ( $solutions->{'view'} ) {
#        printf " %2s ", $group;
#        for ( my $i=0; $i<3; $i++) {
#            print "    " if $i;
#            print join(" ", map(substr($_,$i*3,3),@{$solutions->{'display'}})), "\n"; 
#        }
#        print "\n";
#    }
#    else {
#        print "  $group\n";
#    }
#}
#
#}
