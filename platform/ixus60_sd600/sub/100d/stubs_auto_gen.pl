

while(<STDIN>) {

  if ( / B(L?) \s+ SUB_([\da-fA-F]+) /ix ) {
     
     next if ( $H{$2} );
     
     $H{$2} = 1;
     print "STUB($2)\n";
  }

}