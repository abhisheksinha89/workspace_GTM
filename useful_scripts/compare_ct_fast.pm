#!/usr/bin/perl 

use paul_specials;

@ARGV == 2 or die "

usage:
compare_ct.pl reference.ct subject.ct

prints counts of number:
1. number of base-pairs in both files                   (rcount,scount)
2. number of shared bps                                 (correct,TP)
3. number of bps in reference but not in 'subject'      (false_neg: compatable, conflicting, contradicting)
4. number of bps in 'subject' but not in the reference  (false_pos)

NOTES: 
Let this read vienna format also.
Add gaps if seq lengths are not equal.
Print augmented subject.vienna annotation:
\(\): TP
\{\}: compatable FP
\[\]: conflicting FP
\<\>: contradicting FP

See Also:
compare.pl by Xtina

";

my $ref_filename=shift;
my $filename=shift;

open(REF, "< $ref_filename") || die("Can't open file: $ref_filename.");
open(RNA, "< $filename") || die("Can't open file: $filename.");

#printf "opened files $ref_filename and $filename\n\n\n";

@ref_struct = read_struct_ct(*REF);
@struct = read_struct_ct(*RNA);

my $rlen = length($ref_struct[0]);
my $slen = length($struct[0]);
my $ref_seq = $ref_struct[0];
my $seq = $struct[0];

$ref_struct[0]=$rlen;
$struct[0]=$slen;

my $ref_dotb = table_to_bracket(\@ref_struct);
my $dotb = table_to_bracket(\@struct);

$dotb =~ s/\(/\{/g;
$dotb =~ s/\)/\}/g;

    $_ = $ref_seq;
    my $ref_nogaps = tr/\-//;
    $_ = $seq;
    my $nogaps = tr/\-//;


    if (($rlen-$ref_nogaps) != ($slen-$nogaps)){
	die "seq lengths aren't equal (reference = $rlen, prediction = $slen)!
$rlen-$ref_nogaps ne $slen-$nogaps
ref_nogaps = $ref_nogaps
nogaps     = $nogaps

>ref
$ref_seq
$ref_dotb
>str
$seq\n\n\n";
    }

#print ">ref1
#$ref_seq
#$ref_dotb
#>str1
#$seq
#$dotb\n\n\n";

#If different lengths, gap or delete as appropriate:
while ($rlen != $slen){
    
    for (my $i = 0; $i < length($ref_seq); $i++){
	if ( substr($ref_seq,$i,1) =~ '\-'){  
	    
	    if (substr($ref_dotb,$i,1)  =~ '\.' ){
		substr($ref_seq,$i,1) = "";
		substr($ref_dotb,$i,1) = "";
		$i--;
	    }
	    elsif ((substr($seq,$i,1) ne substr($ref_seq,$i,1)) && (substr($ref_dotb,$i,1)  ne '\.') ) {
		substr($seq,$i,0) = ".";
		substr($dotb,$i,0) = ".";
		
		substr($ref_seq,$i,1) = ".";
		
		
	    }
		}
    }
    
    
    for (my $i = 0; $i < length($seq); $i++){
	
	if ( substr($seq,$i,1) =~ '\-'){  
	    
	    if (substr($dotb,$i,1)  =~ '\.' ){
		substr($seq,$i,1) = "";
		substr($dotb,$i,1) = "";
		$i--;
	    }
	    elsif (substr($seq,$i,1) ne substr($ref_seq,$i,1) && (substr($dotb,$i,1)  ne '\.')) {
		substr($ref_seq,$i,0) = ".";
		substr($ref_dotb,$i,0) = ".";
		substr($seq,$i,1) = ".";
		
	    }
	}
	
    }
#print ">ref
#$ref_seq
#$ref_dotb
#>str
#$seq
#$dotb\n\n";
    @ref_struct = make_pair_table($ref_dotb); 
    @struct = make_pair_table($dotb);
    
    #Update lengths after gapping
    $rlen = length($ref_seq);
    $slen = length($seq);
    
}



#print ">ref
#$ref_seq
#$ref_dotb
#>str
#$seq\n";



my $rcount = 0;
my $scount = 0; 
my $true_pos = 0; 
my $true_neg = 0; 
my $false_neg = 0; 
my $false_pos = 0;
my $conflict = 0;
my $contradict = 0;
my $temp = 0;

for (my $i=1; $i<=$rlen; $i++){
    
    #printf "%6d %6d\n", $ref_struct[$i], $struct[$i];

    if ($ref_struct[$i]>0 && $ref_struct[$i]>$i){
	$rcount++;
	#print "$rcount: $i-$ref_struct[$i]\n";
    }
    
    if ($struct[$i]>0 && $struct[$i]>$i){
	$scount++;
    }

    if (($ref_struct[$i]==$struct[$i]) && $ref_struct[$i]>0 && $ref_struct[$i]>$i){
	#printf "%6d %6d\n", $ref_struct[$i], $struct[$i];
	$true_pos++;
	$temp = $struct[$i];
	substr($dotb,$i-1,1) = '(';
	substr($dotb,$temp-1,1) = ')';
    }  
}


$false_pos = $scount - $true_pos;
#$false_pos = $conflict + $contradict;
$false_neg = $rcount - $true_pos;


my $sensitivity = 0;
my $selectivity =0;
if ($rcount>0){
    $sensitivity = $true_pos/($false_neg + $true_pos); #$rcount;
}
if ($scount>0){
    $selectivity = $true_pos/($false_pos + $true_pos); #$scount;
}

my $approx_corr = ($sensitivity + $selectivity)/2;

#print ">ref
#$ref_seq
#$ref_dotb
#>str
#$seq\n";
#print "$dotb\n";

#printf "
#seq length =         %6d
#num of bps in ref =  %6d 
#num of bps in sub =  %6d
#Basepair distance =  %6d
#true positives =     %6d
#true negatives =     %6d
#false positive =     %6d 
#\t contradict = $contradict
#\t conflict   = $conflict 
#\t compatable = $compatable
#false negative =     %6d
#sensitivity =        %1.3f
#selectivity =        %1.3f
#Approximate correlation = %1.3f
#Correlation Coefficient = %1.3f 
#Matthews Corr. Coeff.   = %1.3f 

#\n\n", $rlen, $rcount, $scount, $false_pos+$false_neg+$compatable, $true_pos, $true_neg, $false_pos, $false_neg, $sensitivity, $selectivity, $approx_corr, $corr_coeff, $MCC;


printf "%d\t%d\t%d\t%2.1f\t%2.1f\t%2.1f\n", 
$rcount, $scount, $true_pos,  $sensitivity*100, $selectivity*100, $approx_corr*100;


sub read_struct_ct{

$fileptr = $_[0];
my $seq = "";

my $i=-1;
while ( <$fileptr> ){

    @F = split;

    #if ((/ = /) && ($#F!=5)) {
    #    next;
    #}
    
    if ($i>=0){
    
    $seq .= $F[1];
    $table[$i] = $F[4];
}
    $i++;

    #if ($F[4]==0) {$s .= "."; next}
    #$s .= "(" if ($F[0]<$F[4]);
    #$s .= ")" if ($F[0]>$F[4]);
}


  $seq  =~ tr/a-z/A-Z/;
#print "2: $seq\n\n";

return ($seq, @table);

}

sub ispair{
    my ($x, $y) = @_;
    
    if ( ($x eq 'A' && $y eq 'U')||($x eq 'U' && $y eq 'A') ) {
	
	return 1;
    }
    elsif ( ($x eq 'G' && $y eq 'C')||($x eq 'C' && $y eq 'G') ) {
	
	return 1;
    }
    elsif ( ($x eq 'G' && $y eq 'U')||($x eq 'U' && $y eq 'G') ) {
	
	return 1;
    }
    
    else {
	return 0;
    }
}

# End of file

